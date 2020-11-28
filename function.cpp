#include "pch.h"
/*
	����Free 3.0�Ĺ��ܺ���
*/

//�Զ�������
int Cls() {
	/*	Position(1, 1);
		for(int x = 1; x <= 20; ++x)
			puts("                                                            ");
		Position(1, 1);
	*/
	return system("cls");//DOS����...�����������ٶȿ�
}

//�����ı�ȫ����ɫ
int Color(const char *str) {
	return system(((string)("color ") + (string)(str)).c_str());
}

//���������
bool Randomize() {
	srand((unsigned)time(NULL) % 10086 + 22682);
	return true;
}

//��ȡ��ȷʱ�䣬��ʱ��
long long GetTimeout() {
	timeb t;
	ftime(&t);
	return t.time * 1000 + t.millitm;
}

//���ַ��������������ת��
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

//��û���λ��
CONSOLE_SCREEN_BUFFER_INFO GetBufferinfo() {
	CONSOLE_SCREEN_BUFFER_INFO Buffer;
	GetConsoleScreenBufferInfo(output_handle, &Buffer);
	return Buffer;
}

//�Ѵ�ʱ��Ļ�ϵ��ַ�ȫ������ȫ�ֱ���FaceMap��
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

//��ȡFaceMap��x�еĵ�y���ַ�
char GetPositionChar(int x, int y) {
	return face_map[yMax * (x - 1) + (y - 1)].Char.AsciiChar;
}

//ʹ���ָ���x�У���y��
BOOL Position(int x, int y) {
	COORD pos = { SHORT(y - 1), SHORT(x - 1) };//ע��ת����Ҫ
	return SetConsoleCursorPosition(output_handle, pos);
}

//�ѹ�������ƶ�dy�������ƶ�dx�������Ǹ�����
BOOL PstTurn(int dx, int dy) {
	CONSOLE_SCREEN_BUFFER_INFO Buffer = GetBufferinfo();
	return Position(Buffer.dwCursorPosition.Y + 1 + dx, Buffer.dwCursorPosition.X + 1 + dy);
}

//���ǹ��ǰ��dy�� Ҫ��֤ǰ�����dy��
bool CoverBack(int dy) {
	PstTurn(0, -dy);
	repeat(dy, i) putchar(' ');
	PstTurn(0, -dy);
	return true;
}

//���x,y�������֣�����len����պ󷵻�x,y����׼�� 
BOOL PstC(int x, int y, int len) {
	Position(x, y);
	while (len--)
		putchar(' ');
	return Position(x, y);
}

//�����첽�������֣������ǵ�ǰ��Sound����ѭ��
BOOL Sound(const char *str) {
	return PlaySound(((string)("Data\\Sound\\") + (string)(str) + (string)(".wav")).c_str(),
		NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
}

//���ǵ�ǰSound
BOOL SoundCover(const char *str) {
	return PlaySound(((string)("Data\\Sound\\") + (string)(str) + (string)(".wav")).c_str(),
		NULL, SND_FILENAME | SND_ASYNC);
}

//���ǵ�ǰSound���Ҳ�����Ż������һ��������"Sleep"��
BOOL SoundWait(const char *str) {
	return PlaySound(((string)("Data\\Sound\\") + (string)(str) + (string)(".wav")).c_str(),
		NULL, SND_FILENAME);
}

//ֹͣSound
BOOL SoundStop() {
	return PlaySound(NULL, NULL,
		SND_FILENAME);
}

//����mciSendString()
BOOL mciSS(const char *str) {
	return mciSendString(str, NULL, 0, NULL);
}

//������α�����Ч�����Ժϲ���Sound()�У����Ƚϸ��ӣ���Ҫ��ɢ���ַ�����ʹ�ô�������ȡ������Ƶ����Ŀ
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

//��ʾ���
BOOL CursorShow() {
	CONSOLE_CURSOR_INFO Cursorinfo = { 1, true };
	return SetConsoleCursorInfo(output_handle, &Cursorinfo);
}

//���ع��
BOOL CursorHide() {
	CONSOLE_CURSOR_INFO Cursorinfo = { 1, false };
	return SetConsoleCursorInfo(output_handle, &Cursorinfo);
}

//����͸����
BOOL SetAlpha() {
	return SetLayeredWindowAttributes(free_handle, 0, 255 * (76 + alpha) / 100, 0x2);
}

//����ΪĬ������
BOOL SetFont() {
	CONSOLE_FONT_INFOEX info = { 1, false };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = font_size; //.X����Ϊ0
	info.FontWeight = FW_NORMAL;

	/*	wcscpy_s(info.FaceName, L"����");
		if (SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info))
			return true;
		wcscpy_s(info.FaceName, L"����");
		if (SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info))
			return true;*/
	wcscpy_s(info.FaceName, L"\u6977\u4f53");
	return SetCurrentConsoleFontEx(output_handle, 0, &info);
}

//��ʾ����ת��Ĭ��
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

//�������õ�Ĭ��
bool WindowSet() {
	Randomize();//Ϊ�˴��ڣ�ҲҪ����һ��

	SetConsoleOutputCP(936);

	output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info = { 1, false };
	SetConsoleCursorInfo(output_handle, &cursor_info);//���ع��

	COORD siz = { yMax, xMax };
	SMALL_RECT rc = { 0, 0, yMax, xMax };
	SetConsoleScreenBufferSize(output_handle, siz);//�������û�������С
	SetConsoleWindowInfo(output_handle, true, &rc);//���ô���λ�úʹ�С

	input_handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(input_handle, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;//�رտ��ٱ༭ģʽ
	mode &= ~ENABLE_MOUSE_INPUT;//�ر��������
	mode |= ENABLE_EXTENDED_FLAGS;//����һ�乲ͬ����
	mode |= ENABLE_INSERT_MODE;//�򿪲���ģʽ
	SetConsoleMode(input_handle, mode);//ž��

	V.Maj = VER_MAJOR; V.Min = VER_MINOR; V.Rel = VER_RELEASE; V.Bui = VER_BUILD;
	SetConsoleTitle((string("Room ") + string(VER_STRING)).c_str());//���ô��ڱ���

	char strTitle[255];
	GetConsoleTitle(strTitle, 255);
	HWND HandleWnd = FindWindow("ConsoleWindowClass", strTitle);
	RECT _rc;

	GetWindowRect(HandleWnd, &_rc);//��ô��ڶ�Ӧ����
	//�ı䴰�ڷ�񣬽�ֹ��󻯣�ȥ���߿�
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

//���ջ�����������
bool Flush() {
	while (_kbhit()) _getch();
	r = '\0';//��Ч�������
	return true;
}

//�����ͬʱ���������Ҽ��������ת��Ϊ��Ӧָ��
int getord(bool stayable) {
	if (stayable)
		Flush();//�ӳ��ڼ���������
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
		Flush();//��ʼ����
	return ch;
}

string getlin(int lenlim) {
	CONSOLE_SCREEN_BUFFER_INFO Buffer = GetBufferinfo();
	int ox = Buffer.dwCursorPosition.Y + 1, oy = Buffer.dwCursorPosition.X + 1;//��ȡ���λ��

	int len = 0, pos = 0;//len��ȷʵ����
	string res = "";
	while (true) {
		Position(ox, oy + pos);
		int ch = getord();

		//����ɢֵ������switch
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
				++pos;//ֹ��pos = len�������ں�
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

//�ڱ�׼��ʾ���������ʾ
bool Tips(const char *str) {
	PstC(19, 2, 53);//�����ʾλ�� 
	printf("%s", str);
	return true;
}

//��궨λ����׼���ִ��������
BOOL PstInput() {
	return PstC(17, 46, 9);
}

//�Դ��������ʾ
bool Error(int c) {
	if (c == 1) {//�ƶ�����
		Sound("Error");
		if (isupper(r)) {
			repeat(3, i)
				Tips(""), Sleep(FLASH_SPAN), Tips("���Сд���̡�"), Sleep(FLASH_SPAN);
		}
		else {
			if (CME <= kFuncnt)
				Tips(kErrorFun[CME]);
			else
				Tips("˼����");
		}
	}
	if (c == 2) {
		Sound("Error");
	}
	return true;
}

//�ڻ��������ַ���ʱ���ܹ�������Sleep()
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

//�������������֣�ͨ��������
bool Printl(const char *str, int DPL, int DPS, bool skipable) {
	int len = strlen(str);
	for (int i = 0; i <= len - 1; ++i) {
		putchar(str[i]);
		Delay(DPL, skipable);
	}

	return Delay(DPS, skipable);
}

bool encfile(char *in_filename, char *pwd, char *out_filename) {//���ܣ����ܣ��ļ�
	FILE *fin, *fout;
	char ch;
	int i = 0, j = 0;

#ifdef MSVC
	fopen_s(&fin, in_filename, "rb");/*������ֻ��*/
#else
	fin = fopen(in_filename, "rb");
#endif
	if (fin == NULL) {
		MessageBox(NULL, "�Ҳ���Ҫ�򿪵��ļ���", "Free 3.0 �浵", MB_SYSTEMMODAL);
		End(-1);/*������ܴ�Ҫ�����ļ�,���˳�����*/
		return false;
	}

#ifdef MSVC
	fopen_s(&fout, out_filename, "wb");
#else
	fout = fopen(out_filename, "wb");
#endif
	if (fout == NULL) {
		MessageBox(NULL, "���λ�ó������⡣", "Free 3.0 �浵", MB_SYSTEMMODAL);
		End(-1);/*������ܽ������ܺ���ļ�,���˳�*/
		return false;
	}

	while (pwd[++j]);

	ch = fgetc(fin);

	while (!feof(fin)) {
		fputc(ch ^ pwd[(i >= j) ? (i = 0) : (i++)], fout);/*�������*/
		ch = fgetc(fin);
	}

	fclose(fin);/*�ر�Դ�ļ�*/
	fclose(fout);/*�ر�Ŀ���ļ�*/
	return true;
}

bool Prese() {//����
	FILE * fout;
#ifdef MSVC
	fopen_s(&fout, "Data\\Temp\\FreePreseData.sev", "wb");
#else
	fout = fopen("Data\\Temp\\FreePreseData.sev", "wb");
#endif
	if (fout == NULL) {
		MessageBox(NULL, "�浵�����Ҳ�������Ҫ���ļ���", "Free 3.0 �浵", MB_SYSTEMMODAL);
		End(-1);
		return false;
	}

	fprintf(fout, "%d %d %d %d\n", V.Maj, V.Min, V.Rel, V.Bui);//������汾����Ϊ��ʶ
	//�����Ǵ˰汾��׼

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

	char in_filename[30] = "Data\\Temp\\FreePreseData.sev";/*Ҫ���ܵ��ļ���*/
	char out_filename[30] = "Data\\Prese\\FreePrese.sev";/*���ܺ󱣴���ļ���*/
	char pwd[16] = "hx2003zzka!";/*password*/
	encfile(in_filename, pwd, out_filename);

	remove("Data\\Temp\\FreePreseData.sev");
	return true;
}

bool Load() {
	border = false;

	char in_filename[30] = "Data\\Prese\\FreePrese.sev";/*���ܵ��ļ���*/
	char out_filename[30] = "Data\\Temp\\FreeLoadData.sev";/*���ܺ���ļ���*/
	char pwd[16] = "hx2003zzka!";/*�������*/

	encfile(in_filename, pwd, out_filename);/*��������*/

	FILE * fin;
#ifdef MSVC
	fopen_s(&fin, "Data\\Temp\\FreeLoadData.sev", "rb");
#else
	fin = fopen("Data\\Temp\\FreeLoadData.sev", "rb");
#endif
	if (fin == NULL) {
		MessageBox(NULL, "���������Ҳ�������Ŀ�е��ļ���", "Free 3.0 �浵", MB_SYSTEMMODAL);
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
		MessageBox(NULL, "��֧�ָô浵�����İ汾�������½���ɫ�ɡ�", "Free 3.0 �浵", MB_SYSTEMMODAL);
		End(-1);
		return false;
	}

	fclose(fin);

	remove("Data\\Temp\\FreeLoadData.sev");
	return true;
}

bool Pause() {
	getord(true);//�Դ�����
	return true;
}
