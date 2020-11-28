#pragma once
/*
	这是Free 3.0的常量库，存储打字室的单词、物品属性等
*/
extern const int FLASH_SPAN;//闪烁间隔常数，单位：毫秒
extern const int SPL_SPEAK, SPS_SPEAK;//对话时Printl的字符间隔和句子间隔
extern const int SPL_THINK, SPS_THINK;//思考时Printl的字符间隔和句子间隔

extern const int kStatecnt;//一共有几种状态
struct Stateinfo {//状态栏提示
	int x;//显示时的纵坐标
	const char *desc[11];//两字中文描述
	int flash[11];//是否提示，以及以什么方式进入会提示
	int common;//给出一个默认状态
};
extern const Stateinfo kStateBoard[21];

extern const int kTaskSeriecnt;//任务系列数
struct Taskinfo {
	int cnt;
	const char *name[110];
};
extern const Taskinfo kTask[21];

extern const int kDecicnt;//重决策计数
extern const int kBirdcnt, kInsectcnt, kChewcnt, kHitcnt,//一些常见音效的文件数
kCoughcnt;

struct Foodinfo {
	long long use_time;//使用消耗的内部时间
	int delay;//使用延迟时间

	double pro;//蛋白质（每份含有量）
	double fat;//脂肪（每份含有量）
	double car;//糖类（每份含有量）
	double can;//致癌物（每份含有量）
	const char *file;//引用文件
};
extern const Foodinfo kFood[110];

struct Bookinfo {
	const char *file;
	int pagecnt;
	long long read_time;
};
extern const Bookinfo kBook[110];

struct Perminfo {
	const char *desc;
};
extern const Perminfo kPerm[110];

struct Druginfo {

};
extern const Druginfo kDrug[110];

extern const char *ItemTypeDesc[110];

struct Iteminfo {//物品信息
	const char *name;//中文名字
	const char *meas;//中文单位

	int type;//品种代号
	int code;//在品种中的代号

	int carry;//单格存放上限
	bool reusable;//可否多次使用
};
extern const Iteminfo kItem[1100];

extern const int kActcnt;//动作的个数
struct Actinfo {
	const char *name;//描述
	double pro_coe;//动作的蛋白质消耗系数。若为1，则在零度情况下，每日恰好消耗60g
	double fat_coe;//动作的脂肪消耗系数。若为1，则在零度情况下，每日恰好消耗60g
	double car_coe;//动作的消耗糖类系数。若为1，则在零度情况下，每日恰好消耗300g
	double can_coe;//动作的抗癌系数。若为1，则在零度情况下，每日恰好分解1单位致癌物
	bool effable;//动作耗时（内时）是否接受力量影响
};

extern const Actinfo kAct[21];

extern const double kProEne, kFatEne, kCarEne;//每克营养素提供能量
extern const double kDailyPro, kDailyFat, kDailyCar, kDailyCan;//每日标准物质摄入量
extern const double kProMus, kFatMus, kCarMus;//强健体质的标准营养保持
extern const double kDailyEne;//每日标准能量
extern const double kSecondCoe, kLossBase, kEffBase;//影响常数
extern const int kStdPhy;//标准体力（生命上限），是integer

extern const int kWordcnt;//词汇书目
extern const string kLexicon[410];

extern const int kFuncnt;//无效移动时出现连续的提示最大数目
extern const char *kErrorFun[110];
