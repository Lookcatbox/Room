#pragma once
/*
	Free 3.0����
*/

#ifndef MSVC

#define fscanf_s fscanf
#define wcscpy_s wcscpy

#endif

#define Vnum VersionNumber

//��t��...���ñ���x
#define repeat(t,x) for (int x = 1; x <= t; ++x)

//������д
#define P Printl

#define days * 86400LL
#define hours * 3600LL
#define minutes * 60LL
#define seconds * 1LL

//ǿ�������ڼ���
#define there > 0

#define e (2.718281828)

//���ڴ���
#define xMax 20
#define yMax 60

//һЩ��Ʒ
#define COOKIE (1)
#define BOOK_OF_SELFCARE (6)
#define Rx (7)//����ҩ�����

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
#define THINK (1)//��٩ 
#define WALK (2)
#define WRITE (3)
#define TYPE (4)
#define FIX (5)//�ӻ�
#define SLEEP (6)
#define EAT (7)

//�̶�
#define ENTER (13)
#define ESC (27)
#define BACKSPACE (8)
#define DIR_KEY (224)

//�Զ��� 
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

//����ֵ
#define abs(x) ( ((x) < 0) ? -(x) : (x))
//�ж�x�ǲ��ǽ���flo��top֮��
#define between(x, flo, top) (x >= flo and x <= top)
//�õ�x����flo-top�߶ζ�Զ�����߶���ʱ����0
#define awayfrom(x, flo, top) ((between(x, flo, top)) ? (0) : ( (x < flo) ? (flo - x) : (x - top) ))
//�Ƿ��Ǵ�д��ĸ
#define isupper(x) (between(x, 'A', 'Z'))
//�Ƿ���Сд��ĸ
#define islower(x) (between(x, 'a', 'z'))
//�ǲ�������
#define isdigit(x) (between(x, '0', '9'))
//�ǲ��Ǳ�׼�ַ���ʶ�����ĵ�������ţ�
#define ischar(x) (between(x, 32, 126))

//�ܸ���͸��󣬱�������
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

//�ǲ��ǿ�ͨ���ķ���
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

//ת��&xΪy������ת�����(NONE, UP, DOWN)
//ת��&xΪy������ת�����(NONE, UP, DOWN)
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

//����xѹ��blo��top֮����ֵ
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

//ʹx��С��flo
template <typename _typeA, typename _typeB>
bool noLessed(_typeA &x, _typeB flo) {
	if (x < flo) {
		x = flo;
		return true;
	}
	return false;
}


//����x������top��ֵ
template <typename _typeA, typename _typeB>
_typeA noMore(_typeA x, _typeB top) {
	if (x > top)
		return top;
	return x;
}

//ʹx������top
template <typename _typeA, typename _typeB>
bool noMored(_typeA &x, _typeB top) {
	if (x > top) {
		x = top;
		return true;
	}
	return false;
}

//Ӧ������Ļ����ʾ�ķ��š��Ķ��˺������ı���档���������Map�����������Ż�����
template <typename _type>
_type Maped(_type ch) {
	if (ch == '`' or (islower(ch) and ch != 'o')) {
		return ' ';
	}
	if (isupper(ch))
		return 'X';
	return ch;
}

//��x[]�������������һ��Ԫ��
template <typename _type>
_type RandS(int num, _type a[]) {
	return a[rand() % num];
}

//ƽ��
template <typename _type>
_type sq(_type x) {
	return x * x;
}

int atBit(int pos);

//���ַ�wasdת��Ϊ�����
int Directed(int ch);

//����ʮ����int�ĳ��ȣ�����0����1
int IntLength(int x);

//�����ַ���ת����int������ǰ�������ַ�����string���� > 9������TOO_LONG��
int StringtoInt(string str);

//�����޷���intת����string
string InttoString(int x);

//0.0 ~ 1.0���ʵ��
double Random(int siz = 1000);

int RandLR(int l, int r);

//���ݸ��ʷ���
bool Happen(double prob, int siz = 1000);

//��midΪƽ��ֵ��ranΪ˫���������ʵ��
double RandAround(double mid, double ran);

//���κ���
double f_Qua(double x, double qua, double pri, double con);
