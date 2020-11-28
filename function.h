#pragma once

/*
	这是Free 3.0的功能函数（执行函数）
*/

//功能函数

//自定义清屏函数
int Cls();

//立即改变全部颜色
int Color(const char *str);

//随机数播种
bool Randomize();

//获取精确时间，计时用
long long GetTimeout();

//把字符串按照码风设置转换
string Converted(string str);

//获得缓存位置
CONSOLE_SCREEN_BUFFER_INFO GetBufferinfo();

//把此时屏幕上的字符全部存入全局变量FaceMap中
BOOL GetFace(CHAR_INFO *face_buf);

//读取FaceMap第x行的第y个字符
char GetPositionChar(int x, int y);

//使光标指向第x行，第y列
BOOL Position(int x, int y);

//把光标向右移动dy，向下移动dx，可以是负数。
BOOL PstTurn(int dx, int dy);

//覆盖光标前方dy格 要保证前面存在dy格
bool CoverBack(int dy = 1);

//清空x,y处的文字，长度len。清空后返回x,y处以准备 
BOOL PstC(int x, int y, int len);

//正常异步播放音乐，不覆盖当前的Sound，不循环
BOOL Sound(const char *str);

//覆盖当前Sound
BOOL SoundCover(const char *str);

//覆盖当前Sound，且播放完才会继续下一步。
BOOL SoundWait(const char *str);

//停止Sound
BOOL SoundStop();

//正常mciSendString()
BOOL mciSS(const char *str);

//常见的伪随机音效。可以合并到Sound()中，但比较复杂，需要离散化字符串或使用代号来获取该类音频的数目
BOOL SoundBird();
BOOL SoundInsect();
BOOL SoundHit();
BOOL SoundCough();

//显示光标
BOOL CursorShow();

//隐藏光标
BOOL CursorHide();

//设置透明度
BOOL SetAlpha();

//设置为默认字体
BOOL SetFont();

//显示参数转到默认
bool FaceInit();

//窗口重置到默认
bool WindowSet();

//吸收缓存区的内容
bool Flush();

//读入的同时把上下左右键等特殊键转换为对应指令
int getord(bool stayable = true);

string getlin(int lenlim = yMax);

//在标准提示框内输出提示
bool Tips(const char *str);

//光标定位至标准短字串输入框内
BOOL PstInput();

//对错误进行提示
bool Error(int c);

//在缓存区有字符的时候能够跳过的Sleep()
bool Delay(int t, bool skipable = true);

//逐字逐句输出文字，通常可跳过
bool Printl(const char *str, int DPL = 0, int DPS = 0, bool skipable = true);

bool encfile(char *in_filename, char *pwd, char *out_filename);

bool Prese();

bool Load();

bool Pause();
