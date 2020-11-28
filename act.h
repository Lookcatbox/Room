#pragma once

#include "pch.h"

bool reNew();
//下一步 
long long Enter();

//有点点复杂
int Pitch(int num, const char *desc[], int dis = 1, int pit = 1, int ym = 30/*第一个字符输出在哪里，然后居中*/, int x = 0);

bool PreseTry();

//结束界面 参数code用于判断结束原因
int End(int c);

//显示状态
bool Stateout();

//显示手表内容到标准位置
bool Watchout();

//转变状态的同时获取状态如何转变了
int StateTurn(int c, int tar);

//某步状态变更后，才到这里判断状态产生的结果
int TimeLapse(long long t = 0, int activity = FRESH/*No too much*/);

//地图读入
bool Mapin(const char *file = map_file, int xs = 1, int xt = xMax, int ys = 1, int yt = yMax);

//块状显示Map，中文不出问题
bool Mapput(int x, int y, bool mapingable = true, int ys = 1, int yt = yMax);

//输出地图
bool Mapout(int pat = NONE, int xs = 1, int xt = xMax, int ys = 1, int yt = yMax);

//常见输出地图方式，必须有状态栏
bool CommonreMap();

//做决定
bool Decide(int c, int pit);

//设置
int Setting();

//查看快捷键
int KeyView();

//帮助界面
int Help();

//保留两个代号以便于回顾先前的任务
int TaskView(int codeA, int codeB);

//显示任务栏
int Task();

//把钱给别人，而非扔掉
bool Pay(int money_need);

//获得金钱
bool Gain(int money_back);

//吃东西
int Eat(int c, int num);

//读书
int Read(int c);

//显示或覆盖输入框
bool InputBox(bool visable);

//常见读入数字，结合输入框
bool CommonInput(int type = INTEGER, bool expand = true, int lenlim = 9, bool InputBoxable = false);

//返回上一步位置。增强代码可读性
bool MoveBack();

//在背包中
bool UseItem(int c, int num);

//重新统计blo格信息
bool BlockFresh(int blo);

int GetItemnum(int c);

//给出num个物品c
bool GiveItem(int c, int num = 1);

//系统放置物品，不用担心putitem(-1)
bool PutItem(int c, int num = 1);

//显示第blo格的物品
bool Blockout(int blo);

//打开包裹
int Pack();

//对Body造成伤害并刷新
bool Injure(Bodyinfo &body, double price);

//睡觉
bool Asleep(long long sleep_time/*, long long TimeSnooze*/);

//内部读入，支持打开背包、任务等 
bool Input(int type, bool expand, int lenlim = 0);

//常用函数。读入移动操作、移动。返回移动是否成功 
bool Move();
