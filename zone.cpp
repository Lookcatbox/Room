#include "pch.h"
/*
	Free 3.0�����еص�
*/

int Supermarket() {
	{//��ʼ����־
		map_file = "Supermarket";
		ins_coe = 1.60;
		move_unit_time = 7;
	}

	remap = true;

	while (place == SUPERMATKET) {
		if (remap) {
			CommonreMap();
			Tips("����Ÿ��ߵ�Ա������������ܵģ��س����ɷ��ء�");

			remap = false;
		}

		if (!CommonInput()) continue;
		switch (n) {
		case 1:
			Tips("\"�㿾���⣬����ʮ�㡣�͹���㼸�ݣ�\"");
			//Position(��);

			if (!CommonInput()) break;
			if (n there) {//δ��������Ϊ���ܳ���
				if (Pay(n * 21)) {
					Tips(""), printf("����%dֻ����", n);
					if (state[HUNGER] <= 1) printf("���������̻���..."); else printf("������Ʈ��ζ��...");

					int eaten = Eat(4, n);
					if (eaten == 0)
						Tips("̫���ˡ���֬�����������Ż��");
					else if (eaten < n)
						Tips(""), printf("��...�ò����ײų�����%dֻ��", eaten);
					else
						Tips("��Ƥ���������пɡ�");
				}
				else
					Tips("\"��û����Ǯ��...\"");
			}
			else
				Tips("\"��ƣ�զ���£�\"");
			break;
		case 2:
			Tips("\"���ֺ決��Ƥ������������ֳ�ʳ�á���Ҫ���٣�\"");

			if (!CommonInput()) break;
			if (n there) {
				if (Pay(n * 8)) {
					Tips(""), printf("�׽�����%d���������...", n);

					int eaten = Eat(2, n);
					if (eaten == 0)
						Tips("���ˡ���Щ����ƣ�͡�");
					else if (eaten < n)
						Tips(""), printf("ֻ��������%d�飬�ٳԿ�Ҫ���ˡ�", eaten);
					else
						Tips("�������˻�ζ��");

					//Task 1-3
					if (task_rate[1] == 2) {
						Delay(1500);//��ζ
						task_rate[1] = 3;
						TaskView(1, 3);
						remap = true;
					}
				}
				else
					Tips("\"��ȷ����û����Ǯ��\"");
			}
			else
				Tips("\"��˵ʲô����û���塣\"");
			break;
		case 3:
			Tips("\"��Ȥ�ᱡ���ɷŽ�������ÿ��22Ƭ���򼸰���\"");

			if (!CommonInput()) break;
			if (n there) {
				if (money >= n * 12) {
					if (PutItem(COOKIE, n * 22)) {//���� 
						Pay(n * 12);
						//Sound
						Tips(""), printf("\"������%d����Ȥ������򿪰�����\"", n);
					}
					else
						Tips("������Ų�����Щ���ɡ�");
				}
				else
					Tips("\"��Я�����ֽ𲻹���\"");
			}
			else
				Tips("\"�Һ��������˵��...\"");
			break;
		case 4:
			Tips("\"�ֱ���Ϊ��ָʾʱ�䡣��λ�ϰ壬����Ҫ��ֻ�ֱ�\"");

			if (!CommonInput()) break;
			if (n there) {
				if (Pay(n * 298)) {
					watch += n;//һЩ����
					TimeLapse(n * 7 minutes, FIX);//�䱸�ֱ�
					Tips(""), printf("\"Ϊ���䱸%dֻ�ֱ����Դ򿪱����鿴ʱ�䡣\"", n);
				}
				else
					Tips("\"����������������ɣ�\"");
			}
			else
				Tips("\"������Ū��Ϳ�ˡ�\"");
			break;
		case 5:
			Tips("\"ĸ��ţ��������Ƶ��䣬�ߵ��ס�����Ҫ���٣�\"");

			if (!CommonInput()) break;
			if (n there) {
				int MoneyNeed = n * 9;
				if (Pay(MoneyNeed)) {
					Tips(""), printf("��ǰ����%d��ţ���������...", n);

					int eaten = Eat(5, n);
					if (eaten == 0)
						Tips("�������Σ���ʱ�����ٳ��ˡ�");
					else if (eaten < n)
						Tips(""), printf("����%d�������з��ᣬ�������ʡ�", eaten);
					else
						Tips("���ʽ�ʵ���ڸж��ء�");
				}
				else
					Tips("Ǯ�����ˡ�");
			}
			else
				Tips("�����ʣ�");
			break;
		case 6:
			Tips("\"�Ʋ�����������ʧ�������������ڵġ�����ݵ���! \"");
			break;
		case 7:
			Tips("\"������������ʱ�������ˡ�����һЩҩƷ! \"");
			break;

		case 0:
			MoveBack();
			place = CITY;
			sx = 12, sy = 36;
			break;

		default:
			Sound("Error");
			TimeLapse(5, THINK);
			Tips("��������Ʒ��ţ����������Է��ء�");
			break;
		}
	}
	return 0;
}

int WeaponShop() {
	{
		map_file = "WeaponShop";
		ins_coe = 1.40;
		move_unit_time = 8;
	}

	remap = true;

	while (place == WEAPONSHOP) {
		if (remap) {
			CommonreMap();
			Tips("�ϰ尴����������ܣ����·��ء�");

			remap = false;
		}

		if (!Input(ORDER, true))
			continue;
		if (r == 's') r = DOWN_KEY;

		switch (r) {
		case DOWN_KEY:
			MoveBack();
			place = CITY;
			sx = 9, sy = 23;
			break;

		default:
			TimeLapse(5, THINK);
			Tips("��������ţ����������Ա��뿪��");
			break;
		}
	}
	return 0;
}

int Bedroom() {
	{
		map_file = "Bedroom";
		ins_coe = 0.48;
		move_unit_time = 6;
	}

	Mapin();
	Mapout();
	border = false;

	Input(ORDER, true);//����������
	r = Directed(r);

	if (r == UP_KEY) {
		long long TimeSleep = 0;

		if (state[SLEEPINESS] == 2 and (hour >= 16 or hour <= 4)) {//�����߽���ʱ������˯
			//Ҫ��֤��һ��22:00��˯��Ԥ������ʱ��Ϊ�糿6ʱ
			TimeSleep = 4 hours + abs(hour - 12) hours / 2;
		}
		else
			if (state[SLEEPINESS] <= 1) {//��ҪͻȻ
				TimeSleep = 4 hours + abs(hour - 12) hours / 2 + me.TS / 2;//ûë�� 
			}
			else {
				Tips("���ڴ��Ϻ��˺��ۣ���˯����...�������ء�");
				Pause();
			}

		if (TimeSleep) {
			TimeSleep += (int)(RandAround(0, 60 minutes));

			Asleep(TimeSleep/*, noLess(3 hours - TimeSleep / 4, 0)*/);
			//	Prese();//�Զ����档���Żᱣ��
		}
	}

	MoveBack();
	place = HOME;
	sx = 7, sy = 34;

	return 0;
}

int Kitchen() {
	{
		map_file = "Kitchen";
		ins_coe = 1.20;
	}

	remap = true;

	while (place == KITCHEN) {
		if (remap) {
			CommonreMap();
			Tips("����������ԾԾ���ԡ����Ҫ���ؾ������ߡ�");

			remap = false;
		}

		if (!Input(ORDER, true))
			continue;
		r = Directed(r);

		switch (r) {
		case DOWN_KEY:
			MoveBack();
			place = HOME;
			sx = 7, sy = 11;
			break;
		default:
			break;
		}
	}
	return 0;
}

int Home() {
	{
		map_file = "Home";
		ins_coe = 0.70;
		move_unit_time = 6;
	}

	mciSS((state[LIFE] > 2) ?
		"open Data\\Music\\Home.mp3 alias Home" : 
		"open Data\\Music\\Homeless.mp3 alias Home");
	mciSS("play Home");

	remap = true;
	while (place == HOME) {
		if (remap) {
			CommonreMap();
			Tips(state[LIFE] <= 2 ?
				"�����ů�͡�" :
				"�ҵĸо���á�");

			remap = false;
		}
		if (!Move())
			continue;

		switch (atlas[sx][sy]) {
		case 'K':
			place = KITCHEN;
			break;

		case 'B':
			place = BEDROOM;
			break;

		case 'D':
			place = CITY;
			sx = 15, sy = 39;
			break;

		default:

			break;
		}
	}

	mciSS("stop Home");
	mciSS("close Home");
	return 0;
}

int Library() {
	Cls();
	Pause();
	return 0;
}

int DiningHall() {
	Cls();
	Pause();
	return 0;
}

int SchoolHistory() {
	Cls();
	Pause();
	return 0;
}

int ObjectHouse() {
	Cls();
	Pause();
	return 0;
}

int NeighborBedroom() {
	{
		map_file = "NeighborBedroom";
		ins_coe = 0.50;
		move_unit_time = 6;
	}

	remap = true;

	while (place == NEIGHBOR_BEDROOM) {
		if (remap) {
			CommonreMap();
			Tips("�����߽��ھӼ����ҡ�");

			remap = false;
		}

		if (!Move())//�ھ����� 
			continue;

		switch (atlas[sx][sy]) {
		case 'D':
			place = NEIGHBOR;
			sx = 12, sy = 38;
			break;

		default:

			break;
		}
	}
	return 0;
}

int Neighbor2F() {
	{
		map_file = "Neighbor2F";
		ins_coe = 0.90;
		move_unit_time = 6;
	}

	mciSS((decision[1] == 0) ?
		"open Data\\Music\\ItomakiA.mp3 alias Itomaki" :
		"open Data\\Music\\ItomakiB.mp3 alias Itomaki");
	mciSS("play Itomaki repeat");

	remap = true;

	while (place == NEIGHBOR_2F) {
		if (remap) {
			CommonreMap();

			Tips((decision[1] == 0) ?
				"��ϸ������֣�Դͷ�������ء�" : 
				"�Ҷ���������Ӱ!");

			remap = false;
		}

		if (!Move())//�ھӶ�¥ 
			continue;

		switch (atlas[sx][sy]) {
		case 'R':
			MoveBack();
			if (decision[1] == 0) {
				Decide(1, 1);

				mciSS("stop Itomaki");
				mciSS("close Itomaki");
				Tips(""), P("...", 1000);
				P("�����ˡ�", 30, 0, false);
				SoundWait("Crash");

				mciSS("open Data\\Music\\ItomakiB.mp3 alias Itomaki");
				mciSS("play Itomaki repeat");

				Tips("������ʲô������ǰֻʣ��Ƭ...");
			}
			else
				Tips("��ɻ�ƿ�����ˡ�");

			break;

		case 'L':

			break;

		case 'S':
			place = NEIGHBOR;
			sx = tx, sy = ty;//һ������ķ��ط�ʽ 
			//��������¥��
			if (decision[1] == 1 and task_rate[4] == 0) {
				task_rate[4] = 1;
				TaskView(4, 1);
			}
			break;

		default:

			break;
		}
	}
	mciSS("stop Itomaki");
	mciSS("close Itomaki");
	return 0;
}

int Neighbor() {
	{
		map_file = "Neighbor";
		ins_coe = 0.75;
		move_unit_time = 6;
	}

	remap = true;

	while (place == NEIGHBOR) {
		if (remap) {
			CommonreMap();
			Tips("�ƺ�û���ˡ�");

			remap = false;
		}

		if (!Move())
			continue;

		switch (atlas[sx][sy]) {
		case 'S':
			place = NEIGHBOR_2F;
			sx = tx, sy = ty;//һ������Ľ��뷽ʽ 
			break;

		case 'B':
			place = NEIGHBOR_BEDROOM;
			sx = 15, sy = 26;
			break;

		case 'D':
			place = CITY;
			sx = 13, sy = 39;
			break;

		default:

			break;
		}
	}
	return 0;
}

int SchoolHide() {
	{
		map_file = "SchoolHide";
		ins_coe = 1.80;
		move_unit_time = 7;
	}

	mciSS("open Data\\Music\\Hide.mp3 alias Hide");
	mciSS("play Hide repeat");

	remap = true;

	while (place == SCHOOL_HIDE) {
		if (remap) {
			CommonreMap();
			Tips("������Ҫ͸¶�������Ϣ��");
			remap = false;
		}

		if (!Move())//����
			continue;

		switch (atlas[sx][sy]) {
		case 'B':
			//Task 3-1
			if (task_rate[3] == 0) {
				task_rate[3] = 1;
				TaskView(3, 1);
				remap = true;
			}
			else
				Tips("���������Ź�һ��ֽ��");

			MoveBack();
			break;

		case 'd':
			place = SCHOOL_2F;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}

	mciSS("stop Hide");
	mciSS("close Hide");
	return 0;
}

int School3F() {
	{
		map_file = "School3F";
		ins_coe = 1.00;
		move_unit_time = 12;
	}

	remap = true;

	while (place == SCHOOL_3F) {
		if (remap) {
			CommonreMap();
			Tips("���Ͽ�������У�š�");

			remap = false;
		}

		if (!Move())//��ѧ¥ 
			continue;

		switch (atlas[sx][sy]) {
		case 'P':
			MoveBack();
			break;

		case 'D':
			place = SCHOOL_2F;
			sx = 9, sy = ty;
			break;

		default:

			break;
		}
	}
	return 0;
}

int School2F() {
	{
		map_file = "School2F";
		ins_coe = 1.00;
		move_unit_time = 12;
	}

	remap = true;

	while (place == SCHOOL_2F) {
		if (remap) {
			CommonreMap();
			Tips("��������·���");

			remap = false;
		}

		if (!Move())//��ѧ¥ 
			continue;

		switch (atlas[sx][sy]) {
		case 'U':
			place = SCHOOL_3F;
			sx = 7, sy = ty;
			break;

		case 'P':
			//SchoolHistory();
			MoveBack();
			//reMap = true;
			break;

		case 'D':
			place = SCHOOL_1F;
			sx = 9, sy = ty;
			break;
		case 'a':
			place = SCHOOL_HIDE;
			sx = sx, sy = 54;
			break;
		default:

			break;
		}
	}
	return 0;
}

int School1F() {
	{
		map_file = "School1F";
		ins_coe = 1.00;
		move_unit_time = 12;
	}

	remap = true;

	while (place == SCHOOL_1F) {
		if (remap) {
			CommonreMap();
			Tips("�����ҵذ塣");

			remap = false;
		}

		if (!Move())//��ѧ¥ 
			continue;

		switch (atlas[sx][sy]) {
		case 'U':
			place = SCHOOL_2F;
			sx = 7, sy = ty;
			break;

		case 'P':
			//ObjectHouse();
			MoveBack();
			//reMap = true;
			break;

		case 'D':
			place = SCHOOL;
			sx = 4, sy = 13;
			break;

		default:

			break;
		}
	}
	return 0;
}

int School() {
	{
		map_file = "School";
		ins_coe = 1.10;
		move_unit_time = 24;
	}

	remap = true;

	while (place == SCHOOL) {
		if (remap) {
			CommonreMap();
			Tips("ԶԶ������");

			remap = false;
		}

		if (!Move())//ѧУ 
			continue;

		switch (atlas[sx][sy]) {
		case 'H':
			//DiningHall(); 
			// RETURN
			Tips("װ�޵�����ľмζ��");
			MoveBack();
			break;

		case 'T':
			place = SCHOOL_1F;
			sx = 7, sy = 7;
			break;

		case 'D':
			place = CITY;
			sx = 6, sy = 50;
			break;

		default:

			break;
		}
	}
	return 0;
}

int MER() {//MedicalExaminationReport ��Ȼ���ڿƣ������Ǳ��ҽԺ�ɣ�
	border = false;//�����ڴ˵�
	Cls();
	puts("");

	P("  ���������ƽ����\n", SPL_SPEAK, SPS_SPEAK);
	if (!between(hour, 5, 21))
		P("  �ƹⰵ����ˮ��ǽ�Ĳ�ƽ��������¶��\n", SPL_SPEAK, 1000);
	P("\n");

	{//�γɾֲ�
		const char *b[] = {
			"  \"���ã���������Ҫ������\"\n",
			"  \"���ǲ�����Ҫ������\"\n",
			"  ����ҽ���������������\n"
		};
		P(RandS(3, b), SPL_SPEAK, SPS_SPEAK);
	}
	puts("");
	int pit = 0;
	{//�γɾֲ�
		const char *b[] = {
			"�ǵ�...",
			"���ˡ�"
		};
		pit = Pitch(2, b, 2);
	}
	if (pit == 2)
		return -1;

	int Prescription = false;

	Cls();
	puts("");
	TimeLapse(6 minutes, FIX);
	me.Examine();//ǿ�����

	P("  \"������\"", SPL_SPEAK, SPS_SPEAK);
	if (state[LIFE] <= 2)
		P("\n  �������ں�������...", SPL_SPEAK, 1500);
	P("\n\n");
	Flush();//Ƭ�ε�ĩβ

	if (GetItemnum(Rx)) {
		P("  \"�㲻�ǻ����Ŵ�����", SPL_SPEAK, SPS_SPEAK), P("ȥ��ҩ�ɡ�\n", SPL_SPEAK, SPS_SPEAK);
		P("   ���ģ�ҩʦ���ǻ��һ�����ġ�\"\n\n", SPL_SPEAK, 1000);
		P("  �����뿪...\n");
		Pause();
		return -1;
	}

	if (state[MUSCLE] <= 1) {
		P("  \"������������屣��������\n", SPL_SPEAK, 1000);
		Happen(0.3) ?
			P("   �����ʳҪ�����ã�", SPL_SPEAK, 0) ://����
			P("   ����߲ˣ�", SPL_SPEAK, 0);
		P("ƽʱ��ǿ����", SPL_SPEAK, 0);
		Happen(0.5) and
			Happen(0.5) ?
			P("������", SPL_SPEAK, 0) :
			P("����ס", SPL_SPEAK, 0);

		P("��\"\n\n", SPL_SPEAK, 1000);
	}
	Happen(0.5) and P("  ���ӹ�������һ�����ӣ���ͷ����������\n\n", SPL_SPEAK, 1500, false);
	Flush();

	P("  ҽ��ת���������۲�������ν����ɫ...\n", SPL_SPEAK, 1500);
	if (state[SLEEPINESS] <= 1)
		Happen(0.4) ?
		P("  \"��ɫƣ���úܣ����겡�Ȼ�ȥ��Ϣ�ɡ�\"\n", SPL_SPEAK, 1500) :
		P("  \"˯��̫�٣��ǲ��ǣ�ע�����Ϣ��\"\n", SPL_SPEAK, 1500);
	P("\n");
	Flush();

	P("  ����������������������ͷ����������ǰ��\n", SPL_SPEAK, 1500);
	Happen(0.4) ?
		P("  �����ֻ��˸��Ƕȣ��������г��ɡ�\n", SPL_SPEAK, 1000) :
		Happen(0.5) ?
		P("  \"���������һ�Ρ�\"\n", SPL_SPEAK, 1000) :
		P("  \"����'��'������\"\n", SPL_SPEAK, 1000);

	Pause();
	Cls();
	puts("");
	if (state[ILLNESS] <= 3) {
		SoundCough();
		Prescription = true;
		if (state[ILLNESS] <= 1)
			P("  \"������β���쳣�����ԡ�\"\n", SPL_SPEAK, 1000);
		else
			P("  \"�Ǹ�ð���𣿺������е㲻�Ծ���\"\n", SPL_SPEAK, 1000);
	}
	else
		P("  ����΢Ц��ɢ�˽��š�\n", SPL_SPEAK, 1000);
	P("\n");
	Flush();

	P("  ...�������ͷ�����˸�����\n", SPL_SPEAK, 1500);
	if (state[HUNGER] <= 1) {
		P("  \"θ��������Ծ����ҿ��Ƕ����˰ɡ�\"\n", SPL_SPEAK, 1000);
	}
	else
		if (state[HUNGER] >= 5) {
			Prescription = true;
			P("  \"�������Ҫ��������㿪����ʳƬ�ɡ�\"\n", SPL_SPEAK, 1000);
		}
		else
			P("  \"�ţ�ûʲôë����\"\n", SPL_SPEAK, SPS_SPEAK);
	P("\n");
	Flush();

	if (Prescription) {
		P("  \"�ã���������д�ˣ�����ȥҩ����ҩ��\n", SPL_SPEAK, SPS_SPEAK);
		P("   �ô�����ɣ��븶15Ԫ��Ϸѡ�\"\n\n", SPL_SPEAK, 1000);
		int pit = 0;
		{
			const char *b[] = {
				"����͸���...",
				"�����ˣ�лл��"
			};
			pit = Pitch(2, b, 2);
		}

		if (pit == 1) {
			if (money >= 15) {
				Pay(15);
				PutItem(Rx);
				Cls();
				puts("");
				Happen(0.5) ?
					P("  \"������ȥ��ȡ����...\"\n\n", SPL_SPEAK, 1000) :
					P("  \"�ǵ�ȥ��ȡ��������\"\n\n", SPL_SPEAK, 1000);
			}
			else {
				Cls();
				puts("");
				P("  \"Ǯû�����ġ�", SPL_SPEAK, SPS_SPEAK);
				P("�����������β����˵�ԭ��������˰ɡ�\"\n\n", SPL_SPEAK, 1000);
				Pay(money);
				PutItem(Rx);
			}
		}
	}
	else {
		P("  \"�������ɡ���������Ҫ�������ˡ���״����������\"\n\n", SPL_SPEAK, 1000);

	}
	P("  �����뿪...\n");
	Pause();
	return 0;
}

int Internal() {
	{
		map_file = "Internal";
		ins_coe = 0.80;//���ò����Ļ���
		move_unit_time = 12;
	}

	remap = true;

	while (place == INTERNAL) {
		if (remap) {
			CommonreMap();
			Tips("�ڿ��Ҵ����仯��ϸ���������");
			remap = false;
		}

		if (!Move())//�ڿ�
			continue;
		switch (atlas[sx][sy]) {
		case 'b':
			MoveBack();
			if (GetItemnum(BOOK_OF_SELFCARE))
				Tips("�����Ѿ���һ�������ֲᣬ�ǾͲ��˷������Դ�ˡ�"); else
				if (PutItem(BOOK_OF_SELFCARE, 1)) {
					Tips("���ϰ��ż��������ı����ֲᡣȡһ��������������ˡ�");
					//Task 1-5 open
					if (task_rate[1] == 4) {
						Sound("TaskComplete");
						task_rate[1] = 5;
					}
				}
				else
					Tips("������Ų����ֲᡣ");
			break;
		case 'A':
			MER();

			MoveBack();
			remap = true;
			break;
		case 'D':
			place = HOSPITAL;
			sx = 16, sy = 20;
			break;
		default: break;
		}

	}
	return 0;
}

int OutWound() {
	Cls();
	Pause();
	return 0;
}

int Hospital() {
	{
		map_file = "Hospital";
		ins_coe = 2.05;
		move_unit_time = 25;
	}

	remap = true;

	while (place == HOSPITAL) {
		if (remap) {
			CommonreMap();
			Tips("ҽԺ����ˮ��ζ���������˻����ȥ���¡�");

			remap = false;
		}

		if (!Move())//ҽԺ 
			continue;

		switch (atlas[sx][sy]) {
		case 'I':
			place = INTERNAL;
			sx = 13, sy = 51;
			break;

		case 'O':
			place = 110502;
			break;

		case 'G':
			Tips("С��Ҳ���ۡ�");
			//Money -= 10;
			MoveBack();
			break;

		case 'D':
			place = CITY;
			sx = 14, sy = 27;
			break;

		default:

			break;
		}
	}
	return 0;
}

int Typist() {
	{
		map_file = "Typist";
		move_unit_time = 17;
		ins_coe = 1.00;
	}

	remap = true;

	long long tot_timeout = 0;

	int combo = 0;
	int cur_score = 0, prize = 0;
	int A = 0, APM = 0;

	string cur_word, nxt_word;
	long long input_timeout;
	while (place == TYPIST) {
		if (remap) {
			CommonreMap();

			SoundCover("Machine");

			nxt_word = Converted(kLexicon[rand() % kWordcnt]);
			Position(6, 14); P("����Աϵͳ����", 0, 125);
			Position(8, 14); P("������ָ���Ĵʻ㲢�س�ȷ��", 0, 125);
			Position(10, 14); P("�����س����ر�ϵͳ", 0, 125);//Map��һ���� 

			//����
			TimeLapse(5 minutes, THINK);

			Position(12, 14); P("����������ã��������ʼ", 0, 125);
			Input(ORDER, false);

			if (r == 'g') {
				PstC(6, 14, 33); printf("��ӭ��������");
				PstC(8, 14, 33); printf("ƫ�ý��յĴ����� �����");
				PstC(10, 14, 33); printf("���� �밴���������");
				PstC(12, 14, 33);

				Input(ORDER, false);

				Sound("Code");
				if (r == 't')
					code_style |= TIGHT, PstC(12, 14, 33), printf("=> ��������ѿ��� ");
				else
					code_style &= ~TIGHT, PstC(12, 14, 33), printf("=> Java��������� ");

				printf("��������");

				Pause();
				remap = true;
				continue;
			}

			remap = false;
		}

		cur_word = nxt_word;

		PstC(8, 14, 33);
		printf("����ʻ㲢���� �����س��˳�");
		PstC(10, 14, 33);
		printf("%s", cur_word.c_str());

		nxt_word = Converted(kLexicon[rand() % kWordcnt]);
		PstC(14, 14, 33);
		printf("=> %s", nxt_word.c_str());

		PstC(12, 14, 33);
		input_timeout = GetTimeout();
		int input_res = Input(STRING, true, 33);//[�򿪰���]�Ȳ���������ҲҪ��ʱ
		input_timeout = GetTimeout() - input_timeout;

		tot_timeout += input_timeout;
		TimeLapse(noMore(input_timeout * 32 / 100, 80 minutes), TYPE);

		if (!input_res)
			continue;

		if (s == "") {//�뿪������ 
			MoveBack();
			place = WRITING;
			sx = 7, sy = 40;
			break;
		}

		if (s == cur_word) {
			SoundCover("Perfect");

			work_score += s.length();
			cur_score += s.length();
			A += s.length();//ע�⣬APM������ȷ�����ӣ���������򲻱� 

			PstC(6, 14, 33);
			printf("��׼���� ���ֹ����ܼ� %d", cur_score);
			++combo;
			if (combo >= 3) {
				PstC(7, 32, 15);
				printf("%9d����! ", combo);
			}
		}
		else {
			SoundCover("Mistake");

			int loss = noMore((int)s.length(), cur_score);
			work_score -= loss;
			cur_score -= loss;

			PstC(6, 14, 33);
			printf("���ֲ��� ���ֹ����ܼ� %d", cur_score);
			PstC(7, 32, 15);
			combo = 0;
		}
	}

	PstC(6, 14, 33);
	printf("��������");
	PstC(7, 14, 33);
	printf("���ֻ���н��Ϊ %d ����", cur_score);
	prize = (int)(noLess(cur_score - tot_timeout * 100 / 60 / 1000, 0));
	PstC(8, 14, 33);
	printf("���ݹ���Ч�� ���� %d", prize);
	work_score += prize;

	if (tot_timeout > 0)
		APM = (int)(A minutes * 1000 / tot_timeout);
	else
		APM = 0;
	PstC(9, 14, 33);
	printf("APM %d", APM);
	PstC(10, 14, 33);

	PstC(11, 14, 33);
	printf("���˹��ֹ��� %d", work_score);
	PstC(12, 14, 33);
	printf("���ֿ������²��һ�����");

	if (tot_timeout >= 60 * 1000 and APM >= 100)
		reward_meal = 1;
	PstC(13, 14, 33);
	if (reward_meal)
		printf("����ʱǰ�����ڲ���ȡ���");

	PstC(14, 14, 33);

	Pause();
	return 0;
}

int Writing() {
	{
		map_file = "Writing";
		ins_coe = 1.00;
		move_unit_time = 12;
	}

	remap = true;

	while (place == WRITING) {
		if (remap) {
			CommonreMap();
			Tips("д��¥���ã��տ����ܻ���Ų�����");

			remap = false;
		}

		if (!Move())//д��¥ 
			continue;

		switch (atlas[sx][sy]) {
		case 'O':
			//mciSS();
			Tips("");

			P("...", 1000, 0, false);

			Tips("�����ţ������˻�Ӧ��");

			MoveBack();
			break;

		case 'W':
			if (!between(hour, 0, 5))
				place = TYPIST;//������ 
			else {
				Tips("[�޲���ʱ ϵͳ���賿0:00��6:00�Զ�����ά��״̬]");
				MoveBack();
			}
			break;

		case 'R':
			if (work_score > 1) {
				Gain(work_score / 2);
				work_score -= (work_score / 2) * 2;//��Ҫ��д

				//Task 1-2
				if (task_rate[1] == 1) {
					SoundCover("Message");
					Delay(750);
					task_rate[1] = 2;
					TaskView(1, 2);
					remap = true;
				}
			}
			else
				Tips("\"ÿ2�����ܻ�Ϊ1Ԫ���ʡ�\"");

			MoveBack();
			break;

		case 'D':
			place = CITY;
			sx = 9, sy = 42;
			break;

		case 'B':
			if (!(hour >= 22 or hour <= 6)) {
				if (reward_meal) {
					if (task_rate[2] == 0)
						Tips("����һ�����ݳ���...");
					else
						Tips("���õ�������...");

					int eaten = Eat(3, 1);
					reward_meal = 0;

					if (eaten < 1)
						Tips("ͻȻ����ԣ����ĵ����ɡ�");
					else
						Tips("ζ��������������̫С����");

					//Task 2-1
					if (task_rate[2] == 0) {
						Delay(1500);
						TimeLapse(4 minutes, THINK);//dialog

						task_rate[2] = 1;
						TaskView(2, 1);
						remap = true;
					}
				}
				else
					Tips("\"���������߽���õ�λ�Ľ�����\"");
			}
			else
				Tips("̫���ˣ�Ա���Ƕ����ڡ�");
			MoveBack();

			break;
		default:
			break;
		}
	}
	return 0;
}

int ZooWest() {
	{
		map_file = "ZooWest";
		ins_coe = 1.20;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_WEST) {
		if (remap) {
			CommonreMap();
			Tips("����԰��������ƫƧ������");

			remap = false;
		}

		if (!Move())//����԰
			continue;

		switch (atlas[sx][sy]) {
		case 'w':
			place = ZOO_NORTH_WEST;
			sx = 17, sy = ty;
			break;

		case 'd':
			place = ZOO_MIDDLE;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooNorthWest() {
	{
		map_file = "ZooNorthWest";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_NORTH_WEST) {
		if (remap) {
			CommonreMap();
			Tips("����԰�������鶯�Ļ��н�����");

			remap = false;
		}

		if (!Move())//����԰
			continue;

		switch (atlas[sx][sy]) {
		case 's':
			place = ZOO_WEST;
			// RETURN
			sx = 2, sy = sy;
			//reMap = true;
			break;

		case 'd':
			place = ZOO_NORTH;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooMiddle() {
	{
		map_file = "ZooMiddle";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_MIDDLE) {
		if (remap) {
			CommonreMap();
			Tips("����԰���ĵش��������ϵĻ��۲�֪�����˻��Ƕ�����Ϊ��");

			remap = false;
		}

		if (!Move())//����԰
			continue;

		switch (atlas[sx][sy]) {
		case 'a':
			place = ZOO_WEST;
			sx = sx, sy = 54;
			break;

		case 'w':
			place = ZOO_NORTH;
			sx = 17, sy = sy;
			break;

		case 'd':
			place = ZOO_EAST;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooNorth() {
	{
		map_file = "ZooNorth";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_NORTH) {
		if (remap) {
			CommonreMap();
			Tips("����԰������ӯ��Ծ����");

			remap = false;
		}

		if (!Move())//����԰
			continue;

		switch (atlas[sx][sy]) {
		case 'a':
			place = ZOO_NORTH_WEST;
			// RETURN
			sx = 7, sy = 54;
			//reMap = true;
			break;

		case 's':
			place = ZOO_MIDDLE;
			sx = 2, sy = sy;
			break;

		case 'd':
			place = ZOO_NORTH_EAST;
			sx = sx, sy = 2;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooNorthEast() {
	{
		map_file = "ZooNorthEast";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_NORTH_EAST) {
		if (remap) {
			CommonreMap();
			Tips("����԰����������ĺ�С�");
			remap = false;
		}

		if (!Move())//����԰
			continue;

		switch (atlas[sx][sy]) {
		case 's':
			place = ZOO_EAST;
			// RETURN
			sx = 2, sy = ty;
			//reMap = true;
			break;

		case 'a':
			place = ZOO_NORTH;
			sx = sx, sy = 54;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooEast() {
	{
		map_file = "ZooEast";
		ins_coe = 1.85;
		move_unit_time = 25;
	}

	remap = true;

	while (place == ZOO_EAST) {
		if (remap) {
			CommonreMap();
			Tips("����԰��������ϸ�顣");

			remap = false;
		}

		if (!Move())//����԰ 
			continue;

		switch (atlas[sx][sy]) {
		case 'w':
			place = ZOO_NORTH_EAST;
			sx = 17, sy = sy;
			break;

		case 'a':
			place = ZOO_MIDDLE;
			sx = sx, sy = 54;
			break;

		case 'D':
			place = CITY;
			sx = 9, sy = 9;
			break;

		case 'O':
			place = ZOO_OFFICE;
			break;

		default:

			break;
		}
	}
	return 0;
}

int ZooOffice() {
	{
		ins_coe = 0.35;
		move_unit_time = 25;
	}

	border = false;
	Cls();
	puts("");

	TimeLapse(7, THINK);
	P("  \"��ã���ʲô�£�\"\n\n", 24, 500);

	if (0 <= task_rate[2] and task_rate[2] <= 1) {
		TimeLapse(5, 0);//���� 
		P("  ԰�������ֱ��Ͼ�Ȼ�а̺ۡ�\n\n", 24, 500);
		P("  Ҳ����������ץ���ˡ�\n\n", 24, 500);
	}

	//Task 2-2
	if (task_rate[2] == 1) {
		printf("  ���������Ի���\n");
		Pause();
		TimeLapse(4 minutes, THINK);

		task_rate[2] = 2;
		TaskView(2, 2);

		Gain(50);
	}
	else
		printf("  �����뿪...\n");

	Pause();

	MoveBack();
	place = ZOO_EAST;
	sx = 10, sy = 27;

	return 0;
}

int Bank() {
	{
		map_file = "Bank";
		ins_coe = 1.20;
		move_unit_time = 12;
	}

	remap = true;

	while (place == BANK) {
		if (remap) {
			CommonreMap();
			Tips("���������������Ǯ����ζ��");
			//else

			remap = false;
		}

		if (!Move())//���� 
			continue;


		switch (atlas[sx][sy]) {
		case 'L':
			Tips("ְԱ�����ŵ��ԣ���΢����һ��ɡ���");
			Sleep(1500);
			Tips("\"�������еĴ������δ���š�\"");

			MoveBack();
			break;

		case 'S':
			MoveBack();//�벻Ҫ���ͷ
			if (!between(hour, 8, 17)) {
				Tips("���н���8:00��16:00���Ŵ�ȡ�");
				break;
			}

			Tips("[ϵͳ���ڻ�ȡ������¼...]");
			Sleep(100);
			Tips(""); printf("���ϻ�����%dԪ����Ļ��ʾ[����������]��", money);

			if (!CommonInput(INTEGER, true, 9, true)) break;

			if (n there) {
				if (Pay(n)) {
					city_bank.Deposit(n);
					Tips("[�����ϣ���л���İ���]");
				}
				else
					Tips("[������û�취ƾ����Ǯ�ģ�����]");
			}
			else
				Tips("[��Ч����]");
			break;

		case 'R':
			MoveBack();
			if (!between(hour, 8, 17)) {
				Tips("���н���8:00��16:00���Ŵ�ȡ�");
				break;
			}

			Tips("[ϵͳ���ڻ�ȡ������¼...]");
			Sleep(100);
			Tips(""); printf("[���Ĵ��Ϊ%dԪ��������ȡ������]", city_bank.GetDepo());
			//if(){

			if (!CommonInput(INTEGER, true, 9, true)) break;

			if (n there) {
				if (city_bank.Draw(n)) {
					Gain(n);
					Tips("[��Ϊ��ȡ���ӭ�´�����]");
				}
				else
					Tips("[��������Υ����Ϊ]");
			}
			else
				Tips("[������ֻ����鿴һ�´��]");
			break;

		case 'D':
			place = CITY;
			sx = 4, sy = 15;
			break;

		default:

			break;
		}
	}
	return 0;
}

int Playground() {
	{
		map_file = "Playground";
		ins_coe = 1.35;
		move_unit_time = 22;
	}

	remap = true;

	while (place == PLAYGROUND) {
		if (remap) {
			CommonreMap();
			if (7 <= hour and hour <= 17)
				Tips("�㳡�������һ����Ӱ��");
			else
				if (18 <= hour and hour <= 21)
					Tips("�㳡�ǳ�ɫ�ƹ��µ���̨��");
				else
					Tips("�㳡�ܰ����������ܵõ������������Ļ��");

			remap = false;
		}

		if (!Move())//�㳡 
			continue;

		switch (atlas[sx][sy]) {
		case 'w':
			place = CITY;
			sx = 12, sy = 46 + sy / 6;
			break;
		default: break;
		}
	}
	return 0;
}

int City() {
	{
		ins_coe = 1.35;
		map_file = "City";
		move_unit_time = 65;
	}

	//Task 1-1
	if (task_rate[1] == 0) {
		SoundCover("Message");
		task_rate[1] = 1;
		TaskView(1, 1);//ǿ�ƽ���Task
		remap = true;
	}

	remap = true;

	while (place == CITY) {
		if (remap) {
			CommonreMap();
			if (day <= 1)
				Tips("��֣�İ��ȴ������ʶ��");
			else
				Tips("��Ϥ�Ĵ�֡�");

			remap = false;
		}

		if (!Move())//���� 
			continue;

		switch (atlas[sx][sy]) {
		case 'H'://Home
			place = HOME;
			sx = 14, sy = 5;
			break;

		case 'S'://
			if (hour >= 7 and hour <= 20)
				place = SUPERMATKET;
			else {
				Tips("[Ӫҵʱ��: 7:00��21:00 :) ]");
				MoveBack();
			}
			break;

		case 'O'://д��¥ 
			place = WRITING;
			sx = 14, sy = 5;
			break;

		case 'C'://School(); 
			place = SCHOOL;
			sx = 15, sy = 27;
			break;

		case 'T'://Hospital(); 
			place = HOSPITAL;
			sx = 4, sy = 21;
			break;

		case 'E'://WeaponShop(); 
			if (hour >= 9 and hour <= 17)
				place = WEAPONSHOP;
			else {
				Tips("���Ž�������͸�������ܿ���չ̨�ϵĶ�����");
				MoveBack();
			}
			break;

		case 'F'://�ھ� 
			place = NEIGHBOR;
			sx = 14, sy = 5;
			break;

		case 'B'://Bank();
			place = BANK;
			sx = 14, sy = 5;
			break;

		case 'Z'://Zoo();
			place = ZOO_EAST;
			sx = 6, sy = 51;
			break;

		case 's':
			place = PLAYGROUND;
			sx = 2, sy = 3 + (sy - 46) * 6;
			break;

		default:

			break;
		}
	}
	return 0;//��Ȼ�˳� 
}

int Gate() {//�ռ䴫���ţ�������ʵ��������ʵ���
	while (place != ESC) {
		switch (place) {
		case CITY: City(); break;

		case HOME: Home(); break;
		case BEDROOM: Bedroom(); break;

		case KITCHEN: Kitchen(); break;

		case SUPERMATKET: Supermarket(); break;

		case WRITING: Writing(); break;
		case TYPIST: Typist(); break;

		case SCHOOL: School(); break;
		case SCHOOL_1F: School1F(); break;
		case SCHOOL_2F: School2F(); break;
		case SCHOOL_3F: School3F(); break;
		case SCHOOL_HIDE: SchoolHide(); break;

		case HOSPITAL: Hospital(); break;
		case INTERNAL: Internal(); break;

		case WEAPONSHOP: WeaponShop(); break;

		case NEIGHBOR: Neighbor(); break;
		case NEIGHBOR_2F: Neighbor2F(); break;
		case NEIGHBOR_BEDROOM: NeighborBedroom(); break;

		case BANK: Bank(); break;

		case ZOO_EAST: ZooEast(); break;
		case ZOO_NORTH_EAST: ZooNorthEast(); break;
		case ZOO_NORTH: ZooNorth(); break;
		case ZOO_MIDDLE: ZooMiddle(); break;
		case ZOO_NORTH_WEST: ZooNorthWest(); break;
		case ZOO_WEST: ZooWest(); break;
		case ZOO_OFFICE: ZooOffice(); break;

		case PLAYGROUND: Playground(); break;

		default:
			place = ESC;
			break;
		}
	}
	return 0;
}
