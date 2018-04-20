#pragma once

#include <QDialog>
#include <QLineEdit>
#include "ui_QtParamSet.h"

class QtParamSet : public QDialog
{
	Q_OBJECT

public:
	QtParamSet(QWidget *parent = Q_NULLPTR);
	~QtParamSet();
public:
	bool endThread = false;

	QLineEdit *pLineEdit_SPD = nullptr;

	//STC is short from sensor1_to_Cam1
	QLineEdit *pLineEdit_STC1 = nullptr;
	//STCD is short from sensor1_to_Cam1_Delay
	QLineEdit *pLineEdit_STCD1 = nullptr;
	//STB Sensor1_To_Blow
	QLineEdit *pLineEdit_STB1 = nullptr;
	QLineEdit *pLineEdit_STBD1 = nullptr;

	QLineEdit *pLineEdit_STC2 = nullptr;
	QLineEdit *pLineEdit_STCD2 = nullptr;
	QLineEdit *pLineEdit_STB2 = nullptr;
	QLineEdit *pLineEdit_STBD2 = nullptr;

	QLineEdit *pLineEdit_STC3 = nullptr;
	QLineEdit *pLineEdit_STCD3 = nullptr;
	QLineEdit *pLineEdit_STB3 = nullptr;
	QLineEdit *pLineEdit_STBD3 = nullptr;
	QLineEdit *pLineEdit_STCOLOR1 = nullptr;
	QLineEdit *pLineEdit_STCOLORD1 = nullptr;
	QLineEdit *pLineEdit_STCOLOR2 = nullptr;
	QLineEdit *pLineEdit_STCOLORD2 = nullptr;
	QLineEdit *pLineEdit_STCOLOR3 = nullptr;
	QLineEdit *pLineEdit_STCOLORD3 = nullptr;

	void closeEvent(QCloseEvent * ev);

	double speed = 99999;
	HANDLE thread_handle = CreateEvent(NULL, TRUE, FALSE, NULL);
	static DWORD WINAPI Calculate(LPVOID lp);
	std::vector<DWORD> ticks;
	DWORD TimeOutTick = 0;
	

private:
	Ui::QtParamSet ui;

public slots:
	void Button_Measure();
	//if sel = 1 then not caculate the delay
	void UpdataInfomation(QString content ,int sel = 0);
};
