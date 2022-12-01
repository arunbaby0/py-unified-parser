# ########################### Author Info #####################
#       Name:   Arun Baby
#       Orgn:   Zapr Media Labs
#       Email:  arun.baby@zapr.in
#       Date:   20-02-2020
#       Desc:   Utils for IndicWord Parser Operations
#       git:    
# ########################### Author Info #####################

# ########################### Update History ##################
# ########################### Update History ##################

import copy
import itertools

# !/usr/bin/python
# -*- coding: utf-8 -*-
import os
import re
import subprocess
from difflib import SequenceMatcher

from py_unified_parser import constants

consonantsSemivowelList = [*constants.CONSONANTS, *constants.SEMIVOWELS]


def createHash(labels=constants.LABELSET, debug=False, nullPhone="$"):
    """
    Create Hash table from the LabelSet
    fullHash and the reverser hash
    """
    if debug:
        print("fn: createHash\t", labels)
    lines = labels.split("\n")
    tempHash = {}
    revHash = {}
    fullHash = {}
    for line in range(1, len(lines)):  # 0th line is always blank
        phones = lines[line].split("\t")
        clsphone = phones[constants.CLS]
        tempHash.clear()
        for row in range(constants.CLS + 1, len(phones)):
            fullHash[phones[row]] = clsphone
            if clsphone != nullPhone:
                tempHash[row] = phones[row]
        if clsphone != nullPhone:
            revHash[clsphone] = tempHash.copy()
    return fullHash, revHash


def normaliseText(word, debug=False):  # This can be a global unit
    """
    Normalising the text from the web
    """
    if debug:
        print("fn: normaliseText\t", word)
    word1 = word
    for left, right in constants.NORMALISETEXT:
        word = word.replace(left, right)
    if word != word1:
        if debug:
            print("Normalised: ", word, word1)
    return word


def mapToCLS(word, fullHash, debug=False, nullPhone="$"):
    """
    Basic mapping from Indic script to CLS.
    eg: ['त', 'ा', 'ज', 'म', 'ह', 'ल'] to ['t', 'aav', 'j', 'm', 'h', 'l']
    """
    if debug:
        print("fn: mapToCLS\t", word)
    inputList = list(word)
    phonelist = []
    if debug:
        print(word, inputList)
    for i in inputList:
        # print (ord(i), i, ord(i)%128) # for testing out of CLS map
        if i in fullHash and fullHash[i] != nullPhone:
            phonelist.append(fullHash[i])
            if debug:
                print(ord(i), i, fullHash[i])
    return phonelist


# '''
# Set the language ID for the language based on the Unicode range
# '''
# def setLang(debug = False, id): # Not used from Word parser
#   # if currLang <= 0: # if force set is enabled
#   #   return
#   if(id>=3328 and id<=3455):
#       currLang = constants.MALAYALAM
#   elif(id>=2944 and id<=3055):
#       currLang = constants.TAMIL
#   elif(id>=3202 and id<=3311):
#       currLang = constants.KANNADA
#   elif(id>=3072 and id<=3198):
#       currLang = constants.TELUGU
#   elif(id>=2304 and id<=2431):
#       currLang = constants.HINDI
#   elif(id>=2432 and id<=2559):
#       currLang = constants.BENGALI
#   elif(id>=2688 and id<=2815):
#       currLang = constants.GUJARATHI
#   elif(id>=2816 and id<=2943):
#       currLang = constants.ODIYA
#   elif(id>=64 and id<=123):
#       currLang = constants.ENGLISH
#   # setIsSouth(currLang)

# '''
# Set the flags for south Indian languages
# '''
# def setIsSouth(debug = False, id): # Not used from Word parser
#   if id > 5:
#       isSouth = False


def getRules(rulesPath, debug=False):  # Not used from Word parser
    path = rulesPath
    if os.path.exists(path) and os.path.isfile(path):
        f = open(path, "r")
        rules = f.readlines()
        return rules
    else:
        return ""


def langSpecificRules(rulesPath, debug=False):
    """
    Populate the language specific rules tables
    To write language specific rule, Check the rules file
    """
    if debug:
        print("fn:langSpecificRules")
    rules = getRules(debug=debug, rulesPath=rulesPath)
    if rules == "":
        if debug:
            print("lang spec rules NOT FOUND!!!")
        return
    langRules = []
    for rule in rules:
        rule = rule.replace("\n", "")
        if rule.find("#") != -1:  # commented rules handling
            continue
        # if rule.find("^") != -1: # begin handle
        #   continue
        # if rule.find("$") != -1: # end handle
        #   continue
        rule = rule.strip()
        sides = rule.split("\t")
        leftData = []
        rightData = []
        for i in range(0, 2):
            for comp in sides[i].split("&"):
                tempList = []
                for phone in comp.split("|"):
                    tempList.append(phone)
                if i == 0 and len(tempList) > 0:
                    leftData.append(tempList.copy())
                elif i == 1 and len(tempList) > 0:
                    rightData.append(tempList.copy())

        if len(leftData) > 1:
            leftComp = list(itertools.product(*leftData))
        else:
            leftComp = list(leftData)
        if len(rightData) > 1:
            rightComp = list(itertools.product(*rightData))
        else:
            rightComp = list(rightData)
        if not checkRules(leftComp, rightComp):
            print(
                "Rule ERROR: ", sides[0], "=>", sides[1], ", skipping the rule for now"
            )
            print("Please correct the above rule ASAP")
        else:
            langRules.append([leftComp.copy(), rightComp.copy()])
    return langRules


def appendSchwa(phonelist, schwaChar="av", debug=False):
    """
    Append "av" in every CC occurance
    CC, CV(V is full vowel) -> CVC
    Eg: ['t', 'aav', 'j', 'm', 'h', 'l'] to ['t', 'aav', 'j', 'av', 'm', 'av', 'h', 'av', 'l']
    """
    if debug:
        print("fn:appendSchwa ", phonelist)
    #  CC to CVC changes and middle vowel corrections
    i = 0
    while i < len(phonelist) - 1:
        if phonelist[i] in consonantsSemivowelList:
            if (
                phonelist[i + 1] in consonantsSemivowelList
                or phonelist[i + 1] in constants.VOWELS
            ):
                phonelist.insert(i + 1, schwaChar)
                i += 1
        i += 1
    if debug:
        print("size: ", len(phonelist))
    if len(phonelist) == 1:  # put it inside schwa
        phonelist = singleCharCorrection(phonelist, schwaChar=schwaChar)
    return phonelist


def schwaCorrection(phonelist, schwaChar="av", debug=False):
    """
    Schwa specific correcitons:
        1) get the sub array to be processed
        2) use the lexicographic order to correct the parsing
    eg: ['t', 'aav', 'j', 'av', 'm', 'av', 'h', 'av', 'l', 'euv'] to
        ['t', 'aav', 'j', 'euv', 'm', 'av', 'h', 'av', 'l', 'euv']
    """
    if debug:
        print("fn:schwaCorrection ", phonelist)
    if len(phonelist) == 1:
        if phonelist[0] in constants.CONSONANTS:
            phonelist.append(schwaChar)
            return phonelist
        if phonelist[0] in constants.VOWELS:
            return phonelist
    if len(phonelist) < 3:
        return phonelist
    start = 2

    if phonelist[0] in constants.VOWELS:
        if phonelist[1] in constants.CONSONANTS:
            start = 1  # This starting poing need to be verified for consonants
        elif phonelist[1] in constants.SEMIVOWELS:
            start = 1  # This starting poing need to be verified for Semi vowels

    end = len(phonelist) - 1

    # # find end split  - handle q mq later # not used now
    # if phonelist[len(phonelist)-1] in consonantsSemivowelList:
    #   end = len(phonelist) - 1
    # else:
    #   end = len(phonelist) - 2

    if debug:
        print(start, end, phonelist[start:end])

    for i in range(start, end - 4):
        if (
            phonelist[i] in consonantsSemivowelList
            and phonelist[i + 1] == constants.HALANT
            and phonelist[i + 2] in consonantsSemivowelList
        ):
            if phonelist[i + 3] == schwaChar:
                phonelist[i + 3] = schwaChar + "$"
                if i + 5 < len(phonelist) and phonelist[i + 5] == schwaChar:
                    phonelist[i + 5] = schwaChar + "$"
    if debug:
        print("Mix akshara correction:", phonelist)

    for schwa in range(0, len(consonantsSemivowelList) - 1):
        for i in range(start, end - 1):
            # print (consonantsSemivowelList[schwa], phonelist[i],
            # phonelist[i+1], phonelist[i+2])
            if (
                phonelist[i] == schwaChar
                and phonelist[i + 1] == consonantsSemivowelList[schwa]
                and phonelist[i + 2] in constants.VOWELMODIFIERS
                and phonelist[i - 2] not in [*constants.HALANT, *constants.HALANTMOD]
            ):
                # != "q":
                if i - 2 >= 0 and phonelist[i - 2] not in constants.SPECIALVOWELS:
                    phonelist[i] = schwaChar + "*"
                    if phonelist[i + 2] == schwaChar:
                        phonelist[i + 2] = schwaChar + "$"
    i = 0
    while i < len(phonelist):
        if phonelist[i] == schwaChar + "*":
            # changing to euv instead of deleting for syllabification
            phonelist[i] = constants.HALANTMOD
        i += 1
    phonelist = list(map(lambda b: b.replace(schwaChar + "$", schwaChar), phonelist))

    return phonelist


def checkRules(leftRule, rightRule, debug=False):
    """
    Check if the language specific rules format is correct for all the rules
    """
    if len(leftRule) != len(rightRule):  # check if the left of rules matching the right
        return False
    return True


def langSpecificCorrection(phonelist, langRules=[], isForward=True, debug=False):
    """
    lang Specific corrections for specific language
    The lang specific rules are populated and used for left to right correction
    if isForward is False, reverse correction happens
    """
    if debug:
        print("fn:langSpecificCorrection ", phonelist, isForward)
    if not langRules:
        return phonelist
    # for begin and end corrections
    phonelist.insert(0, "^")
    phonelist.append("$")

    for left, right in langRules:  # left to right correction using rules
        if not isForward:
            left, right = right, left
        for i in range(0, len(left)):
            for j in range(0, len(phonelist) - len(left[i]) + 1):
                # print ("iter", phonelist[j:j+len(left[i])], list(left[i]))
                if phonelist[j : j + len(left[i])] == list(left[i]):
                    phonelist[j : j + len(left[i])] = list(right[i])

    # for begin and end reverse corrections
    del phonelist[0]
    del phonelist[len(phonelist) - 1]
    return phonelist


def gemminateCorrection(phonelist, isForward=True, debug=False):
    """
    Gemminates are kept together using this rule
    eg: ["a", "m", "eu","m", "a"] to ["a", "m", "m", "a"]
    """
    if debug:
        print("fn:gemminateCorrection ", phonelist, isForward)
    for phone in consonantsSemivowelList:
        if isForward:
            i = 0
            while i < len(phonelist) - 2:
                if (
                    phonelist[i] == phone
                    and phonelist[i + 1] == constants.HALANT
                    and phonelist[i + 2] == phone
                ):
                    del phonelist[i + 1]
                i += 1
        else:
            i = 0
            while i < len(phonelist) - 2:
                if phonelist[i] == phone and phonelist[i + 1] == phone:
                    phonelist.insert(i + 1, constants.HALANTMOD)
                i += 1
    return phonelist


def qCorrection(phonelist, schwaChar="av", debug=False):
    """
    q and hq correction
    Eg: ["k","q"] to ["k", "a", "q"] only for consonents or semi vowels
    """
    if debug:
        print("fn:qCorrection ", phonelist)
    i = 0
    while i < len(phonelist) - 1:
        # == 'q' or phonelist[i+1] == 'hq') :
        if phonelist[i] in consonantsSemivowelList and (
            phonelist[i + 1] in constants.SPECIALVOWELS
        ):
            phonelist.insert(i + 1, schwaChar)
        i += 1
    return phonelist


def singleCharCorrection(phonelist, schwaChar="av", debug=False):
    """
    If only one char is there append with schwaChar
    """
    if phonelist[0] in consonantsSemivowelList:
        phonelist.append(schwaChar)
    return phonelist


def loadWordsDict(dictLocation="", debug=False):
    """
    Load the hash table from the dict file
    """
    if debug:
        print("fn:loadWordsDict locn:", dictLocation)
    wordsDict = {}
    if dictLocation != "":
        if os.path.exists(dictLocation) and os.path.isfile(dictLocation):
            file = open(dictLocation, "r", encoding="utf8", errors="ignore")
            text = file.readlines()
            for words in text:
                words = words.strip()
                tempHash = {}
                dictItems = words.split("\t")
                word = dictItems[0].upper()
                tempHash[0] = dictItems[1]
                if len(dictItems) == 3:
                    tempHash[1] = dictItems[2]
                else:
                    tempHash[1] = ""
                if len(dictItems) == 4:
                    tempHash[2] = dictItems[3]
                else:
                    tempHash[2] = ""
                wordsDict[word.strip()] = tempHash.copy()
        else:
            if debug:
                print("Dictionary path ", dictLocation, " doesnt exists!")
    return wordsDict


def checkAllSyllabified(phonelist, debug=False):
    """
    Check if all the syllables is having a vowel.
    All syllables should be C*VC* form
    """
    flag = False
    for i in phonelist[1:]:
        if i in [*constants.VOWELMODIFIERS, *constants.VOWELS]:
            flag = True
        elif i in consonantsSemivowelList:
            pass
        elif i == constants.SYLLDELIMITER:
            if not flag:
                return False
            flag = False
    return True


def ifVowelExist(phones, debug=False):
    """
    Check if vowel exist in phones
    """
    for i in phones:
        if i in [*constants.VOWELMODIFIERS, *constants.VOWELS]:
            return True
    return False


def syllabify(phonelist, isIndicSyllable=False, langRules=[], debug=False):
    """
    Syllabification operation:
    Split at vowels/vowel modifiers and "eu","euv"
    If a group is not having a vowel, append to the previous group
    itereate till all groups are syllables
    """
    if debug:
        print("fn:syllabify ", phonelist)
    if isIndicSyllable:
        phonelist = gemminateCorrection(
            debug=debug, phonelist=phonelist, isForward=True
        )
    if debug:
        print("gemminate forward correction", phonelist)
    if isIndicSyllable:
        phonelist = langSpecificCorrection(
            debug=debug, phonelist=phonelist, langRules=langRules, isForward=False
        )
    i = 0
    while i < len(phonelist):
        if phonelist[i] in [
            *constants.VOWELS,
            *constants.VOWELMODIFIERS,
            *constants.SPECIALVOWELS,
            *constants.HALANT,
            *constants.HALANTMOD,
        ]:
            phonelist.insert(i + 1, constants.SYLLDELIMITER)
            i += 1
        i += 1
    if phonelist[len(phonelist) - 1] != constants.SYLLDELIMITER:
        phonelist.append(constants.SYLLDELIMITER)

    i = 0
    while True:
        if phonelist[i] == constants.SYLLDELIMITER:
            del phonelist[i]
            i -= 1
        elif phonelist[i] in [*constants.VOWELMODIFIERS, *constants.VOWELS]:
            break
        i += 1

    phonelist.insert(0, constants.SYLLDELIMITER)

    if debug:
        print("morpheme correction", phonelist)

    while not checkAllSyllabified(phonelist):
        end = len(phonelist) - 1
        i = end - 1
        while i >= 0:
            if phonelist[i] == constants.SYLLDELIMITER:
                if not ifVowelExist(phonelist[i + 1 : end]) and i != 0:
                    phonelist[i] = "*"
                end = i
            i = i - 1

        i = 0
        while i < len(phonelist):
            if phonelist[i] == "*":
                del phonelist[i]
            i += 1
    if isIndicSyllable:
        phonelist = gemminateCorrection(
            debug=debug, phonelist=phonelist, isForward=False
        )
    if debug:
        print("gemminate reverse correction", phonelist)

    return phonelist


def aksharaSplit(phonelist, debug=False):
    """
    Akshara based split:
    """
    if debug:
        print("fn:aksharaSplit ", phonelist)
    i = 0
    while i < len(phonelist) - 1:
        if (
            phonelist[i]
            in [*constants.VOWELMODIFIERS, *constants.VOWELS, *constants.SPECIALVOWELS]
            and phonelist[i + 1] != constants.SYLLDELIMITER
            and phonelist[i + 1] not in constants.SPECIALVOWELS
        ):
            phonelist.insert(i + 1, constants.SYLLDELIMITER)
        i += 1
    i = 0
    while i < len(phonelist) - 3:
        if (
            phonelist[i] in [*constants.HALANT, *constants.HALANTMOD]
            and phonelist[i + 1] == constants.SYLLDELIMITER
        ):
            del phonelist[i + 1]
        i += 1
    return phonelist


def suffixRules(word, suffix, phonelist, phonesToreplace, replacement, isStrict=False):
    """
    Apply suffix rules to the phone sequence
    """
    if bool(re.search(suffix + "$", word)):
        if isStrict:
            if phonelist[-len(phonesToreplace) :] == phonesToreplace:
                phonelist_new = phonelist[: len(phonelist) - len(phonesToreplace)]
                ret_list = []
                ret_list.extend(phonelist_new)
                ret_list.extend(replacement)
                return True, ret_list
        else:
            phonelist_new = phonelist[: len(phonelist) - len(phonesToreplace)]
            ret_list = []
            ret_list.extend(phonelist_new)
            ret_list.extend(replacement)
            return True, ret_list
    return False, phonelist


def prefixRules(
    word, prefix, phonelist, phonesToreplace, replacement=[], isStrict=False
):
    """
    Apply prefix rules to the phone sequence
    """
    if bool(re.search("^" + prefix, word)):
        if isStrict:
            if phonelist[-len(phonesToreplace) :] == phonesToreplace:
                phonelist_new = phonelist[: len(phonelist) - len(phonesToreplace)]
                ret_list = []
                ret_list.extend(replacement)
                ret_list.extend(phonelist_new)
                return True, ret_list
        else:
            phonelist_new = phonelist[len(phonesToreplace) :]
            ret_list = []
            ret_list.extend(replacement)
            ret_list.extend(phonelist_new)
            return True, ret_list
    return False, phonelist


def getSyllables(phonelist, tsylpath=""):  # direct executable
    """
    Get the syllable sequence from the phone list using tsylab2
    """
    str1 = " ".join(
        i.lower().replace("0", "").replace("1", "").replace("2", "") for i in phonelist
    )
    str1 = str1.replace("ng", "nx")
    execpath = os.path.join(tsylpath, "tsylb2")
    pcdpath = os.path.join(tsylpath, "phon1ax.pcd")
    str1 = subprocess.run(
        [execpath, "-n", pcdpath, "0", str1, tsylpath], stdout=subprocess.PIPE
    ).stdout.decode("utf-8")
    str1 = str1.strip().replace("nx", "ng")
    str1 = (
        str1.replace(" ] [", "-")
        .replace("#", "")
        .replace("]", "")
        .replace("[", "")
        .replace("'0", "")
        .replace("  ", " ")
    )
    return str1


def separateLetters(w):
    """
    separate out letters from the word w with some rules
    """
    w = re.sub(r"([a-zA-Z])", r"  \1  ", w)
    # combine /ph/ /ch/ /ng/ /sh/ /th/ /er/ /ow/
    w = re.sub(r"([^a-z])p\s\s*h([^a-z])", r"\1ph\2", w)
    w = re.sub(r"([^a-z])c\s\s*h([^a-z])", r"\1ch\2", w)
    w = re.sub(r"([^a-z])n\s\s*g([^a-z])", r"\1ng\2", w)
    w = re.sub(r"([^a-z])s\s\s*h([^a-z])", r"\1sh\2", w)
    w = re.sub(r"([^a-z])t\s\s*h([^a-z])", r"\1th\2", w)
    w = re.sub(r"([^a-z])e\s\s*r([^a-z])", r"\1er\2", w)
    w = re.sub(r"([^a-z])o\s\s*w([^a-z])", r"\1ow\2", w)
    # combine duplicate consecutive non-vowels
    w = re.sub(r"([^a-z])([^aeiou])\s\s*\2([^a-z])", r"\1\2\2\3", w)
    # combine consecutive vowels and letter y
    w = re.sub(r"([^a-z])([aeiou])\s\s*([aeiouy])([^a-z])", r"\1\2\3\4", w)
    # remove dashes
    w = re.sub(r"-", r"", w)
    # all cap
    w = w.upper()
    return w


def getMapping(a, b, debug=False):
    """
    A mapping between the string sequnces a and b, using the diff method.
    """
    s = SequenceMatcher(None, a, b)
    letters = []
    phones = []

    for tag, i1, i2, j1, j2 in s.get_opcodes():
        if len(a[i1:i2]) == len(b[j1:j2]):
            phones.extend(a[i1:i2])
            letters.extend(b[j1:j2])
        else:
            if len(a[i1:i2]) > len(b[j1:j2]):
                phones.extend(a[i1:i2])
                letters.extend(b[j1:j2])
                for x in range(0, len(a[i1:i2]) - len(b[j1:j2])):
                    letters.append("*")
            elif len(a[i1:i2]) < len(b[j1:j2]):
                phones.extend(a[i1:i2])
                letters.extend(b[j1:j2])
                for x in range(0, len(b[j1:j2]) - len(a[i1:i2])):
                    phones.append("*")
            if debug:
                # s1 is for second level matching - only while debug
                s1 = SequenceMatcher(
                    None,
                    " ".join(i for i in a[i1:i2]).split(),
                    " ".join(i for i in b[j1:j2]).split(),
                )
                for tagn, i1n, i2n, j1n, j2n in s1.get_opcodes():
                    print(
                        "{:7}   a[{}:{}] --> b[{}:{}] {!r:>8} --> {!r}".format(
                            tagn, i1n, i2n, j1n, j2n, a[i1n:i2n], b[j1n:j2n]
                        )
                    )
        if debug:
            print(
                "{:7}   a[{}:{}] --> b[{}:{}] {!r:>8} --> {!r}".format(
                    tag, i1, i2, j1, j2, a[i1:i2], b[j1:j2]
                )
            )
    return letters, phones


def syllRules(
    letters, phonelist, fromSeq, fromPhones, toPhones, syllPos, isStrict=True
):
    """
    Apply syllable based rules
    """
    flag = False
    for i, letter in enumerate(letters):
        let = ""
        position = 0
        let = "".join([i for i in letter if not i.isdigit()])
        pos = re.findall(r"\d+", letter)
        if len(pos) == 0:
            position = 0
        else:
            position = pos[0]

        # if bool(re.search("[A-Z]-[0-9]+", letter)):
        #     # if "-" in letter:
        #     let, position = letter.split("-")
        #     let += "-"
        # else:
        #     let = letter
        # pattern = ""
        # if syllPos == 0:
        #     pattern = fromSeq[0]
        # elif syllPos == 1:
        #     pattern = fromSeq[0]

        pattern = fromSeq[0]
        if pattern == let and phonelist[i] == fromPhones[0]:
            flag = True
            phonelist[i] = toPhones[0]
        if str(syllPos) == "1" and str(position) == "1":
            break

    return phonelist, flag


def seqRules(letters, phonelist, fromSeq, fromPhones, toPhones):
    """
    Rules for sequnces of phones and matching letters
    """
    return replace_sublist(phonelist, fromPhones, letters, fromSeq, toPhones)
    return phonelist, flag


def find_first_sublist(seq, sublist, start=0):
    """
    Replace single time
    """
    length = len(sublist)
    for index in range(start, len(seq)):
        if seq[index : index + length] == sublist:
            return index, index + length


def replace_sublist(seq, sublist, secondlist, conditionList, replacement):
    """
    Replace a sublist recursively
    """
    length = len(replacement)
    index = 0
    flag = False
    for start, end in iter(lambda: find_first_sublist(seq, sublist, index), None):
        if secondlist[start:end] == conditionList:
            seq[start:end] = replacement
            flag = True
            index = start + length
        break
    return seq, flag


def mapIE(phonelist):
    """
    Apply new mapping with CMU+cls to common
    """
    phones = []
    for i, phone in enumerate(phonelist):
        if phone != "*":
            phone = re.sub("[^A-Za-z]+", "", phone)
            if phone in constants.IEMAP:
                phones.append(constants.IEMAP[phone])
            else:
                phones.append(phone)
    phones = list(filter(None, phones))
    return phones


def applyIE(word, phonelist, tsylpath="", debug=False):
    """
    Apply the new Indian English Rules
    steps:
        0) Get syllable boundaries using the phone sequence
        1) Create a mapping between letters and phones
        2) Apply SYll and Seq level rules
        3) Apply _fix rules
    """
    rule_name, suf_name, pre_name = "", "", ""
    word = word.lower()

    syllables = getSyllables(phonelist, tsylpath=tsylpath)
    lettersCombined = [separateLetters(word)]
    if debug:
        print("letters:", lettersCombined)
    phonelist = syllables.upper().strip().split(" ")

    # Get mapping between letters and phones
    letters, phonelist = getMapping(
        " ".join(i for i in phonelist).split(),
        " ".join(i for i in lettersCombined).split(),
        debug=debug,
    )

    if len(letters) != len(phonelist):
        if debug:
            print("ERROR ", word, letters, phonelist)

    pos = 1
    letters[0] = "-" + letters[0]
    # create syllable mapping for letters wrt to Phones
    for i, phone in enumerate(phonelist):
        if "-" in phone:
            i_n = i
            if letters[i] == "*":
                letters[i], letters[i - 1] = letters[i - 1], letters[i]
            letters[i] = letters[i] + "-" + str(pos)
            letters[i + 1] = "-" + letters[i + 1]
            pos += 1
    letters[len(letters) - 1] = letters[len(letters) - 1] + "-"
    if debug:
        print(letters)
        print(phonelist)

    letters_act = copy.deepcopy(letters)
    phonelist_act = copy.deepcopy(phonelist)

    # Apply different set of rules
    # Syllable level rules
    for rule in constants.SYLLRULES:
        phonelist, flag = syllRules(
            letters,
            phonelist,
            constants.SYLLRULES[rule][0],
            constants.SYLLRULES[rule][1],
            constants.SYLLRULES[rule][2],
            constants.SYLLRULES[rule][3],
        )
        if flag:
            rule_name += rule + ";"
    if debug:
        print("Syll rules", phonelist)
    # Remove syllable boundaries
    for i, phone in enumerate(phonelist):
        if "-" in phone:
            phonelist[i] = re.sub("[^A-Za-z]+", "", phone)

    for i, phone in enumerate(letters):
        if "-" in phone:
            letters[i] = re.sub("[^A-Za-z]+", "", phone)

    # Sequence level rules
    for rule in constants.SEQRULES:
        phonelist, flag = seqRules(
            letters,
            phonelist,
            constants.SEQRULES[rule][0],
            constants.SEQRULES[rule][1],
            constants.SEQRULES[rule][2],
        )
        if flag:
            rule_name += rule + ";"

    if debug:
        print("Seq rules", phonelist)

    if "*" in phonelist:
        phonelist = list(filter(lambda x: x != "*", phonelist))

    # Suffix level rules
    for suffix in constants.SUFFIXRULES:
        flag, phonelist = suffixRules(
            word,
            suffix,
            phonelist,
            constants.SUFFIXRULES[suffix][0],
            constants.SUFFIXRULES[suffix][1],
            constants.SUFFIXRULES[suffix][2],
        )
        if flag:
            suf_name = suffix
            break

    if debug:
        print("Suffix rules", phonelist)

    # Prefix level rules
    for prefix in constants.PREFIXRULES:
        flag, phonelist = prefixRules(
            word,
            prefix,
            phonelist,
            constants.PREFIXRULES[prefix][0],
            constants.PREFIXRULES[prefix][1],
            constants.PREFIXRULES[prefix][2],
        )
        if flag:
            pre_name = prefix
            break

    if debug:
        print("IE English rules:", phonelist)

    return phonelist, rule_name, suf_name, pre_name, letters_act, phonelist_act


def mapASR(phonelist):
    """
    Apply new mapping with CMU+cls to common
    """
    phones = []
    for i, phone in enumerate(phonelist):
        if phone != "*":
            phone = re.sub("[^A-Za-z]+", "", phone)
            if phone in constants.ASRMAP:
                phones.append(constants.ASRMAP[phone])
            else:
                phones.append(phone)
    phones = list(filter(None, phones))
    return phones
