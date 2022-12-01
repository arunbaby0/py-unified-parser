# ########################### Author Info #####################
#       Name:   Arun Baby
#       Orgn:   Zapr Media Labs
#       Email:  arun.baby@zapr.in
#       Date:   06-02-2020
#       Desc:   Config for the Word parser
#       git:    
# ########################### Author Info #####################

# ########################### Update History ##################
# ########################### Update History ##################
# !/usr/bin/python

# Keep BASEPATH null in the master branch
BASEPATH = ""


CONFIG = {
    "Lang": {
        "Malayalam": {
            "id": 2,
            "scriptId": 2,
            "unicodeRange": [3328, 3455],
            "south": True,
            "dictFile": {"cls": "dict/MALAYALAM.dict"},
            "rulesFile": "rules/MALAYALAM.rules",
            "isIndic": True,
            "schwaChar": "av",
        },
        "Tamil": {
            "id": 3,
            "scriptId": 3,
            "unicodeRange": [2944, 3055],
            "south": True,
            "dictFile": {"cls": "dict/TAMIL.dict"},
            "rulesFile": "rules/TAMIL.rules",
            "isIndic": True,
            "schwaChar": "av",
        },
        "Telugu": {
            "id": 4,
            "scriptId": 4,
            "unicodeRange": [3072, 3198],
            "south": True,
            "dictFile": {"cls": "dict/TELUGU.dict"},
            "rulesFile": "rules/TELUGU.rules",
            "isIndic": True,
            "schwaChar": "av",
        },
        "Kannada": {
            "id": 5,
            "scriptId": 5,
            "unicodeRange": [3202, 3311],
            "south": True,
            "dictFile": {"cls": "dict/KANNADA.dict"},
            "rulesFile": "rules/KANNADA.rules",
            "isIndic": True,
            "schwaChar": "av",
        },
        "Hindi": {
            "id": 6,
            "scriptId": 6,
            "unicodeRange": [2304, 2431],
            "south": False,
            "dictFile": {
                "cls": "dict/HINDI.dict",
                "EngHndCommon": "dict/HINDI.dict1.dict",
            },
            "rulesFile": "rules/HINDI.rules",
            "isIndic": True,
            "schwaChar": "av",
        },
        "Bengali": {
            "id": 7,
            "scriptId": 7,
            "unicodeRange": [2432, 2559],
            "south": False,
            "dictFile": "",
            "rulesFile": "",
            "isIndic": True,
            "schwaChar": "ov",
        },
        "Gujarati": {
            "id": 8,
            "scriptId": 8,
            "unicodeRange": [2688, 2815],
            "south": False,
            "dictFile": "",
            "rulesFile": "",
            "isIndic": True,
            "schwaChar": "av",
        },
        "Odia": {
            "id": 9,
            "scriptId": 9,
            "unicodeRange": [2816, 2943],
            "south": False,
            "dictFile": "",
            "rulesFile": "",
            "isIndic": True,
            "schwaChar": "av",
        },
        "English": {
            "id": 10,
            "unicodeRange": [32, 122],
            "isIndic": False,
            "dictFile": {
                "CMU": "dict/ENGLISH.dict",
                "EngHndCommon": "dict/English.EngHndCommon.dict",
            },  # cmudict-0.7b.txt",
        },
        "Latin": {
            "id": 11,
            "unicodeRange": [192, 255],
            "isIndic": False,
            "dictFile": {"CMU": "dict/LATIN.dict"},
        },
    }
}

# Flow chart: ######
# //IE rules for Indian English
# apply IE(word,phoneSeq);
# //tsylab
# get Syllables(phoneSeq);

# split Word to letters(word);
# //difftool for alignment
# letters to Syllable(phones,letters);

# Syllable Rules();
# Sequnence Rules();
# Prefix Rules();
# Suffix Rules();

# Apply mapping to EngHndCommon();
# Final phones;
