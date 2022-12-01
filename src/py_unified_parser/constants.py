# ########################### Author Info #####################
# 		Name:	Arun Baby
#  		Orgn: 	Zapr Media Labs
#   	Email: 	arun.baby@zapr.in
# 		Date:	28-01-2020
# 		Desc:	constants used for IndicParser and Word parser
# 		git: 	
# ########################### Author Info #####################

# ########################### Update History ##################
# ########################### Update History ##################
# !/usr/bin/python
# -*- coding: utf-8 -*-

CLS = 1  # The location of CLS phoneset in LABELSET

SYLLDELIMITER = "@"

HALANT = "eu"
HALANTMOD = "euv"

LABELSET = """
0	$	#	#	#	#	ऀ	#	#	#
1	mq	#	#	#	#	ँ	ঁ	ઁ	ଁ
2	q	ം	ஂ	ం	ಂ	ं	ং	ં	ଂ
3	hq	ഃ	ஃ	ః	ಃ	ः	ঃ	ઃ	ଃ
4	$	#	#	#	#	ऄ	#	#	#
5	a	അ	அ	అ	ಅ	अ	অ	અ	ଅ
6	aa	ആ	ஆ	ఆ	ಆ	आ	আ	આ	ଆ
7	i	ഇ	இ	ఇ	ಇ	इ	ই	ઇ	ଇ
8	ii	ഈ	ஈ	ఈ	ಈ	ई	ঈ	ઈ	ଈ
9	u	ഉ	உ	ఉ	ಉ	उ	উ	ઉ	ଉ
10	uu	ഊ	ஊ	ఊ	ಊ	ऊ	ঊ	ઊ	ଊ
11	rq	ഋ	#	ఋ	ಋ	ऋ	ঋ	ઋ	ଋ
12	$	#	#	#	#	ऌ	ঌ	ઌ	ଌ
13	ae	#	#	#	#	ऍ	#	ઍ	#
14	e	എ	எ	ఎ	ಎ	ऎ	#	#	#
15	ee	ഏ	ஏ	ఏ	ಏ	ए	এ	એ	ଏ
16	ei	ഐ	ஐ	ఐ	ಐ	ऐ	ঐ	ઐ	ଐ
17	ax	#	#	#	#	ऑ	#	ઑ	#
18	o	ഒ	ஒ	ఒ	ಒ	ऒ	#	#	#
19	oo	ഓ	ஓ	ఓ	ಓ	ओ	ও	ઓ	ଓ
20	ou	ഔ	ஔ	ఔ	ಔ	औ	ঔ	ઔ	ଔ
21	k	ക	க	క	ಕ	क	ক	ક	କ
22	kh	ഖ	#	ఖ	ಖ	ख	খ	ખ	ଖ
23	g	ഗ	#	గ	ಗ	ग	গ	ગ	ଗ
24	gh	ഘ	#	ఘ	ಘ	घ	ঘ	ઘ	ଘ
25	ng	ങ	ங	ఙ	ಙ	ङ	ঙ	ઙ	ଙ
26	c	ച	ச	చ	ಚ	च	চ	ચ	ଚ
27	ch	ഛ	#	ఛ	ಛ	छ	ছ	છ	ଛ
28	j	ജ	ஜ	జ	ಜ	ज	জ	જ	ଜ
29	jh	ഝ	#	ఝ	ಝ	झ	ঝ	ઝ	ଝ
30	nj	ഞ	ஞ	ఞ	ಞ	ञ	ঞ	ઞ	ଞ
31	tx	ട	ட	ట	ಟ	ट	ট	ટ	ଟ
32	txh	ഠ	#	ఠ	ಠ	ठ	ঠ	ઠ	ଠ
33	dx	ഡ	#	డ	ಡ	ड	ড	ડ	ଡ
34	dxh	ഢ	#	ఢ	ಢ	ढ	ঢ	ઢ	ଢ
35	nx	ണ	ண	ణ	ಣ	ण	ণ	ણ	ଣ
36	t	ത	த	త	ತ	त	ত	ત	ତ
37	th	ഥ	#	థ	ಥ	थ	থ	થ	ଥ
38	d	ദ	#	ద	ದ	द	দ	દ	ଦ
39	dh	ധ	#	ధ	ಧ	ध	ধ	ધ	ଧ
40	n	ന	ந	న	ನ	न	ন	ન	ନ
41	nd	ഩ	ன	#	#	ऩ	#	#	#
42	p	പ	ப	ప	ಪ	प	প	પ	ପ
43	ph	ഫ	#	ఫ	ಫ	फ	ফ	ફ	ଫ
44	b	ബ	#	బ	ಬ	ब	ব	બ	ବ
45	bh	ഭ	#	భ	ಭ	भ	ভ	ભ	ଭ
46	m	മ	ம	మ	ಮ	म	ম	મ	ମ
47	y	യ	ய	య	ಯ	य	য	ય	ଯ
48	r	ര	ர	ర	ರ	र	র	ર	ର
49	rx	റ	ற	#	#	ऱ	#	#	#
50	l	ല	ல	ల	ಲ	ल	ল	લ	ଲ
51	lx	ള	ள	ళ	ಳ	ळ	#	ળ	ଳ
52	zh	ഴ	ழ	#	#	ऴ	#	#	#
53	w	വ	வ	వ	ವ	व	#	વ	ଵ
54	sh	ശ	ஶ	శ	ಶ	श	শ	શ	ଶ
55	sx	ഷ	ஷ	ష	ಷ	ष	ষ	ષ	ଷ
56	s	സ	ஸ	స	ಸ	स	স	સ	ସ
57	h	ഹ	ஹ	హ	ಹ	ह	হ	હ	ହ
58	$	#	#	#	#	ऺ	#	#	#
59	$	#	#	#	#	ऻ	#	#	#
60	nk	#	#	#	#	़	়	઼	଼
61	ag	#	#	#	#	ऽ	ঽ	ઽ	ଽ
62	aav	ാ	ா	ా	ಾ	ा	া	ા	ା
63	iv	ി	ி	ి	ಿ	ि	ি	િ	ି
64	iiv	ീ	ீ	ీ	ೀ	ी	ী	ી	ୀ
65	uv	ു	ு	ు	ು	ु	ু	ુ	ୁ
66	uuv	ൂ	ூ	ూ	ೂ	ू	ূ	ૂ	ୂ
67	rqv	ൃ	#	ృ	ೃ	ृ	ৃ	ૃ	ୃ
68	rqwv	ൄ	#	ౄ	ೄ	ॄ	ৄ	ૄ	#
69	aev	#	#	#	#	ॅ	#	#	#
70	ev	െ	ெ	ె	ೆ	ॆ	#	#	ୄ
71	eev	േ	ே	ే	ೇ	े	ে	ે	େ
72	eiv	ൈ	ை	ై	ೈ	ै	ৈ	ૈ	ୈ
73	axv	#	#	#	#	ॉ	#	ૉ	#
74	ov	ൊ	ொ	ొ	ೊ	ॊ	#	#	#
75	oov	ോ	ோ	ో	ೋ	ो	ো	ો	ୋ
76	ouv	ൌ	ௌ	ౌ	ೌ	ौ	ৌ	ૌ	ୌ
77	eu	്	்	్	್	्	্	્	୍
78	tv	#	#	#	#	ॎ	ৎ	#	#
79	$	#	#	#	#	ॏ	#	#	#
80	om	#	#	#	#	ॐ	#	ૐ	#
81	$	#	#	#	#	॓	#	#	#
82	$	#	#	#	#	॔	#	#	#
83	$	#	#	#	#	#	#	#	#
84	$	#	#	#	#	#	#	#	#
85	$	#	#	#	#	ॕ	#	#	#
86	$	#	#	#	#	ॖ	#	#	ୖ
87	auv	ൗ	#	#	#	ॗ	ৗ	#	ୗ
88	kq	#	#	#	#	क़	#	#	#
89	khq	#	#	#	#	ख़	#	#	#
90	gq	#	#	#	#	ग़	#	#	#
91	z	#	#	#	#	ज़	#	#	#
92	dxq	#	#	#	#	ड़	ড়	#	ଡ଼
93	dxhq	#	#	#	#	ढ़	ঢ়	#	ଢ଼
94	f	#	#	#	#	फ़	#	#	#
95	y	#	#	#	#	य़	য়	#	ୟ
96	rqw	#	#	#	#	ॠ	ৠ	ૠ	ୠ
97	$	#	#	#	#	ॡ	ৡ	ૡ	ୡ
98	$	#	#	#	#	ॢ	ৢ	ૢ	#
99	$	#	#	#	#	ॣ	ৣ	ૣ	ୢ
100	$	#	#	#	#	।	#	#	#
101	$	#	#	#	#	॥	#	#	ୣ
102	$	#	#	#	#	०	০	૦	୦
103	$	#	#	#	#	१	১	૧	୧
104	$	#	#	#	#	२	২	૨	୨
105	$	#	#	#	#	३	৩	૩	୩
106	$	#	#	#	#	४	৪	૪	୪
107	$	#	#	#	#	५	৫	૫	୫
108	$	#	#	#	#	६	৬	૬	୬
109	$	#	#	#	#	७	৭	૭	୭
110	$	#	#	#	#	८	৮	૮	୮
111	$	#	#	#	#	९	৯	૯	୯
112	rv	#	#	#	#	॰	ৰ	૰	୰
113	wv	#	#	#	#	ॱ	ৱ	૱	ୱ
114	$	#	#	#	#	ॲ	৲	#	୲
115	$	#	#	#	#	ॳ	৳	#	୳
116	$	#	#	#	#	ॴ	৴	#	୴
117	$	#	#	#	#	ॵ	৵	#	୵
118	$	#	#	#	#	ॶ	৶	#	୶
119	$	#	#	#	#	ॷ	৷	#	୷
120	$	#	#	#	#	ॸ	৸	#	#
121	$	#	#	#	#	ॹ	৹	#	#
122	nwv	ൺ	#	#	#	ॺ	৺	#	#
123	nnv	ൻ	#	#	#	ॻ	৻	#	#
124	rwv	ർ	#	#	#	ॼ	#	#	#
125	lwv	ൽ	#	#	#	ॽ	#	#	#
126	lnv	ൾ	#	#	#	ॾ	#	#	#
127	$	#	#	#	#	ॿ	#	#	#"""


VOWELS = [
    "a",
    "e",
    "i",
    "o",
    "u",
    "aa",
    "aa",
    "ii",
    "uu",
    "rq",
    "rqw",
    "au",
    "ee",
    "ei",
    "ou",
    "oo",
    "ax",
    "ai",
    "om",
    "ae",
]

SPECIALVOWELS = ["q", "hq", "mq"]

CONSONANTS = [
    "k",
    "kh",
    "g",
    "gh",
    "ng",
    "c",
    "ch",
    "j",
    "jh",
    "nj",
    "tx",
    "txh",
    "dx",
    "dxh",
    "nx",
    "nd",
    "t",
    "th",
    "d",
    "dh",
    "n",
    "p",
    "ph",
    "b",
    "bh",
    "m",
    "dxhq",
    "kq",
    "khq",
    "gq",
    "dxq",
]

SEMIVOWELS = [
    "y",
    "r",
    "l",
    "w",
    "s",
    "sh",
    "sx",
    "zh",
    "h",
    "lx",
    "rx",
    "f",
    "dxq",
    "z",
]

VOWELMODIFIERS = [
    "av",
    "nwv",
    "nnv",
    "rwv",
    "lwv",
    "lnv",
    "aav",
    "iiv",
    "uuv",
    "rqv",
    "eev",
    "eiv",
    "ouv",
    "axv",
    "oov",
    "aiv",
    "iv",
    "ov",
    "ev",
    "uv",
    "aev",
]

NORMALISETEXT = [
    ["ऩ", "ऩ"],
    ["ऱ", "ऱ"],
    ["क़", "क़"],
    ["ख़", "ख़"],
    ["ग़", "ग़"],
    ["ज़", "ज़"],
    ["ड़", "ड़"],
    ["ढ़", "ढ़"],
    ["ढ़", "ढ़"],
    ["फ़", "फ़"],
    ["य़", "य़"],
    ["ऴ", "ऴ"],
    ["ொ", "ொ"],
    ["ோ", "ோ"],
    ["ൊ", "ൊ"],
    ["ോ", "ോ"],
    ["ല്‍‌", "ൽ"],
    ["ള്‍", "ൾ"],
    ["ര്‍", "ർ"],
    ["ന്‍", "ൻ"],
    ["ണ്‍", "ൺ"],
    ["ೀ", "ೀ"],
    # [":", "ः"],
]

CMUtoCLS = {
    "aa": "aa",
    "ae": "axx",
    "ah": "a",
    "ao": "ax",
    "aw": "ou",
    "ax": "a",
    "ay": "ei",
    "b": "b",
    "ch": "c",
    "d": "dx",
    "dh": "d",
    "eh": "ee",
    "er": "a r",
    "ey": "ee",
    "f": "f",
    "g": "g",
    "hh": "h",
    "ih": "i",
    "iy": "ii",
    "jh": "j",
    "k": "k",
    "l": "l",
    "m": "m",
    "n": "n",
    "ng": "ng",
    "ow": "o",
    "oy": "ei",
    "p": "p",
    "pau": "SIL",
    "r": "r",
    "s": "s",
    "sh": "sh",
    "t": "tx",
    "th": "t",
    "uh": "u",
    "uw": "uu",
    "v": "w",
    "w": "w",
    "y": "y",
    "z": "z",
    "zh": "sh",
    " ": " ",
    "'": "'",
    ",": ",",
    "?": "?",
    "!": "!",
}

# the first list is just the representation. Need not be exactly same.
# It just remove that many phones and add the ones in the second column
# Third column is isStrict. This will check for exact match of first list
# while replacing.
SUFFIXRULES = {
    "[a-z]+a": [["AH"], ["aa"], True],
    "ment": [["M", "AH0", "N", "T"], ["M", "EH0", "N", "T"], False],
    "less": [["L", "AH0", "S"], ["L", "EH0", "S"], False],
    "ness": [["N", "AH0", "S"], ["N", "EH0", "S"], False],
    "ress": [["R", "AH0", "S"], ["R", "EH0", "S"], False],
    "ted": [["T", "AH0", "D"], ["T", "EH0", "D"], False],
    "er": [["ER0"], ["ER0"], False],
    "[a-z]+ions": [["AH0", "N", "Z"], ["AH0", "N", "s"], False],
    "[a-z]+ion": [["AH0", "N"], ["AH0", "N"], False],
    "[a-z]+ted": [["T", "IH0", "D"], ["T", "EH0", "D"], False],
    "[a-z]+nist": [["N", "IH0", "S", "T"], ["N", "IH0", "S", "T"], False],
    "ity": [["AH0", "T", "IY0"], ["i", "tx", "ii"], False],
    "[a-z]+ant": [["AH0", "N", "T"], ["a", "n", "tx"], False],
    "ic": [["IH0", "K"], ["i", "k"], False],
    "ay": [["EY2"], ["ee"], False],
    "or": [["ER0"], ["a", "r"], False],
    "ship": [["SH", "IH2", "P"], ["sh", "i", "p"], False],
    "th": [["TH"], ["th"], False],
    "ful": [["F", "AH0", "L"], ["f", "u", "l"], False],
    "ing": [["IH0", "NG"], ["i", "q", "g"], False],
    "y": [["IY0"], ["ii"], True],
    "ns": [["Z"], ["s"], True],
    "bs": [["Z"], ["s"], True],
    "ds": [["Z"], ["s"], True],
    "ches": [["Z"], ["s"], True],
    "ces": [["Z"], ["s"], True],
    "ses": [["Z"], ["s"], True],
    "[aeiou]rs": [["Z"], ["s"], True],
    "[iou]se": [["S"], ["Z"], True],
    "ess": [["AH0", "S"], ["EH0", "S"], False],
}

# the first list is just the representation. Need not be exactly same.
# It just remove that many phones and add the ones in the second column
# Third column is isStrict. This will check for exact match of first list
# while replacing.
PREFIXRULES = {
    "anti": [["AE1", "N", "T", "IY0"], ["AE", "N", "T", "IY"], False],
    "auto": [["AO0", "T", "AH0"], ["ax", "tx", "o"], False],
    "down": [["D", "AW1", "N"], ["D", "AW", "N"], False],
    "ext": [["EH2", "K", "S", "T"], ["EH", "K", "S", "T"], False],
    "hyper": [["HH", "AY2", "P", "ER0"], ["HH", "AY", "P", "ER"], False],
    "in": [["IH2", "N"], ["IH", "N"], False],
    "out": [["UW1", "T"], ["AW", "T"], False],
    "super": [["S", "UW1", "P", "ER0"], ["S", "UW", "P", "ER"], False],
    "under": [["AH1", "N", "D", "ER0"], ["AH", "N", "D", "ER"], False],
    "up": [["AH1", "P"], ["AH", "P"], False],
}


# "rule name": [[source letter], [corresponding phone], [replacement phone], syll pos, isStrict]
# syll pos 0-non positional 1 - first , 2 - mid, 3 - last
# Third column is isStrict. This will check for exact match of first list
# while replacing. (This is for future extension)
SYLLRULES = {
    "ruleAH88": [["O-"], ["AH-"], ["o-"], 0, True],
    "ruleAH89": [["I-"], ["AH-"], ["i-"], 0, True],
    "ruleEH80": [["A-"], ["EH-"], ["AH-"], 0, True],
    "rule1": [["E-"], ["AH-"], ["i-"], 0, True],  # for me EH is better
    "rule2": [["O-"], ["AA-"], ["ax-"], 0, True],
    "rule3": [["O"], ["AA"], ["ax"], 0, True],
    "rule4": [["O"], ["AA-"], ["ax-"], 0, True],
    "rule5": [["-O"], ["AA"], ["ax"], 0, True],
    "rule5junked": [["O"], ["AA2"], ["ax"], 1, True],
    "rule6": [["A-"], ["EH-"], ["ei-"], 1, True],
    "rule7junked": [["A-"], ["EH2"], ["ei"], 1, True],
}

# "rule name": [[source letter sequence], [corresponding phone seq], [replacement phone seq]]
SEQRULES = {
    "rule7UL": [["*", "U", "L"], ["Y", "AH", "L"], ["*", "u", "l"]],
    "rule8TIF": [["T", "I", "F"], ["T", "AH", "F"], ["T", "i", "F"]],
}

# Final mapping of all phones to common set(IE map).
IEMAP = {
    "AE": "ae",
    "AO": "ax",
    "IH": "i",
    "OW": "ou",
    "UH": "u",
    "B": "b",
    "CH": "c",
    "D": "dx",
    "F": "f",
    "G": "g",
    "HH": "h",
    "JH": "j",
    "K": "k",
    "L": "l",
    "M": "m",
    "N": "n",
    "NX": "NG",
    "P": "p",
    "R": "r",
    "S": "s",
    "SH": "sx",
    "T": "tx",
    "TH": "th",
    "Y": "y",
    "Z": "z",
    "d": "DH",
    "ng": "NG",
    "AA": "aa",
}

ASRMAP = {
    "rx": "r",
    "kq": "k",
    "khq": "kh",
    "zh": "lx",
    "nd": "n",
    "sh": "sx",
    "gq": "g",
    "dxq": "dx",
    "dxhq": "dxh",
    "w": "W",
}
