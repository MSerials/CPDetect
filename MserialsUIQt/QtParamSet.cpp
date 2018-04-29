#include "stdafx.h"
#include "QtParamSet.h"
#include "Machine.h"
#include "Ini.h"
#include <vector>

QtParamSet::QtParamSet(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ResetEvent(thread_handle);
	CreateThread(NULL, 0, Calculate, this, 0, NULL);
	QGridLayout *pGridLayout = new QGridLayout(this);
	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��1�����1�ľ���(mm)")), 0, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STC1 = new QLineEdit(QString::number(STC1,10,0)), 0, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), 0, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STCD1 = new QLineEdit("0"), 0, 6, 1, 2);
	pLineEdit_STCD1->setEnabled(false);
	pLineEdit_STCD1->setText(QString::number(CAM1DELAY, 10, 0));

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��1������1�ľ���(mm)")), 1, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STB1 = new QLineEdit(QString::number(STB1, 10, 0)), 1, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), 1, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STBD1 = new QLineEdit("0"), 1, 6, 1, 2);
	pLineEdit_STBD1->setEnabled(false);
	pLineEdit_STBD1->setText(QString::number(POS1BLOW_DELAY, 10, 0));

	//
	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��2�����2�ľ���(mm)")), 3, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STC2 = new QLineEdit(QString::number(STC2, 10, 0)), 3, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), 3, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STCD2 = new QLineEdit("0"), 3, 6, 1, 2);
	pLineEdit_STCD2->setEnabled(false);
	pLineEdit_STCD2->setText(QString::number(CAM2DELAY, 10, 0));

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��2������2�ľ���(mm)")), 4, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STB2 = new QLineEdit(QString::number(STB2, 10, 0)), 4, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), 4, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STBD2 = new QLineEdit("0"), 4, 6, 1, 2);
	pLineEdit_STBD2->setEnabled(false);
	pLineEdit_STBD2->setText(QString::number(POS2BLOW_DELAY, 10, 0));


	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��3�����3�ľ���(mm)")), 5, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STC3 = new QLineEdit(QString::number(STC3, 10, 0)), 5, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), 5, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STCD3 = new QLineEdit("0"), 5, 6, 1, 2);
	pLineEdit_STCD3->setEnabled(false);
	pLineEdit_STCD3->setText(QString::number(CAM3DELAY, 10, 0));

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��3������3�ľ���(mm)")), 6, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STB3 = new QLineEdit(QString::number(STB3, 10, 0)), 6, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), 6, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STBD3 = new QLineEdit("0"), 6, 6, 1, 2);
	pLineEdit_STBD3->setEnabled(false);
	pLineEdit_STBD3->setText(QString::number(POS3BLOW_DELAY, 10, 0));

	int rpos = 7;
	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��3��ɫ��1�ľ���(mm)")), rpos, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STCOLOR1 = new QLineEdit(QString::number(STCOLOR1, 10, 0)), rpos, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), rpos, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STCOLORD1 = new QLineEdit("0"), rpos, 6, 1, 2);
	pLineEdit_STCOLORD1->setEnabled(false);
	pLineEdit_STCOLORD1->setText(QString::number(POS3BLOW_COLOR1_DELAY, 10, 0));


	rpos = 8;
	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��3��ɫ��2�ľ���(mm)")), rpos, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STCOLOR2 = new QLineEdit(QString::number(STCOLOR2, 10, 0)), rpos, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), rpos, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STCOLORD2 = new QLineEdit("0"), rpos, 6, 1, 2);
	pLineEdit_STCOLORD2->setEnabled(false);
	pLineEdit_STCOLORD2->setText(QString::number(POS3BLOW_COLOR2_DELAY, 10, 0));


	rpos = 9;
	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��Ӧ��3��ɫ��3�ľ���(mm)")), rpos, 0, 1, 3);
	pGridLayout->addWidget(pLineEdit_STCOLOR3 = new QLineEdit(QString::number(STCOLOR3, 10, 0)), rpos, 3, 1, 2);

	pGridLayout->addWidget(new QLabel(QString::fromLocal8Bit("��ʱms")), rpos, 5, 1, 1);
	pGridLayout->addWidget(pLineEdit_STCOLORD3 = new QLineEdit("0"), rpos, 6, 1, 2);
	pLineEdit_STCOLORD3->setEnabled(false);
	pLineEdit_STCOLORD3->setText(QString::number(POS3BLOW_COLOR3_DELAY, 10, 0));

	rpos = 10;
	//�����ٶȰ�ť
	QPushButton* pButton_measure_speed = new QPushButton(QString::fromLocal8Bit("�����ٶ�"));
	connect(pButton_measure_speed, SIGNAL(clicked()), this, SLOT(Button_Measure()));
	pGridLayout->addWidget(pButton_measure_speed, rpos, 0, 1, 8);

	rpos = 11;
	pGridLayout->addWidget(pLineEdit_SPD = new QLineEdit(), rpos, 0, 1, 8);
}

QtParamSet::~QtParamSet()
{
}

void QtParamSet::Button_Measure() {
	ticks.clear();
	UpdataInfomation(QString::fromLocal8Bit("�Ե�..."));
	TimeOutTick = GetTickCount();
	SetEvent(thread_handle);
	
}

void QtParamSet::UpdataInfomation(QString content,int sel) {
	pLineEdit_SPD->setText(content);
	if (1 == sel) return;
	if (speed == 0) return;
	//�������Ӧ��1�����1����ʱʱ��
	double _stc1 = pLineEdit_STC1->text().toDouble();
	double _stc1d = _stc1 / speed;
	pLineEdit_STCD1->setText(QString::number(_stc1d,10,0));

	double _stb1 = pLineEdit_STB1->text().toDouble();
	double _stb1d = _stb1 / speed;
	pLineEdit_STBD1->setText(QString::number(_stb1d, 10, 0));




	double _stc2 = pLineEdit_STC2->text().toDouble();
	double _stc2d = _stc2 / speed;
	pLineEdit_STCD2->setText(QString::number(_stc2d, 10, 0));

	double _stb2 = pLineEdit_STB2->text().toDouble();
	double _stb2d = _stb2 / speed;
	pLineEdit_STBD2->setText(QString::number(_stb2d, 10, 0));



	//��λ3����ʱ����

	double _stc3 = pLineEdit_STC3->text().toDouble();
	double _stc3d = _stc3 / speed;
	pLineEdit_STCD3->setText(QString::number(_stc3d, 10, 0));



	double _stb3 = pLineEdit_STB3->text().toDouble();
	double _stb3d = _stb3 / speed;
	pLineEdit_STBD3->setText(QString::number(_stb3d, 10, 0));

	double _stcolor1 = pLineEdit_STCOLOR1->text().toDouble();
	double _stcolor1d = _stcolor1 / speed;
	pLineEdit_STCOLORD1->setText(QString::number(_stcolor1d, 10, 0));

	double _stcolor2 = pLineEdit_STCOLOR2->text().toDouble();
	double _stcolor2d = _stcolor2 / speed;
	pLineEdit_STCOLORD2->setText(QString::number(_stcolor2d, 10, 0));

	double _stcolor3 = pLineEdit_STCOLOR3->text().toDouble();
	double _stcolor3d = _stcolor3 / speed;
	pLineEdit_STCOLORD3->setText(QString::number(_stcolor3d, 10, 0));
}


void QtParamSet::closeEvent(QCloseEvent *ev) {
	int res = QMessageBox::question(this, "Quit", QString::fromLocal8Bit("���������"),
		QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);


	endThread = true;
	Machine::GetIns()->push_button(Machine::START);
	if (QMessageBox::Ok == res)
	{

		//���������  һ����ʱ
		STC1 = pLineEdit_STC1->text().toDouble();
		CAM1DELAY = pLineEdit_STCD1->text().toDouble();
		STB1 = pLineEdit_STB1->text().toDouble();
		POS1BLOW_DELAY = pLineEdit_STBD1->text().toDouble();

		//��������� ������ʱ
		STC2 = pLineEdit_STC2->text().toDouble();
		CAM2DELAY = pLineEdit_STCD2->text().toDouble();
		STB2 = pLineEdit_STB2->text().toDouble();
		POS2BLOW_DELAY = pLineEdit_STBD2->text().toDouble();

		//��������� ������ʱ
		STC3 = pLineEdit_STC3->text().toDouble();
		CAM3DELAY = pLineEdit_STCD3->text().toDouble();
		STB3 = pLineEdit_STB3->text().toDouble();
		POS3BLOW_DELAY = pLineEdit_STBD3->text().toDouble();

		STCOLOR1				= pLineEdit_STCOLOR1->text().toDouble();
		POS3BLOW_COLOR1_DELAY	= pLineEdit_STCOLORD1->text().toDouble();
		STCOLOR2				= pLineEdit_STCOLOR2->text().toDouble();
		POS3BLOW_COLOR2_DELAY	= pLineEdit_STCOLORD2->text().toDouble();
		STCOLOR3				= pLineEdit_STCOLOR3->text().toDouble();
		POS3BLOW_COLOR3_DELAY	= pLineEdit_STCOLORD3->text().toDouble();
		
		SAVE_PARA_IO;
		
		return;
	}


	
	ev->accept();
}

DWORD QtParamSet::Calculate(LPVOID lp)
{
	QtParamSet * pDlg = (QtParamSet*)lp;

	if (nullptr == Machine::GetIns()->m_mc) {
		return 0;
	}

	DWORD new_state = Machine::GetIns()->m_mc->Read_Input(0);
	DWORD old_state = new_state;

	for (;;)
	{
		::WaitForSingleObject(pDlg->thread_handle,INFINITE);
		if (pDlg->endThread) return 0;
		new_state = Machine::GetIns()->m_mc->Read_Input(0);

		int NCT1 = Camera_Trigger1 & new_state;
		int OCT1 = Camera_Trigger1 & old_state;

		int NCT2 = Camera_Trigger2 & new_state;
		int OCT2 = Camera_Trigger2 & old_state;


		if (NCT1 && NCT1 != OCT1) {
			pDlg->ticks.push_back(GetTickCount());
		}

		if (NCT2 && NCT2 != OCT2) {
			if (pDlg->ticks.size() > 1)
			{
				//std::cout << "����Ŷ��ƿ����Ƥ����" << std::endl;
				pDlg->UpdataInfomation(QString::fromLocal8Bit("����Ŷ��ƿ����Ƥ����"), 1);
				ResetEvent(pDlg->thread_handle);
				pDlg->ticks.clear();
			}
			else if (1 == pDlg->ticks.size())
			{
				double time_gap = static_cast<double>(GetTickCount() - pDlg->ticks.at(0));
				pDlg->speed = MEASURE_DIS / time_gap;
				std::cout << "Ƥ���ٶȣ�" << pDlg->speed << " mm/ms" << std::endl;
				pDlg->UpdataInfomation(QString::fromLocal8Bit("Ƥ���ٶ�:") + QString::number(pDlg->speed,10,4)+ QString::fromLocal8Bit(" ����/���루m/s��"));
				ResetEvent(pDlg->thread_handle);
				pDlg->ticks.clear();
			}

		}
		if ((GetTickCount() - pDlg->TimeOutTick) > 20000)
		{
			pDlg->UpdataInfomation(QString::fromLocal8Bit("��ʱ��û�м�⵽����"),1);
			ResetEvent(pDlg->thread_handle);
			pDlg->ticks.clear();
		}
		old_state = new_state;
	}

	return 0;
}
