# ########################### Author Info #####################
#       Name:   Arun Baby
#       Orgn:   Zapr Media Labs
#       Email:  arun.baby@zapr.in
#       Date:   04-02-2020
#       Desc:   Word parser for languages
#       git:    
# ########################### Author Info #####################

# ########################### Update History ##################
# v2: Direct script usage enabled, Config is updated using script
#     sh configure.sh should be run before using the code
# v3: Latin support added
# v4: English dictionary support
# v5: Added words for new release
# v6: IE rules + EngHndCommon phoneset + multi dict added
# ########################### Update History ##################

import os

# !/usr/bin/python
# -*- coding: utf-8 -*-
import sys
from pathlib import Path

from g2p_en import G2p

from py_unified_parser import Config, LangSupport, Utils, constants

from .IndicWord import IndicWord

# instance of CMU g2p
g2p = G2p()


class Word:
    """
    Wrapper class for all different languages
    """

    def __init__(self, langSpec=True, debug=False):
        """
        Load the CONFIG file
        create language objects for each of the languages using the config
        """
        self.basePath = str(Path(__file__).parent)
        self.tsylPath = os.path.join(self.basePath, "tsylb2-1.1")
        self.Config = Config.CONFIG
        self.debug = debug
        self.langObjects = {}
        self.globalDict = {}
        # create factory of obejcts
        for i in self.Config["Lang"]:
            if self.debug:
                print(i, self.Config["Lang"][i]["id"])
            if LangSupport.LANGUAGES[i] and self.Config["Lang"][i]["isIndic"]:
                self.langObjects[self.Config["Lang"][i]["id"]] = IndicWord(
                    langId=self.Config["Lang"][i]["scriptId"],
                    langSpec=langSpec,
                    debug=debug,
                    isSouth=self.Config["Lang"][i]["south"],
                    dictPath=self.Config["Lang"][i]["dictFile"],
                    rulesPath=os.path.join(
                        self.basePath, self.Config["Lang"][i]["rulesFile"]
                    ),
                    schwaChar=self.Config["Lang"][i]["schwaChar"],
                    basePath=self.basePath,
                )
            elif (
                LangSupport.LANGUAGES[i]
                and self.Config["Lang"][i]["dictFile"] != ""
                and not self.Config["Lang"][i]["isIndic"]
            ):
                for dictType in self.Config["Lang"][i]["dictFile"]:
                    if self.Config["Lang"][i]["id"] not in self.globalDict:
                        self.globalDict[self.Config["Lang"][i]["id"]] = {}
                    self.globalDict[self.Config["Lang"][i]["id"]][
                        dictType
                    ] = Utils.loadWordsDict(
                        dictLocation=os.path.join(
                            self.basePath, self.Config["Lang"][i]["dictFile"][dictType]
                        )
                    )
        # print(self.globalDict)

    def getLangId(self, word=""):
        """
        Use the unicode in the config to get the language ID
        """
        if self.debug:
            print("fn: getLangId\t", word)
        unicodeChar = ord(list(word)[0])
        if self.debug:
            print("unicode: ", unicodeChar)
        for lang in self.Config["Lang"]:
            if self.debug:
                print(
                    self.Config["Lang"][lang]["unicodeRange"][0],
                    self.Config["Lang"][lang]["unicodeRange"][1],
                )
            if (
                unicodeChar >= self.Config["Lang"][lang]["unicodeRange"][0]
                and unicodeChar <= self.Config["Lang"][lang]["unicodeRange"][1]
            ):
                if LangSupport.LANGUAGES[lang]:
                    return self.Config["Lang"][lang]["id"]
        # print("Unknown lang!!!")
        return -1

    def getPhones(
        self, word="", langId=-1, applyIErules=False, targetPhoneSet="CMU", isASR=False
    ):
        """
        Get the phoneme sequence using Indicword or g2p_en
        for g2p_en, convert to CLS afterwards
        args:
            word: the input word
            langID: Language ID of the word(optional)
            applyIErules: Custom rules for IE
            targetPhoneSetSet: Output phoneset
            isASR: For ASR applications only
        """
        if self.debug:
            print("fn: getPhones\t", word, langId)
        currLang = langId
        if langId == -1:
            currLang = self.getLangId(word)
            if currLang == -1:
                return "ERROR"  # only if not supported language
        if self.debug:
            print("Lang Id: ", currLang)
        parsedWord = ""
        # Handle english first
        if (
            currLang == self.Config["Lang"]["English"]["id"]
            or currLang == self.Config["Lang"]["Latin"]["id"]
        ):
            if (
                targetPhoneSet in self.globalDict[self.Config["Lang"]["English"]["id"]]
                and word.upper()
                in self.globalDict[self.Config["Lang"]["English"]["id"]][targetPhoneSet]
            ):
                # check in the default dictionary
                parsedWord = list(
                    self.globalDict[self.Config["Lang"]["English"]["id"]][
                        targetPhoneSet
                    ][word.upper()][0].split(" ")
                )
                if targetPhoneSet == "EngHndCommon":
                    # A mapping to ensure correctness
                    parsedWord = Utils.mapIE(parsedWord)
                    if isASR:
                        parsedWord = Utils.mapASR(parsedWord)
                    return " ".join(i for i in parsedWord)
            elif (
                targetPhoneSet == "EngHndCommon"
                and "CMU" in self.globalDict[self.Config["Lang"]["English"]["id"]]
                and word.upper()
                in self.globalDict[self.Config["Lang"]["English"]["id"]]["CMU"]
            ):
                # check in the fallback dictionary
                parsedWord = list(
                    self.globalDict[self.Config["Lang"]["English"]["id"]]["CMU"][
                        word.upper()
                    ][0].split(" ")
                )
                # A mapping to ensure correctness
                parsedWord = Utils.mapIE(parsedWord)
                if isASR:
                    parsedWord = Utils.mapASR(parsedWord)
                return " ".join(i for i in parsedWord)
            else:
                parsedWord = g2p(word)
            if self.debug:
                print(parsedWord)
            if targetPhoneSet == "CMU" and not targetPhoneSet == "EngHndCommon":
                return " ".join(i for i in parsedWord)
            elif targetPhoneSet == "EngHndCommon":
                new_phones = parsedWord
                if applyIErules:
                    # apply the IE rules
                    (
                        new_phones,
                        rule_name,
                        suf_name,
                        pre_name,
                        letters_act,
                        phonelist_act,
                    ) = Utils.applyIE(
                        word, parsedWord, tsylpath=self.tsylPath, debug=self.debug
                    )
                phones = Utils.mapIE(new_phones)
                # # The following is for debug - keep it as such
                # fin = ""
                # idi = 0
                # if word.upper() in self.globalDict[self.Config["Lang"]["English"]["id"]]:
                #     fin = self.globalDict[self.Config["Lang"]["English"]["id"]][
                #         word.upper()][0]
                #     idi = 1
                # else:
                #     fin = " ".join(i for i in phones)
                # if True:  # this is for rules checking, dont remove
                #     print("{0},{1},{2},{3},{4},{5}".format(
                #         word.upper(), " ".join(i for i in parsedWord), " ".join(i for i in new_phones), " ".join(i for i
                # in phones), fin, idi))
                # if True:  # this is for rules checking, dont remove
                #     for i, item in enumerate(parsedWord):
                #         parsedWord[i] = re.sub(
                #             '[^A-Za-z]+', '', parsedWord[i])
                #     for i, item in enumerate(new_phones):
                #         new_phones[i] = re.sub(
                #             '[^A-Za-z]+', '', new_phones[i])
                #     if not parsedWord != new_phones:
                #         # print("{0},{1},{2},{3},{4},{5},{6},{7},{8}".format(
                #         #     word.lower(), " ".join(i for i in parsedWord), " ".join(i for
                #         #                                                             i in new_phones), " ".join(i for i in phones), rule_name, suf_name, pre_name, " ".join(i for
                #         #                                                                                                                                                    i in letters_act), " ".join(i for
                #         # i in phonelist_act)))
                #         print(word.lower())
                if isASR:
                    phones = Utils.mapASR(phones)
                return " ".join(i for i in phones)
            return " ".join(
                constants.CMUtoCLS[
                    i.replace("0", "").replace("1", "").replace("2", "").lower()
                ]
                for i in parsedWord
            )
        elif targetPhoneSet != "CMU":
            # Handle Indian Languages
            if targetPhoneSet == "EngHndCommon":
                # if the targent phones is EngHndCommon
                phonelist = self.langObjects[currLang].getPhones(
                    word=word, langId=langId, targetPhone=targetPhoneSet
                )
                phonelist = phonelist.split(" ")
                phonelist = Utils.mapIE(phonelist)
                if isASR:
                    phonelist = Utils.mapASR(phonelist)
                return " ".join(i for i in phonelist)
            else:
                # For CLS phoneset
                return self.langObjects[currLang].getPhones(
                    word=word, langId=langId, targetPhone=targetPhoneSet
                )
        else:
            return "CMU phonset not supported for Indic languages"

    def getSyllables(
        self, word="", langId=-1, isIndicSyllable=False, phoneMark="", isAksharas=False
    ):
        """
        Get the syllable sequence using Indicword or g2p_en
        Output in: CLS or Indic script
        """
        if self.debug:
            print("fn: getSyllables\t", word, langId, isIndicSyllable)
        currLang = langId
        if langId == -1:
            currLang = self.getLangId(word)
            if currLang == -1:
                return "ERROR"
        if self.debug:
            print("Lang Id: ", currLang)
        # Handle english here
        if (
            currLang == self.Config["Lang"]["English"]["id"]
            or currLang == self.Config["Lang"]["Latin"]["id"]
        ):
            print("No Syllabifier for English/Latin available")
            return
        return self.langObjects[currLang].getSyllables(
            word=word,
            langId=langId,
            isIndicSyllable=isIndicSyllable,
            phoneMark=phoneMark,
            isAksharas=isAksharas,
        )


# ### Direct script usage functionality helper code
if __name__ == "__main__":
    word = ""
    if len(sys.argv) == 1:
        print("please enter the word")
        exit()
    elif len(sys.argv) == 2:
        word = sys.argv[1]
        outType = "phone"
    elif len(sys.argv) == 3:
        word = sys.argv[1]
        outType = sys.argv[2]
    else:
        print("Invalid number of arguments")
        exit()

    wordObj = Word()
    if outType == "phone":
        print(wordObj.getPhones(word=word))
    elif outType == "syllable":
        print(wordObj.getSyllables(word=word))
    elif outType == "akshara":
        print(wordObj.getSyllables(word=word, isAksharas=True))
    else:
        print("Invalid parsing type entered. use phone/syllable/akshara.")
