#include "pch.h"
/*
	Free 3.0互联
*/

int atBit(int pos) {
	return 1 << (pos - 1);
}



//把字符wasd转换为方向键
int Directed(int ch) {
	if (ch == 'w') ch = UP_KEY;
	else if (ch == 's') ch = DOWN_KEY;
	else if (ch == 'a') ch = LEFT_KEY;
	else if (ch == 'd') ch = RIGHT_KEY;
	return ch;
}

//返回十进制int的长度，传入0返回1
int IntLength(int x) {
	int len = 0;
	do ++len; while (x /= 10);
	return len;
}

//返回字符串转换的int，接受前导无用字符。若string长度 > 9，返回TOO_LONG。
int StringtoInt(string str) {
	int len = str.length(), res = 0;
	if (len > 9)
		return TOO_LONG;
	int i = 0;
	while (!isdigit(str[i]) and i <= len - 1)
		++i;
	while (isdigit(str[i]) and i <= len - 1)
		res = res * 10 + (str[i] - '0'), ++i;
	return res;
}

//返回无符号int转换的string
string InttoString(int x) {
	string res = "";
	while (x >= 10) {
		res = (char)(x % 10 + '0') + res;
		x /= 10;
	}
	res = (char)(x + '0') + res;
	return res;
}

//0.0 ~ 1.0随机实数
double Random(int siz) {
	return (double)(rand() % (siz + 1)) / (double)(siz);
}

int RandLR(int l, int r) {
	if (l > r)
		return EOF;
	return l + (rand() % (r - l + 1));
}

//根据概率发生
bool Happen(double prob, int siz) {
	if (prob >= 1.0)
		return true;
	while (prob < 0.1) {
		if (Random(siz - 1) >= 0.1)
			return false;
		prob *= 10.0;
	}
	return Random(siz) < prob;
}

//以mid为平均值，ran为双臂生成随机实数
double RandAround(double mid, double ran) {
	return mid + ran * Random() * ((rand() % 2) ? 1.0 : -1.0);
}



//二次函数
double f_Qua(double x, double qua, double pri, double con) {
	return x * x * qua + x * pri + con;
}
