#pragma once

/*
	����Free 3.0�Ĺ��ܺ�����ִ�к�����
*/

//���ܺ���

//�Զ�����������
int Cls();

//�����ı�ȫ����ɫ
int Color(const char *str);

//���������
bool Randomize();

//��ȡ��ȷʱ�䣬��ʱ��
long long GetTimeout();

//���ַ��������������ת��
string Converted(string str);

//��û���λ��
CONSOLE_SCREEN_BUFFER_INFO GetBufferinfo();

//�Ѵ�ʱ��Ļ�ϵ��ַ�ȫ������ȫ�ֱ���FaceMap��
BOOL GetFace(CHAR_INFO *face_buf);

//��ȡFaceMap��x�еĵ�y���ַ�
char GetPositionChar(int x, int y);

//ʹ���ָ���x�У���y��
BOOL Position(int x, int y);

//�ѹ�������ƶ�dy�������ƶ�dx�������Ǹ�����
BOOL PstTurn(int dx, int dy);

//���ǹ��ǰ��dy�� Ҫ��֤ǰ�����dy��
bool CoverBack(int dy = 1);

//���x,y�������֣�����len����պ󷵻�x,y����׼�� 
BOOL PstC(int x, int y, int len);

//�����첽�������֣������ǵ�ǰ��Sound����ѭ��
BOOL Sound(const char *str);

//���ǵ�ǰSound
BOOL SoundCover(const char *str);

//���ǵ�ǰSound���Ҳ�����Ż������һ����
BOOL SoundWait(const char *str);

//ֹͣSound
BOOL SoundStop();

//����mciSendString()
BOOL mciSS(const char *str);

//������α�����Ч�����Ժϲ���Sound()�У����Ƚϸ��ӣ���Ҫ��ɢ���ַ�����ʹ�ô�������ȡ������Ƶ����Ŀ
BOOL SoundBird();
BOOL SoundInsect();
BOOL SoundHit();
BOOL SoundCough();

//��ʾ���
BOOL CursorShow();

//���ع��
BOOL CursorHide();

//����͸����
BOOL SetAlpha();

//����ΪĬ������
BOOL SetFont();

//��ʾ����ת��Ĭ��
bool FaceInit();

//�������õ�Ĭ��
bool WindowSet();

//���ջ�����������
bool Flush();

//�����ͬʱ���������Ҽ��������ת��Ϊ��Ӧָ��
int getord(bool stayable = true);

string getlin(int lenlim = yMax);

//�ڱ�׼��ʾ���������ʾ
bool Tips(const char *str);

//��궨λ����׼���ִ��������
BOOL PstInput();

//�Դ��������ʾ
bool Error(int c);

//�ڻ��������ַ���ʱ���ܹ�������Sleep()
bool Delay(int t, bool skipable = true);

//�������������֣�ͨ��������
bool Printl(const char *str, int DPL = 0, int DPS = 0, bool skipable = true);

bool encfile(char *in_filename, char *pwd, char *out_filename);

bool Prese();

bool Load();

bool Pause();
