/*
	Free 3.0 SC for Visual Studio
	By:
	Hoale,
	Hoare,
	Dilute,
	xuxing,
	bilibili,
	Jeff,
	and You.
*/
#include "pch.h"

//主界面
int mainful(int argc, char *argv[]) {

	puts("");
	printf("  正在初始化。\n\n");

	WindowSet();
	s = "中文";
	FaceInit();//很少使用
	mciSS("open Data\\Music\\Array.mp3 alias Array");
	mciSS("play Array");

	printf("  初始化完毕。\n");

	remap = true;

	FILE *fin;

	int pit = 1;//"pitch on"，选中的
#ifdef MSVC
	fopen_s(&fin, "Data\\Prese\\FreePrese.sev", "rb");
#else
	fin = fopen("Data\\Prese\\FreePrese.sev", "rb");
#endif
	if (fin != NULL) {
		pit = 2;
		fclose(fin);
	}

	while (true) {
		if (remap) {//All Because of Help()
			Cls();//自定义清屏
			printf(
				"    ___________                              \n"
				"   |                                         \n"
				"   |                                         \n"
				"   |                                         \n"
				"   |                                         \n"
				"   |                                         \n"
				"   |__________   ______    ____      ____    \n"
				"   |           |/      \\  /    \\    /    \\   \n"//是转义字符导致不对齐
				"   |           |         /      \\  /      \\  \n"
				"   |           |        /________\\/________\\ \n"
				"   |           |        \\         \\          \n"
				"   |           |         \\         \\       / \n"
				"   |           |          \\_____/   \\_____/  \n"
				"                              _  _  _        \n"
				"                          ----\\\\( )//----    \n"
				"             (\\           |  开始 - ｐ  |   \n"
				"              \\)_         |  继续 - ｃ  |   \n"
				"           .--' ')        |  帮助 - ｈ  |   \n"
				"         o(  )_-\\         |  结束 - ｑ  |   \n"
				"           `\"\"\"` `        |-------------|    \n"
			);
			Position(4, 24);
			printf("%s : %s", VER_STRING, VER_DESCRIPTION);//版本号、版本主题

			GetFace(face_map);
		//	Cls();
		//	for (int i = 0; i <= 200; (++i) % 60 == 0 ? putchar('\n') : 1)
		//		putchar(FaceMap[i].Char.AsciiChar);
		//	Pause();

			repeat(10, t) {
				int x = RandLR(1, 20), y = RandLR(1, 45);
				char ch = GetPositionChar(x, y);

				if (ch == ' ') {
					Position(x, y);
					putchar('*');
				}
			}//FESTIVAL
			remap = false;
		}
		//显示选择状态
		Position(15 + pit, 28), putchar('[');
		Position(15 + pit, 40), putchar(']');

		r = getord();//在这里等待。getord自带
		r = Directed(r);//w, s转换成上下键
		//取消显示选择状态
		Position(15 + pit, 28), putchar(' ');
		Position(15 + pit, 40), putchar(' ');

		if (r == ENTER)//准备进入。这与switch()共同作用
			switch (pit) {
			case 1: r = 'p'; break;
			case 2: r = 'c'; break;
			case 3: r = 'h'; break;
			case 4: r = 'q'; break;
			default: break;
			}
		switch (r) {
		case UP_KEY:
			Sound("Cursor");//游标
			pit = (pit == 1) ? (4) : (pit - 1);
			break;

		case DOWN_KEY:
			Sound("Cursor");
			pit = (pit == 4) ? (1) : (pit + 1);
			break;

		case 'p':
			SoundCover("New");

			Cls();
			puts("");
			printf("  新建角色。\n\n");

		#ifdef MSVC
			fopen_s(&fin, "Data\\Prese\\FreePrese.sev", "rb");//新建时，检测是否有存档
		#else
			fin = fopen("Data\\Prese\\FreePrese.sev", "rb");
		#endif
			if (fin != NULL) {
				fclose(fin);
				printf(
					"  然而检测到先前的存档。\n"
					"  \n"
					"  120步后将覆盖原存档，确定吗？\n"
					"  \n"
					"  键入 0 返回，其它任意键继续。\n"
				);

				r = getord();
				if (r == '0' or r == ESC) {
					remap = true;
					break;
				}
			}

			reNew();//属性初始化
			Setting();//进入设置，自带刷新

			Cls();//清屏
			mciSS("stop Array");
			mciSS("close Array");//取消连接音乐

			Gate(); // 空间传送门

			mciSS("open Data\\Music\\Array.mp3 alias Array");//重新连接音乐
			mciSS("play Array");
			remap = true;//重新输出主界面
			FaceInit();
			break;

		case 'c':
			Cls();
			puts("");
			printf("  读取存档中...\n");

			reNew();
			Load();//包括Setting的参数

			Cls();//卧室不自动清屏.. 
			mciSS("stop Array");
			mciSS("close Array");

			TimeLapse(0, FRESH);//对于Load的刷新
			Gate();

			mciSS("open Data\\Music\\Array.mp3 alias Array");
			mciSS("play Array");
			remap = true;
			FaceInit();
			break;

		case 'h'://独立的帮助
			Sound("Helpin");

			Cls();
			puts("");
			printf(
				"  Free 是决策游戏。\n"
				"  \n"
				"  起初，你是城市里的一位自由居民，\n"
				"  拥有工作、学习和锻炼的权利。\n"
				"  \n"
				"  有人会阻止你探险游玩吗？\n"
				"  或许只有身体会妨碍自己吧。\n"
				"  行动时，随时注意状态变化。\n"
				"  \n"
				"  依照提示按键，时间流逝，游戏将进入下一步。\n"
				"  多数场景内，ｉ表示你的位置，\n"
				"  操作上下左右键来移动。\n"
				"  \n"
				"  120步以上，每20步自动存档。\n"
				"  一些事件也会触发自动保存。\n"
			);

			printf(
				"  \n"
				"  下一页...\n"
			);

			Pause();

			Cls();
			puts("");
			printf(
				"  推荐在控制台使用：\n"
				"  小写键盘\n"
				"  英文输入法\n"
				"  \"黑体\"或\"楷体\"\n"
				"  \n"
				"  在游戏中的各地输入ｈ，都可以获得对应帮助。\n"
				"  这里，键入ｖ以了解最近更新。\n"
				"  \n"
				"  \n"
				"   编写者\n"
				"  ·Hoale\n"
				"  ·Hoare\n"
				"  ·Dilute\n"
				"  ·xuxing\n"
				"  ·bilibili\n"
				"  ·Jeff\n"
			);

			r = getord();
			if (r == 'v')
				system("start http://mant.ink/");//进入网站

			Sound("Helpout");//note
			remap = true;
			break;

		case 'q':
			Cls();
			return 0;
			break;

		default:
			Error(2);
			if (isupper(r)) {//输入了大写字母
				Cls();
				puts("");
				printf("  请打开小写键盘。\n");
				Pause();
				remap = true;
			}
			break;
		}
	}
	return 0;
}
