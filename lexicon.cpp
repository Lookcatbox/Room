#include "pch.h"
/*
	这是Free 3.0的常量库，存储打字室的单词、物品属性等
*/
const int FLASH_SPAN = 90;//闪烁间隔常数，单位：毫秒
const int SPL_SPEAK = 20, SPS_SPEAK = 750;//对话时Printl的字符间隔和句子间隔
const int SPL_THINK = 15, SPS_THINK = 900;//思考时Printl的字符间隔和句子间隔

const int kStatecnt = 6;//一共有几种状态
const Stateinfo kStateBoard[21] = {
	{},
	{2,  {"死亡", "垂危", "体虚", "    ", "气盈"}, {0, DOWN, DOWN, 0, 0}, 3},
	{4,  {"饥昏", "饥饿", "空腹", "    ", "饱足", "腹胀"}, {DOWN, DOWN, 0, 0, 0, UP}, 3},
	{5,  {"憔悴", "困倦", "    ", "清醒"}, {DOWN, DOWN, 0, 0}, 2},
	{7,  {"滞笨", "迟缓", "    ", "矫健"}, {DOWN, DOWN, 0, 0}, 2},
	{8,  {"失调", "    ", "平衡"}, {DOWN, 0, 0}, 2},
	{9,  {"衰竭", "恶疾", "伤风", "咳嗽", "    "}, {DOWN, DOWN, DOWN, DOWN, 0}, 4}
	//{9, {"", "感染"}}
};

const int kTaskSeriecnt = 9;//任务系列数
const Taskinfo kTask[21] = {
	{},
	{4, {"", "生计", "要面包，不要战争! ", "NP完全问题", "陌生人的最后一条消息"}},
	{2, {"", "人脉"}},
	{2, {"", "校长的困境"}},
	{2, {"", "未名之家"}},
	{}
};

const int kDecicnt = 10;//重决策计数
const int kBirdcnt = 4, kInsectcnt = 3, kChewcnt = 6, kHitcnt = 3,//一些常见音效的文件数
kCoughcnt = 3;

const Foodinfo kFood[110] = {
	{},
	{15,                   335,    0.327273,  0.954545,  2.959545,  0.017,    "Chew"},//需要100片才能获得8500能量
	{3 minutes,            950,    7.02,      7.02,      43.11,     0.067,    "Chew"},//8
	{14 minutes,           2850,   15.876,    10.368,    52.488,    0.105,    "Chew"},//5~6
	{13 minutes,           2800,   67.2,      50.1,      0.3,       0.545,    "Chew"},//3
	{52,                   750,    7.7,       1.232,     1.76,      0.077,    "Chew"},//40+
	{}
};

const Bookinfo kBook[110] = {
	{},
	{"BookofSelfcare", 5, 27},
	{}
};

const Perminfo kPerm[110] = {
	{},
	{"字迹实在潦草，只能依稀辨认签名。"},
};

const Druginfo kDrug[110] = {
	{},
	{},
	{}
};

const char *ItemTypeDesc[110] = {//物品品种中文名称
	"",
	"食物",
	"读物",
	"药品"
};

const Iteminfo kItem[1100] = {
	{},
	{"饼干",     "片", FOOD, 1,   22,  false}, 
	{"面包",     "块", FOOD, 2,   0,   false},
	{"炒饭",     "份", FOOD, 3,   0,   false},
	{"烤鸡",     "只", FOOD, 4,   0,   false},
	{"牛肉棒",   "根", FOOD, 5,   0,   false},
	{"保健手册", "本", BOOK, 1,   1,   true},
	{"处方许可", "张", PERM, 1,   1,   true},
	{"感冒冲剂", "包", DRUG, 1,   4,   false},
	{"抗生素",   "粒", DRUG, 2,   12,  false},
	{}
};

const int kActcnt = 7;//动作的个数
const Actinfo kAct[21] = {
	            //Pro    //Fat    //Car    //Can
	{"更新",     0.000,   0.000,   0.000,   0.000,   0},
	{"思考",     0.600,   0.300,   0.600,   0.375,   0},
	{"行走",     0.750,   1.100,   1.000,   1.750,   1},//能量消耗大约是标准情况
	{"写字",     0.750,   0.450,   0.900,   0.650,  1},
	{"打字",     0.896,   0.512,   0.768,   -0.128,  1},
	{"改正",     0.750,   0.450,   0.750,   0.500,   0},
	{"睡眠",     0.450,   0.250,   0.350,   0.125,   0},
	{"进食",     0.750,   0.450,   0.900,   0.000,   0}
};

const double kProEne = 17.15, kFatEne = 38.91, kCarEne = 17.15;//每克营养素提供能量
const double kDailyPro = 60.0, kDailyFat = 60.0, kDailyCar = 300.0, kDailyCan = 1.00;//每日标准物质摄入量
const double kProMus = 108.0, kFatMus = 15.0, kCarMus = 260.0;//强健体质的标准营养保持
const double kDailyEne = kDailyPro * kProEne + kDailyFat * kFatEne + kDailyCar * kCarEne;//每日标准能量
const double kSecondCoe = 0.00001157, kLossBase = 1.00 + 1.00 / e, kEffBase = 1.00 + 1.00 / e;//影响常数
const int kStdPhy = 100;//标准体力（生命上限），是integer

const int kWordcnt = 217;//词汇书目
const string kLexicon[410] = {//词汇分配库
"include", "iostream", "cstdio", "int", "double", "float", "long", "bool", "cin", "cout", //1
"printf", "scanf", "while", "for", "return", "main", "flag", "char", "string", "using", //2
"namespace", "std", "if", "void", "max", "min", "queue", "vector", "set", "list", //3
"gets", "algorithm", "map", "cmath", "stack", "iomanip", "dfs", "bfs", "define", "short", //4
"const", "unsigned", "memset", "memcpy", "time", "do", "sizeof", "strlen", "length", "switch", //5
"true", "false", "case", "inline", "insert", "pop", "push", "clear", "delete", "typedef", //6
"break", "continue", "auto", "freopen", "fclose", "stdin", "stdout", "heap", "operator", "struct", //7
"class", "register", "srand", "rand", "sort", "else", "dp", "kmp", "rmq", "splay", //8
"public", "erase", "priority", "multiset", "deque", "dijkstra", "spfa", "floyd", "automaton", "tarjan", //9
"manacher", "multimap", "back", "empty", "front", "getchar", "putchar", "getline", "puts", "ctime", //10
"sqrt", "pow", "abs", "fabs", "floor", "ceil", "log", "subtree", "null", "default", //11
"stirling", "swap", "clear", "find", "equal", "fill", "reverse", "lower", "bound", "binary", //12
"search", "upper", "range", "merge", "make", "next", "prev", "permutation", "exit", "system", //13
"pause", "gcd", "substr", "input", "output", "sync", "base", "with", "ios", "stdio", //14
"fstream", "fin", "fout", "ifstream", "ofstream","pragma", "typeid", "catch", "virtual", "asm", // 15
"program", "var", "integer", "real", "longint", "read", "write", "array", "begin", "}", //16
"randomize", "random", "then", "of", "div", "mod", "record", "to", "downto", "repeat", //17
"null", "until", "goto", "and", "or", "xor", "forward", "procedure", "long long", "main", //18 
"what", "tree", "today", "type", "goose", "lexicon", "interface", "function", "zone", "int n;",//19
"cnt`=`9;", "install", "uninstall", "settings", "soft", "development", "#undef div",
"scanf(\"%d\",`&n);", "free", "new", //20
"#include`<algorithm>", "#include`<iostream>", "for(int i`=`1;`i`<=`n;`i++)", "while(len--)", "char *a",
"#include`<cctype>", "#include`<ctime>", "inc(i);", "for i`:=`1 to n do", "printf(\"%d\\n\",`n);",//21
"private", "public", "first", "second", "prefix", "using std::string;" "extern",
""
};

const int kFuncnt = 53;//无效移动时出现连续的提示最大数目
const char *kErrorFun[110] = {//无效移动时出现连续的提示
	"",
	"挥了一下手臂。",
	"观察了一下手掌。",
	"哪儿来的凉风。",
	"感觉心脏少跳了一下。",
	"揪了一下眉毛。",
	"突然想练习射箭。",
	"扯了一下头发。",
	"没人看着我吧？",
	"驼背了。", "背挺直了。",//10
	"驼背了。", "背挺直了。",
	"驼背了。", "背挺直了。",
	"驼背了。", "背挺直了。",
	"驼背了。", "背挺直了。",
	"记得到医院可以治病。",
	"记得卧室可以睡觉。",//20
	"卧室不能睡觉。",
	"但我能睡觉。",
	"\"你的饱食度是10，你饿了! 请吃东西! \"",
	"\"时空\"、\"遨游\"、\"诠释\"、\"经典\"...",
	"\"你太薄了! \"",
	"\"你太饱了! \"",
	"以前银行存钱后不久再访问银行系统会导致崩溃。",
	"记得在小岛上很容易生病。",
	"想起打比武大会时的越战越勇。",
	"想起刺客手下不留情。",//30
	"仔细考虑一下。",
	"冷静分析一下。",
	"穿衣服使人变重。",
	"护符似乎能让人感到活力，那只是心理作用吧。",
	"现在仍偏向于过去，他曾因此改动自由密码。",
	"但是过去的想法，不可得而知。",
	"过去时。",
	"过去将来时。",
	"过去将来现在完成时。",
	"璀璨宝剑需要12块铁、15块铜、5份火药和1块玉。",//40
	"辉光盔甲则要1块布、8张皮革、10块铁和1块玉。",
	"圣洁玉护符需要布革铁铜各1单位、30份火药和3块玉。",
	"孩子，那都是过去的事了。",
	"要保持身体健康，不要经常熬夜。",
	"一字节相当于一个英文字母。",
	"一千字节相当于胡思乱想到这里的文字量。",
	"一兆字节相当于一本小说的文字量。",
	"一吉字节相当于一卡车的纸的文字量。",
	"一太字节相当于地球观测系统每天产生的数据量。",
	"一拍字节相当于一半美国学术研究图书馆记载的信息量。",//50
	"一艾字节和人类说过的所有的话的信息量同级。",
	"一泽字节和人类说过所有的话的低质音频的信息量同级。",
	"h + q 可以查看所有快捷键。",
};
