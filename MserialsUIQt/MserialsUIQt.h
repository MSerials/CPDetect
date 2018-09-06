#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MserialsUIQt.h"

class MserialsUIQt : public QMainWindow
{
	Q_OBJECT

public:
	MserialsUIQt(QWidget *parent = Q_NULLPTR);
	void OnInitDiaog();
private:
	Ui::MserialsUIQtClass ui;
	void initUI();
	void initConnect();
	void initMenu();


private slots:
	void open();
	void setModel();
	void setFuntionFlow();
	void btn_clicked_getxml();

	void UpdateUI();
	void _Button_Start_Detect();
	void _Button_Param_Set();
	void _Button_Model_Mgr();
	void _Button_Detect_Census();
	void _Button_Def_Census();
	void _Button_Start_Record();
	void _Button_Counter_to_Zero();
	void _Button_Quit();
	void _Button_Refresh_Camera();
	void _Button_Snap();
	
	void closeEvent(QCloseEvent * ev);
	void OnClose();
	void _Timer_LCD();

private:
	QAction *openAction;
	QAction *setModelAction;
	QAction *setFunFlowAction;
	//界面布局
	QGridLayout *pGlobalLayout;
	QGridLayout	*pTableLayout;
	//相机显示
	QLabel	*pLabelCamera1;
	QLabel	*pLabelCamera2;
	QLabel	*pLabelCamera3;
	QLabel	*pLabelCamera4;
	QLabel	*pLabelCamera5;
	QLabel	*pLabelCamera6;


	QWidget *pWidgetCamera1;
	QWidget *pWidgetCamera2;
	QWidget *pWidgetCamera3;
	QWidget *pWidgetCamera4;
	QWidget *pWidgetCamera5;
	QWidget *pWidgetCamera6;
	//结果显示
	QLabel	*pLabelResult1;
	QLabel	*pLabelResult2;
	QLabel	*pLabelResult3;
	QLabel	*pLabelResult4;
	QLabel	*pLabelResult5;
	QLabel	*pLabelResult6;


	QWidget *pWidgetResult1;
	QWidget *pWidgetResult2;
	QWidget *pWidgetResult3;
	QWidget *pWidgetResult4;
	QWidget *pWidgetResult5;
	QWidget *pWidgetResult6;

	QLabel *text_yield;
	QLabel *text_ok;
	QLabel *text_ng;
	QLabel *text_qty;
	QLabel *text_tqty;
	QLabel *text_oper;
	QLabel *text_tNo;
	QLabel *text_box_counter;
	QLabel *text_current_spd;
	QLabel *text_batch;
	QLabel *text_model_name;
	QLabel *text_computer_no;

	std::tuple<int, QLabel*> tuple_Labels;

	//显示当前时间
	//QLCDNumber *lcd;// = new QLCDNumber();
	QLCDNumber *液晶时间显示 = nullptr;// = new QLCDNumber();

	QPushButton *Button_Start_Detect;
	QPushButton *Button_Param_Set;
	QPushButton *Button_Model_Mgr;
	QPushButton *Button_Detect_Census;
	QPushButton *Button_Def_Census;
	QPushButton *Button_Start_Record;
	QPushButton *Button_Counter_to_Zero;
	QPushButton *Button_Quit;
	QPushButton *Button_Refresh_Camera;
	QPushButton *Button_Snap;

	std::vector<QLabel*> m_vec_label;
	std::vector<QWidget*> m_vec_widget;

	//相机供应商数量
	int vendors;
	//历史记录
	//QWidget *QWigetForList;
	QLabel *label;
	QPushButton *btn;




void XmlParse();
signals:
void XmlData(QString); 




};
