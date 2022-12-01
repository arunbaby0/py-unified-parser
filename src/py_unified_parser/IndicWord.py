# ########################### Author Info #####################
#       Name:   Arun Baby
#       Orgn:   Zapr Media Labs
#       Email:  arun.baby@zapr.in
#       Date:   28-01-2020
#       Desc:   Indic languages word - phonemes/syllables parser
#       git:    
# ########################### Author Info #####################

# ########################### Update History ##################
# ########################### Update History ##################

# !/usr/bin/python
# -*- coding: utf-8 -*-

import os

from py_unified_parser import Utils, constants


class IndicWord:
    """
    IndicWord class for parsing Indic script
    """

    def __init__(
        self,
        langId=-1,
        langSpec=True,
        debug=False,
        isSouth=False,
        dictPath="",
        rulesPath="",
        schwaChar="av",
        basePath="",
    ):
        """
        Initialize the class with all the private vatiables
        """
        self.debug = debug
        self.currLang = -1
        self.text = ""
        self.fullHash = {}
        self.revHash = {}
        self.phonelist = []
        self.consonantsSemivowelList = [*constants.CONSONANTS, *constants.SEMIVOWELS]
        self.langRules = []
        self.isSouth = isSouth
        self.isLangSpecEnabled = langSpec
        self.wordsDict = {}
        self.dictPath = dictPath
        self.rulesPath = rulesPath
        self.schwaChar = schwaChar

        self.fullHash, self.revHash = Utils.createHash(debug=self.debug)
        if langId != -1:
            self.currLang = langId
            self.langRules = Utils.langSpecificRules(
                debug=self.debug, rulesPath=self.rulesPath
            )
            # self.setIsSouth(self.currLang)
        for dictType in dictPath:
            self.wordsDict[dictType] = Utils.loadWordsDict(
                debug=self.debug,
                dictLocation=os.path.join(basePath, dictPath[dictType]),
            )
        # print(self.wordsDict)

    def setWord(self, word, langId=0):
        """
        populate the current language, word and the corresponding language specific rules
        lang specific - rules are reloaded only when necessary
        """
        if self.debug:
            print("fn:setWord locn:", word, langId)
        # word = self.normaliseText(word)
        self.text = word
        self.phonelist = []
        # No more used since LangId is always set
        # if self.currLang <= 0 and langId <= 0:
        #   self.setLang(ord(list(word)[0]))
        #   self.langRules = Utils.langSpecificRules(debug = debug, rulesPath = self.rulesPath)
        # elif langId > 0 and langId != self.currLang:
        #   self.currLang = langId
        #   self.langRules = Utils.langSpecificRules(debug = debug, rulesPath = self.rulesPath)
        # # self.setIsSouth(self.currLang)

        self.phonelist = Utils.mapToCLS(
            debug=self.debug, word=word, fullHash=self.fullHash
        )

    def checkDict(self, word="", targetPhone="cls"):
        """
        Check in dict if exists
        """
        if self.debug:
            print("fn:checkDict ", word)
        if targetPhone in self.wordsDict and word in self.wordsDict[targetPhone]:
            if self.debug:
                print("Word from dict")
            return True
        return False

    def processWord(self, word, langId=0, isIndicSyllable=False):
        """
        Parse the input text:

           set lang specific flags
           append schwa
           lang specific corrections
           schwa corrections for North languages
        """
        if self.debug:
            print("fn:processWord ", word, langId, isIndicSyllable)

        self.setWord(word, langId)

        if len(self.phonelist) == 0:
            if self.debug:
                print("no phone mapping available")
            return

        self.phonelist = Utils.appendSchwa(
            debug=self.debug, phonelist=self.phonelist, schwaChar=self.schwaChar
        )

        if self.debug:
            print("append schwa: ", self.phonelist)

        if not isIndicSyllable and self.isLangSpecEnabled:
            if self.debug:
                print("Lang spec", isIndicSyllable, self.isLangSpecEnabled)
            self.phonelist = Utils.gemminateCorrection(
                debug=self.debug, phonelist=self.phonelist
            )
            self.phonelist = Utils.langSpecificCorrection(
                debug=self.debug, phonelist=self.phonelist, langRules=self.langRules
            )

        if self.debug:
            print("Lang spec correction: ", self.phonelist)

        if not self.isSouth:
            if self.phonelist[len(self.phonelist) - 1] in self.consonantsSemivowelList:
                self.phonelist.append(constants.HALANTMOD)
        else:
            if self.phonelist[len(self.phonelist) - 1] in self.consonantsSemivowelList:
                self.phonelist.append(self.schwaChar)

        self.phonelist = Utils.qCorrection(
            debug=self.debug, schwaChar=self.schwaChar, phonelist=self.phonelist
        )

        if not self.isSouth:
            self.phonelist = Utils.schwaCorrection(
                debug=self.debug, phonelist=self.phonelist, schwaChar=self.schwaChar
            )
            if self.debug:
                print("Schwa correction: ", self.phonelist)

        if self.debug:
            print("q correction: ", self.phonelist)

        # for no vowel words
        if (
            len(
                set(self.phonelist).intersection(
                    [*constants.VOWELS, *constants.VOWELMODIFIERS]
                )
            )
            == 0
        ):
            self.phonelist.append(self.schwaChar)

    def getPhones(self, word, targetPhone="cls", langId=0):
        """
        Get phonemes from word
        """
        if self.debug:
            print("fn:getPhones ", word, langId)

        word = Utils.normaliseText(debug=self.debug, word=word)

        if self.checkDict(word=word, targetPhone=targetPhone):
            return self.wordsDict[targetPhone][word][0]

        self.processWord(word=word, langId=langId)

        # add to dict and file
        phones = (
            (
                " ".join(
                    i
                    for i in self.phonelist
                    if (
                        i
                        not in [
                            constants.HALANT,
                            constants.HALANTMOD,
                            constants.SYLLDELIMITER,
                        ]
                    )
                )
            )
            .replace("v", "")
            .strip()
        )

        # self.addToDict(phones)

        if self.debug:
            print("phones: ", phones)
        return phones

    def getSyllables(
        self, word, langId=0, isIndicSyllable=False, phoneMark="", isAksharas=False
    ):
        """
        Get syllables from word
        """
        if self.debug:
            print("fn:getSyllables ", word, langId, isIndicSyllable)
        word = Utils.normaliseText(word)

        if self.checkDict(word=word):
            if isAksharas:
                return self.wordsDict[word][2]
            else:
                return self.wordsDict[word][1]

        self.processWord(word=word, langId=langId, isIndicSyllable=isIndicSyllable)
        self.phonelist = Utils.syllabify(
            debug=self.debug,
            phonelist=self.phonelist,
            langRules=self.langRules,
            isIndicSyllable=isIndicSyllable,
        )

        if self.debug:
            print("Syllabify: ", self.phonelist)

        if isAksharas:
            self.phonelist = Utils.aksharaSplit(
                phonelist=self.phonelist, debug=self.debug
            )
            if self.debug:
                print("Aksharas: ", self.phonelist)

        if isIndicSyllable:
            syllables = ""
            for i in self.phonelist:
                if i == self.schwaChar:
                    pass
                elif i == constants.SYLLDELIMITER:
                    syllables += " "
                elif i == constants.HALANTMOD:
                    syllables += self.revHash[constants.HALANT][self.currLang]
                elif i in self.revHash:
                    syllables += self.revHash[i][self.currLang]
        else:
            syllables = (
                phoneMark.join(
                    i
                    for i in self.phonelist
                    if (i not in [constants.HALANT, constants.HALANTMOD])
                )
            ).replace("v", "")
        syllables = syllables.replace(constants.SYLLDELIMITER, " ")
        syllables = syllables.replace("*", "")
        syllables = syllables.strip()
        if self.debug:
            print("syllables: ", syllables)
        return syllables

    def addToDict(self, phones):
        """
        Add unseen words to dict
        # have to handle syll and aksharas
        """
        if self.debug:
            print("fn:addToDict ", phones)
        self.wordsDict[self.text] = phones
        if self.debug:
            print(self.wordsDict[self.text], phones)
        if os.path.exists(self.dictPath):
            file = open(self.dictPath, "a+")
            file.write("{0}\t{1}\n".format(self.text, phones))
        else:
            if self.debug:
                print("No Dict file to write")
        return
