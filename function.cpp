#include "pch.h"
/*
	这是Free 3.0的功能函数
*/

//自定义清屏
int Cls() {
	/*	Position(1, 1);
		for(int x = 1; x <= 20; ++x)
			puts("                                                            ");
		Position(1, 1);
	*/
	return system("cls");//DOS命令...清屏彻底且速度快
}

//立即改变全部颜色
int Color(const char *str) {
	return system(((string)("color ") + (string)(str)).c_str());
}

//随机数播种
bool Randomize() {
	srand((unsigned)time(NULL) % 10086 + 22682);
	return true;
}

//获取精确时间，计时用
long long GetTimeout() {
	timeb t;
	ftime(&t);
	return t.time * 1000 + t.millitm;
}

//把字符串按照码风设置转换
string Converted(string str) {
	int len = str.length(); string res = "";
	for (int i = 0; i <= len - 1; ++i) {
		if (str[i] == '`') {
			if (!(code_style & TIGHT))
				res += ' ';
			//else do nothing
		}
		else
			res += str[i];
	}
	return res;
}

//获得缓存位置
CONSOLE_SCREEN_BUFFER_INFO GetBufferinfo() {
	CONSOLE_SCREEN_BUFFER_INFO Buffer;
	GetConsoleScreenBufferInfo(output_handle, &Buffer);
	return Buffer;
}

//把此时屏幕上的字符全部存入全局变量FaceMap中
BOOL GetFace(CHAR_INFO *face_buf) {
	COORD Coin, CoUpperLeft;
	SMALL_RECT Rect;

	Coin.X = yMax;
	Coin.Y = xMax;
	CoUpperLeft.X = 0;
	CoUpperLeft.Y = 0;
	Rect.Left = 0;
	Rect.Top = 0;
	Rect.Right = yMax;
	Rect.Bottom = xMax;
	return ReadConsoleOutput(output_handle, face_buf, Coin, CoUpperLeft, &Rect);
}

//读取FaceMap第x行的第y个字符
char GetPositionChar(int x, int y) {
	return face_map[yMax * (x - 1) + (y - 1)].Char.AsciiChar;
}

//使光标指向第x行，第y列
BOOL Position(int x, int y) {
	COORD pos = { SHORT(y - 1), SHORT(x - 1) };//注意转换必要
	return SetConsoleCursorPosition(output_handle, pos);
}

//把光标向右移动dy，向下移动dx，可以是负数。
BOOL PstTurn(int dx, int dy) {
	CONSOLE_SCREEN_BUFFER_INFO Buffer = GetBufferinfo();
	return Position(Buffer.dwCursorPosition.Y + 1 + dx, Buffer.dwCursorPosition.X + 1 + dy);
}

//覆盖光标前方dy格 要保证前面存在dy格
bool CoverBack(int dy) {
	PstTurn(0, -dy);
	repeat(dy, i) putchar(' ');
	PstTurn(0, -dy);
	return true;
}

//清空x,y处的文字，长度len。清空后返回x,y处以准备 
BOOL PstC(int x, int y, int len) {
	Position(x, y);
	while (len--)
		putchar(' ');
	return Position(x, y);
}

//正常异步播放音乐，不覆盖当前的Sound，不循环
BOOL Sound(const char *str) {
	return PlaySound(((string)("Data\\Sound\\") + (string)(str) + (string)(".wav")).c_str(),
		NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

//覆盖当前Sound
BOOL SoundCover(const char *str) {
	return PlaySound(((string)("Data\\Sound\\") + (string)(str) + (string)(".wav")).c_str(),
		NULL, SND_FILENAME | SND_ASYNC);
}

//覆盖当前Sound，且播放完才会继续下一步。保留"Sleep"串
BOOL SoundWait(const char *str) {
	return PlaySound(((string)("Data\\Sound\\") + (string)(str) + (string)(".wav")).c_str(),
		NULL, SND_FILENAME);
}

//停止Sound
BOOL SoundStop() {
	return PlaySound(NULL, NULL,
		SND_FILENAME);
}

//正常mciSendString()
BOOL mciSS(const char *str) {
	return mciSendString(str, NULL, 0, NULL);
}

//常见的伪随机音效。可以合并到Sound()中，但比较复杂，需要离散化字符串或使用代号来获取该类音频的数目
BOOL SoundBird() {
	return Sound(((string)("Bird") + (char)('A' + step % kBirdcnt)).c_str());
}
BOOL SoundInsect() {
	return Sound(((string)("Insect") + (char)('A' + step % kInsectcnt)).c_str());
}
BOOL SoundHit() {
	return Sound(((string)("Hit") + (char)('A' + step % kHitcnt)).c_str());
}
BOOL SoundCough() {
	return SoundCover(((string)("Cough") + (char)('A' + step % kCoughcnt)).c_str());
}

//显示光标
BOOL CursorShow() {
	CONSOLE_CURSOR_INFO Cursorinfo = { 1, true };
	return SetConsoleCursorInfo(output_handle, &Cursorinfo);
}

//隐藏光标
BOOL CursorHide() {
	CONSOLE_CURSOR_INFO Cursorinfo = { 1, false };
	return SetConsoleCursorInfo(output_handle, &Cursorinfo);
}

//设置透明度
BOOL SetAlpha() {
	return SetLayeredWindowAttributes(free_handle, 0, 255 * (76 + alpha) / 100, 0x2);
}

//设置为默认字体
BOOL SetFont() {
	CONSOLE_FONT_INFOEX info = { 1, false };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = font_size; //.X保留为0
	info.FontWeight = FW_NORMAL;

	/*	wcscpy_s(info.FaceName, L"楷体");
		if (SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info))
			return true;
		wcscpy_s(info.FaceName, L"黑体");
		if (SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info))
			return true;*/
	wcscpy_s(info.FaceName, L"\u6977\u4f53");
	return SetCurrentConsoleFontEx(output_handle, 0, &info);
}

//显示参数转到默认
bool FaceInit() {
	light = -1;
	Color("0F");

	alpha = 20;
	char strTitle[255];
	GetConsoleTitle(strTitle, 255);
	free_handle = FindWindow("ConsoleWindowClass", strTitle);//GOT
	LONG t = GetWindowLong(free_handle, GWL_EXSTYLE);
	t |= WS_EX_LAYERED;
	SetWindowLong(free_handle, GWL_EXSTYLE, t);
	SetAlpha();

	font_size = 16;
	SetFont();
	return true;
}

//窗口重置到默认
bool WindowSet() {
	Randomize();//为了窗口，也要播种一次

	SetConsoleOutputCP(936);

	output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info = { 1, false };
	SetConsoleCursorInfo(output_handle, &cursor_info);//隐藏光标

	COORD siz = { yMax, xMax };
	SMALL_RECT rc = { 0, 0, yMax, xMax };
	SetConsoleScreenBufferSize(output_handle, siz);//重新设置缓冲区大小
	SetConsoleWindowInfo(output_handle, true, &rc);//重置窗口位置和大小

	input_handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(input_handle, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;//关闭快速编辑模式
	mode &= ~ENABLE_MOUSE_INPUT;//关闭鼠标输入
	mode |= ENABLE_EXTENDED_FLAGS;//和下一句共同作用
	mode |= ENABLE_INSERT_MODE;//打开插入模式
	SetConsoleMode(input_handle, mode);//啪嚓

	V.Maj = VER_MAJOR; V.Min = VER_MINOR; V.Rel = VER_RELEASE; V.Bui = VER_BUILD;
	SetConsoleTitle((string("Room ") + string(VER_STRING)).c_str());//设置窗口标题

	char strTitle[255];
	GetConsoleTitle(strTitle, 255);
	HWND HandleWnd = FindWindow("ConsoleWindowClass", strTitle);
	RECT _rc;

	GetWindowRect(HandleWnd, &_rc);//获得窗口对应矩形
	//改变窗口风格，禁止最大化，去除边框
	SetWindowLongPtr(HandleWnd, GWL_STYLE, GetWindowLongPtr(HandleWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX);

	//SetWindowLongPtr(hWnd,  GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) & ~WS_EX_LEFtsCROLLBAR);
	SetWindowPos(HandleWnd, NULL, _rc.left, _rc.top, _rc.right - _rc.left, _rc.bottom - _rc.top, 0);
	//ShowScrollBar(hWnd, SB_HORZ, 0);
	//ShowScrollBar(hWnd, SB_VERT, 0);
	//GetScrollBarInfo(hWnd, SB_HORZ, NULL);
	//ShowScrollBar(hwndScrollBar, SB_CTL, 0);
	//SetScrollRange(hWnd, SB_HORZ, 0, 0, 0);
	  // 
	//HIMC g_hIMC = NULL;
	//g_hIMC = ImmAssociateContext(hWnd, NULL);
	//m_hlayout = GetKeyboardLayout(0);
	//LoadKeyboardLayout("0x0409", KLF_ACTIVATE);
	Sound("Drip");//finish
	return true;
}

//吸收缓存区的内容
bool Flush() {
	while (_kbhit()) _getch();
	r = '\0';//无效的玩意儿
	return true;
}

//读入的同时把上下左右键等特殊键转换为对应指令
int getord(bool stayable) {
	if (stayable)
		Flush();//延迟期间的玩意吃了
	int ch = _getch();
	if (ch == DIR_KEY) {
		ch = _getch();
		switch (ch) {
		case 72: ch = UP_KEY; break;
		case 80: ch = DOWN_KEY; break;
		case 75: ch = LEFT_KEY; break;
		case 77: ch = RIGHT_KEY; break;
		case 83: ch = DEL_KEY; break;
		default:
			ch = ' ';
			break;
		}
	}
	if (stayable)
		Flush();//善始善终
	return ch;
}

string getlin(int lenlim) {
	CONSOLE_SCREEN_BUFFER_INFO Buffer = GetBufferinfo();
	int ox = Buffer.dwCursorPosition.Y + 1, oy = Buffer.dwCursorPosition.X + 1;//获取起点位置

	int len = 0, pos = 0;//len是确实长度
	string res = "";
	while (true) {
		Position(ox, oy + pos);
		int ch = getord();

		//非离散值，不用switch
		if (ch == ENTER or ch == ESC)
			break;
		else if (ischar(ch)) {
			Position(ox, oy + pos);
			putchar(ch);
			for (int i = pos; i <= len - 1; ++i)
				putchar(res[i]);

			res.insert((string::size_type)pos, 1, (char)(ch));

			++pos;
			++len;
			if (len >= lenlim)
				break;
		}
		else if (ch == LEFT_KEY) {
			if (pos > 0)
				--pos;
		}
		else if (ch == RIGHT_KEY) {
			if (pos < len)
				++pos;//止于pos = len，即等在后方
		}
		else if (ch == DEL_KEY) {
			if (pos < len) {
				Position(ox, oy + pos);

				for (int i = pos + 1; i <= len - 1; ++i)
					putchar(res[i]);
				putchar(' ');

				res.erase(pos, 1);

				--len;
				continue;
			}
			else
				ch = BACKSPACE;
		}
		if (ch == BACKSPACE) {
			if (pos >= 1) {
				Position(ox, oy + pos - 1);
				for (int i = pos; i <= len - 1; ++i)
					putchar(res[i]);
				putchar(' ');

				res.erase(pos - 1, 1);

				--pos;
				--len;
			}
		}
	}
	return res;
}

//在标准提示框内输出提示
bool Tips(const char *str) {
	PstC(19, 2, 53);//清空提示位置 
	printf("%s", str);
	return true;
}

//光标定位至标准短字串输入框内
BOOL PstInput() {
	return PstC(17, 46, 9);
}

//对错误进行提示
bool Error(int c) {
	if (c == 1) {//移动问题
		Sound("Error");
		if (isupper(r)) {
			repeat(3, i)
				Tips(""), Sleep(FLASH_SPAN), Tips("请打开小写键盘。"), Sleep(FLASH_SPAN);
		}
		else {
			if (CME <= kFuncnt)
				Tips(kErrorFun[CME]);
			else
				Tips("思考。");
		}
	}
	if (c == 2) {
		Sound("Error");
	}
	return true;
}

//在缓存区有字符的时候能够跳过的Sleep()
bool Delay(int t, bool skipable) {
	if (!skipable) {
		Sleep(t);
		return true;
	}
	while (t > 0) {
		if (_kbhit()) {
			r = getord(false);
			if (r == ' ' or r == ESC or r == ENTER)
				r = JUMP;
		}
		if (r == JUMP)
			return false;
		Sleep(noMore(40, t));
		t -= noMore(40, t);
	}
	return true;
}

//逐字逐句输出文字，通常可跳过
bool Printl(const char *str, int DPL, int DPS, bool skipable) {
	int len = strlen(str);
	for (int i = 0; i <= len - 1; ++i) {
		putchar(str[i]);
		Delay(DPL, skipable);
	}

	return Delay(DPS, skipable);
}

bool encfile(char *in_filename, char *pwd, char *out_filename) {//加密（解密）文件
	FILE *fin, *fout;
	char ch;
	int i = 0, j = 0;

#ifdef MSVC
	fopen_s(&fin, in_filename, "rb");/*二进制只读*/
#else
	fin = fopen(in_filename, "rb");
#endif
	if (fin == NULL) {
		MessageBox(NULL, "找不到要打开的文件。", "Free 3.0 存档", MB_SYSTEMMODAL);
		End(-1);/*如果不能打开要加密文件,便退出程序*/
		return false;
	}

#ifdef MSVC
	fopen_s(&fout, out_filename, "wb");
#else
	fout = fopen(out_filename, "wb");
#endif
	if (fout == NULL) {
		MessageBox(NULL, "输出位置出现问题。", "Free 3.0 存档", MB_SYSTEMMODAL);
		End(-1);/*如果不能建立加密后的文件,便退出*/
		return false;
	}

	while (pwd[++j]);

	ch = fgetc(fin);

	while (!feof(fin)) {
		fputc(ch ^ pwd[(i >= j) ? (i = 0) : (i++)], fout);/*异或后输出*/
		ch = fgetc(fin);
	}

	fclose(fin);/*关闭源文件*/
	fclose(fout);/*关闭目标文件*/
	return true;
}

bool Prese() {//保存
	FILE * fout;
#ifdef MSVC
	fopen_s(&fout, "Data\\Temp\\FreePreseData.sev", "wb");
#else
	fout = fopen("Data\\Temp\\FreePreseData.sev", "wb");
#endif
	if (fout == NULL) {
		MessageBox(NULL, "存档函数找不到它想要的文件。", "Free 3.0 存档", MB_SYSTEMMODAL);
		End(-1);
		return false;
	}

	fprintf(fout, "%d %d %d %d\n", V.Maj, V.Min, V.Rel, V.Bui);//先输出版本号作为标识
	//以下是此版本标准

	me.PrintFile(fout);
	city_bank.PrintFile(fout);

	fprintf(fout, "%d %d %d\n", place, sx, sy);

	fprintf(fout, "%d %d %d %d\n", money, watch, reward_meal, work_score);
	fprintf(fout, "%d\n", blocknum);
	for (int i = 1; i <= blocknum; ++i)
		fprintf(fout, "%d %d\n", block[i].itm, block[i].num);

	fprintf(fout, "%d\n", kTaskSeriecnt);
	for (int i = 1; i <= kTaskSeriecnt; ++i)
		fprintf(fout, "%d", task_rate[i]), fputc(i == kTaskSeriecnt ? '\n' : ' ', fout);

	fprintf(fout, "%d\n", kDecicnt);
	for (int i = 1; i <= kDecicnt; ++i)
		fprintf(fout, "%d", decision[i]), fputc(i == kDecicnt ? '\n' : ' ', fout);

	fprintf(fout, "%lld %lld\n", timein, step);

	fprintf(fout, "%d %d %ud\n", colorable, flashable, code_style);

	fclose(fout);

	char in_filename[30] = "Data\\Temp\\FreePreseData.sev";/*要加密的文件名*/
	char out_filename[30] = "Data\\Prese\\FreePrese.sev";/*加密后保存的文件名*/
	char pwd[16] = "hx2003zzka!";/*password*/
	encfile(in_filename, pwd, out_filename);

	remove("Data\\Temp\\FreePreseData.sev");
	return true;
}

bool Load() {
	border = false;

	char in_filename[30] = "Data\\Prese\\FreePrese.sev";/*解密的文件名*/
	char out_filename[30] = "Data\\Temp\\FreeLoadData.sev";/*解密后的文件名*/
	char pwd[16] = "hx2003zzka!";/*异或密码*/

	encfile(in_filename, pwd, out_filename);/*函数调用*/

	FILE * fin;
#ifdef MSVC
	fopen_s(&fin, "Data\\Temp\\FreeLoadData.sev", "rb");
#else
	fin = fopen("Data\\Temp\\FreeLoadData.sev", "rb");
#endif
	if (fin == NULL) {
		MessageBox(NULL, "读档函数找不到它心目中的文件。", "Free 3.0 存档", MB_SYSTEMMODAL);
		End(-1);
		return false;
	}
	int cnt = 0;

	fscanf_s(fin, "%d %d %d %d", &FileV.Maj, &FileV.Min, &FileV.Rel, &FileV.Bui);

	if (FileV.Maj == 3 and FileV.Min == 0 and FileV.Rel == 1) {
		fscanf_s(fin, "%lf %d %lf %lf %lf %lf %lld", &me.life, &me.phy, &me.pro, &me.fat, &me.car, &me.can, &me.awake_time);
		fscanf_s(fin, "%lf", &me.sick);
		me.Examine();

		fscanf_s(fin, "%d %d %d", &place, &sx, &sy);
		fscanf_s(fin, "%d %d %d %d", &money, &watch, &reward_meal, &work_score);

		fscanf_s(fin, "%d", &blocknum);
		for (int i = 1; i <= blocknum; ++i)
			fscanf_s(fin, "%d %d", &block[i].itm, &block[i].num);

		fscanf_s(fin, "%d", &cnt);
		for (int i = 1; i <= cnt; ++i)
			fscanf_s(fin, "%d", &task_rate[i]);

		fscanf_s(fin, "%d", &cnt);
		for (int i = 1; i <= cnt; ++i)
			fscanf_s(fin, "%d", &decision[i]);

		fscanf_s(fin, "%lld %lld", &timein, &step);

		fscanf_s(fin, "%d %d %ud", &colorable, &flashable, &code_style);
	}
	else if (FileV.Maj == 3 and FileV.Min == 0 and FileV.Rel == 2) {
		me.ScanFile(fin);
		city_bank.ScanFile(fin);

		fscanf_s(fin, "%d %d %d\n", &place, &sx, &sy);

		fscanf_s(fin, "%d %d %d %d\n", &money, &watch, &reward_meal, &work_score);
		fscanf_s(fin, "%d\n", &blocknum);
		for (int i = 1; i <= blocknum; ++i)
			fscanf_s(fin, "%d %d", &block[i].itm, &block[i].num);

		fscanf_s(fin, "%d", &cnt);
		for (int i = 1; i <= cnt; ++i)
			fscanf_s(fin, "%d", &task_rate[i]);

		fscanf_s(fin, "%d", &cnt);
		for (int i = 1; i <= cnt; ++i)
			fscanf_s(fin, "%d", &decision[i]);

		fscanf_s(fin, "%lld %lld", &timein, &step);

		fscanf_s(fin, "%d %d %ud", &colorable, &flashable, &code_style);
	}
	else {
		MessageBox(NULL, "不支持该存档所属的版本。考虑新建角色吧。", "Free 3.0 存档", MB_SYSTEMMODAL);
		End(-1);
		return false;
	}

	fclose(fin);

	remove("Data\\Temp\\FreeLoadData.sev");
	return true;
}

bool Pause() {
	getord(true);//自带回收
	return true;
}
