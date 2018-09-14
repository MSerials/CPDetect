#pragma once





#ifndef ___INI______
#define ___INI______

//��ͼ��Ĳ�������
#define PARA_SET	(1)
//sys�ﱣ���prj
#define PARA_PRJ	(1<<1)
//ͼ���������
#define PARA_IMAGE	(1<<2)

#define PARA_IO		(1<<3)

#define PARA_ALL	(PARA_SET | PARA_PRJ | PARA_IMAGE |PARA_IO)   //ALL -1

#define STR_SET "PARA_SET"
#define STR_PRJ "PARA_PRJ"
#define STR_IMAGE "PARA_IMAGE"
#define STR_IO	"PARA_IO"

struct _Rect {
	double r1 = 0;
	double c1 = 0;
	double r2 = 0;
	double c2 = 0;
};

//���ýṹ��ķ�ʽ���Է�����в�����ֵ
struct _Param {
	_Param() {};
	QString Project_Name = "Prj";

	double back_circularity = 0.9;

	int b_bianxingjiance = 0;

	int threshold_bianxingjiance = 128;

	int b_silakoupingbi = 0;

	int b_dingaojiance = 0;

	int b_chuancijiance = 0;

	int sel_lvgaileixing = 0;

	int sel_lvgaiyanse = 0;

	int sel_tiqvfangshi = 0;

	int sel_pidaiyanse = 0;



	int Project_Index = 0;
	//��ֵ��ƿ�Ǳ������
	int threshold_back_cap = 30;
	//��ֵ��ƿ���������
	int threshold_front_cap = 30;




	int dibuhuiduzhi = 35;




	//�ڶ�����λ�Ĳ�����bug��Ӧ�÷ֳ����ĸ�����Ĳ�������ֻ����һ��
	double Mean_Var = 3;

	double Cap_Mouth_Threshold = 45;
	
	double Cap_Border = 22;
	//�ָ��ƿ����Ķ�ֵ������
	double S_Saturation_Var = 60;
	//�ָ��ѹ���Ķ�ֵ������
	double Cap_Yahua = 60;
	//ѹ����ƫ����
	double Cap_Yahua_Bias = 15;
	//�õ�ƿ�������ƫ����
	double Cap_Body_Lower_Bias = 40;
	//�õ�ƿ������ϲ��߽�ƫ����
	double Cap_Body_Upper_Bias = 5;
	//����������С���
	double Error_Area = 15;
	double Error_LowerBias = -120;
	double Error_UpperBias = -20;


	//��������λ�Ĳ���
	//ɫ�������Сֵ
	double cap_error_area_var = 20;
	//��ȡɫ��ƫ������ֵ
	double peak_lower = -55;
	//��ȡɫ��ƫ������ֵ
	double peak_upper = -18;


	//area_select_scale = 20;
	//��ֵ�˲�����
	double mean_filter_var = 5;
	//����Ǳ�Ե��ȥ���
	double erosion_di = 8;
	//NG��ֵ���ޣ�С���������ɫ�߲���NG
	double NG_area_lower = 50;
	//��ɫ��ǳ����Ľ��ݴ�С
	double color_sigma = 12;
	//NG��ɫ��Сֵ
	double color_lower = 100;



	//���ڲ����ٶȵ�������Ӧ�����
	double Sensor1_Sensor2_distance = 435;

	//��Ӧ��1�����1�ľ���mm
	double Sensor1_To_Cam1 = 110;
	//ms
	double Sensor1_To_Cam1_Delay = 75;

	double Sensor1_To_Blow1 = 271;

	double Sensor1_To_Blow1_Delay = 176;

	double Sensor2_To_Cam2 = 105;

	double Sensor2_To_Cam2_Delay = 73;

	double Sensor2_To_Blow2 = 320;

	double Sensor2_To_Blow2_Delay = 243;

	double Sensor3_To_Cam3 = 118;

	double Sensor3_To_Cam3_Delay = 120;

	double Sensor3_To_Blow3 = 313;

	double Sensor3_To_Blow3_Delay = 100;

	double Sensor3_To_Color1 = 480;

	double Sensor3_To_Color1_Delay = 150;

	double Sensor3_To_Color2 = 740;

	double Sensor3_To_Color2_Delay = 175;

	double Sensor3_To_Color3 = 930;

	double Sensor3_To_Color3_Delay = 210;


	double speed = 1.56; //500mm/ms

	_Rect front, side, back;

	//red blue
	double red_limt = 10;
	double blue_limit = 45;

	//
	double saturation_limit_lower = 100;
	//��ɫ����С����
	double saturation_limit_sigma = 30;
	//��ɫ�ĸ�����
	double saturation_limit_steop = 4;

	double intensty_lower = 10;

};


#endif


class Ini
{
public:
	Ini(char * class_name = "Preference")
		: settings(nullptr)
		, m_class_name(class_name)
	{
		str_set = STR_SET; str_set += "/";
		str_prj = STR_PRJ; str_prj += "/";
		str_img = STR_IMAGE; str_img += "/";
		str_io = STR_IO; str_io += "/";	
	}
	~Ini() { delete settings;}

	const char* Class_Name() { return m_class_name; }

	void SetFilePos(QString str) {
		if (nullptr != settings) 
			delete settings;
		settings = new QSettings(str, QSettings::IniFormat);
		ReadSettings(PARA_ALL);
	}

	void WriteSettings(int SEL = PARA_ALL)
	{
		qDebug() << "start writing";
		if (SEL & PARA_SET)
		{
			qDebug() << "start writing...";
			settings->beginGroup(STR_SET);
			//��ʾ�ļ�����
			settings->setValue("sign", 1);
			


			settings->endGroup();
		}


		if (SEL & PARA_PRJ)
		{
			settings->beginGroup(STR_PRJ);

			settings->setValue("MOTIONCARD",card_num);
			settings->setValue("PRJ_NAME", para.Project_Name);

			settings->endGroup();
		}


		if (SEL & PARA_IMAGE)
		{
			settings->beginGroup(STR_IMAGE);

			settings->setValue("THRSH_BAK_CAP", para.threshold_back_cap);
			settings->setValue("THRSH_FNT_CAP", para.threshold_front_cap);
			//settings->setValue("THRSH_BAK_CAP", para.threshold_back_cap);
			settings->setValue("FRONT_RECT_R1", para.front.r1);
			settings->setValue("FRONT_RECT_C1", para.front.c1);
			settings->setValue("FRONT_RECT_R2", para.front.r2);
			settings->setValue("FRONT_RECT_C2", para.front.c2);


			settings->endGroup();
		}


		if (SEL & PARA_IO)
		{
			settings->beginGroup(STR_IO);

			settings->setValue("S1S2_DIS", para.Sensor1_Sensor2_distance);


			settings->setValue("STC1", para.Sensor1_To_Cam1);
			settings->setValue("STCD1", para.Sensor1_To_Cam1_Delay);
			settings->setValue("STB1", para.Sensor1_To_Blow1);
			settings->setValue("STBD1", para.Sensor1_To_Blow1_Delay);
			settings->setValue("STC2", para.Sensor2_To_Cam2);
			settings->setValue("STCD2", para.Sensor2_To_Cam2_Delay);
			settings->setValue("STB2", para.Sensor2_To_Blow2);
			settings->setValue("STBD2", para.Sensor2_To_Blow2_Delay);
			settings->setValue("STC3", para.Sensor3_To_Cam3);
			settings->setValue("STCD3", para.Sensor3_To_Cam3_Delay);
			settings->setValue("STB3", para.Sensor3_To_Blow3);
			settings->setValue("STBD3", para.Sensor3_To_Blow3_Delay);
			settings->setValue("STCOLOR1", para.Sensor3_To_Color1);
			settings->setValue("STCOLORD1", para.Sensor3_To_Color1_Delay);
			settings->setValue("STCOLOR2", para.Sensor3_To_Color2);
			settings->setValue("STCOLORD2", para.Sensor3_To_Color2_Delay);
			settings->setValue("STCOLOR3", para.Sensor3_To_Color3);
			settings->setValue("STCOLORD3", para.Sensor3_To_Color3_Delay);

			settings->setValue("SPD", para.speed);

			settings->endGroup();
		}
	}

	void ReadSettings(int SEL = PARA_ALL)
	{
		if (SEL & PARA_SET)
		{
			//��ʾ�ļ�����
			int Sign = settings->value(str_set + "sign",0).toInt();
			if (1!=Sign) {
				Init(); 
				DLOG(LOG_INFO, "ini file not found");
				return; 
			}
		}


		if (SEL & PARA_PRJ)
		{
			card_num = settings->value(str_prj + "MOTIONCARD", 0).toInt();

			para.Project_Name = settings->value(str_prj + "PRJ_NAME", QString::fromLocal8Bit("Ĭ��")).toString();
			//Color_Circle.c = settings->value(str_prj + "COLORCIR_C", 100).toDouble();
			//Color_Circle.r = settings->value(str_prj + "COLORCIR_R", 100).toDouble();
			//Color_Circle.radius = settings->value(str_prj + "COLORCIR_RIDUS", 100).toDouble();


		}


		if (SEL & PARA_IMAGE)
		{
			para.threshold_back_cap = settings->value(str_img + "THRSH_BAK_CAP", 30).toInt(); 
			para.threshold_front_cap = settings->value(str_img + "THRSH_FNT_CAP", 30).toInt(); 

		}


		if (SEL & PARA_IO)
		{

			para.Sensor1_Sensor2_distance = settings->value(str_io + "S1S2_DIS", 440).toDouble();

			//��Ӧ��1�����1�ľ���mm
			para.Sensor1_To_Cam1 = settings->value(str_io + "STC1", 440).toDouble();
			//ms
			para.Sensor1_To_Cam1_Delay = settings->value(str_io + "STCD1", 440).toDouble();

			para.Sensor1_To_Blow1 = settings->value(str_io + "STB1", 440).toDouble();

			para.Sensor1_To_Blow1_Delay = settings->value(str_io + "STBD1", 440).toDouble();

			para.Sensor2_To_Cam2 = settings->value(str_io + "STC2", 440).toDouble();

			para.Sensor2_To_Cam2_Delay = settings->value(str_io + "STCD2", 440).toDouble();

			para.Sensor2_To_Blow2 = settings->value(str_io + "STB2", 440).toDouble();;

			para.Sensor2_To_Blow2_Delay = settings->value(str_io + "STBD2", 440).toDouble();

			para.Sensor3_To_Cam3 = settings->value(str_io + "STC3", 440).toDouble();

			para.Sensor3_To_Cam3_Delay = settings->value(str_io + "STCD3", 440).toDouble();;

			para.Sensor3_To_Blow3 = settings->value(str_io + "STB3", 440).toDouble();

			para.Sensor3_To_Blow3_Delay = settings->value(str_io + "STBD3", 440).toDouble();

			para.Sensor3_To_Color1 = settings->value(str_io + "STCOLOR1", 440).toDouble();

			para.Sensor3_To_Color1_Delay = settings->value(str_io + "STCOLORD1", 440).toDouble();

			para.Sensor3_To_Color2 = settings->value(str_io + "STCOLOR2", 440).toDouble();

			para.Sensor3_To_Color2_Delay = settings->value(str_io + "STCOLORD2", 440).toDouble();

			para.Sensor3_To_Color3 = settings->value(str_io + "STCOLOR3", 440).toDouble();

			para.Sensor3_To_Color3_Delay = settings->value(str_io + "STCOLORD3", 440).toDouble();



			para.speed = settings->value(str_io + "SPD", 500).toDouble();
		}

		

	}

private:
	void Init() {
		InitData();
		int SEL = PARA_ALL;
		if (0 == strcmp("sys", m_class_name))
		{
			SEL = PARA_PRJ | PARA_IO | PARA_SET;
		}
		WriteSettings(SEL);
	}
	//�޷���ȡ�����ļ���ʱ���ʼ������
	void InitData() {
		return;
		Project_Name = QString::fromLocal8Bit("");
		Project_Index = 0;
		Color_Circle.r = 100;
		Color_Circle.c = 100;
		Color_Circle.radius = 100;
	}

	char* m_class_name;
	QSettings *settings; ///<to store something
	QString str_set;
	QString str_prj;
	QString str_img;
	QString str_io;

public:
	struct _Rect
	{
		double x;
		double y;
		double w;
		double h;
	};

	struct h_Rect
	{
		double c1;
		double r1;
		double c2;
		double r2;
	};


	struct h_Circle
	{
		double c;
		double r;
		double radius;
	};

	//SET
	


	//PRJ
	QString Project_Name;
	int Project_Index;

	//IMAGE
	h_Circle Color_Circle;//�����ɫ��Բ��ROI

	_Param para,para_bak;

	int card_num = 0;


























};


















class Preference
{
public:
	Preference() { 
		sys = new Ini("sys");
		prj = new Ini("prj");
	};
	~Preference() { delete sys; delete prj; }
	static Preference *GetIns() { static Preference ini; return &ini; }

	//ϵͳ����
	Ini *sys;
	//��Ŀ����
	Ini *prj;
};