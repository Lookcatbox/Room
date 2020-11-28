#pragma once
/*
	Free 3.0互联
*/

#ifndef MSVC

#define fscanf_s fscanf
#define wcscpy_s wcscpy

#endif

#define Vnum VersionNumber

//做t次...借用变量x
#define repeat(t,x) for (int x = 1; x <= t; ++x)

//函数简写
#define P Printl

#define days * 86400LL
#define hours * 3600LL
#define minutes * 60LL
#define seconds * 1LL

//强调：存在即可
#define there > 0

#define e (2.718281828)

//关于窗口
#define xMax 20
#define yMax 60

//一些物品
#define COOKIE (1)
#define BOOK_OF_SELFCARE (6)
#define Rx (7)//处方药的许可

//some ItemType
#define FOOD (1)
#define BOOK (2)
#define PERM (3)
#define DRUG (4)

//State
#define LIFE (1)
#define HUNGER (2)
#define SLEEPINESS (3)
#define MUSCLE (4)
#define ENTROPY (5)
#define ILLNESS (6)

//Activity
#define FRESH (0)
#define THINK (1)//调侃 
#define WALK (2)
#define WRITE (3)
#define TYPE (4)
#define FIX (5)//杂活
#define SLEEP (6)
#define EAT (7)

//固定
#define ENTER (13)
#define ESC (27)
#define BACKSPACE (8)
#define DIR_KEY (224)

//自定义 
//#define UP (1)
#define NONE (0)
//#define DOWN (-1)

#define TOO_LONG (-128)
#define UP_KEY (-72)
#define DOWN_KEY (-80)
#define LEFT_KEY (-75)
#define RIGHT_KEY (-77)
#define DEL_KEY (-83)

#define TACTIC (1)
#define UNFOLD (2)
#define REVERSE (3)

//CodeStyles
#define TIGHT (atBit(1))

#define ORDER (1)
#define STRING (2)
#define INTEGER (3)

#define JUMP (202)

//Place
#define CITY (110000)

#define HOME (110100)
#define BEDROOM (110101)
#define KITCHEN (110102)

#define SUPERMATKET (110200)

#define WRITING (110300)
#define TYPIST (110301)

#define SCHOOL (110400)
#define SCHOOL_1F (110401)
#define SCHOOL_2F (110402)
#define SCHOOL_3F (110403)
#define SCHOOL_HIDE (110404)

#define HOSPITAL (110500)
#define INTERNAL (110501)

#define WEAPONSHOP (110600)

#define NEIGHBOR (110700)
#define NEIGHBOR_2F (110701)
#define NEIGHBOR_BEDROOM (110702)

#define BANK (110800)

#define ZOO_EAST (110900)
#define ZOO_NORTH_EAST (110901)
#define ZOO_NORTH (110902)
#define ZOO_MIDDLE (110903)
#define ZOO_NORTH_WEST (110904)
#define ZOO_WEST (110905)
#define ZOO_OFFICE (110906)

#define TASK (210100)
#define POCKET (210200)
#define BAG (210201) 

#define PLAYGROUND (111000)

//绝对值
#define abs(x) ( ((x) < 0) ? -(x) : (x))
//判断x是不是介于flo和top之间
#define between(x, flo, top) (x >= flo and x <= top)
//得到x距离flo-top线段多远。在线段中时返回0
#define awayfrom(x, flo, top) ((between(x, flo, top)) ? (0) : ( (x < flo) ? (flo - x) : (x - top) ))
//是否是大写字母
#define isupper(x) (between(x, 'A', 'Z'))
//是否是小写字母
#define islower(x) (between(x, 'a', 'z'))
//是不是数字
#define isdigit(x) (between(x, '0', '9'))
//是不是标准字符（识别中文等特殊符号）
#define ischar(x) (between(x, 32, 126))

//能更大就更大，表达更新义
template <typename _typeA, typename _typeB>
bool Maxed(_typeA &host, _typeB guest) {
	if (guest > host) {
		host = guest;
		return true;
	}
	return false;
}

template <typename _typeA, typename _typeB>
bool Mined(_typeA &host, _typeB guest) {
	if (guest < host) {
		host = guest;
		return true;
	}
	return false;
}

//是不是可通过的符号
template <typename _type>
bool iswall(_type ch) {
	return
		ch == '|' or
		ch == '-' or
		ch == '+' or
		ch == 'o' or
		ch == '/' or
		ch == '\\' or
		ch == '[' or
		ch == ']' or
		ch == '=' or
		!ischar(ch);
}

//转换&x为y，返回转换情况(NONE, UP, DOWN)
//转换&x为y，返回转换情况(NONE, UP, DOWN)
template <typename _typeA, typename _typeB>
int Turn(_typeA &x, _typeB y) {
	if (x == y)
		return NONE;
	if (x < y) {
		x = y;
		return 1;
	}
	x = y;
	return -1;
}

//返回x压入blo和top之间后的值
template <typename _typeA, typename _typeB>
_typeA Between(_typeA x, _typeB flo, _typeB top) {
	if (between(x, flo, top))
		return x;
	if (x < flo)
		return flo;
	return top;
}

template <typename _typeA, typename _typeB>
bool noLess(_typeA x, _typeB flo) {
	if (x < flo)
		return flo;
	return x;
}

//使x不小于flo
template <typename _typeA, typename _typeB>
bool noLessed(_typeA &x, _typeB flo) {
	if (x < flo) {
		x = flo;
		return true;
	}
	return false;
}


//返回x不大于top的值
template <typename _typeA, typename _typeB>
_typeA noMore(_typeA x, _typeB top) {
	if (x > top)
		return top;
	return x;
}

//使x不大于top
template <typename _typeA, typename _typeB>
bool noMored(_typeA &x, _typeB top) {
	if (x > top) {
		x = top;
		return true;
	}
	return false;
}

//应当在屏幕上显示的符号。改动此函数将改变界面。若配合其他Map函数，可以优化界面
template <typename _type>
_type Maped(_type ch) {
	if (ch == '`' or (islower(ch) and ch != 'o')) {
		return ' ';
	}
	if (isupper(ch))
		return 'X';
	return ch;
}

//从x[]数组中随机返回一个元素
template <typename _type>
_type RandS(int num, _type a[]) {
	return a[rand() % num];
}

//平方
template <typename _type>
_type sq(_type x) {
	return x * x;
}

int atBit(int pos);

//把字符wasd转换为方向键
int Directed(int ch);

//返回十进制int的长度，传入0返回1
int IntLength(int x);

//返回字符串转换的int，接受前导无用字符。若string长度 > 9，返回TOO_LONG。
int StringtoInt(string str);

//返回无符号int转换的string
string InttoString(int x);

//0.0 ~ 1.0随机实数
double Random(int siz = 1000);

int RandLR(int l, int r);

//根据概率发生
bool Happen(double prob, int siz = 1000);

//以mid为平均值，ran为双臂生成随机实数
double RandAround(double mid, double ran);

//二次函数
double f_Qua(double x, double qua, double pri, double con);
