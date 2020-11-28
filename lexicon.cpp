#include "pch.h"
/*
	����Free 3.0�ĳ����⣬�洢�����ҵĵ��ʡ���Ʒ���Ե�
*/
const int FLASH_SPAN = 90;//��˸�����������λ������
const int SPL_SPEAK = 20, SPS_SPEAK = 750;//�Ի�ʱPrintl���ַ�����;��Ӽ��
const int SPL_THINK = 15, SPS_THINK = 900;//˼��ʱPrintl���ַ�����;��Ӽ��

const int kStatecnt = 6;//һ���м���״̬
const Stateinfo kStateBoard[21] = {
	{},
	{2,  {"����", "��Σ", "����", "    ", "��ӯ"}, {0, DOWN, DOWN, 0, 0}, 3},
	{4,  {"����", "����", "�ո�", "    ", "����", "����"}, {DOWN, DOWN, 0, 0, 0, UP}, 3},
	{5,  {"��", "����", "    ", "����"}, {DOWN, DOWN, 0, 0}, 2},
	{7,  {"�ͱ�", "�ٻ�", "    ", "�ý�"}, {DOWN, DOWN, 0, 0}, 2},
	{8,  {"ʧ��", "    ", "ƽ��"}, {DOWN, 0, 0}, 2},
	{9,  {"˥��", "��", "�˷�", "����", "    "}, {DOWN, DOWN, DOWN, DOWN, 0}, 4}
	//{9, {"", "��Ⱦ"}}
};

const int kTaskSeriecnt = 9;//����ϵ����
const Taskinfo kTask[21] = {
	{},
	{4, {"", "����", "Ҫ�������Ҫս��! ", "NP��ȫ����", "İ���˵����һ����Ϣ"}},
	{2, {"", "����"}},
	{2, {"", "У��������"}},
	{2, {"", "δ��֮��"}},
	{}
};

const int kDecicnt = 10;//�ؾ��߼���
const int kBirdcnt = 4, kInsectcnt = 3, kChewcnt = 6, kHitcnt = 3,//һЩ������Ч���ļ���
kCoughcnt = 3;

const Foodinfo kFood[110] = {
	{},
	{15,                   335,    0.327273,  0.954545,  2.959545,  0.017,    "Chew"},//��Ҫ100Ƭ���ܻ��8500����
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
	{"�ּ�ʵ���ʲݣ�ֻ����ϡ����ǩ����"},
};

const Druginfo kDrug[110] = {
	{},
	{},
	{}
};

const char *ItemTypeDesc[110] = {//��ƷƷ����������
	"",
	"ʳ��",
	"����",
	"ҩƷ"
};

const Iteminfo kItem[1100] = {
	{},
	{"����",     "Ƭ", FOOD, 1,   22,  false}, 
	{"���",     "��", FOOD, 2,   0,   false},
	{"����",     "��", FOOD, 3,   0,   false},
	{"����",     "ֻ", FOOD, 4,   0,   false},
	{"ţ���",   "��", FOOD, 5,   0,   false},
	{"�����ֲ�", "��", BOOK, 1,   1,   true},
	{"�������", "��", PERM, 1,   1,   true},
	{"��ð���", "��", DRUG, 1,   4,   false},
	{"������",   "��", DRUG, 2,   12,  false},
	{}
};

const int kActcnt = 7;//�����ĸ���
const Actinfo kAct[21] = {
	            //Pro    //Fat    //Car    //Can
	{"����",     0.000,   0.000,   0.000,   0.000,   0},
	{"˼��",     0.600,   0.300,   0.600,   0.375,   0},
	{"����",     0.750,   1.100,   1.000,   1.750,   1},//�������Ĵ�Լ�Ǳ�׼���
	{"д��",     0.750,   0.450,   0.900,   0.650,  1},
	{"����",     0.896,   0.512,   0.768,   -0.128,  1},
	{"����",     0.750,   0.450,   0.750,   0.500,   0},
	{"˯��",     0.450,   0.250,   0.350,   0.125,   0},
	{"��ʳ",     0.750,   0.450,   0.900,   0.000,   0}
};

const double kProEne = 17.15, kFatEne = 38.91, kCarEne = 17.15;//ÿ��Ӫ�����ṩ����
const double kDailyPro = 60.0, kDailyFat = 60.0, kDailyCar = 300.0, kDailyCan = 1.00;//ÿ�ձ�׼����������
const double kProMus = 108.0, kFatMus = 15.0, kCarMus = 260.0;//ǿ�����ʵı�׼Ӫ������
const double kDailyEne = kDailyPro * kProEne + kDailyFat * kFatEne + kDailyCar * kCarEne;//ÿ�ձ�׼����
const double kSecondCoe = 0.00001157, kLossBase = 1.00 + 1.00 / e, kEffBase = 1.00 + 1.00 / e;//Ӱ�쳣��
const int kStdPhy = 100;//��׼�������������ޣ�����integer

const int kWordcnt = 217;//�ʻ���Ŀ
const string kLexicon[410] = {//�ʻ�����
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

const int kFuncnt = 53;//��Ч�ƶ�ʱ������������ʾ�����Ŀ
const char *kErrorFun[110] = {//��Ч�ƶ�ʱ������������ʾ
	"",
	"����һ���ֱۡ�",
	"�۲���һ�����ơ�",
	"�Ķ��������硣",
	"�о�����������һ�¡�",
	"����һ��üë��",
	"ͻȻ����ϰ�����",
	"����һ��ͷ����",
	"û�˿����Ұɣ�",
	"�ձ��ˡ�", "��ֱͦ�ˡ�",//10
	"�ձ��ˡ�", "��ֱͦ�ˡ�",
	"�ձ��ˡ�", "��ֱͦ�ˡ�",
	"�ձ��ˡ�", "��ֱͦ�ˡ�",
	"�ձ��ˡ�", "��ֱͦ�ˡ�",
	"�ǵõ�ҽԺ�����β���",
	"�ǵ����ҿ���˯����",//20
	"���Ҳ���˯����",
	"������˯����",
	"\"��ı�ʳ����10�������! ��Զ���! \"",
	"\"ʱ��\"��\"����\"��\"ڹ��\"��\"����\"...",
	"\"��̫����! \"",
	"\"��̫����! \"",
	"��ǰ���д�Ǯ�󲻾��ٷ�������ϵͳ�ᵼ�±�����",
	"�ǵ���С���Ϻ�����������",
	"����������ʱ��ԽսԽ�¡�",
	"����̿����²����顣",//30
	"��ϸ����һ�¡�",
	"�侲����һ�¡�",
	"���·�ʹ�˱��ء�",
	"�����ƺ������˸е���������ֻ���������ðɡ�",
	"������ƫ���ڹ�ȥ��������˸Ķ��������롣",
	"���ǹ�ȥ���뷨�����ɵö�֪��",
	"��ȥʱ��",
	"��ȥ����ʱ��",
	"��ȥ�����������ʱ��",
	"�貱�����Ҫ12������15��ͭ��5�ݻ�ҩ��1����",//40
	"�Թ������Ҫ1�鲼��8��Ƥ�10������1����",
	"ʥ���񻤷���Ҫ������ͭ��1��λ��30�ݻ�ҩ��3����",
	"���ӣ��Ƕ��ǹ�ȥ�����ˡ�",
	"Ҫ�������彡������Ҫ������ҹ��",
	"һ�ֽ��൱��һ��Ӣ����ĸ��",
	"һǧ�ֽ��൱�ں�˼���뵽�������������",
	"һ���ֽ��൱��һ��С˵����������",
	"һ���ֽ��൱��һ������ֽ����������",
	"һ̫�ֽ��൱�ڵ���۲�ϵͳÿ���������������",
	"һ���ֽ��൱��һ������ѧ���о�ͼ��ݼ��ص���Ϣ����",//50
	"һ���ֽں�����˵�������еĻ�����Ϣ��ͬ����",
	"һ���ֽں�����˵�����еĻ��ĵ�����Ƶ����Ϣ��ͬ����",
	"h + q ���Բ鿴���п�ݼ���",
};
