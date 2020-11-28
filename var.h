#pragma once

#include "inter.h"
/*
	这是Free 3.0的变量定义区
*/
//存档识别用的版本号
struct VersionNumber {
	int Maj;//主版本号
	int Min;//子版本号
	int Rel;//修正版本号
	int Bui;//编译版本号
	string Desc() {//版本字符串
		return InttoString(Maj) + "." + InttoString(Min) + "." + InttoString(Rel) + "." + InttoString(Bui);
	}
	bool operator < (const char *str) { return Desc() < (string)(str); }
	bool operator > (const char *str) { return Desc() > (string)(str); }
	bool operator == (const char *str) { return Desc() == (string)(str); }
	bool operator <= (const char *str) { return Desc() <= (string)(str); }
	bool operator >= (const char *str) { return Desc() >= (string)(str); }

	bool operator < (const Vnum t) {
		if (Maj != t.Maj)
			return Maj < t.Maj;
		if (Min != t.Min)
			return Min < t.Min;
		if (Rel != t.Rel)
			return Rel < t.Rel;
		if (Bui != t.Bui)
			return Bui < t.Bui;
		return false;
	}
	bool operator == (const Vnum t) {
		return Maj == t.Maj and
			Min == t.Min and
			Rel == t.Rel and
			Bui == t.Bui;
	}
	bool operator <= (const Vnum t) { return *this < t or *this == t; }
	bool operator > (const Vnum t) { return not(*this <= t); }
	bool operator >= (const Vnum t) { return not(*this < t); }
};

extern Vnum V, FileV;

Vnum Vn(int Maj, int Min, int Rel, int Bui);

//属性、物品数量：
extern int blocknum;
extern int place, sx, sy;
extern int money, watch, reward_meal, work_score;
struct Blockinfo {
	int itm;
	int num;
};
extern Blockinfo block[21];
extern int task_rate[21];
extern long long timein;
extern long long step;

//设置，也要存档 
extern int colorable, flashable;
extern unsigned int code_style;

//用于全局的临时变量
extern bool remap, inpack;
extern int tx, ty;
extern int state[21], statechange[21];
extern long long day, hour, minute, second;
extern HWND free_handle;
extern HANDLE output_handle, input_handle;

extern int light, alpha, font_size;

//for All Faces
extern bool border;
//for Areas
extern const char *map_file;
extern double ins_coe;
extern int move_unit_time;

//buffer
extern int r;
extern string s;
extern int n;
extern char atlas[25][65];
extern bool maping[25][65];

extern CHAR_INFO face_map[yMax * xMax];

class Bodyinfo {

public:
	int phy;
	double life;
	double pro;
	double fat;
	double car;
	double can;
	long long awake_time;
	double sick;

	double ene;
	double nut_ave;
	double mus;
	double ent;

	double l;
	double h;
	long long TS;
	double Floor;

	bool Examine() {
		l = life / phy;

		ene = pro * kProEne + fat * kFatEne + car * kCarEne;
		h = ene / kDailyEne;

		nut_ave = (pro / kDailyPro + fat / kDailyFat + car / kDailyCar) / 3.0;


		TS = noLess(awake_time - 16 hours, 0);
		Floor = (double)(TS) / (double)(16 hours);

		mus = pow(
			kEffBase,
			1.00
			- awayfrom(ene / kDailyEne, 0.45, 0.90)
			- abs(pro - kProMus) / kDailyPro / 3.0
			- abs(fat - kFatMus) / kDailyFat / 3.0
			- abs(car - kCarMus) / kDailyCar / 3.0
			- (double)(TS) / (double)(36 hours)
		);

		ent = -1.00
			+ sick / 4.0 / mus
			+ awayfrom(ene / kDailyEne, 0.45, 0.90) * 1.5
			+ sq(abs(pro / kDailyPro - nut_ave)) / 2.0
			+ sq(abs(fat / kDailyFat - nut_ave)) / 2.0
			+ sq(abs(car / kDailyCar - nut_ave)) / 2.0
			+ can / kDailyCan / 4.0
			+ (double)(TS) / (double)(24 hours);


		return true;
	}

	bool NewBorn() {
		phy = kStdPhy;//读取存档会按照存档来
		life = 96.0;
		pro = 0.48 * kDailyPro;
		fat = 0.48 * kDailyFat;
		car = 0.48 * kDailyCar;
		can = 0.48 * kDailyCan;
		awake_time = 0;
		sick = 0.24;

		Examine();
		return true;
	}

/*	int StateTurn(int c, int tar) {
		if (State[c] == tar)
			return NONE;//就算状态没有改变，也不要改动标记
		if (State[c] < tar) {
			State[c] = tar;
			StateChange[c] = UP;//闪烁待用
			return UP;
		}
		State[c] = tar;
		StateChange[c] = DOWN;
		return DOWN;
	}*/

	bool ScanFile(FILE *Stream) {
		if (between(FileV, Vn(3, 0, 2, 0), Vn(3, 0, 2, 10))) {
			fscanf_s(Stream, "%lf %d %lf %lf %lf %lf %lld", &life, &phy, &pro, &fat, &car, &can, &awake_time);
			fscanf_s(Stream, "%lf", &sick);
			Examine();
			return true;
		}
		return false;
	}
	bool PrintFile(FILE *Stream) {
		fprintf(Stream, "%.6lf %d %.6lf %.6lf %.6lf %.6lf %lld\n", life, phy, pro, fat, car, can, awake_time);
		fprintf(Stream, "%.6lf\n", sick);
		return true;
	}
protected:
};

extern Bodyinfo me;

class Bankinfo {
	double rate;
	double lim;
public:
	bool Init() {
		depo = 0;
		system_day = 0;

		rate = 0.0097;
		lim = 50000.0 / (1 + rate);
		return true;
	}

	bool Grow() {
		while (day > system_day) {
			if (depo <= lim)
				depo = depo + depo * rate;
			++system_day;
		}
		return true;
	}

	bool Deposit(double moneyin) {
		depo = depo + moneyin;
		return true;
	}
	
	bool Draw(int moneyout) {
		if (depo >= moneyout) {
			depo = depo - (double)(moneyout);
			return true;
		}
		return false;
	}
	int GetDepo() {
		return (int)(depo);
	}
	bool ScanFile(FILE *stream) {
		if (between(FileV, Vn(3, 0, 2, 0), Vn(3, 0, 2, 10))) {
			fscanf_s(stream, "%lld %lf", &system_day, &depo);
			return true;
		}
		return false;
	}
	bool PrintFile(FILE *stream) {
		fprintf(stream, "%lld %.6lf\n", system_day, depo);
		return true;
	}
protected:
	long long system_day;
	double depo;
};
extern Bankinfo city_bank;

extern int CME;

extern int decision[1100];
/*
1:花瓶破碎
2:花瓶任务4-1的决定
*/