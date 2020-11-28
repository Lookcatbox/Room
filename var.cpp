#include "pch.h"
/*
	这是Free 3.0的变量定义代码
*/
//存档识别用的版本号

Vnum V, FileV;
Vnum Vn(int Maj, int Min, int Rel, int Bui) {
	Vnum V;
	V.Maj = Maj;
	V.Min = Min;
	V.Rel = Rel;
	V.Bui = Bui;
	return V;
}

int blocknum;//背包容量
int place, sx, sy;//地点和位置
int money, watch, reward_meal, work_score;//基本物品的数目

Blockinfo block[21];//背包
int task_rate[21];//任务进度
long long timein;//内时间（Free游戏内时间）
long long step;//步数

//设置，也要存档 
int colorable, flashable;//设置
unsigned int code_style;//打字机代码风格

//用于全局的临时变量
bool remap, inpack;//界面标记
int tx, ty;//上一步
int state[21], statechange[21];//状态，状态是否变化
long long day, hour, minute, second;//内时间实时转换成日、时、分、秒
HWND free_handle;//全局窗口句柄
HANDLE output_handle, input_handle;//全局标准输入输出句柄

int light, alpha, font_size;//界面显示

//for All Faces
bool border;//是否有边框
//for Areas
const char *map_file;//该场景地图文件
double ins_coe;//环境脏乱差系数
int move_unit_time;//单位移动时间

//buffer
int r;//Input(1)，存入单个字符
string s;//Input(2)，存入字符串
int n;//Input(3)，存入数字
char atlas[25][65];//地图，被迫不能叫作map
bool maping[25][65];//地图的改点是否已经被输出

CHAR_INFO face_map[yMax * xMax];//缓存界面上的字符，通过GetFace()获得的

Bodyinfo me;//我的身体信息

Bankinfo city_bank;//城市银行

//局内细节变量
int CME;//连续的移动错误

//列表
int decision[1100];
/*
1:花瓶破碎
2:花瓶任务4-1的决定
*/