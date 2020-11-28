#include "pch.h"
/*
	Free 3.0的所有地点
*/

int Supermarket() {
	{//初始化标志
		map_file = "Supermarket";
		ins_coe = 1.60;
		move_unit_time = 7;
	}

	remap = true;

	while (place == SUPERMATKET) {
		if (remap) {
			CommonreMap();
			Tips("把序号告诉店员，她会给出介绍的；回车即可返回。");

			remap = false;
		}

		if (!CommonInput()) continue;
		switch (n) {
		case 1:
			Tips("\"香烤鸡肉，分量十足。客官想点几份？\"");
			//Position(下);

			if (!CommonInput()) break;
			if (n there) {//未来购买行为可能程序化
				if (Pay(n * 21)) {
					Tips(""), printf("点了%d只烤鸡", n);
					if (state[HUNGER] <= 1) printf("后立刻狼吞虎咽..."); else printf("。哪里飘来味道...");

					int eaten = Eat(4, n);
					if (eaten == 0)
						Tips("太撑了。油脂酸臭，令人作呕。");
					else if (eaten < n)
						Tips(""), printf("嗝...好不容易才吃下了%d只。", eaten);
					else
						Tips("表皮脆软，肉质尚可。");
				}
				else
					Tips("\"您没带够钱吧...\"");
			}
			else
				Tips("\"伙计，咋回事？\"");
			break;
		case 2:
			Tips("\"丹林烘焙虎皮夹心面包，请现场食用。您要多少？\"");

			if (!CommonInput()) break;
			if (n there) {
				if (Pay(n * 8)) {
					Tips(""), printf("咀嚼着这%d块面包，嗯...", n);

					int eaten = Eat(2, n);
					if (eaten == 0)
						Tips("撑了。有些审美疲劳。");
					else if (eaten < n)
						Tips(""), printf("只吃下其中%d块，再吃可要撑了。", eaten);
					else
						Tips("麦香让人回味。");

					//Task 1-3
					if (task_rate[1] == 2) {
						Delay(1500);//回味
						task_rate[1] = 3;
						TaskView(1, 3);
						remap = true;
					}
				}
				else
					Tips("\"我确信您没带足钱。\"");
			}
			else
				Tips("\"您说什么？我没听清。\"");
			break;
		case 3:
			Tips("\"甜趣轻薄，可放进背包。每包22片，买几包？\"");

			if (!CommonInput()) break;
			if (n there) {
				if (money >= n * 12) {
					if (PutItem(COOKIE, n * 22)) {//正常 
						Pay(n * 12);
						//Sound
						Tips(""), printf("\"这里是%d包甜趣。ｐ键打开包裹。\"", n);
					}
					else
						Tips("背包里放不下这些饼干。");
				}
				else
					Tips("\"您携带的现金不够。\"");
			}
			else
				Tips("\"我好像不理解您说的...\"");
			break;
		case 4:
			Tips("\"手表能为你指示时间。这位老板，您想要几只手表？\"");

			if (!CommonInput()) break;
			if (n there) {
				if (Pay(n * 298)) {
					watch += n;//一些声望
					TimeLapse(n * 7 minutes, FIX);//配备手表
					Tips(""), printf("\"为您配备%d只手表。可以打开背包查看时间。\"", n);
				}
				else
					Tips("\"先生，您不会买不起吧？\"");
			}
			else
				Tips("\"都把我弄糊涂了。\"");
			break;
		case 5:
			Tips("\"母亲牛肉棒，秘制调配，高蛋白。请问要多少？\"");

			if (!CommonInput()) break;
			if (n there) {
				int MoneyNeed = n * 9;
				if (Pay(MoneyNeed)) {
					Tips(""), printf("面前放着%d条牛肉棒，尝尝...", n);

					int eaten = Eat(5, n);
					if (eaten == 0)
						Tips("亚硝酸盐？暂时不想再吃了。");
					else if (eaten < n)
						Tips(""), printf("吃了%d条，口中发酸，难以下咽。", eaten);
					else
						Tips("肉质紧实，口感独特。");
				}
				else
					Tips("钱不够了。");
			}
			else
				Tips("反物质？");
			break;
		case 6:
			Tips("\"财产可能意外损失，仅除保险箱内的。买后快递到家! \"");
			break;
		case 7:
			Tips("\"你能利用它及时治疗外伤。附赠一些药品! \"");
			break;

		case 0:
			MoveBack();
			place = CITY;
			sx = 12, sy = 36;
			break;

		default:
			Sound("Error");
			TimeLapse(5, THINK);
			Tips("请输入商品序号，或向右走以返回。");
			break;
		}
	}
	return 0;
}

int WeaponShop() {
	{
		map_file = "WeaponShop";
		ins_coe = 1.40;
		move_unit_time = 8;
	}

	remap = true;

	while (place == WEAPONSHOP) {
		if (remap) {
			CommonreMap();
			Tips("老板按序号作出介绍；向下返回。");

			remap = false;
		}

		if (!Input(ORDER, true))
			continue;
		if (r == 's') r = DOWN_KEY;

		switch (r) {
		case DOWN_KEY:
			MoveBack();
			place = CITY;
			sx = 9, sy = 23;
			break;

		default:
			TimeLapse(5, THINK);
			Tips("请输入序号，或向下走以便离开。");
			break;
		}
	}
	return 0;
}

int Bedroom() {
	{
		map_file = "Bedroom";
		ins_coe = 0.48;
		move_unit_time = 6;
	}

	Mapin();
	Mapout();
	border = false;

	Input(ORDER, true);//不会进入帮助
	r = Directed(r);

	if (r == UP_KEY) {
		long long TimeSleep = 0;

		if (state[SLEEPINESS] == 2 and (hour >= 16 or hour <= 4)) {//仅光线较弱时可以入睡
			//要保证第一天22:00入睡，预期醒来时间为早晨6时
			TimeSleep = 4 hours + abs(hour - 12) hours / 2;
		}
		else
			if (state[SLEEPINESS] <= 1) {//不要突然
				TimeSleep = 4 hours + abs(hour - 12) hours / 2 + me.TS / 2;//没毛病 
			}
			else {
				Tips("躺在床上合了合眼，可睡不着...按键返回。");
				Pause();
			}

		if (TimeSleep) {
			TimeSleep += (int)(RandAround(0, 60 minutes));

			Asleep(TimeSleep/*, noLess(3 hours - TimeSleep / 4, 0)*/);
			//	Prese();//自动保存。存活才会保存
		}
	}

	MoveBack();
	place = HOME;
	sx = 7, sy = 34;

	return 0;
}

int Kitchen() {
	{
		map_file = "Kitchen";
		ins_coe = 1.20;
	}

	remap = true;

	while (place == KITCHEN) {
		if (remap) {
			CommonreMap();
			Tips("来到厨房，跃跃欲试。如果要返回就向下走。");

			remap = false;
		}

		if (!Input(ORDER, true))
			continue;
		r = Directed(r);

		switch (r) {
		case DOWN_KEY:
			MoveBack();
			place = HOME;
			sx = 7, sy = 11;
			break;
		default:
			break;
		}
	}
	return 0;
}

int Home() {
	{
		map_file = "Home";
		ins_coe = 0.70;
		move_unit_time = 6;
	}

	mciSS((state[LIFE] > 2) ?
		"open Data\\Music\\Home.mp3 alias Home" : 
		"open Data\\Music\\Homeless.mp3 alias Home");
	mciSS("play Home");

	remap = true;
	while (place == HOME) {
		if (remap) {
			CommonreMap();
			Tips(state[LIFE] <= 2 ?
				"这里很暖和。" :
				"家的感觉真好。");

			remap = false;
		}
		if (!Move())
			continue;

		switch (atlas[sx][sy]) {
		case 'K':
			place = KITCHEN;
			break;

		case 'B':
			place = BEDROOM;
			break;

		case 'D':
			place = CITY;
			sx = 15, sy = 39;
			break;

		default:

			break;
		}
	}

	mciSS("stop Home");
	mciSS("close Home");
	return 0;
}

int Library() {
	Cls();
	Pause();
	return 0;
}

int DiningHall() {
	Cls();
	Pause();
	return 0;
}

int SchoolHistory() {
	Cls();
	Pause();
	return 0;
}

int ObjectHouse() {
	Cls();
	Pause();
	return 0;
}

int NeighborBedroom() {
	{
		map_file = "NeighborBedroom";
		ins_coe = 0.50;
		move_unit_time = 6;
	}

	remap = true;

	while (place == NEIGHBOR_BEDROOM) {
		if (remap) {
			CommonreMap();
			Tips("轻轻走进邻居家卧室。");

			remap = false;
		}

		if (!Move())//邻居卧室 
			continue;

		switch (atlas[sx][sy]) {
		case 'D':
			place = NEIGHBOR;
			sx = 12, sy = 38;
			break;

		default:

			break;
		}
	}
	return 0;
}

int Neighbor2F() {
	{
		map_file = "Neighbor2F";
		ins_coe = 0.90;
		move_unit_time = 6;
	}

	mciSS((decision[1] == 0) ?
		"open Data\\Music\\ItomakiA.mp3 alias Itomaki" :
		"open Data\\Music\\ItomakiB.mp3 alias Itomaki");
	mciSS("play Itomaki repeat");

	remap = true;

	while (place == NEIGHBOR_2F) {
		if (remap) {
			CommonreMap();

			Tips((decision[1] == 0) ?
				"是细碎的音乐，源头在哪里呢。" : 
				"我对这里有阴影!");

			remap = false;
		}

		if (!Move())//邻居二楼 
			continue;

		switch (atlas[sx][sy]) {
		case 'R':
			MoveBack();
			if (decision[1] == 0) {
				Decide(1, 1);

				mciSS("stop Itomaki");
				mciSS("close Itomaki");
				Tips(""), P("...", 1000);
				P("滑落了。", 30, 0, false);
				SoundWait("Crash");

				mciSS("open Data\\Music\\ItomakiB.mp3 alias Itomaki");
				mciSS("play Itomaki repeat");

				Tips("我做了什么，让眼前只剩碎片...");
			}
			else
				Tips("青瓷花瓶破碎了。");

			break;

		case 'L':

			break;

		case 'S':
			place = NEIGHBOR;
			sx = tx, sy = ty;//一个特殊的返回方式 
			//正在走下楼梯
			if (decision[1] == 1 and task_rate[4] == 0) {
				task_rate[4] = 1;
				TaskView(4, 1);
			}
			break;

		default:

			break;
		}
	}
	mciSS("stop Itomaki");
	mciSS("close Itomaki");
	return 0;
}

int Neighbor() {
	{
		map_file = "Neighbor";
		ins_coe = 0.75;
		move_unit_time = 6;
	}

	remap = true;

	while (place == NEIGHBOR) {
		if (remap) {
			CommonreMap();
			Tips("似乎没有人。");

			remap = false;
		}

		if (!Move())
			continue;

		switch (atlas[sx][sy]) {
		case 'S':
			place = NEIGHBOR_2F;
			sx = tx, sy = ty;//一个特殊的进入方式 
			break;

		case 'B':
			place = NEIGHBOR_BEDROOM;
			sx = 15, sy = 26;
			break;

		case 'D':
			place = CITY;
			sx = 13, sy = 39;
			break;

		default:

			break;
		}
	}
	return 0;
}

int SchoolHide() {
	{
		map_file = "SchoolHide";
		ins_coe = 1.80;
		move_unit_time = 7;
	}

	mciSS("open Data\\Music\\Hide.mp3 alias Hide");
	mciSS("play Hide repeat");

	remap = true;

	while (place == SCHOOL_HIDE) {
		if (remap) {
			CommonreMap();
			Tips("空气欲要透露寒冷的消息。");
			remap = false;
		}

		if (!Move())//密室
			continue;

		switch (atlas[sx][sy]) {
		case 'B':
			//Task 3-1
			if (task_rate[3] == 0) {
				task_rate[3] = 1;
				TaskView(3, 1);
				remap = true;
			}
			else
				Tips("箱子里曾放过一张纸。");

			MoveBack();
			break;

		case 'd':
			place = SCHOOL_2F;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}

	mciSS("stop Hide");
	mciSS("close Hide");
	return 0;
}

int School3F() {
	{
		map_file = "School3F";
		ins_coe = 1.00;
		move_unit_time = 12;
	}

	remap = true;

	while (place == SCHOOL_3F) {
		if (remap) {
			CommonreMap();
			Tips("向南可以望到校门。");

			remap = false;
		}

		if (!Move())//教学楼 
			continue;

		switch (atlas[sx][sy]) {
		case 'P':
			MoveBack();
			break;

		case 'D':
			place = SCHOOL_2F;
			sx = 9, sy = ty;
			break;

		default:

			break;
		}
	}
	return 0;
}

int School2F() {
	{
		map_file = "School2F";
		ins_coe = 1.00;
		move_unit_time = 12;
	}

	remap = true;

	while (place == SCHOOL_2F) {
		if (remap) {
			CommonreMap();
			Tips("第三层的下方。");

			remap = false;
		}

		if (!Move())//教学楼 
			continue;

		switch (atlas[sx][sy]) {
		case 'U':
			place = SCHOOL_3F;
			sx = 7, sy = ty;
			break;

		case 'P':
			//SchoolHistory();
			MoveBack();
			//reMap = true;
			break;

		case 'D':
			place = SCHOOL_1F;
			sx = 9, sy = ty;
			break;
		case 'a':
			place = SCHOOL_HIDE;
			sx = sx, sy = 54;
			break;
		default:

			break;
		}
	}
	return 0;
}

int School1F() {
	{
		map_file = "School1F";
		ins_coe = 1.00;
		move_unit_time = 12;
	}

	remap = true;

	while (place == SCHOOL_1F) {
		if (remap) {
			CommonreMap();
			Tips("花岗岩地板。");

			remap = false;
		}

		if (!Move())//教学楼 
			continue;

		switch (atlas[sx][sy]) {
		case 'U':
			place = SCHOOL_2F;
			sx = 7, sy = ty;
			break;

		case 'P':
			//ObjectHouse();
			MoveBack();
			//reMap = true;
			break;

		case 'D':
			place = SCHOOL;
			sx = 4, sy = 13;
			break;

		default:

			break;
		}
	}
	return 0;
}

int School() {
	{
		map_file = "School";
		ins_coe = 1.10;
		move_unit_time = 24;
	}

	remap = true;

	while (place == SCHOOL) {
		if (remap) {
			CommonreMap();
			Tips("远远书声。");

			remap = false;
		}

		if (!Move())//学校 
			continue;

		switch (atlas[sx][sy]) {
		case 'H':
			//DiningHall(); 
			// RETURN
			Tips("装修的油漆木屑味。");
			MoveBack();
			break;

		case 'T':
			place = SCHOOL_1F;
			sx = 7, sy = 7;
			break;

		case 'D':
			place = CITY;
			sx = 6, sy = 50;
			break;

		default:

			break;
		}
	}
	return 0;
}

int MER() {//MedicalExaminationReport 依然在内科（可能是别的医院吧）
	border = false;//仅限于此地
	Cls();
	puts("");

	P("  门诊室里很平静。\n", SPL_SPEAK, SPS_SPEAK);
	if (!between(hour, 5, 21))
		P("  灯光暗淡，水泥墙的不平整更加显露。\n", SPL_SPEAK, 1000);
	P("\n");

	{//形成局部
		const char *b[] = {
			"  \"您好，请是问需要看病吗？\"\n",
			"  \"您是不是需要帮助？\"\n",
			"  该向医生问问身体情况吗？\n"
		};
		P(RandS(3, b), SPL_SPEAK, SPS_SPEAK);
	}
	puts("");
	int pit = 0;
	{//形成局部
		const char *b[] = {
			"是的...",
			"算了。"
		};
		pit = Pitch(2, b, 2);
	}
	if (pit == 2)
		return -1;

	int Prescription = false;

	Cls();
	puts("");
	TimeLapse(6 minutes, FIX);
	me.Examine();//强调体检

	P("  \"坐正。\"", SPL_SPEAK, SPS_SPEAK);
	if (state[LIFE] <= 2)
		P("\n  可我现在很难做到...", SPL_SPEAK, 1500);
	P("\n\n");
	Flush();//片段的末尾

	if (GetItemnum(Rx)) {
		P("  \"你不是还带着处方吗？", SPL_SPEAK, SPS_SPEAK), P("去拿药吧。\n", SPL_SPEAK, SPS_SPEAK);
		P("   放心，药师他是会进一步检查的。\"\n\n", SPL_SPEAK, 1000);
		P("  按键离开...\n");
		Pause();
		return -1;
	}

	if (state[MUSCLE] <= 1) {
		P("  \"看看，最近身体保养不够。\n", SPL_SPEAK, 1000);
		Happen(0.3) ?
			P("   这个饮食要调整好，", SPL_SPEAK, 0) ://口语
			P("   多吃蔬菜，", SPL_SPEAK, 0);
		P("平时加强锻炼", SPL_SPEAK, 0);
		Happen(0.5) and
			Happen(0.5) ?
			P("，记牢", SPL_SPEAK, 0) :
			P("，记住", SPL_SPEAK, 0);

		P("。\"\n\n", SPL_SPEAK, 1000);
	}
	Happen(0.5) and P("  他从柜子里抽出一本簿子，低头翻了起来。\n\n", SPL_SPEAK, 1500, false);
	Flush();

	P("  医生转过身来，观察着他所谓的气色...\n", SPL_SPEAK, 1500);
	if (state[SLEEPINESS] <= 1)
		Happen(0.4) ?
		P("  \"脸色疲惫得很，看完病先回去休息吧。\"\n", SPL_SPEAK, 1500) :
		P("  \"睡眠太少，是不是？注意多休息。\"\n", SPL_SPEAK, 1500);
	P("\n");
	Flush();

	P("  他随后戴上听诊器，把听诊头轻贴在我胸前。\n", SPL_SPEAK, 1500);
	Happen(0.4) ?
		P("  接着又换了个角度，眼神略有迟疑。\n", SPL_SPEAK, 1000) :
		Happen(0.5) ?
		P("  \"来，深呼吸一次。\"\n", SPL_SPEAK, 1000) :
		P("  \"发声'啊'，来。\"\n", SPL_SPEAK, 1000);

	Pause();
	Cls();
	puts("");
	if (state[ILLNESS] <= 3) {
		SoundCough();
		Prescription = true;
		if (state[ILLNESS] <= 1)
			P("  \"你这个肺部活动异常很明显。\"\n", SPL_SPEAK, 1000);
		else
			P("  \"是感冒了吗？呼吸道有点不对劲。\"\n", SPL_SPEAK, 1000);
	}
	else
		P("  他的微笑分散了紧张。\n", SPL_SPEAK, 1000);
	P("\n");
	Flush();

	P("  ...随后，听诊头放在了腹部。\n", SPL_SPEAK, 1500);
	if (state[HUNGER] <= 1) {
		P("  \"胃肠道不大对劲，我看是饿着了吧。\"\n", SPL_SPEAK, 1000);
	}
	else
		if (state[HUNGER] >= 5) {
			Prescription = true;
			P("  \"如果你想要，待会给你开点消食片吧。\"\n", SPL_SPEAK, 1000);
		}
		else
			P("  \"嗯，没什么毛病。\"\n", SPL_SPEAK, SPS_SPEAK);
	P("\n");
	Flush();

	if (Prescription) {
		P("  \"好，处方我已写了，领着去药房拿药。\n", SPL_SPEAK, SPS_SPEAK);
		P("   拿处方许可，请付15元诊断费。\"\n\n", SPL_SPEAK, 1000);
		int pit = 0;
		{
			const char *b[] = {
				"我这就付款...",
				"不用了，谢谢。"
			};
			pit = Pitch(2, b, 2);
		}

		if (pit == 1) {
			if (money >= 15) {
				Pay(15);
				PutItem(Rx);
				Cls();
				puts("");
				Happen(0.5) ?
					P("  \"别忘了去领取处方...\"\n\n", SPL_SPEAK, 1000) :
					P("  \"记得去领取处方啊。\"\n\n", SPL_SPEAK, 1000);
			}
			else {
				Cls();
				puts("");
				P("  \"钱没带够哪。", SPL_SPEAK, SPS_SPEAK);
				P("不过，本着治病救人的原则，这次算了吧。\"\n\n", SPL_SPEAK, 1000);
				Pay(money);
				PutItem(Rx);
			}
		}
	}
	else {
		P("  \"先这样吧。身体最重要，别忘了。有状况请再来。\"\n\n", SPL_SPEAK, 1000);

	}
	P("  按键离开...\n");
	Pause();
	return 0;
}

int Internal() {
	{
		map_file = "Internal";
		ins_coe = 0.80;//还好不算差的环境
		move_unit_time = 12;
	}

	remap = true;

	while (place == INTERNAL) {
		if (remap) {
			CommonreMap();
			Tips("内科室传来变化的细碎的声音。");
			remap = false;
		}

		if (!Move())//内科
			continue;
		switch (atlas[sx][sy]) {
		case 'b':
			MoveBack();
			if (GetItemnum(BOOK_OF_SELFCARE))
				Tips("好像已经有一本保健手册，那就不浪费社会资源了。"); else
				if (PutItem(BOOK_OF_SELFCARE, 1)) {
					Tips("架上摆着几本薄薄的保健手册。取一本来，放入包裹了。");
					//Task 1-5 open
					if (task_rate[1] == 4) {
						Sound("TaskComplete");
						task_rate[1] = 5;
					}
				}
				else
					Tips("包裹里放不下手册。");
			break;
		case 'A':
			MER();

			MoveBack();
			remap = true;
			break;
		case 'D':
			place = HOSPITAL;
			sx = 16, sy = 20;
			break;
		default: break;
		}

	}
	return 0;
}

int OutWound() {
	Cls();
	Pause();
	return 0;
}

int Hospital() {
	{
		map_file = "Hospital";
		ins_coe = 2.05;
		move_unit_time = 25;
	}

	remap = true;

	while (place == HOSPITAL) {
		if (remap) {
			CommonreMap();
			Tips("医院消毒水的味道，总让人回想过去的事。");

			remap = false;
		}

		if (!Move())//医院 
			continue;

		switch (atlas[sx][sy]) {
		case 'I':
			place = INTERNAL;
			sx = 13, sy = 51;
			break;

		case 'O':
			place = 110502;
			break;

		case 'G':
			Tips("小草也会疼。");
			//Money -= 10;
			MoveBack();
			break;

		case 'D':
			place = CITY;
			sx = 14, sy = 27;
			break;

		default:

			break;
		}
	}
	return 0;
}

int Typist() {
	{
		map_file = "Typist";
		move_unit_time = 17;
		ins_coe = 1.00;
	}

	remap = true;

	long long tot_timeout = 0;

	int combo = 0;
	int cur_score = 0, prize = 0;
	int A = 0, APM = 0;

	string cur_word, nxt_word;
	long long input_timeout;
	while (place == TYPIST) {
		if (remap) {
			CommonreMap();

			SoundCover("Machine");

			nxt_word = Converted(kLexicon[rand() % kWordcnt]);
			Position(6, 14); P("打字员系统启动", 0, 125);
			Position(8, 14); P("请输入指定的词汇并回车确认", 0, 125);
			Position(10, 14); P("单个回车将关闭系统", 0, 125);//Map的一部分 

			//启动
			TimeLapse(5 minutes, THINK);

			Position(12, 14); P("按ｇ进入设置，其余键开始", 0, 125);
			Input(ORDER, false);

			if (r == 'g') {
				PstC(6, 14, 33); printf("欢迎来到设置");
				PstC(8, 14, 33); printf("偏好紧凑的代码风格 键入ｔ");
				PstC(10, 14, 33); printf("若否 请按其它任意键");
				PstC(12, 14, 33);

				Input(ORDER, false);

				Sound("Code");
				if (r == 't')
					code_style |= TIGHT, PstC(12, 14, 33), printf("=> 紧凑码风已开启 ");
				else
					code_style &= ~TIGHT, PstC(12, 14, 33), printf("=> Java风格已启用 ");

				printf("按键继续");

				Pause();
				remap = true;
				continue;
			}

			remap = false;
		}

		cur_word = nxt_word;

		PstC(8, 14, 33);
		printf("输入词汇并发送 单个回车退出");
		PstC(10, 14, 33);
		printf("%s", cur_word.c_str());

		nxt_word = Converted(kLexicon[rand() % kWordcnt]);
		PstC(14, 14, 33);
		printf("=> %s", nxt_word.c_str());

		PstC(12, 14, 33);
		input_timeout = GetTimeout();
		int input_res = Input(STRING, true, 33);//[打开帮助]等操作，这里也要耗时
		input_timeout = GetTimeout() - input_timeout;

		tot_timeout += input_timeout;
		TimeLapse(noMore(input_timeout * 32 / 100, 80 minutes), TYPE);

		if (!input_res)
			continue;

		if (s == "") {//离开打字室 
			MoveBack();
			place = WRITING;
			sx = 7, sy = 40;
			break;
		}

		if (s == cur_word) {
			SoundCover("Perfect");

			work_score += s.length();
			cur_score += s.length();
			A += s.length();//注意，APM输入正确会增加，输入错误则不变 

			PstC(6, 14, 33);
			printf("精准输入 本轮工分总计 %d", cur_score);
			++combo;
			if (combo >= 3) {
				PstC(7, 32, 15);
				printf("%9d连击! ", combo);
			}
		}
		else {
			SoundCover("Mistake");

			int loss = noMore((int)s.length(), cur_score);
			work_score -= loss;
			cur_score -= loss;

			PstC(6, 14, 33);
			printf("发现差异 本轮工分总计 %d", cur_score);
			PstC(7, 32, 15);
			combo = 0;
		}
	}

	PstC(6, 14, 33);
	printf("结束码字");
	PstC(7, 14, 33);
	printf("本轮基本薪资为 %d 工分", cur_score);
	prize = (int)(noLess(cur_score - tot_timeout * 100 / 60 / 1000, 0));
	PstC(8, 14, 33);
	printf("依据工作效率 奖金 %d", prize);
	work_score += prize;

	if (tot_timeout > 0)
		APM = (int)(A minutes * 1000 / tot_timeout);
	else
		APM = 0;
	PstC(9, 14, 33);
	printf("APM %d", APM);
	PstC(10, 14, 33);

	PstC(11, 14, 33);
	printf("个人工分共计 %d", work_score);
	PstC(12, 14, 33);
	printf("工分可在人事部兑换工资");

	if (tot_timeout >= 60 * 1000 and APM >= 100)
		reward_meal = 1;
	PstC(13, 14, 33);
	if (reward_meal)
		printf("请随时前往后勤部领取快餐");

	PstC(14, 14, 33);

	Pause();
	return 0;
}

int Writing() {
	{
		map_file = "Writing";
		ins_coe = 1.00;
		move_unit_time = 12;
	}

	remap = true;

	while (place == WRITING) {
		if (remap) {
			CommonreMap();
			Tips("写字楼厅堂，空旷得能回响脚步声。");

			remap = false;
		}

		if (!Move())//写字楼 
			continue;

		switch (atlas[sx][sy]) {
		case 'O':
			//mciSS();
			Tips("");

			P("...", 1000, 0, false);

			Tips("敲了门，但无人回应。");

			MoveBack();
			break;

		case 'W':
			if (!between(hour, 0, 5))
				place = TYPIST;//打字室 
			else {
				Tips("[无操作时 系统在凌晨0:00到6:00自动进入维护状态]");
				MoveBack();
			}
			break;

		case 'R':
			if (work_score > 1) {
				Gain(work_score / 2);
				work_score -= (work_score / 2) * 2;//不要简写

				//Task 1-2
				if (task_rate[1] == 1) {
					SoundCover("Message");
					Delay(750);
					task_rate[1] = 2;
					TaskView(1, 2);
					remap = true;
				}
			}
			else
				Tips("\"每2工分能换为1元工资。\"");

			MoveBack();
			break;

		case 'D':
			place = CITY;
			sx = 9, sy = 42;
			break;

		case 'B':
			if (!(hour >= 22 or hour <= 6)) {
				if (reward_meal) {
					if (task_rate[2] == 0)
						Tips("端来一盘扬州炒饭...");
					else
						Tips("享用蛋炒饭中...");

					int eaten = Eat(3, 1);
					reward_meal = 0;

					if (eaten < 1)
						Tips("突然不想吃，狠心倒掉吧。");
					else
						Tips("味道还不错，份量上太小气。");

					//Task 2-1
					if (task_rate[2] == 0) {
						Delay(1500);
						TimeLapse(4 minutes, THINK);//dialog

						task_rate[2] = 1;
						TaskView(2, 1);
						remap = true;
					}
				}
				else
					Tips("\"榜样工作者将获得单位的奖励。\"");
			}
			else
				Tips("太晚了，员工们都不在。");
			MoveBack();

			break;
		default:
			break;
		}
	}
	return 0;
}

int ZooWest() {
	{
		map_file = "ZooWest";
		ins_coe = 1.20;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_WEST) {
		if (remap) {
			CommonreMap();
			Tips("动物园西，格外偏僻宁静。");

			remap = false;
		}

		if (!Move())//动物园
			continue;

		switch (atlas[sx][sy]) {
		case 'w':
			place = ZOO_NORTH_WEST;
			sx = 17, sy = ty;
			break;

		case 'd':
			place = ZOO_MIDDLE;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooNorthWest() {
	{
		map_file = "ZooNorthWest";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_NORTH_WEST) {
		if (remap) {
			CommonreMap();
			Tips("动物园西北，灵动的还有建筑。");

			remap = false;
		}

		if (!Move())//动物园
			continue;

		switch (atlas[sx][sy]) {
		case 's':
			place = ZOO_WEST;
			// RETURN
			sx = 2, sy = sy;
			//reMap = true;
			break;

		case 'd':
			place = ZOO_NORTH;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooMiddle() {
	{
		map_file = "ZooMiddle";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_MIDDLE) {
		if (remap) {
			CommonreMap();
			Tips("动物园中心地带，栏杆上的划痕不知是游人还是动物所为。");

			remap = false;
		}

		if (!Move())//动物园
			continue;

		switch (atlas[sx][sy]) {
		case 'a':
			place = ZOO_WEST;
			sx = sx, sy = 54;
			break;

		case 'w':
			place = ZOO_NORTH;
			sx = 17, sy = sy;
			break;

		case 'd':
			place = ZOO_EAST;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooNorth() {
	{
		map_file = "ZooNorth";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_NORTH) {
		if (remap) {
			CommonreMap();
			Tips("动物园北，轻盈的跃动。");

			remap = false;
		}

		if (!Move())//动物园
			continue;

		switch (atlas[sx][sy]) {
		case 'a':
			place = ZOO_NORTH_WEST;
			// RETURN
			sx = 7, sy = 54;
			//reMap = true;
			break;

		case 's':
			place = ZOO_MIDDLE;
			sx = 2, sy = sy;
			break;

		case 'd':
			place = ZOO_NORTH_EAST;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooNorthEast() {
	{
		map_file = "ZooNorthEast";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_NORTH_EAST) {
		if (remap) {
			CommonreMap();
			Tips("动物园东北，深沉的吼叫。");
			remap = false;
		}

		if (!Move())//动物园
			continue;

		switch (atlas[sx][sy]) {
		case 's':
			place = ZOO_EAST;
			// RETURN
			sx = 2, sy = ty;
			//reMap = true;
			break;

		case 'a':
			place = ZOO_NORTH;
			sx = sx, sy = 54;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooEast() {
	{
		map_file = "ZooEast";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_EAST) {
		if (remap) {
			CommonreMap();
			Tips("动物园东，人声细碎。");

			remap = false;
		}

		if (!Move())//动物园 
			continue;

		switch (atlas[sx][sy]) {
		case 'w':
			place = ZOO_NORTH_EAST;
			sx = 17, sy = sy;
			break;

		case 'a':
			place = ZOO_MIDDLE;
			sx = sx, sy = 54;
			break;

		case 'D':
			place = CITY;
			sx = 9, sy = 9;
			break;

		case 'O':
			place = ZOO_OFFICE;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooOffice() {
	{
		ins_coe = 0.35;
		move_unit_time = 25;
	}

	border = false;
	Cls();
	puts("");

	TimeLapse(7, THINK);
	P("  \"你好，有什么事？\"\n\n", 24, 500);

	if (0 <= task_rate[2] and task_rate[2] <= 1) {
		TimeLapse(5, 0);//发现 
		P("  园长的右手臂上竟然有疤痕。\n\n", 24, 500);
		P("  也许他被动物抓伤了。\n\n", 24, 500);
	}

	//Task 2-2
	if (task_rate[2] == 1) {
		printf("  按键继续对话。\n");
		Pause();
		TimeLapse(4 minutes, THINK);

		task_rate[2] = 2;
		TaskView(2, 2);

		Gain(50);
	}
	else
		printf("  按键离开...\n");

	Pause();

	MoveBack();
	place = ZOO_EAST;
	sx = 10, sy = 27;

	return 0;
}

int Bank() {
	{
		map_file = "Bank";
		ins_coe = 1.20;
		move_unit_time = 12;
	}

	remap = true;

	while (place == BANK) {
		if (remap) {
			CommonreMap();
			Tips("银行里，机器翻出金钱的气味。");
			//else

			remap = false;
		}

		if (!Move())//银行 
			continue;


		switch (atlas[sx][sy]) {
		case 'L':
			Tips("职员操作着电脑，稍微等他一会吧……");
			Sleep(1500);
			Tips("\"本市银行的贷款功能尚未开放。\"");

			MoveBack();
			break;

		case 'S':
			MoveBack();//请不要冲过头
			if (!between(hour, 8, 17)) {
				Tips("银行仅在8:00到16:00开放存取款。");
				break;
			}

			Tips("[系统正在获取信誉记录...]");
			Sleep(100);
			Tips(""); printf("身上还带着%d元。屏幕显示[输入存款数额]。", money);

			if (!CommonInput(INTEGER, true, 9, true)) break;

			if (n there) {
				if (Pay(n)) {
					city_bank.Deposit(n);
					Tips("[存款完毕，感谢您的办理]");
				}
				else
					Tips("[银行是没办法凭空生钱的，先生]");
			}
			else
				Tips("[无效数字]");
			break;

		case 'R':
			MoveBack();
			if (!between(hour, 8, 17)) {
				Tips("银行仅在8:00到16:00开放存取款。");
				break;
			}

			Tips("[系统正在获取信誉记录...]");
			Sleep(100);
			Tips(""); printf("[您的存款为%d元，请输入取款数额]", city_bank.GetDepo());
			//if(){

			if (!CommonInput(INTEGER, true, 9, true)) break;

			if (n there) {
				if (city_bank.Draw(n)) {
					Gain(n);
					Tips("[已为您取款，欢迎下次再来]");
				}
				else
					Tips("[抢银行是违法行为]");
			}
			else
				Tips("[您或许只是想查看一下存款]");
			break;

		case 'D':
			place = CITY;
			sx = 4, sy = 15;
			break;

		default:

			break;
		}
	}
	return 0;
}

int Playground() {
	{
		map_file = "Playground";
		ins_coe = 1.35;
		move_unit_time = 22;
	}

	remap = true;

	while (place == PLAYGROUND) {
		if (remap) {
			CommonreMap();
			if (7 <= hour and hour <= 17)
				Tips("广场里，步伐不一的人影。");
			else
				if (18 <= hour and hour <= 21)
					Tips("广场是橙色灯光下的舞台。");
				else
					Tips("广场很安静，但感受得到人们曾经愉快的活动。");

			remap = false;
		}

		if (!Move())//广场 
			continue;

		switch (atlas[sx][sy]) {
		case 'w':
			place = CITY;
			sx = 12, sy = 46 + sy / 6;
			break;
		default: break;
		}
	}
	return 0;
}

int City() {
	{
		ins_coe = 1.35;
		map_file = "City";
		move_unit_time = 65;
	}

	//Task 1-1
	if (task_rate[1] == 0) {
		SoundCover("Message");
		task_rate[1] = 1;
		TaskView(1, 1);//强制进入Task
		remap = true;
	}

	remap = true;

	while (place == CITY) {
		if (remap) {
			CommonreMap();
			if (day <= 1)
				Tips("大街，陌生却似曾相识。");
			else
				Tips("熟悉的大街。");

			remap = false;
		}

		if (!Move())//城市 
			continue;

		switch (atlas[sx][sy]) {
		case 'H'://Home
			place = HOME;
			sx = 14, sy = 5;
			break;

		case 'S'://
			if (hour >= 7 and hour <= 20)
				place = SUPERMATKET;
			else {
				Tips("[营业时间: 7:00至21:00 :) ]");
				MoveBack();
			}
			break;

		case 'O'://写字楼 
			place = WRITING;
			sx = 14, sy = 5;
			break;

		case 'C'://School(); 
			place = SCHOOL;
			sx = 15, sy = 27;
			break;

		case 'T'://Hospital(); 
			place = HOSPITAL;
			sx = 4, sy = 21;
			break;

		case 'E'://WeaponShop(); 
			if (hour >= 9 and hour <= 17)
				place = WEAPONSHOP;
			else {
				Tips("大门紧锁。但透过玻璃能看到展台上的东西。");
				MoveBack();
			}
			break;

		case 'F'://邻居 
			place = NEIGHBOR;
			sx = 14, sy = 5;
			break;

		case 'B'://Bank();
			place = BANK;
			sx = 14, sy = 5;
			break;

		case 'Z'://Zoo();
			place = ZOO_EAST;
			sx = 6, sy = 51;
			break;

		case 's':
			place = PLAYGROUND;
			sx = 2, sy = 3 + (sy - 46) * 6;
			break;

		default:

			break;
		}
	}
	return 0;//自然退出 
}

int Gate() {//空间传送门，机制其实不符合现实情况
	while (place != ESC) {
		switch (place) {
		case CITY: City(); break;

		case HOME: Home(); break;
		case BEDROOM: Bedroom(); break;

		case KITCHEN: Kitchen(); break;

		case SUPERMATKET: Supermarket(); break;

		case WRITING: Writing(); break;
		case TYPIST: Typist(); break;

		case SCHOOL: School(); break;
		case SCHOOL_1F: School1F(); break;
		case SCHOOL_2F: School2F(); break;
		case SCHOOL_3F: School3F(); break;
		case SCHOOL_HIDE: SchoolHide(); break;

		case HOSPITAL: Hospital(); break;
		case INTERNAL: Internal(); break;

		case WEAPONSHOP: WeaponShop(); break;

		case NEIGHBOR: Neighbor(); break;
		case NEIGHBOR_2F: Neighbor2F(); break;
		case NEIGHBOR_BEDROOM: NeighborBedroom(); break;

		case BANK: Bank(); break;

		case ZOO_EAST: ZooEast(); break;
		case ZOO_NORTH_EAST: ZooNorthEast(); break;
		case ZOO_NORTH: ZooNorth(); break;
		case ZOO_MIDDLE: ZooMiddle(); break;
		case ZOO_NORTH_WEST: ZooNorthWest(); break;
		case ZOO_WEST: ZooWest(); break;
		case ZOO_OFFICE: ZooOffice(); break;

		case PLAYGROUND: Playground(); break;

		default:
			place = ESC;
			break;
		}
	}
	return 0;
}
