#include "pch.h"
/*
	����Free 3.0�ı����������
*/
//�浵ʶ���õİ汾��

Vnum V, FileV;
Vnum Vn(int Maj, int Min, int Rel, int Bui) {
	Vnum V;
	V.Maj = Maj;
	V.Min = Min;
	V.Rel = Rel;
	V.Bui = Bui;
	return V;
}

int blocknum;//��������
int place, sx, sy;//�ص��λ��
int money, watch, reward_meal, work_score;//������Ʒ����Ŀ

Blockinfo block[21];//����
int task_rate[21];//�������
long long timein;//��ʱ�䣨Free��Ϸ��ʱ�䣩
long long step;//����

//���ã�ҲҪ�浵 
int colorable, flashable;//����
unsigned int code_style;//���ֻ�������

//����ȫ�ֵ���ʱ����
bool remap, inpack;//������
int tx, ty;//��һ��
int state[21], statechange[21];//״̬��״̬�Ƿ�仯
long long day, hour, minute, second;//��ʱ��ʵʱת�����ա�ʱ���֡���
HWND free_handle;//ȫ�ִ��ھ��
HANDLE output_handle, input_handle;//ȫ�ֱ�׼����������

int light, alpha, font_size;//������ʾ

//for All Faces
bool border;//�Ƿ��б߿�
//for Areas
const char *map_file;//�ó�����ͼ�ļ�
double ins_coe;//�������Ҳ�ϵ��
int move_unit_time;//��λ�ƶ�ʱ��

//buffer
int r;//Input(1)�����뵥���ַ�
string s;//Input(2)�������ַ���
int n;//Input(3)����������
char atlas[25][65];//��ͼ�����Ȳ��ܽ���map
bool maping[25][65];//��ͼ�ĸĵ��Ƿ��Ѿ������

CHAR_INFO face_map[yMax * xMax];//��������ϵ��ַ���ͨ��GetFace()��õ�

Bodyinfo me;//�ҵ�������Ϣ

Bankinfo city_bank;//��������

//����ϸ�ڱ���
int CME;//�������ƶ�����

//�б�
int decision[1100];
/*
1:��ƿ����
2:��ƿ����4-1�ľ���
*/