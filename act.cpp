#include "pch.h"

bool reNew() {//数据初始化到默认
	Randomize();

	me.NewBorn();

	money = 50; watch = 0;
	reward_meal = 0; work_score = 0;

	blocknum = 6;
	for (int i = 1; i <= blocknum; ++i)
		block[i].itm = 0, block[i].num = 0;

	for (int i = 1; i <= kTaskSeriecnt; ++i)
		task_rate[i] = 0;
	for (int i = 1; i <= kDecicnt; ++i)
		decision[i] = 0;

	timein = 6 hours;
	step = 0;

	place = HOME;
	sx = 8, sy = 34;//全局变量坐标
	CME = 0;

	colorable = true;
	flashable = true;
	code_style = 0;
	code_style &= ~TIGHT;//默认关闭紧凑的代码风格

	border = false;

	for (int i = 1; i <= kStatecnt; ++i)
		state[i] = kStateBoard[i].common, statechange[i] = NONE;

	city_bank.Init();
	return true;
}
//下一步 
long long Enter() {
	return ++step;
}

//有点点复杂
int Pitch(int num, const char *desc[], int dis, int pit, int ym, int x) {
	int Maxlen = 0;
	if (x == 0)
		x = GetBufferinfo().dwCursorPosition.Y + 1;
	for (int i = 0; i <= num - 1; ++i) {
		int len = strlen(desc[i]);
		Maxed(Maxlen, len);
		Position(x + i * dis, ym - (len - 1) / 2);
		printf("%s", desc[i]);
	}//文字输出结束
	const int yl = ym - (Maxlen - 1) / 2 - 2, yr = yl + Maxlen + 3;
	while (between(pit, 1, num)) {
		Position(x + (pit - 1) * dis, yl), putchar('[');
		Position(x + (pit - 1) * dis, yr), putchar(']');
		r = Directed(getord());
		if (r == ENTER or r == ESC)
			break;
		Position(x + (pit - 1) * dis, yl), putchar(' ');//选中不必消失
		Position(x + (pit - 1) * dis, yr), putchar(' ');
		if (r == UP_KEY) {
			Sound("Cursor");
			pit = (pit == num) ? 1 : pit + 1;
		}
		else if (r == DOWN_KEY) {
			Sound("Cursor");
			pit = (pit == 1) ? num : pit - 1;
		}
		else
			Error(2);//谨慎选择，别按错键
	}
	Sound("Click");
	Enter();

	Position(x + (num - 1) * dis + 2, 1);//相当于多了个换行符
	return pit;
}

bool PreseTry() {
	if (step >= 120 and step % 20 == 0) {
		Prese();
		return true;
	}
	return false;
}

//结束界面 参数code用于判断结束原因
int End(int c) {
	Cls();
	puts("");
	switch (c) {
	case -1:
		printf("  运行时错误，程序终止。\n");
		exit(0);
		break;

	case 0:
		SoundCover("Escape");
		printf("  返回标题界面。\n");
		place = ESC;//仅一部分场景可Esc，需是正常结束地点、能回到Gate的。 
		return 0;
		break;

	case 1:
		mciSS("stop all");
		mciSS("close all");
		mciSS("open Data\\Music\\Leave.mp3 alias Leave");//保持音效继续
		mciSS("play Leave");

		printf("  失去生命。\n\n");
		printf("  "), s = getlin();
		mciSS("stop Leave");
		mciSS("close Leave");
		exit(0);//强制退出程序
		break;

	default:
		break;
	}
	//接下来显示修养等，如Free 2 
	return 0;
}

//显示状态
bool Stateout() {
	for (int i = 1; i <= kStatecnt; ++i) {
		//闪烁提示
		if (flashable and statechange[i] and statechange[i] == kStateBoard[i].flash[state[i]]) {
			repeat(3, j)
				PstC(kStateBoard[i].x, 56, 4), Sleep(FLASH_SPAN), printf("%s", kStateBoard[i].desc[state[i]]), Sleep(FLASH_SPAN);
		}
		else
			PstC(kStateBoard[i].x, 56, 4), printf("%s", kStateBoard[i].desc[state[i]]);
		statechange[i] = NONE;
	}
	return true;
}

//显示手表内容到标准位置
bool Watchout() {
	if (watch there) {
		Position(17, 2), printf("时间 Day%lld %02lld:%02lld", day, hour, minute);
		return true;
	}
	return false;
}

//转变状态的同时获取状态如何转变了
int StateTurn(int c, int tar) {
	if (state[c] == tar)
		return NONE;//就算状态没有改变，也不要改动标记
	if (state[c] < tar) {
		state[c] = tar;
		statechange[c] = UP;//闪烁待用
		return UP;
	}
	state[c] = tar;
	statechange[c] = DOWN;
	return DOWN;
}

#define l me.l
#define h me.h
#define TS me.TS
#define Floor me.Floor
//某步状态变更后，才到这里判断状态产生的结果
int TimeLapse(long long t, int activity/*No too much*/) {
	if (kAct[activity].effable)
		t = (long long)(round((double)(t)* RandAround(1.0, 0.10) / me.mus));

	timein += t;

	day = timein / (1 days);
	hour = (timein - day days) / (1 hours);
	minute = (timein - day days - hour hours) / (1 minutes);
	second = timein - day days - hour hours - minute minutes;
	++day;

	city_bank.Grow();//自动判断天数是否增

	//同步
	me.awake_time += t;

	me.pro -= kAct[activity].pro_coe * t * kSecondCoe * kDailyPro * pow(kLossBase, me.pro / kDailyPro);
	me.fat -= kAct[activity].fat_coe * t * kSecondCoe * kDailyFat * pow(kLossBase, me.fat / kDailyFat);
	me.car -= kAct[activity].car_coe * t * kSecondCoe * kDailyCar * pow(kLossBase, me.car / kDailyCar);
	me.can -= kAct[activity].can_coe * t * kSecondCoe * kDailyCan * pow(kLossBase, me.can / kDailyCan);
	if (me.can < 0.0) me.can = 0.0;//身体略有调节
	//为保持体态，饮食结构不同，每增加60g蛋白质则日需求量变为1.37倍


	if (me.mus < 1.0 - (kEffBase - 1.0))
		StateTurn(MUSCLE, 0);
	else if (me.mus < 1.0 - (kEffBase - 1.0) / 3.0)
		StateTurn(MUSCLE, 1);
	else if (me.mus >= (1.0 + (kEffBase - 1.0) / 3.0 * 2.0))//照顾好了两样就不错了 
		StateTurn(MUSCLE, 3);
	else
		StateTurn(MUSCLE, 2);



	if (me.ent <= -0.5)
		StateTurn(ENTROPY, 2);
	else if (me.ent > 0.0)
		StateTurn(ENTROPY, 0);
	else
		StateTurn(ENTROPY, 1);



	if (me.awake_time <= 8 hours)
		StateTurn(SLEEPINESS, 3);
	else if (me.awake_time <= 16 hours)
		StateTurn(SLEEPINESS, 2);
	else if (me.awake_time <= 24 hours)
		StateTurn(SLEEPINESS, 1);
	else {
		StateTurn(SLEEPINESS, 0);
		me.life -= (Floor - 0.50) * t * kSecondCoe * kStdPhy * 0.96;
	}


	//Hunger
	if (h < noMore(Floor * 0.10, 0.10)) {//又困又饿更糟糕
		if (StateTurn(HUNGER, 0) == DOWN)
			SoundCover("Hungry");//即使黑着眼睛也听得到
		me.life -= (noMore(Floor * 0.10, 0.10) - h) * t * kSecondCoe * kStdPhy * 2.22;
	}
	else if (h < 0.20)
		StateTurn(HUNGER, 1);
	else if (h < 0.45)
		StateTurn(HUNGER, 2);
	else if (h >= 0.90 and h <= 1.10) {//别吃完一天需要的 
		if (StateTurn(HUNGER, 4) == UP)
			SoundCover("Full");
	}
	else if (h > 1.10) {
		StateTurn(HUNGER, 5);
		me.life -= (h - 1.10) * t * kSecondCoe * kStdPhy * 1.00;
	}
	else
		StateTurn(HUNGER, 3);



	me.sick += RandAround(me.ent, 1.0) * t * kSecondCoe;//必然

	if (Happen(pow(kEffBase, me.ent) * ins_coe * t * kSecondCoe)) {
		me.sick += Random();//偶然入侵，强制保存，为了调试暂时不加 DEBUGING
		//Prese();
	}
	if (me.sick < 0.0)
		me.sick = 0.0;

	if (me.sick <= 1.00)
		StateTurn(ILLNESS, 4);
	else if (me.sick <= 2.00) {
		if (StateTurn(ILLNESS, 3) == DOWN)//注，疾病状态代号下降是消极的
			SoundCough();
	}
	else {
		if (me.sick <= 4.00) {
			StateTurn(ILLNESS, 2);
		}
		else if (me.sick <= 8.00) {
			StateTurn(ILLNESS, 1);
		}
		else {
			StateTurn(ILLNESS, 0);
		}
		me.life -= (me.sick - 2.00) * t * kSecondCoe * kStdPhy * 0.50;
	}



	if (-me.ent > 0 and between(l, 0.0, 0.96))
		me.life +=
		//	f_Qua(l, -400.0 * SecondCoe / 81.0, 40.0 * SecondCoe / 9.0, 0.0)
		f_Qua(l, -2500 / 576.0, 100.0 / 24.0, 0.0)
		* (-me.ent)
		* me.phy
		* t
		* kSecondCoe
		* 0.48;
		/*
		二次函数关系，当血量在48%时恢复最快，为48% * 体有序程度/24h
		零点为0和96%
		*/

	noMored(me.life, me.phy);



	//AFTER
	me.Examine();
	if (l <= 0.00)
		StateTurn(LIFE, 0);
	else if (l < 0.20)
		StateTurn(LIFE, 1);
	else if (l < 0.45)
		StateTurn(LIFE, 2);
	else if (l >= 0.90)
		StateTurn(LIFE, 4);
	else
		StateTurn(LIFE, 3);

				//非生命垂危则根据时间改变地图的颜色，否则以红色警告
	if (state[LIFE] <= 0) {
		if (light != 0) {
			Color("04");
			light = 0;
		}
	}
	else {
		if (!colorable) {
			if (light != -1) {
				Color("0F");
				light = -1;//White
			}
		}
		else {
			if ((22 <= hour or hour <= 4) and light != 1) {
				Color("01");
				light = 1;
			}
			else if ((5 <= hour and hour <= 6) and light != 2) {
				Color("03");
				light = 2;
			}
			else if ((7 <= hour and hour <= 8) and light != 3) {
				SoundBird();
				Color("0E");
				light = 3;
			}
			else if ((9 <= hour and hour <= 15) and light != 4) {
				Color("0F");
				light = 4;
			}
			else if ((16 <= hour and hour <= 17) and light != 5) {
				Color("0E");
				light = 5;
			}
			else if ((18 <= hour and hour <= 21) and light != 6) {
				SoundInsect();
				Color("09");
				light = 6;
			}
		}
	}

	if (Turn(alpha, (int)(round(l * 20.0))))
		SetAlpha();//透明

	if (border)//有边框
		for (int i = 1; i <= kStatecnt; ++i)
			if (statechange[i]) {//可能是UP或DOWN
				Stateout();
				break;
			}

	if (inpack)//罕见的特判
		Watchout();

	if (me.life <= 0.0)
		End(1);

	return 0;
}
#undef l
#undef h
#undef TS
#undef Floor

//地图读入
bool Mapin(const char *file, int xs, int xt, int ys, int yt) {
	FILE *fin = NULL;
#ifdef MSVC
	fopen_s(&fin, ((string)("Data\\Map\\") + (string)(file)+(string)(".in")).c_str(), "rb");
#else
	fin = fopen(((string)("Data\\Map\\") + (string)(file)+(string)(".in")).c_str(), "rb");
#endif

	if (fin == NULL) {//读取错误
		MessageBox(NULL, "地图读取失败。请检查版本。", "Free 3.0 地图读取", MB_SYSTEMMODAL);
		End(-1);
	}

	for (int x = xs; x <= xt; ++x) {
		for (int y = ys; y <= yt; ++y)
		#ifdef MSVC
			fscanf_s(fin, "%c", &atlas[x][y], 1);
	#else
			fscanf_s(fin, "%c", &atlas[x][y]);
	#endif
		fscanf_s(fin, "\n");//换行
	}
	fclose(fin);
	return true;
}

//块状显示Map，中文不出问题
bool Mapput(int x, int y, bool mapingable, int ys, int yt) {
	if (mapingable and maping[x][y])
		return false;
	maping[x][y] = true;
	char ch = Maped(atlas[x][y]);

	if (ch == '^')
		return false;
	if (ischar(ch))
		Position(x, y), putchar(ch);
	else {
		int yl = y, yr = y;
		while (yl - 1 >= ys and !ischar(atlas[x][yl - 1]))
			--yl;
		while (yr + 1 <= yt and !ischar(atlas[x][yr + 1]))
			++yr;
		Position(x, yl);
		s = "";
		for (; yl <= yr; ++yl)
			s += atlas[x][yl], maping[x][yl] = true;
		printf("%s", s.c_str());
	}
	return true;
}

//输出地图
bool Mapout(int pat, int xs, int xt, int ys, int yt) {
	memset(maping, false, sizeof(maping));
	//不强制清屏

	if (pat == NONE)
		pat = step % 3 + 1;
	switch (pat) {
	case TACTIC:
	{
		for (int y = ys; y <= yt; ++y)
			for (int x = xs; x <= xt; ++x)
				Mapput(x, y);
		break;
	}
	case UNFOLD:
	{
		for (int yl = (ys + yt) / 2, yr = (ys + yt) / 2 + 1; yl >= ys or yr <= yt; --yl, ++yr)
			for (int x = xs; x <= xt; ++x) {
				if (yl >= ys)
					Mapput(x, yl);
				if (yr <= yt)
					Mapput(x, yr);
			}
		break;
	}
	case REVERSE:
	{
		for (int y = yt; y >= ys; --y) {
			if (y % 2 == 0) {
				for (int x = xs; x <= xt; ++x)
					Mapput(x, y);
			}
			else {
				for (int x = xt; x >= xs; --x)
					Mapput(x, y);
			}
		}
		break;
	}
	default:
		break;
	}
	return true;
}

//常见输出地图方式，必须有状态栏
bool CommonreMap() {
	Mapin();
	Mapout();
	border = true;
	Stateout();

	return true;
}

//做决定
bool Decide(int c, int pit) {
	decision[c] = pit;
	Prese();
	return true;
}

//设置
int Setting() {
	border = false;
	Cls();
	puts("");
	printf(
		"  现在进行一些基本设置...\n"
		"  以下，按 0 表示否定，回车以表示肯定。\n"
		"  \n"
	);

	//颜色
	printf("  是否开启颜色变化，用于区分昼夜？\n");
	r = getord();
	if (r == '0')
		colorable = false, printf("  => 随身携带了手电筒。\n");
	else
		colorable = true, printf("  => 日光决定颜色。\n");
	printf("\n");//可读性
	TimeLapse(0, FRESH);

	//状态闪烁 
	printf("  对于高危状态，需要闪烁提示吗？\n");
	r = getord();
	if (r == '0')
		flashable = false, printf("  => 关闭了状态栏闪烁，请更加留意状态哦。\n");
	else
		flashable = true, printf("  => 身体感知的危险状态将会闪烁。\n");
	printf("\n");
	TimeLapse(0, FRESH);

	WindowSet();

	printf(
		"  已完成基本设置。\n"
		"  想要重设，在任意地点输入ｈ后，输入ｇ来到本界面。\n"
	);

	Pause();
	return 0;
}

//查看快捷键
int KeyView() {
	Cls();
	puts("");
	printf("  常见快捷键：\n\n");
	printf(
		"  o-------o------------o\n"
		"  |w/a/s/d|    移动    |\n"
		"  |   h   |    帮助    |\n"
		"  | h + g |    设置    |\n"
		"  | h + q | 查看快捷键 |\n"
		"  |   t   |   任务栏   |\n"
		"  |   p   |    包裹    |\n"
		"  |  Esc  |返回标题界面|\n"
		"  o-------o------------o\n\n"
	);
	printf("  %lld步后自动存档。\n\n", (step < 120) ? (120 - step) : (20 - step % 20));

	printf("  若已了解，按键继续。\n");
	Pause();
	return 0;
}

//帮助界面
int Help() {
	Sound("Helpin");//防止连续播放 

	Cls();
	puts("");
	switch (place) {
	case CITY:
		printf(
			"  自在城。\n"
			"  \n"
			"  这里生活自如，大多数工作可以直接参与。\n"
			"  这里大街宽敞，是锻炼的不错场所。\n"
			"  \n"
			"  去超市购买餐饮百货；\n"
			"  到武器店，装备自己；\n"
			"  来学校得到知识；\n"
			"  访邻居，增进友谊...\n"
			"  \n"
			"  按上下左右键移动，到达 X 处进入新地点。\n"
			"  \n"
		);
		break;

	case HOME:
		printf(
			"  温暖的家。\n"
			"  不免有些孤独的家。\n"
			"  \n"
			"  既能休养生息，\n"
			"  又可发挥创造力。\n"
			"  \n"
			"  想要外出吗？走向大门。\n"
			"  \n"
		);
		break;
	case KITCHEN:
		printf(
			"  厨房，食材的用武之地。\n"
			"  \n"
			"  自己做的饭菜最合自己的胃口。\n"
			"  \n"
			"  除此之外，研究药品也要到这里。\n"
			"  \n"
		);
		break;
	case SUPERMATKET:
		printf(
			"  门前挂着掉色的招牌：美君平价超市。\n"
			"  \n"
			"  把物品序号告诉店员，她会给出介绍，\n"
			"  然后输入数量以购买。\n"
			"  如果要放弃购买，单独回车即可。\n"
			"  \n"
			"  回车即可离开超市。\n"
			"  \n"
		);
		break;
	case WRITING:
		printf(
			"  写字楼是工作密集区域。\n"
			"  \n"
			"  在这座秩序井然的城市，大多数工作可以直接分配出去。\n"
			"  \"我们信任你，但也要求你的效率够高! \"\n"
			"  \n"
			"  参与工作能得到工分，接着可到人事部换取工资。\n"
			"  有疑惑请到办公室询问。\n"
			"  \n"
		);
		break;
	case TYPIST:
		printf(
			"  在打字室，本单位会自动分配给你任务的。\n"
			"  输入屏幕上的单词，然后按回车确认。\n"
			"  想退出打字，单独回车即可。\n"
			"  \n"
			"  不适应这样的码风？\n"
			"  在打字机重启时，按ｇ进入设置。\n"
			"  \n"
			"  提高效率，获取更多奖励。\n"
			"  表现不赖的话，后勤部会为你提供免费快餐。\n"
			"  待会儿别忘了到人事部领取你的工资。\n"
			"  \n"
			"  使用帮助不会打断连击哦! \n"
			"  \n"
		);
		break;
	case SCHOOL:
		printf(
			"  我们一定要给自己提出这样的任务：\n"
			"  第一，学习，第二是学习，第三还是学习。\n"
			"  \n"
			"  这所对外公开的学校免费提供学习资料。\n"
			"  学习使人能获得知识和修养的提升。\n"
			"  但请先到教学楼报名处报名。\n"
			"  \n"
			"  不要手持危险的武器，这不合学校的氛围。\n"
			"  \n"
		);
		break;
	case SCHOOL_1F:
		printf(
			"  教学楼一层。"
		);
		break;//教学楼一层
	case SCHOOL_2F:
		printf(
			"  教学楼二层。"
		);
		break;//教学楼二层
	case SCHOOL_3F:
		printf(
			"  教学楼三层。"
		);
		break;//教学楼三层
	case SCHOOL_HIDE:
		printf(
			"  信号不好。"
		);
		break;//教学楼密室

	case HOSPITAL:
		printf(
			"  市立医院提供基本医疗服务。\n"
			"  \n"
			"  治病要对症下药，\n"
			"  别忘记锻炼和食疗。\n"
			"  当然，医生会为你提供指导的。\n"
			"  \n"
		);

		break;
	case WEAPONSHOP:
		printf(
			"  \"本市风气不错。\n"
			"    想想也不太有人会去搞事。\n"
			"    你要冒险去，应当做好防身工作。\n"
			"    当然，小子，有钱再说话。\"\n"
			"  \n"
		);
		break;
	}

	printf("  键入ｇ进入设置界面，ｑ则了解各快捷键。\n\n");
	printf("  回车以关闭这个帮助。\n");

	r = getord();

	if (r == 'g')
		Setting();
	else if (r == 'q')
		KeyView();

	Sound("Helpout");//note	
	return 0;
}

//保留两个代号以便于回顾先前的任务
int TaskView(int codeA, int codeB) {
	Cls();
	puts("");

	Flush();//乱按？不要主动跳过 

	switch (codeA) {
	case 1:
		switch (codeB) {
		case 1:
			P("  大街通向各处...", 30, 250); P("有闲逛的心情吗？\n\n", 30, 1000);
			P("  但为了维持生计，还得努力赚些钱。\n", 30, 500);
			P("  \"人们手里的金钱是保持自由的一种工具。\"\n\n", 30, 1000);
			P("  前往写字楼赚取工分，然后到里面的人事部换取工资。\n\n", 30, 1000);
			P("  如果某时出现了疑惑，可输入ｈ打开帮助。\n\n", 30, 1000);
			break;
		case 2:
			P("  一分耕耘，一分收获...\n\n", 27, 1000);
			P("  但是，", 27);
			if (state[HUNGER] <= 2)
				P("肚子开始抗议了。\n\n  ", 27, 1000);
			P("就算工作努力也不能影响身体。\n\n", 27, 1000);
			P("  注意状态栏，", 27, 250); P("饥劳状态会威胁健康。\n\n", 27, 1000);
			P("  现在可以去买点面包，", 27, 250); P("超市就在邻居家对面。\n\n", 27, 1000);
			break;
		case 3:
			P("  超市的面包，分量还算足。\n\n", 24, 1000);
			P("  如果想随时随地解决饥饿问题，可以利用包裹。\n\n", 24, 1000);
			P("  购买超市的饼干，接着按ｐ打开包裹，\n\n", 24, 500);
			P("  尝尝这便携的食品吧。\n\n", 24, 1000);
			break;
		case 4:
			if (state[HUNGER] <= 2)
				P("  肚子还在咕咕叫，不知饥饿以外威胁健康的因素。\n\n", 21, 1000);
			else
				P("  虽然解决了温饱问题，但健康不止这一方面。\n\n", 21, 1000);
			P("  身体健康，才有能力把事情做好。\n\n", 21, 1000);
			P("  听说，医院最近新添了保健书栏，\n\n", 21, 500);
			P("  去那里找找免费的保健指导吧。\n\n", 21, 1000);
		default:
			break;
		}
		break;
	case 2:
		switch (codeB) {
		case 1:
			//注意倾向
			//此后办公室的门开了 
			P("  \"干的挺卖力啊。\"\n\n", 18, 750);
			P("  \"老板过奖，好好干活是应该的。\"\n\n", 18, 750);
			P("  \"好伙计! 我正有个任务要交给你。\n", 18, 500);
			P("   你把这个医疗包送给动物园园长。\n", 18, 750);
			P("   报酬嘛，园长会给你的。\"\n\n", 18, 750);
			//此处可以添加回答选项，对声望和修养的影响不同 
			P("  \"没问题! \"\n\n", 18, 750);
			break;
		case 2:
			P("  \"单位老板托我送这个医疗包过来。\"\n\n", 18, 500);//choice
			P("  \"啊，得谢谢他了! \n", 18, 500);
			P("   改天我也去看望看望他。\n", 18, 500);
			P("   对了，这里50元报酬，不成敬意。\"\n\n", 18, 500);
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (codeB) {
		case 1:
			Sound("PageThrough");
			P("  这儿有一张纸，上面潦草地写了些字：\n\n", 24, 1000);

			P("    \"学校负债累累，快要开不下去了。\n", 18, 500);
			P("     是我这个校长办事不力啊! \n", 18, 500);
			P("     我如何面对那些可爱的学生呢？\n", 18, 750);
			P("     学校已经欠了2000元，根本还不起啊! ", 18, 500); P("怎么办？\"\n\n", 18, 1000);

			P("  虽然话风奇怪，但也算是个靠谱的校长。\n\n", 24, 1000);
			printf("  按键继续。\n");

			Pause();

			Sound("PageThrough");
			Cls();
			puts("");
			P("  (翻到纸的背面)\n\n", 24, 1000);

			P("    \"我还是跑路吧! \"\n\n", 18, 1000);

			P("  收回刚刚的夸奖...\n\n", 24, 1000);
			P("  不过怎能放任学校倒闭呢？", 24, 250); P("我应该考虑帮忙。\n\n", 24, 500);
			break;
		}
		break;
	case 4:
		switch (codeB) {
		case 1:
		{
			P("  只轻轻碰了一下，花瓶随它过高的底座粉碎在地。\n\n", SPL_THINK, SPS_THINK);
			P("  内心越来越纠结...\n\n", SPL_THINK, SPS_THINK);
			if (not decision[2]) {//形成局部
				const char *b[] = {
					"我心甘情愿负责",
					"容许自己瞒天过海"
				};
				Decide(2, Pitch(2, b, 2));
			}
			if (decision[2] == 1) {
				P("  对，现在就去找这座空楼的主人。\n\n", 18, 1000);
				P("  可他在哪呢？\n\n", 18, 1000);
			}
			else
				if (decision[2] == 2) {
					P("  机械作响，气氛诡异，赶紧离开这里吧。\n\n", 18, 1000);
				}

			break;
		}
		default:
			break;
		}
		break;
	default:
		break;
	}

	printf("  => 任务%d-%d：%s\n\n", codeA, codeB, kTask[codeA].name[codeB]/*.c_str()*/);

	printf("     任务栏快捷键ｔ。按任意键返回。\n");

	Pause();

	return 0;
}

//显示任务栏
int Task() {
	Sound("Pagein");

	Mapin("Task");//1为前缀，与图像(Map)有关 
	Mapout(UNFOLD);

	int Takecnt = 0;
	for (int i = 1; i <= kTaskSeriecnt; ++i)
		if (task_rate[i] != 0) {
			++Takecnt;

			Position(Takecnt * 2, 2);
			if (task_rate[i] > 0) {
				if (task_rate[i] > kTask[i].cnt)
					printf("系列%d已完成! ", i);//便于写新任务
				else
					printf("%d-%d：%s", i, task_rate[i], kTask[i].name[task_rate[i]]);
			}
			else
				printf("系列%d失败。", i);

			Position(Takecnt * 2 + 1, 1);
			printf("o----------------------------------------------------------o");
		}

	r = getord(); n = r - '0';

	if (between(n, 1, kTaskSeriecnt))
		if (between(task_rate[n], 1, kTask[n].cnt))//正在执行该系列任务 
			TaskView(n, task_rate[n]);
	//ef(TaskRate == -1)

	Sound("Pageout");

	return 0;
}

//把钱给别人，而非扔掉
bool Pay(int money_need) {
	if (not(money_need there))
		return false;

	TimeLapse(11, FIX);
	if (money < money_need)
		return false;
	money -= money_need;
	//必须要有边框才提示
	if (border)
		Tips(""), printf("支出%d元...", money_need);
	SoundWait("MoneyPaid");
	return true;
}

//获得金钱
bool Gain(int money_back) {
	if (!(money_back there))
		return false;
	TimeLapse(11, FIX);
	money += money_back;
	if (border)
		Tips(""), printf("得到%d元。", money_back);
	SoundWait("MoneyBack");
	return true;
}

//吃东西
int Eat(int c, int num) {
	mciSS(((string)("open Data\\Music\\") + (string)(kFood[c].file) + (char)('A' + step % kChewcnt) + (string)(".mp3 alias Eat")).c_str());

	mciSS("play Eat repeat");

	int eaten = 0;
	for (int i = 1; i <= num; ++i) {
		Sleep(kFood[c].delay);
		if (state[HUNGER] >= 4)
			break;

		++eaten;
		me.pro += kFood[c].pro;
		me.fat += kFood[c].fat;
		me.car += kFood[c].car;
		me.can += kFood[c].can;

		TimeLapse(kFood[c].use_time, EAT);
	}

	mciSS("stop Eat");
	mciSS("close Eat");

	return eaten;//successfully eaten
}

//读书
int Read(int c) {
	border = false;

	int Pagecur = 1;

	while (between(Pagecur, 1, kBook[c].pagecnt)) {
		Sound("Pagein");
		Mapin((string(kBook[c].file) + string("\\Page") + InttoString(Pagecur)).c_str());
		Mapout(UNFOLD);
		TimeLapse(kBook[c].read_time, THINK);

		if (Pagecur != 1) {
			Position(19, 2);
			printf("<= 上一页");
		}
		if (Pagecur != kBook[c].pagecnt) {
			Position(19, 46);
			printf("下一页 =>");
		}
		Position(19, 24);
		printf("回车以合上");

		Input(ORDER, false);
		r = Directed(r);
		if (r == LEFT_KEY)
			--Pagecur;
		else if (r == RIGHT_KEY)
			++Pagecur;
		else
			break;
	}
	Sound("Pageout");
	return 0;
}

//显示或覆盖输入框
bool InputBox(bool visable) {
	if (visable) {
		Position(16, 45); printf("o--输-入--o");
		Position(17, 45); printf("|         |");
		Position(18, 45); printf("o---------o");
	}
	else {
		Mapout(UNFOLD, 16, 18, 45, 55);
	}
	return true;
}

//常见读入数字，结合输入框
bool CommonInput(int type, bool expand, int lenlim, bool InputBoxable) {
	if (InputBoxable)
		InputBox(true);

	PstInput();
	if (!Input(type, expand, lenlim))//进入了帮助啥的
		return false;

	if (InputBoxable)
		InputBox(false);
	return true;
}

//返回上一步位置。增强代码可读性
bool MoveBack() {
	TimeLapse(move_unit_time, WALK);
	sx = tx, sy = ty;
	return true;
}

//在背包中
bool UseItem(int c, int num) {
	int Used = 0;
	switch (kItem[c].type) {
	case FOOD:
	{//食物，进行具体描述
		switch (c) {
		case COOKIE:
		{
			Tips(""), printf("嚼着%d片饼干...", num);
			Used = Eat(kItem[COOKIE].code, num);
			if (Used == 0)//result
				Tips("一点也吃不下了。");
			else if (Used < num)
				Tips(""), printf("只吃得下%d片...有点腻。", Used);
			else
				Tips("松脆清甜。");
				//Task 1-4 open
			if (task_rate[1] == 3) {
				SoundCover("Message");
				Delay(1500);
				task_rate[1] = 4;
				TaskView(1, 4);
				remap = true;
			}
			break;
		}
		default: break;
		}
		break;
	}
	case BOOK:
	{
		Read(kItem[c].code);
		remap = true;
		break;
	}
	case PERM:
	{
		Tips(kPerm[kItem[c].code].desc);
		break;
	}
	default:
		break;
	}
	return Used;
}

//重新统计blo格信息
bool BlockFresh(int blo) {
	if (block[blo].num == 0)
		block[blo].itm = 0;
	return true;
}

int GetItemnum(int c) {
	int res = 0;
	for (int i = 1; i <= blocknum; ++i)
		if (block[i].itm == c)
			res += block[i].itm;
	return res;
}

//给出num个物品c
bool GiveItem(int c, int num) {
	if (GetItemnum(c) < num)
		return false;
	for (int i = 1; i <= blocknum and num; ++i)
		if (block[i].itm == c) {
			int Loss = noMore(num, block[i].num);
			block[i].num -= Loss;
			BlockFresh(i);
			num -= Loss;
		}
	return true;
}

//系统放置物品，不用担心putitem(-1)
bool PutItem(int c, int num) {
	int Space = 0;
	for (int i = 1; i <= blocknum; ++i) {
		if (block[i].itm == c)
			Space += kItem[c].carry - block[i].num; else
			if (block[i].itm == 0)
				Space += kItem[c].carry;
	}

	if (Space < num) {//不放
		Sound("PackFull");
		return false;
	}

	SoundWait("PutItem");

	TimeLapse(10 * num, FIX);//大小物件
	for (int i = 1; i <= blocknum and num there; ++i)//从前向后依次填满
		if (block[i].itm == c) {
			Space = kItem[c].carry - block[i].num;
			if (Space < num) {
				block[i].num += Space;
				num -= Space;
			}
			else {
				block[i].num += num;
				num -= num;
			}
		}
	//优先放到同类 
	for (int i = 1; i <= blocknum and num there; ++i)
		if (block[i].itm == 0) {
			block[i].itm = c;

			Space = kItem[c].carry;
			if (Space < num) {
				block[i].num += Space;
				num -= Space;
			}
			else {
				block[i].num += num;
				num -= num;
			}
		}
	return true;
}

//显示第blo格的物品
bool Blockout(int blo) {
	int x = (blo - 1) / 6, y = (blo - 1) % 6;
	x = 2 + x * 5; y = 2 + y * 9;
	BlockFresh(blo);
	if (block[blo].itm there) {
		Position(x, y);
		printf("%s", kItem[block[blo].itm].name);
		Position(x + 1, y);
		printf("%6d%s", block[blo].num, kItem[block[blo].itm].meas);
		Position(x + 3, y);
		printf("%s", ItemTypeDesc[kItem[block[blo].itm].type]);
	}
	else {
		for (int i = x; i <= x + 3; ++i)
			PstC(i, y, 8);
	}
	return true;
}

//打开包裹
int Pack() {
	inpack = true;
	Sound("Packin");

	remap = true;
	while (inpack) {
		if (remap) {
			if (blocknum == 6)
				Mapin("Packet");
			else if (blocknum == 12)
				Mapin("Bag");
			Mapout(UNFOLD);
			border = true;//也是半个场景
			Stateout();

			Position(17, 36), printf("%d", money);

			for (int i = 1; i <= blocknum; ++i) {
				if (block[i].num == 0)
					continue;
				Blockout(i);
			}

			Tips("输入序号以选择物品，或按回车返回。");

			remap = false;
		}

		CommonInput(INTEGER, false);

		if (n == 0)
			break;
		if (between(n, 1, blocknum) and block[n].itm there) {
			//显示选择状态
			int blo = n;//选定的格子

			Sound("Cursor");
			int x = (blo - 1) / 6, y = (blo - 1) % 6;
			Position(1 + x * 5, 1 + y * 9), putchar('o');
			Position(1 + x * 5 + 5, 1 + y * 9), putchar('o');
			Position(1 + x * 5, 1 + y * 9 + 9), putchar('o');
			Position(1 + x * 5 + 5, 1 + y * 9 + 9), putchar('o');

			Tips(""), printf("%s:输入使用数目，或者ｄ、ｍ来丢弃、挪动。", kItem[block[blo].itm].name);

			CommonInput(STRING, false);

			if (s.find("d") != string::npos)
				r = 'd';
			else if (s.find("m") != string::npos)
				r = 'm';
			else {
				r = 'u';
				n = StringtoInt(s);
			}

			int itm = block[blo].itm;
			switch (r) {
			case 'u'://use
				if ((n = noMore(n, block[blo].num)) >= 1) {
					if (!kItem[block[blo].itm].reusable)
						block[blo].num -= n;
					Blockout(blo);
					UseItem(itm, n);
				}
				else
					Tips("眼神迷离了。");
				break;
			case 'd'://discard
				if (block[blo].num == 1)
					n = 1;
				else {
					Tips("丢弃数目...");

					CommonInput(INTEGER, false);
				}
				if ((n = noMore(n, block[blo].num)) >= 1) {
					Sound("Discard");//本来就是不好的东西
					TimeLapse(10 * n, FIX);
					block[blo].num -= n;
					Blockout(blo);
					Tips(""), printf("刚刚丢弃了%d%s%s。", n, kItem[itm].meas, kItem[itm].name);
				}
				else
					Tips("最近手也不太听使唤啊。");
				break;
			case 'm':
			{//move
				if (block[blo].num == 1)
					n = 1;
				else {
					Tips("移动数目...");

					CommonInput(INTEGER, false);
				}

				int num = n;//这里需要暂存
				if ((num = noMore(num, block[blo].num)) >= 1) {
					Tips("目标格子...");

					CommonInput(INTEGER, false);

					if (between(n, 1, blocknum) and n != blo) {
						if (block[n].itm == itm or block[n].itm == 0) {
							int Space = kItem[itm].carry - block[n].num;
							if (Space >= num) {
								Sound("MoveItem");
								TimeLapse(10, FIX);

								block[blo].num -= num;
								block[n].itm = itm;
								block[n].num += num;
								Blockout(blo), Blockout(n);
								Tips(""), printf("把%d%s%s放到了第%d个格子。", num, kItem[itm].meas, kItem[itm].name, n);
							}
							else
								Sound("PackFull"), Tips(""), printf("目标格子装不下这些%s，", kItem[block[blo].itm].name);
						}
						else
							Tips("打了个哈欠。");
					}
					else
						Tips("富于空间感。");
				}
				else
					Tips("奇怪。");
				break;
			}

			default:
				Tips("做不到。");
				break;
			}

			//取消显示选择状态
			if (not remap) {
				x = (blo - 1) / 6, y = (blo - 1) % 6;
				Mapput(1 + x * 5, 1 + y * 9, false);
				Mapput(1 + x * 5 + 5, 1 + y * 9, false);
				Mapput(1 + x * 5, 1 + y * 9 + 9, false);
				Mapput(1 + x * 5 + 5, 1 + y * 9 + 9, false);
			}
		}
		else
			Tips("输入序号来选择，或回车返回。");
	}
	Sound("Packout");
	inpack = false;
	return 0;
}

//对Body造成伤害并刷新
bool Injure(Bodyinfo &body, double price) {
	body.life -= price;
	TimeLapse();
	return true;
}

//睡觉
bool Asleep(long long sleep_time/*, long long TimeSnooze*/) {
	Cls();
	mciSS("open Data\\Music\\Asleep.mp3 alias Asleep");
	if (state[LIFE] > 2)//体虚时不发出呼噜声
		mciSS("play Asleep repeat");
	//成功入睡 

	//困倦不影响了

	int zizz = 0;//ZZZ字符个数
	long long loss;
	while (sleep_time > 0) {
		zizz = zizz % 6 + 1;
		if (zizz == 1)
			PstC(10, 28, 6);//no else

		if (zizz <= 3)
			putchar('Z');
		else
			putchar('.');

		loss = noMore(1 hours, sleep_time);

		Sleep((int)(loss * 1000 / (1 hours)));
		TimeLapse(loss, SLEEP);
		sleep_time -= loss;
		me.awake_time = 0;

/*		if (TimeSleep == 0 and TimeSnooze > 0) {
			Zizz = 0;
			PstC(10, 24, 15);
			printf("贪睡？键入ｓ...");
			r = getord();
			PstC(10, 24, 15);
			Loss = noMore(1 hours, TimeSnooze)
			if(r == 's')
				TimeSnooze -=
		}*/
	}

	PstC(10, 28, 6); P((step % 2 == 0) ? ("Ahh...") : ("Emm..."), 48, 500, false);

	mciSS("stop Asleep");
	mciSS("close Asleep");
	return true;
}

//内部读入，支持打开背包、任务等 
bool Input(int type, bool expand, int lenlim) {
	//可能每隔一定步数自动保存，关键事件直接保存 
	switch (type) {
	case ORDER://char 用int存储
		PreseTry();//Things were done
		r = getord();

		if (expand) {//必须在可以reMap的界面可能More
			if (r == ESC) { End(0); remap = true; return false; }
			if (r == 'h') { Help(); remap = true; return false; }
			if (r == 't') { Task(); remap = true; return false; }
			if (r == 'p') { Enter(); Pack(); remap = true; return false; }
			if (r == 'v') {//Debugging
				me.Examine();
				Tips("");
				printf("肌%.3lf 能%.1lf 生命%.1lf 失调%.3lf 病%.3lf", me.mus, me.ene, me.life, me.ent, me.sick);
				return false;
			}
			if (r == 'm') {//Debugging
				me.Examine();
				Tips("");
				printf("蛋%.3lf 脂%.3lf 糖%.3lf 致癌物%.3lf 时%02lld:%02lld", me.pro, me.fat, me.car, me.can, hour, minute);
				return false;
			}
		}
		break;

	case STRING://string
		PreseTry();
		CursorShow();
		s = getlin(lenlim);
		CursorHide();

		if (expand) {
			if (s == "h") { Help(); remap = true; return false; }
			if (s == "t") { Task(); remap = true; return false; }
			if (s == "p") { Enter(); Pack(); remap = true; return false; }
		}
		break;

	case INTEGER:
		PreseTry();
		CursorShow();
		s = getlin(lenlim);
		CursorHide();

		if (expand) {
			if (s == "h") { Help(); remap = true; return false; }
			if (s == "t") { Task(); remap = true; return false; }
			if (s == "p") { Enter(); Pack(); remap = true; return false; }
		}

		n = StringtoInt(s);
		break;
	default:
		break;
	}

	Enter();

	return true;
}

//常用函数。读入移动操作、移动。返回移动是否成功 
bool Move() {
	Position(sx, sy);
	putchar('i');
	Position(sx, sy);//输出Y（我）并重置光标 

	if (!Input(ORDER, true))//等待读入 
		return false;
	r = Directed(r);

	//Sleep(MoveTime);
	Mapput(sx, sy, false);

	tx = sx, ty = sy;

	switch (r) {
	case UP_KEY: --sx; break;

	case DOWN_KEY: ++sx; break;

	case LEFT_KEY: --sy; break;

	case RIGHT_KEY: ++sy; break;

	default:
		TimeLapse(7, THINK);
		++CME;
		Error(1);
		return false;
		break;
	}//else
	CME = 0;//连续的移动错误

	//常见障碍物
	if (iswall(atlas[sx][sy])) {
		MoveBack();
		Tips("是电磁力阻碍我前进...");
		SoundHit();
		return false;//移动错误
	}
	if (atlas[sx][sy] == '~') {
		MoveBack();
		Tips("不能在水里呼吸。");
		return false;
	}

	TimeLapse(move_unit_time, WALK);
	return true;
}
