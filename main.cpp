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

//������
int mainful(int argc, char *argv[]) {

	puts("");
	printf("  ���ڳ�ʼ����\n\n");

	WindowSet();
	s = "����";
	FaceInit();//����ʹ��
	mciSS("open Data\\Music\\Array.mp3 alias Array");
	mciSS("play Array");

	printf("  ��ʼ����ϡ�\n");

	remap = true;

	FILE *fin;

	int pit = 1;//"pitch on"��ѡ�е�
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
			Cls();//�Զ�������
			printf(
				"    ___________                              \n"
				"   |                                         \n"
				"   |                                         \n"
				"   |                                         \n"
				"   |                                         \n"
				"   |                                         \n"
				"   |__________   ______    ____      ____    \n"
				"   |           |/      \\  /    \\    /    \\   \n"//��ת���ַ����²�����
				"   |           |         /      \\  /      \\  \n"
				"   |           |        /________\\/________\\ \n"
				"   |           |        \\         \\          \n"
				"   |           |         \\         \\       / \n"
				"   |           |          \\_____/   \\_____/  \n"
				"                              _  _  _        \n"
				"                          ----\\\\( )//----    \n"
				"             (\\           |  ��ʼ - ��  |   \n"
				"              \\)_         |  ���� - ��  |   \n"
				"           .--' ')        |  ���� - ��  |   \n"
				"         o(  )_-\\         |  ���� - ��  |   \n"
				"           `\"\"\"` `        |-------------|    \n"
			);
			Position(4, 24);
			printf("%s : %s", VER_STRING, VER_DESCRIPTION);//�汾�š��汾����

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
		//��ʾѡ��״̬
		Position(15 + pit, 28), putchar('[');
		Position(15 + pit, 40), putchar(']');

		r = getord();//������ȴ���getord�Դ�
		r = Directed(r);//w, sת�������¼�
		//ȡ����ʾѡ��״̬
		Position(15 + pit, 28), putchar(' ');
		Position(15 + pit, 40), putchar(' ');

		if (r == ENTER)//׼�����롣����switch()��ͬ����
			switch (pit) {
			case 1: r = 'p'; break;
			case 2: r = 'c'; break;
			case 3: r = 'h'; break;
			case 4: r = 'q'; break;
			default: break;
			}
		switch (r) {
		case UP_KEY:
			Sound("Cursor");//�α�
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
			printf("  �½���ɫ��\n\n");

		#ifdef MSVC
			fopen_s(&fin, "Data\\Prese\\FreePrese.sev", "rb");//�½�ʱ������Ƿ��д浵
		#else
			fin = fopen("Data\\Prese\\FreePrese.sev", "rb");
		#endif
			if (fin != NULL) {
				fclose(fin);
				printf(
					"  Ȼ����⵽��ǰ�Ĵ浵��\n"
					"  \n"
					"  120���󽫸���ԭ�浵��ȷ����\n"
					"  \n"
					"  ���� 0 ���أ����������������\n"
				);

				r = getord();
				if (r == '0' or r == ESC) {
					remap = true;
					break;
				}
			}

			reNew();//���Գ�ʼ��
			Setting();//�������ã��Դ�ˢ��

			Cls();//����
			mciSS("stop Array");
			mciSS("close Array");//ȡ����������

			Gate(); // �ռ䴫����

			mciSS("open Data\\Music\\Array.mp3 alias Array");//������������
			mciSS("play Array");
			remap = true;//�������������
			FaceInit();
			break;

		case 'c':
			Cls();
			puts("");
			printf("  ��ȡ�浵��...\n");

			reNew();
			Load();//����Setting�Ĳ���

			Cls();//���Ҳ��Զ�����.. 
			mciSS("stop Array");
			mciSS("close Array");

			TimeLapse(0, FRESH);//����Load��ˢ��
			Gate();

			mciSS("open Data\\Music\\Array.mp3 alias Array");
			mciSS("play Array");
			remap = true;
			FaceInit();
			break;

		case 'h'://�����İ���
			Sound("Helpin");

			Cls();
			puts("");
			printf(
				"  Free �Ǿ�����Ϸ��\n"
				"  \n"
				"  ��������ǳ������һλ���ɾ���\n"
				"  ӵ�й�����ѧϰ�Ͷ�����Ȩ����\n"
				"  \n"
				"  ���˻���ֹ��̽��������\n"
				"  ����ֻ�����������Լ��ɡ�\n"
				"  �ж�ʱ����ʱע��״̬�仯��\n"
				"  \n"
				"  ������ʾ������ʱ�����ţ���Ϸ��������һ����\n"
				"  ���������ڣ����ʾ���λ�ã�\n"
				"  �����������Ҽ����ƶ���\n"
				"  \n"
				"  120�����ϣ�ÿ20���Զ��浵��\n"
				"  һЩ�¼�Ҳ�ᴥ���Զ����档\n"
			);

			printf(
				"  \n"
				"  ��һҳ...\n"
			);

			Pause();

			Cls();
			puts("");
			printf(
				"  �Ƽ��ڿ���̨ʹ�ã�\n"
				"  Сд����\n"
				"  Ӣ�����뷨\n"
				"  \"����\"��\"����\"\n"
				"  \n"
				"  ����Ϸ�еĸ�������裬�����Ի�ö�Ӧ������\n"
				"  �����������˽�������¡�\n"
				"  \n"
				"  \n"
				"   ��д��\n"
				"  ��Hoale\n"
				"  ��Hoare\n"
				"  ��Dilute\n"
				"  ��xuxing\n"
				"  ��bilibili\n"
				"  ��Jeff\n"
			);

			r = getord();
			if (r == 'v')
				system("start http://mant.ink/");//������վ

			Sound("Helpout");//note
			remap = true;
			break;

		case 'q':
			Cls();
			return 0;
			break;

		default:
			Error(2);
			if (isupper(r)) {//�����˴�д��ĸ
				Cls();
				puts("");
				printf("  ���Сд���̡�\n");
				Pause();
				remap = true;
			}
			break;
		}
	}
	return 0;
}
