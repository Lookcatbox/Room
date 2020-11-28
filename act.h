#pragma once

#include "pch.h"

bool reNew();
//��һ�� 
long long Enter();

//�е�㸴��
int Pitch(int num, const char *desc[], int dis = 1, int pit = 1, int ym = 30/*��һ���ַ���������Ȼ�����*/, int x = 0);

bool PreseTry();

//�������� ����code�����жϽ���ԭ��
int End(int c);

//��ʾ״̬
bool Stateout();

//��ʾ�ֱ����ݵ���׼λ��
bool Watchout();

//ת��״̬��ͬʱ��ȡ״̬���ת����
int StateTurn(int c, int tar);

//ĳ��״̬����󣬲ŵ������ж�״̬�����Ľ��
int TimeLapse(long long t = 0, int activity = FRESH/*No too much*/);

//��ͼ����
bool Mapin(const char *file = map_file, int xs = 1, int xt = xMax, int ys = 1, int yt = yMax);

//��״��ʾMap�����Ĳ�������
bool Mapput(int x, int y, bool mapingable = true, int ys = 1, int yt = yMax);

//�����ͼ
bool Mapout(int pat = NONE, int xs = 1, int xt = xMax, int ys = 1, int yt = yMax);

//���������ͼ��ʽ��������״̬��
bool CommonreMap();

//������
bool Decide(int c, int pit);

//����
int Setting();

//�鿴��ݼ�
int KeyView();

//��������
int Help();

//�������������Ա��ڻع���ǰ������
int TaskView(int codeA, int codeB);

//��ʾ������
int Task();

//��Ǯ�����ˣ������ӵ�
bool Pay(int money_need);

//��ý�Ǯ
bool Gain(int money_back);

//�Զ���
int Eat(int c, int num);

//����
int Read(int c);

//��ʾ�򸲸������
bool InputBox(bool visable);

//�����������֣���������
bool CommonInput(int type = INTEGER, bool expand = true, int lenlim = 9, bool InputBoxable = false);

//������һ��λ�á���ǿ����ɶ���
bool MoveBack();

//�ڱ�����
bool UseItem(int c, int num);

//����ͳ��blo����Ϣ
bool BlockFresh(int blo);

int GetItemnum(int c);

//����num����Ʒc
bool GiveItem(int c, int num = 1);

//ϵͳ������Ʒ�����õ���putitem(-1)
bool PutItem(int c, int num = 1);

//��ʾ��blo�����Ʒ
bool Blockout(int blo);

//�򿪰���
int Pack();

//��Body����˺���ˢ��
bool Injure(Bodyinfo &body, double price);

//˯��
bool Asleep(long long sleep_time/*, long long TimeSnooze*/);

//�ڲ����룬֧�ִ򿪱���������� 
bool Input(int type, bool expand, int lenlim = 0);

//���ú����������ƶ��������ƶ��������ƶ��Ƿ�ɹ� 
bool Move();
