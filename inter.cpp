#include "pch.h"
/*
	Free 3.0����
*/

int atBit(int pos) {
	return 1 << (pos - 1);
}



//���ַ�wasdת��Ϊ�����
int Directed(int ch) {
	if (ch == 'w') ch = UP_KEY;
	else if (ch == 's') ch = DOWN_KEY;
	else if (ch == 'a') ch = LEFT_KEY;
	else if (ch == 'd') ch = RIGHT_KEY;
	return ch;
}

//����ʮ����int�ĳ��ȣ�����0����1
int IntLength(int x) {
	int len = 0;
	do ++len; while (x /= 10);
	return len;
}

//�����ַ���ת����int������ǰ�������ַ�����string���� > 9������TOO_LONG��
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

//�����޷���intת����string
string InttoString(int x) {
	string res = "";
	while (x >= 10) {
		res = (char)(x % 10 + '0') + res;
		x /= 10;
	}
	res = (char)(x + '0') + res;
	return res;
}

//0.0 ~ 1.0���ʵ��
double Random(int siz) {
	return (double)(rand() % (siz + 1)) / (double)(siz);
}

int RandLR(int l, int r) {
	if (l > r)
		return EOF;
	return l + (rand() % (r - l + 1));
}

//���ݸ��ʷ���
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

//��midΪƽ��ֵ��ranΪ˫���������ʵ��
double RandAround(double mid, double ran) {
	return mid + ran * Random() * ((rand() % 2) ? 1.0 : -1.0);
}



//���κ���
double f_Qua(double x, double qua, double pri, double con) {
	return x * x * qua + x * pri + con;
}
