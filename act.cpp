#include "pch.h"

bool reNew() {//���ݳ�ʼ����Ĭ��
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
	sx = 8, sy = 34;//ȫ�ֱ�������
	CME = 0;

	colorable = true;
	flashable = true;
	code_style = 0;
	code_style &= ~TIGHT;//Ĭ�Ϲرս��յĴ�����

	border = false;

	for (int i = 1; i <= kStatecnt; ++i)
		state[i] = kStateBoard[i].common, statechange[i] = NONE;

	city_bank.Init();
	return true;
}
//��һ�� 
long long Enter() {
	return ++step;
}

//�е�㸴��
int Pitch(int num, const char *desc[], int dis, int pit, int ym, int x) {
	int Maxlen = 0;
	if (x == 0)
		x = GetBufferinfo().dwCursorPosition.Y + 1;
	for (int i = 0; i <= num - 1; ++i) {
		int len = strlen(desc[i]);
		Maxed(Maxlen, len);
		Position(x + i * dis, ym - (len - 1) / 2);
		printf("%s", desc[i]);
	}//�����������
	const int yl = ym - (Maxlen - 1) / 2 - 2, yr = yl + Maxlen + 3;
	while (between(pit, 1, num)) {
		Position(x + (pit - 1) * dis, yl), putchar('[');
		Position(x + (pit - 1) * dis, yr), putchar(']');
		r = Directed(getord());
		if (r == ENTER or r == ESC)
			break;
		Position(x + (pit - 1) * dis, yl), putchar(' ');//ѡ�в�����ʧ
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
			Error(2);//����ѡ�񣬱𰴴��
	}
	Sound("Click");
	Enter();

	Position(x + (num - 1) * dis + 2, 1);//�൱�ڶ��˸����з�
	return pit;
}

bool PreseTry() {
	if (step >= 120 and step % 20 == 0) {
		Prese();
		return true;
	}
	return false;
}

//�������� ����code�����жϽ���ԭ��
int End(int c) {
	Cls();
	puts("");
	switch (c) {
	case -1:
		printf("  ����ʱ���󣬳�����ֹ��\n");
		exit(0);
		break;

	case 0:
		SoundCover("Escape");
		printf("  ���ر�����档\n");
		place = ESC;//��һ���ֳ�����Esc���������������ص㡢�ܻص�Gate�ġ� 
		return 0;
		break;

	case 1:
		mciSS("stop all");
		mciSS("close all");
		mciSS("open Data\\Music\\Leave.mp3 alias Leave");//������Ч����
		mciSS("play Leave");

		printf("  ʧȥ������\n\n");
		printf("  "), s = getlin();
		mciSS("stop Leave");
		mciSS("close Leave");
		exit(0);//ǿ���˳�����
		break;

	default:
		break;
	}
	//��������ʾ�����ȣ���Free 2 
	return 0;
}

//��ʾ״̬
bool Stateout() {
	for (int i = 1; i <= kStatecnt; ++i) {
		//��˸��ʾ
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

//��ʾ�ֱ����ݵ���׼λ��
bool Watchout() {
	if (watch there) {
		Position(17, 2), printf("ʱ�� Day%lld %02lld:%02lld", day, hour, minute);
		return true;
	}
	return false;
}

//ת��״̬��ͬʱ��ȡ״̬���ת����
int StateTurn(int c, int tar) {
	if (state[c] == tar)
		return NONE;//����״̬û�иı䣬Ҳ��Ҫ�Ķ����
	if (state[c] < tar) {
		state[c] = tar;
		statechange[c] = UP;//��˸����
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
//ĳ��״̬����󣬲ŵ������ж�״̬�����Ľ��
int TimeLapse(long long t, int activity/*No too much*/) {
	if (kAct[activity].effable)
		t = (long long)(round((double)(t)* RandAround(1.0, 0.10) / me.mus));

	timein += t;

	day = timein / (1 days);
	hour = (timein - day days) / (1 hours);
	minute = (timein - day days - hour hours) / (1 minutes);
	second = timein - day days - hour hours - minute minutes;
	++day;

	city_bank.Grow();//�Զ��ж������Ƿ���

	//ͬ��
	me.awake_time += t;

	me.pro -= kAct[activity].pro_coe * t * kSecondCoe * kDailyPro * pow(kLossBase, me.pro / kDailyPro);
	me.fat -= kAct[activity].fat_coe * t * kSecondCoe * kDailyFat * pow(kLossBase, me.fat / kDailyFat);
	me.car -= kAct[activity].car_coe * t * kSecondCoe * kDailyCar * pow(kLossBase, me.car / kDailyCar);
	me.can -= kAct[activity].can_coe * t * kSecondCoe * kDailyCan * pow(kLossBase, me.can / kDailyCan);
	if (me.can < 0.0) me.can = 0.0;//�������е���
	//Ϊ������̬����ʳ�ṹ��ͬ��ÿ����60g������������������Ϊ1.37��


	if (me.mus < 1.0 - (kEffBase - 1.0))
		StateTurn(MUSCLE, 0);
	else if (me.mus < 1.0 - (kEffBase - 1.0) / 3.0)
		StateTurn(MUSCLE, 1);
	else if (me.mus >= (1.0 + (kEffBase - 1.0) / 3.0 * 2.0))//�չ˺��������Ͳ����� 
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
	if (h < noMore(Floor * 0.10, 0.10)) {//�����ֶ������
		if (StateTurn(HUNGER, 0) == DOWN)
			SoundCover("Hungry");//��ʹ�����۾�Ҳ���õ�
		me.life -= (noMore(Floor * 0.10, 0.10) - h) * t * kSecondCoe * kStdPhy * 2.22;
	}
	else if (h < 0.20)
		StateTurn(HUNGER, 1);
	else if (h < 0.45)
		StateTurn(HUNGER, 2);
	else if (h >= 0.90 and h <= 1.10) {//�����һ����Ҫ�� 
		if (StateTurn(HUNGER, 4) == UP)
			SoundCover("Full");
	}
	else if (h > 1.10) {
		StateTurn(HUNGER, 5);
		me.life -= (h - 1.10) * t * kSecondCoe * kStdPhy * 1.00;
	}
	else
		StateTurn(HUNGER, 3);



	me.sick += RandAround(me.ent, 1.0) * t * kSecondCoe;//��Ȼ

	if (Happen(pow(kEffBase, me.ent) * ins_coe * t * kSecondCoe)) {
		me.sick += Random();//żȻ���֣�ǿ�Ʊ��棬Ϊ�˵�����ʱ���� DEBUGING
		//Prese();
	}
	if (me.sick < 0.0)
		me.sick = 0.0;

	if (me.sick <= 1.00)
		StateTurn(ILLNESS, 4);
	else if (me.sick <= 2.00) {
		if (StateTurn(ILLNESS, 3) == DOWN)//ע������״̬�����½���������
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
		���κ�����ϵ����Ѫ����48%ʱ�ָ���죬Ϊ48% * ������̶�/24h
		���Ϊ0��96%
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

				//��������Σ�����ʱ��ı��ͼ����ɫ�������Ժ�ɫ����
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
		SetAlpha();//͸��

	if (border)//�б߿�
		for (int i = 1; i <= kStatecnt; ++i)
			if (statechange[i]) {//������UP��DOWN
				Stateout();
				break;
			}

	if (inpack)//����������
		Watchout();

	if (me.life <= 0.0)
		End(1);

	return 0;
}
#undef l
#undef h
#undef TS
#undef Floor

//��ͼ����
bool Mapin(const char *file, int xs, int xt, int ys, int yt) {
	FILE *fin = NULL;
#ifdef MSVC
	fopen_s(&fin, ((string)("Data\\Map\\") + (string)(file)+(string)(".in")).c_str(), "rb");
#else
	fin = fopen(((string)("Data\\Map\\") + (string)(file)+(string)(".in")).c_str(), "rb");
#endif

	if (fin == NULL) {//��ȡ����
		MessageBox(NULL, "��ͼ��ȡʧ�ܡ�����汾��", "Free 3.0 ��ͼ��ȡ", MB_SYSTEMMODAL);
		End(-1);
	}

	for (int x = xs; x <= xt; ++x) {
		for (int y = ys; y <= yt; ++y)
		#ifdef MSVC
			fscanf_s(fin, "%c", &atlas[x][y], 1);
	#else
			fscanf_s(fin, "%c", &atlas[x][y]);
	#endif
		fscanf_s(fin, "\n");//����
	}
	fclose(fin);
	return true;
}

//��״��ʾMap�����Ĳ�������
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

//�����ͼ
bool Mapout(int pat, int xs, int xt, int ys, int yt) {
	memset(maping, false, sizeof(maping));
	//��ǿ������

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

//���������ͼ��ʽ��������״̬��
bool CommonreMap() {
	Mapin();
	Mapout();
	border = true;
	Stateout();

	return true;
}

//������
bool Decide(int c, int pit) {
	decision[c] = pit;
	Prese();
	return true;
}

//����
int Setting() {
	border = false;
	Cls();
	puts("");
	printf(
		"  ���ڽ���һЩ��������...\n"
		"  ���£��� 0 ��ʾ�񶨣��س��Ա�ʾ�϶���\n"
		"  \n"
	);

	//��ɫ
	printf("  �Ƿ�����ɫ�仯������������ҹ��\n");
	r = getord();
	if (r == '0')
		colorable = false, printf("  => ����Я�����ֵ�Ͳ��\n");
	else
		colorable = true, printf("  => �չ������ɫ��\n");
	printf("\n");//�ɶ���
	TimeLapse(0, FRESH);

	//״̬��˸ 
	printf("  ���ڸ�Σ״̬����Ҫ��˸��ʾ��\n");
	r = getord();
	if (r == '0')
		flashable = false, printf("  => �ر���״̬����˸�����������״̬Ŷ��\n");
	else
		flashable = true, printf("  => �����֪��Σ��״̬������˸��\n");
	printf("\n");
	TimeLapse(0, FRESH);

	WindowSet();

	printf(
		"  ����ɻ������á�\n"
		"  ��Ҫ���裬������ص���������������������档\n"
	);

	Pause();
	return 0;
}

//�鿴��ݼ�
int KeyView() {
	Cls();
	puts("");
	printf("  ������ݼ���\n\n");
	printf(
		"  o-------o------------o\n"
		"  |w/a/s/d|    �ƶ�    |\n"
		"  |   h   |    ����    |\n"
		"  | h + g |    ����    |\n"
		"  | h + q | �鿴��ݼ� |\n"
		"  |   t   |   ������   |\n"
		"  |   p   |    ����    |\n"
		"  |  Esc  |���ر������|\n"
		"  o-------o------------o\n\n"
	);
	printf("  %lld�����Զ��浵��\n\n", (step < 120) ? (120 - step) : (20 - step % 20));

	printf("  �����˽⣬����������\n");
	Pause();
	return 0;
}

//��������
int Help() {
	Sound("Helpin");//��ֹ�������� 

	Cls();
	puts("");
	switch (place) {
	case CITY:
		printf(
			"  ���ڳǡ�\n"
			"  \n"
			"  �����������磬�������������ֱ�Ӳ��롣\n"
			"  �����ֿ����Ƕ����Ĳ�������\n"
			"  \n"
			"  ȥ���й�������ٻ���\n"
			"  �������꣬װ���Լ���\n"
			"  ��ѧУ�õ�֪ʶ��\n"
			"  ���ھӣ���������...\n"
			"  \n"
			"  ���������Ҽ��ƶ������� X �������µص㡣\n"
			"  \n"
		);
		break;

	case HOME:
		printf(
			"  ��ů�ļҡ�\n"
			"  ������Щ�¶��ļҡ�\n"
			"  \n"
			"  ����������Ϣ��\n"
			"  �ֿɷ��Ӵ�������\n"
			"  \n"
			"  ��Ҫ�����������š�\n"
			"  \n"
		);
		break;
	case KITCHEN:
		printf(
			"  ������ʳ�ĵ�����֮�ء�\n"
			"  \n"
			"  �Լ����ķ�������Լ���θ�ڡ�\n"
			"  \n"
			"  ����֮�⣬�о�ҩƷҲҪ�����\n"
			"  \n"
		);
		break;
	case SUPERMATKET:
		printf(
			"  ��ǰ���ŵ�ɫ�����ƣ�����ƽ�۳��С�\n"
			"  \n"
			"  ����Ʒ��Ÿ��ߵ�Ա������������ܣ�\n"
			"  Ȼ�����������Թ���\n"
			"  ���Ҫ�������򣬵����س����ɡ�\n"
			"  \n"
			"  �س������뿪���С�\n"
			"  \n"
		);
		break;
	case WRITING:
		printf(
			"  д��¥�ǹ����ܼ�����\n"
			"  \n"
			"  ����������Ȼ�ĳ��У��������������ֱ�ӷ����ȥ��\n"
			"  \"���������㣬��ҲҪ�����Ч�ʹ���! \"\n"
			"  \n"
			"  ���빤���ܵõ����֣����ſɵ����²���ȡ���ʡ�\n"
			"  ���ɻ��뵽�칫��ѯ�ʡ�\n"
			"  \n"
		);
		break;
	case TYPIST:
		printf(
			"  �ڴ����ң�����λ���Զ������������ġ�\n"
			"  ������Ļ�ϵĵ��ʣ�Ȼ�󰴻س�ȷ�ϡ�\n"
			"  ���˳����֣������س����ɡ�\n"
			"  \n"
			"  ����Ӧ��������磿\n"
			"  �ڴ��ֻ�����ʱ������������á�\n"
			"  \n"
			"  ���Ч�ʣ���ȡ���ཱ����\n"
			"  ���ֲ����Ļ������ڲ���Ϊ���ṩ��ѿ�͡�\n"
			"  ����������˵����²���ȡ��Ĺ��ʡ�\n"
			"  \n"
			"  ʹ�ð�������������Ŷ! \n"
			"  \n"
		);
		break;
	case SCHOOL:
		printf(
			"  ����һ��Ҫ���Լ��������������\n"
			"  ��һ��ѧϰ���ڶ���ѧϰ����������ѧϰ��\n"
			"  \n"
			"  �������⹫����ѧУ����ṩѧϰ���ϡ�\n"
			"  ѧϰʹ���ܻ��֪ʶ��������������\n"
			"  �����ȵ���ѧ¥������������\n"
			"  \n"
			"  ��Ҫ�ֳ�Σ�յ��������ⲻ��ѧУ�ķ�Χ��\n"
			"  \n"
		);
		break;
	case SCHOOL_1F:
		printf(
			"  ��ѧ¥һ�㡣"
		);
		break;//��ѧ¥һ��
	case SCHOOL_2F:
		printf(
			"  ��ѧ¥���㡣"
		);
		break;//��ѧ¥����
	case SCHOOL_3F:
		printf(
			"  ��ѧ¥���㡣"
		);
		break;//��ѧ¥����
	case SCHOOL_HIDE:
		printf(
			"  �źŲ��á�"
		);
		break;//��ѧ¥����

	case HOSPITAL:
		printf(
			"  ����ҽԺ�ṩ����ҽ�Ʒ���\n"
			"  \n"
			"  �β�Ҫ��֢��ҩ��\n"
			"  �����Ƕ�����ʳ�ơ�\n"
			"  ��Ȼ��ҽ����Ϊ���ṩָ���ġ�\n"
			"  \n"
		);

		break;
	case WEAPONSHOP:
		printf(
			"  \"���з�������\n"
			"    ����Ҳ��̫���˻�ȥ���¡�\n"
			"    ��Ҫð��ȥ��Ӧ�����÷�������\n"
			"    ��Ȼ��С�ӣ���Ǯ��˵����\"\n"
			"  \n"
		);
		break;
	}

	printf("  �����������ý��棬�����˽����ݼ���\n\n");
	printf("  �س��Թر����������\n");

	r = getord();

	if (r == 'g')
		Setting();
	else if (r == 'q')
		KeyView();

	Sound("Helpout");//note	
	return 0;
}

//�������������Ա��ڻع���ǰ������
int TaskView(int codeA, int codeB) {
	Cls();
	puts("");

	Flush();//�Ұ�����Ҫ�������� 

	switch (codeA) {
	case 1:
		switch (codeB) {
		case 1:
			P("  ���ͨ�����...", 30, 250); P("���й��������\n\n", 30, 1000);
			P("  ��Ϊ��ά�����ƣ�����Ŭ��׬ЩǮ��\n", 30, 500);
			P("  \"��������Ľ�Ǯ�Ǳ������ɵ�һ�ֹ��ߡ�\"\n\n", 30, 1000);
			P("  ǰ��д��¥׬ȡ���֣�Ȼ����������²���ȡ���ʡ�\n\n", 30, 1000);
			P("  ���ĳʱ�������ɻ󣬿������򿪰�����\n\n", 30, 1000);
			break;
		case 2:
			P("  һ�ָ��ţ�һ���ջ�...\n\n", 27, 1000);
			P("  ���ǣ�", 27);
			if (state[HUNGER] <= 2)
				P("���ӿ�ʼ�����ˡ�\n\n  ", 27, 1000);
			P("���㹤��Ŭ��Ҳ����Ӱ�����塣\n\n", 27, 1000);
			P("  ע��״̬����", 27, 250); P("����״̬����в������\n\n", 27, 1000);
			P("  ���ڿ���ȥ��������", 27, 250); P("���о����ھӼҶ��档\n\n", 27, 1000);
			break;
		case 3:
			P("  ���е���������������㡣\n\n", 24, 1000);
			P("  �������ʱ��ؽ���������⣬�������ð�����\n\n", 24, 1000);
			P("  �����еı��ɣ����Ű���򿪰�����\n\n", 24, 500);
			P("  �������Я��ʳƷ�ɡ�\n\n", 24, 1000);
			break;
		case 4:
			if (state[HUNGER] <= 2)
				P("  ���ӻ��ڹ����У���֪����������в���������ء�\n\n", 21, 1000);
			else
				P("  ��Ȼ������±����⣬��������ֹ��һ���档\n\n", 21, 1000);
			P("  ���彡���������������������á�\n\n", 21, 1000);
			P("  ��˵��ҽԺ��������˱���������\n\n", 21, 500);
			P("  ȥ����������ѵı���ָ���ɡ�\n\n", 21, 1000);
		default:
			break;
		}
		break;
	case 2:
		switch (codeB) {
		case 1:
			//ע������
			//�˺�칫�ҵ��ſ��� 
			P("  \"�ɵ�ͦ��������\"\n\n", 18, 750);
			P("  \"�ϰ�������úøɻ���Ӧ�õġ�\"\n\n", 18, 750);
			P("  \"�û��! �����и�����Ҫ�����㡣\n", 18, 500);
			P("   ������ҽ�ư��͸�����԰԰����\n", 18, 750);
			P("   �����԰�������ġ�\"\n\n", 18, 750);
			//�˴�������ӻش�ѡ���������������Ӱ�첻ͬ 
			P("  \"û����! \"\n\n", 18, 750);
			break;
		case 2:
			P("  \"��λ�ϰ����������ҽ�ư�������\"\n\n", 18, 500);//choice
			P("  \"������лл����! \n", 18, 500);
			P("   ������Ҳȥ������������\n", 18, 500);
			P("   ���ˣ�����50Ԫ���꣬���ɾ��⡣\"\n\n", 18, 500);
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (codeB) {
		case 1:
			Sound("PageThrough");
			P("  �����һ��ֽ�������ʲݵ�д��Щ�֣�\n\n", 24, 1000);

			P("    \"ѧУ��ծ���ۣ���Ҫ������ȥ�ˡ�\n", 18, 500);
			P("     �������У�����²�����! \n", 18, 500);
			P("     ����������Щ�ɰ���ѧ���أ�\n", 18, 750);
			P("     ѧУ�Ѿ�Ƿ��2000Ԫ������������! ", 18, 500); P("��ô�죿\"\n\n", 18, 1000);

			P("  ��Ȼ������֣���Ҳ���Ǹ����׵�У����\n\n", 24, 1000);
			printf("  ����������\n");

			Pause();

			Sound("PageThrough");
			Cls();
			puts("");
			P("  (����ֽ�ı���)\n\n", 24, 1000);

			P("    \"�һ�����·��! \"\n\n", 18, 1000);

			P("  �ջظոյĿ佱...\n\n", 24, 1000);
			P("  �������ܷ���ѧУ�����أ�", 24, 250); P("��Ӧ�ÿ��ǰ�æ��\n\n", 24, 500);
			break;
		}
		break;
	case 4:
		switch (codeB) {
		case 1:
		{
			P("  ֻ��������һ�£���ƿ�������ߵĵ��������ڵء�\n\n", SPL_THINK, SPS_THINK);
			P("  ����Խ��Խ����...\n\n", SPL_THINK, SPS_THINK);
			if (not decision[2]) {//�γɾֲ�
				const char *b[] = {
					"���ĸ���Ը����",
					"�����Լ��������"
				};
				Decide(2, Pitch(2, b, 2));
			}
			if (decision[2] == 1) {
				P("  �ԣ����ھ�ȥ��������¥�����ˡ�\n\n", 18, 1000);
				P("  ���������أ�\n\n", 18, 1000);
			}
			else
				if (decision[2] == 2) {
					P("  ��е���죬���չ��죬�Ͻ��뿪����ɡ�\n\n", 18, 1000);
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

	printf("  => ����%d-%d��%s\n\n", codeA, codeB, kTask[codeA].name[codeB]/*.c_str()*/);

	printf("     ��������ݼ���������������ء�\n");

	Pause();

	return 0;
}

//��ʾ������
int Task() {
	Sound("Pagein");

	Mapin("Task");//1Ϊǰ׺����ͼ��(Map)�й� 
	Mapout(UNFOLD);

	int Takecnt = 0;
	for (int i = 1; i <= kTaskSeriecnt; ++i)
		if (task_rate[i] != 0) {
			++Takecnt;

			Position(Takecnt * 2, 2);
			if (task_rate[i] > 0) {
				if (task_rate[i] > kTask[i].cnt)
					printf("ϵ��%d�����! ", i);//����д������
				else
					printf("%d-%d��%s", i, task_rate[i], kTask[i].name[task_rate[i]]);
			}
			else
				printf("ϵ��%dʧ�ܡ�", i);

			Position(Takecnt * 2 + 1, 1);
			printf("o----------------------------------------------------------o");
		}

	r = getord(); n = r - '0';

	if (between(n, 1, kTaskSeriecnt))
		if (between(task_rate[n], 1, kTask[n].cnt))//����ִ�и�ϵ������ 
			TaskView(n, task_rate[n]);
	//ef(TaskRate == -1)

	Sound("Pageout");

	return 0;
}

//��Ǯ�����ˣ������ӵ�
bool Pay(int money_need) {
	if (not(money_need there))
		return false;

	TimeLapse(11, FIX);
	if (money < money_need)
		return false;
	money -= money_need;
	//����Ҫ�б߿����ʾ
	if (border)
		Tips(""), printf("֧��%dԪ...", money_need);
	SoundWait("MoneyPaid");
	return true;
}

//��ý�Ǯ
bool Gain(int money_back) {
	if (!(money_back there))
		return false;
	TimeLapse(11, FIX);
	money += money_back;
	if (border)
		Tips(""), printf("�õ�%dԪ��", money_back);
	SoundWait("MoneyBack");
	return true;
}

//�Զ���
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

//����
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
			printf("<= ��һҳ");
		}
		if (Pagecur != kBook[c].pagecnt) {
			Position(19, 46);
			printf("��һҳ =>");
		}
		Position(19, 24);
		printf("�س��Ժ���");

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

//��ʾ�򸲸������
bool InputBox(bool visable) {
	if (visable) {
		Position(16, 45); printf("o--��-��--o");
		Position(17, 45); printf("|         |");
		Position(18, 45); printf("o---------o");
	}
	else {
		Mapout(UNFOLD, 16, 18, 45, 55);
	}
	return true;
}

//�����������֣���������
bool CommonInput(int type, bool expand, int lenlim, bool InputBoxable) {
	if (InputBoxable)
		InputBox(true);

	PstInput();
	if (!Input(type, expand, lenlim))//�����˰���ɶ��
		return false;

	if (InputBoxable)
		InputBox(false);
	return true;
}

//������һ��λ�á���ǿ����ɶ���
bool MoveBack() {
	TimeLapse(move_unit_time, WALK);
	sx = tx, sy = ty;
	return true;
}

//�ڱ�����
bool UseItem(int c, int num) {
	int Used = 0;
	switch (kItem[c].type) {
	case FOOD:
	{//ʳ����о�������
		switch (c) {
		case COOKIE:
		{
			Tips(""), printf("����%dƬ����...", num);
			Used = Eat(kItem[COOKIE].code, num);
			if (Used == 0)//result
				Tips("һ��Ҳ�Բ����ˡ�");
			else if (Used < num)
				Tips(""), printf("ֻ�Ե���%dƬ...�е��塣", Used);
			else
				Tips("�ɴ�����");
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

//����ͳ��blo����Ϣ
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

//����num����Ʒc
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

//ϵͳ������Ʒ�����õ���putitem(-1)
bool PutItem(int c, int num) {
	int Space = 0;
	for (int i = 1; i <= blocknum; ++i) {
		if (block[i].itm == c)
			Space += kItem[c].carry - block[i].num; else
			if (block[i].itm == 0)
				Space += kItem[c].carry;
	}

	if (Space < num) {//����
		Sound("PackFull");
		return false;
	}

	SoundWait("PutItem");

	TimeLapse(10 * num, FIX);//��С���
	for (int i = 1; i <= blocknum and num there; ++i)//��ǰ�����������
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
	//���ȷŵ�ͬ�� 
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

//��ʾ��blo�����Ʒ
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

//�򿪰���
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
			border = true;//Ҳ�ǰ������
			Stateout();

			Position(17, 36), printf("%d", money);

			for (int i = 1; i <= blocknum; ++i) {
				if (block[i].num == 0)
					continue;
				Blockout(i);
			}

			Tips("���������ѡ����Ʒ���򰴻س����ء�");

			remap = false;
		}

		CommonInput(INTEGER, false);

		if (n == 0)
			break;
		if (between(n, 1, blocknum) and block[n].itm there) {
			//��ʾѡ��״̬
			int blo = n;//ѡ���ĸ���

			Sound("Cursor");
			int x = (blo - 1) / 6, y = (blo - 1) % 6;
			Position(1 + x * 5, 1 + y * 9), putchar('o');
			Position(1 + x * 5 + 5, 1 + y * 9), putchar('o');
			Position(1 + x * 5, 1 + y * 9 + 9), putchar('o');
			Position(1 + x * 5 + 5, 1 + y * 9 + 9), putchar('o');

			Tips(""), printf("%s:����ʹ����Ŀ�����ߣ䡢����������Ų����", kItem[block[blo].itm].name);

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
					Tips("���������ˡ�");
				break;
			case 'd'://discard
				if (block[blo].num == 1)
					n = 1;
				else {
					Tips("������Ŀ...");

					CommonInput(INTEGER, false);
				}
				if ((n = noMore(n, block[blo].num)) >= 1) {
					Sound("Discard");//�������ǲ��õĶ���
					TimeLapse(10 * n, FIX);
					block[blo].num -= n;
					Blockout(blo);
					Tips(""), printf("�ոն�����%d%s%s��", n, kItem[itm].meas, kItem[itm].name);
				}
				else
					Tips("�����Ҳ��̫��ʹ������");
				break;
			case 'm':
			{//move
				if (block[blo].num == 1)
					n = 1;
				else {
					Tips("�ƶ���Ŀ...");

					CommonInput(INTEGER, false);
				}

				int num = n;//������Ҫ�ݴ�
				if ((num = noMore(num, block[blo].num)) >= 1) {
					Tips("Ŀ�����...");

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
								Tips(""), printf("��%d%s%s�ŵ��˵�%d�����ӡ�", num, kItem[itm].meas, kItem[itm].name, n);
							}
							else
								Sound("PackFull"), Tips(""), printf("Ŀ�����װ������Щ%s��", kItem[block[blo].itm].name);
						}
						else
							Tips("���˸���Ƿ��");
					}
					else
						Tips("���ڿռ�С�");
				}
				else
					Tips("��֡�");
				break;
			}

			default:
				Tips("��������");
				break;
			}

			//ȡ����ʾѡ��״̬
			if (not remap) {
				x = (blo - 1) / 6, y = (blo - 1) % 6;
				Mapput(1 + x * 5, 1 + y * 9, false);
				Mapput(1 + x * 5 + 5, 1 + y * 9, false);
				Mapput(1 + x * 5, 1 + y * 9 + 9, false);
				Mapput(1 + x * 5 + 5, 1 + y * 9 + 9, false);
			}
		}
		else
			Tips("���������ѡ�񣬻�س����ء�");
	}
	Sound("Packout");
	inpack = false;
	return 0;
}

//��Body����˺���ˢ��
bool Injure(Bodyinfo &body, double price) {
	body.life -= price;
	TimeLapse();
	return true;
}

//˯��
bool Asleep(long long sleep_time/*, long long TimeSnooze*/) {
	Cls();
	mciSS("open Data\\Music\\Asleep.mp3 alias Asleep");
	if (state[LIFE] > 2)//����ʱ������������
		mciSS("play Asleep repeat");
	//�ɹ���˯ 

	//���벻Ӱ����

	int zizz = 0;//ZZZ�ַ�����
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
			printf("̰˯�������...");
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

//�ڲ����룬֧�ִ򿪱���������� 
bool Input(int type, bool expand, int lenlim) {
	//����ÿ��һ�������Զ����棬�ؼ��¼�ֱ�ӱ��� 
	switch (type) {
	case ORDER://char ��int�洢
		PreseTry();//Things were done
		r = getord();

		if (expand) {//�����ڿ���reMap�Ľ������More
			if (r == ESC) { End(0); remap = true; return false; }
			if (r == 'h') { Help(); remap = true; return false; }
			if (r == 't') { Task(); remap = true; return false; }
			if (r == 'p') { Enter(); Pack(); remap = true; return false; }
			if (r == 'v') {//Debugging
				me.Examine();
				Tips("");
				printf("��%.3lf ��%.1lf ����%.1lf ʧ��%.3lf ��%.3lf", me.mus, me.ene, me.life, me.ent, me.sick);
				return false;
			}
			if (r == 'm') {//Debugging
				me.Examine();
				Tips("");
				printf("��%.3lf ֬%.3lf ��%.3lf �°���%.3lf ʱ%02lld:%02lld", me.pro, me.fat, me.car, me.can, hour, minute);
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

//���ú����������ƶ��������ƶ��������ƶ��Ƿ�ɹ� 
bool Move() {
	Position(sx, sy);
	putchar('i');
	Position(sx, sy);//���Y���ң������ù�� 

	if (!Input(ORDER, true))//�ȴ����� 
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
	CME = 0;//�������ƶ�����

	//�����ϰ���
	if (iswall(atlas[sx][sy])) {
		MoveBack();
		Tips("�ǵ�����谭��ǰ��...");
		SoundHit();
		return false;//�ƶ�����
	}
	if (atlas[sx][sy] == '~') {
		MoveBack();
		Tips("������ˮ�������");
		return false;
	}

	TimeLapse(move_unit_time, WALK);
	return true;
}
