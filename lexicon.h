#pragma once
/*
	����Free 3.0�ĳ����⣬�洢�����ҵĵ��ʡ���Ʒ���Ե�
*/
extern const int FLASH_SPAN;//��˸�����������λ������
extern const int SPL_SPEAK, SPS_SPEAK;//�Ի�ʱPrintl���ַ�����;��Ӽ��
extern const int SPL_THINK, SPS_THINK;//˼��ʱPrintl���ַ�����;��Ӽ��

extern const int kStatecnt;//һ���м���״̬
struct Stateinfo {//״̬����ʾ
	int x;//��ʾʱ��������
	const char *desc[11];//������������
	int flash[11];//�Ƿ���ʾ���Լ���ʲô��ʽ�������ʾ
	int common;//����һ��Ĭ��״̬
};
extern const Stateinfo kStateBoard[21];

extern const int kTaskSeriecnt;//����ϵ����
struct Taskinfo {
	int cnt;
	const char *name[110];
};
extern const Taskinfo kTask[21];

extern const int kDecicnt;//�ؾ��߼���
extern const int kBirdcnt, kInsectcnt, kChewcnt, kHitcnt,//һЩ������Ч���ļ���
kCoughcnt;

struct Foodinfo {
	long long use_time;//ʹ�����ĵ��ڲ�ʱ��
	int delay;//ʹ���ӳ�ʱ��

	double pro;//�����ʣ�ÿ�ݺ�������
	double fat;//֬����ÿ�ݺ�������
	double car;//���ࣨÿ�ݺ�������
	double can;//�°��ÿ�ݺ�������
	const char *file;//�����ļ�
};
extern const Foodinfo kFood[110];

struct Bookinfo {
	const char *file;
	int pagecnt;
	long long read_time;
};
extern const Bookinfo kBook[110];

struct Perminfo {
	const char *desc;
};
extern const Perminfo kPerm[110];

struct Druginfo {

};
extern const Druginfo kDrug[110];

extern const char *ItemTypeDesc[110];

struct Iteminfo {//��Ʒ��Ϣ
	const char *name;//��������
	const char *meas;//���ĵ�λ

	int type;//Ʒ�ִ���
	int code;//��Ʒ���еĴ���

	int carry;//����������
	bool reusable;//�ɷ���ʹ��
};
extern const Iteminfo kItem[1100];

extern const int kActcnt;//�����ĸ���
struct Actinfo {
	const char *name;//����
	double pro_coe;//�����ĵ���������ϵ������Ϊ1�������������£�ÿ��ǡ������60g
	double fat_coe;//������֬������ϵ������Ϊ1�������������£�ÿ��ǡ������60g
	double car_coe;//��������������ϵ������Ϊ1�������������£�ÿ��ǡ������300g
	double can_coe;//�����Ŀ���ϵ������Ϊ1�������������£�ÿ��ǡ�÷ֽ�1��λ�°���
	bool effable;//������ʱ����ʱ���Ƿ��������Ӱ��
};

extern const Actinfo kAct[21];

extern const double kProEne, kFatEne, kCarEne;//ÿ��Ӫ�����ṩ����
extern const double kDailyPro, kDailyFat, kDailyCar, kDailyCan;//ÿ�ձ�׼����������
extern const double kProMus, kFatMus, kCarMus;//ǿ�����ʵı�׼Ӫ������
extern const double kDailyEne;//ÿ�ձ�׼����
extern const double kSecondCoe, kLossBase, kEffBase;//Ӱ�쳣��
extern const int kStdPhy;//��׼�������������ޣ�����integer

extern const int kWordcnt;//�ʻ���Ŀ
extern const string kLexicon[410];

extern const int kFuncnt;//��Ч�ƶ�ʱ������������ʾ�����Ŀ
extern const char *kErrorFun[110];
