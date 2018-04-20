#include "stdafx.h"
#include "MserialsUIQt.h"
#include "QtParamSet.h"
#include "../../QtCommon/common.h"
#include "XmlParse.h"
#include <functional>
#include "IR.h"

//#include "QtFunctionListView.h"
//#include "FunEditDlg.h"
#include "common.h"
#include "QtModelSet.h"
#include "Machine.h"
#include "MSerialsCam.h"
// #include "../MserialsQtList/HistoryListWidget.h"
//������Ĺ��캯��
MserialsUIQt::MserialsUIQt(QWidget *parent)
	: QMainWindow(parent)
{
	vendors = 0;
	ui.setupUi(this);
	Tools tool;
	int w = 0, h = 0, counter = 0;
	tool.GetScreenInfo(w, h, counter);
	if (counter != 0) resize(w, h-100);
	initMenu();
	initUI();
	initConnect();
	QString path = QDir::currentPath();
	QByteArray ba = path.toLatin1();
	DEBUGPRINT;
	DLOG(LOG_INFO, ba.data());
}
//��ʼ������
void MserialsUIQt::initUI()
{
	//����Ϊ��ɫ
	//ȫ��layout����
	static QWidget *CenterWidget = new QWidget(this);
	CenterWidget->setStyleSheet("QWidget{background:rgba(28,28,32,255)}");
	pGlobalLayout = new QGridLayout(CenterWidget);
	this->setCentralWidget(CenterWidget);
	//�����ʾ
	pWidgetCamera1 = new QWidget(this);
	//pWidgetCamera1->setAttribute(Qt::AlignCenter);
	pWidgetCamera2 = new QWidget(this);
	pWidgetCamera3 = new QWidget(this);
	pWidgetCamera4 = new QWidget(this);
	pWidgetCamera5 = new QWidget(this);
	pWidgetCamera6 = new QWidget(this);

	pWidgetResult1 = new QWidget(this);
	pWidgetResult2 = new QWidget(this);
	pWidgetResult3 = new QWidget(this);
	pWidgetResult4 = new QWidget(this);
	pWidgetResult5 = new QWidget(this);
	pWidgetResult6 = new QWidget(this);


	pLabelCamera1 = new QLabel(QString::fromLocal8Bit("��·1"), pWidgetCamera1);
	pLabelCamera1->setAlignment(Qt::AlignCenter);

	pLabelCamera2 = new QLabel(QString::fromLocal8Bit("��·2"), pWidgetCamera2);
	pLabelCamera2->setAlignment(Qt::AlignCenter);

	pLabelCamera3 = new QLabel(QString::fromLocal8Bit("��·3"), pWidgetCamera3);
	pLabelCamera3->setAlignment(Qt::AlignCenter);

	pLabelCamera4 = new QLabel(QString::fromLocal8Bit("��·4"), pWidgetCamera4);
	pLabelCamera4->setAlignment(Qt::AlignCenter);

	pLabelCamera5 = new QLabel(QString::fromLocal8Bit("��·5"), pWidgetCamera5);
	pLabelCamera5->setAlignment(Qt::AlignCenter);

	pLabelCamera6 = new QLabel(QString::fromLocal8Bit("��·6"), pWidgetCamera6);
	pLabelCamera6->setAlignment(Qt::AlignCenter);
	//�����ʾ
	pLabelResult1 = new QLabel(QString::fromLocal8Bit("���1"), pWidgetResult1);
	pLabelResult1->setAlignment(Qt::AlignCenter);

	pLabelResult2 = new QLabel(QString::fromLocal8Bit("���2"), pWidgetResult2);
	pLabelResult2->setAlignment(Qt::AlignCenter);

	pLabelResult3 = new QLabel(QString::fromLocal8Bit("���3"), pWidgetResult3);
	pLabelResult3->setAlignment(Qt::AlignCenter);

	pLabelResult4 = new QLabel(QString::fromLocal8Bit("���4"), pWidgetResult4);
	pLabelResult4->setAlignment(Qt::AlignCenter);

	pLabelResult5 = new QLabel(QString::fromLocal8Bit("���5"), pWidgetResult5);
	pLabelResult5->setAlignment(Qt::AlignCenter);

	pLabelResult6 = new QLabel(QString::fromLocal8Bit("���6"), pWidgetResult6);
	pLabelResult6->setAlignment(Qt::AlignCenter);

	pGlobalLayout->addWidget(pWidgetCamera1, 0, 0, 6, 8);
	pGlobalLayout->addWidget(pWidgetCamera2, 0, 8, 3, 4);
	pGlobalLayout->addWidget(pWidgetCamera3, 0, 12, 3, 4);
	pGlobalLayout->addWidget(pWidgetCamera4, 3, 8, 3, 4);
	pGlobalLayout->addWidget(pWidgetCamera5, 3, 12, 3, 4);
	pGlobalLayout->addWidget(pWidgetCamera6, 0, 16, 6, 8);

	pGlobalLayout->addWidget(pWidgetResult1, 6, 0, 6, 8);
	pGlobalLayout->addWidget(pWidgetResult2, 6, 8, 3, 4);
	pGlobalLayout->addWidget(pWidgetResult3, 6, 12, 3, 4);
	pGlobalLayout->addWidget(pWidgetResult4, 9, 8, 3, 4);
	pGlobalLayout->addWidget(pWidgetResult5, 9, 12, 3, 4);
	pGlobalLayout->addWidget(pWidgetResult6, 6, 16, 6, 8);


	m_vec_label.push_back(pLabelCamera1);
	m_vec_label.push_back(pLabelCamera2);
	m_vec_label.push_back(pLabelCamera3);
	m_vec_label.push_back(pLabelCamera4);
	m_vec_label.push_back(pLabelCamera5);
	m_vec_label.push_back(pLabelCamera6);

	m_vec_label.push_back(pLabelResult1);
	m_vec_label.push_back(pLabelResult2);
	m_vec_label.push_back(pLabelResult3);
	m_vec_label.push_back(pLabelResult4);
	m_vec_label.push_back(pLabelResult5);
	m_vec_label.push_back(pLabelResult6);

	m_vec_widget.push_back(pWidgetCamera1);
	m_vec_widget.push_back(pWidgetCamera2);
	m_vec_widget.push_back(pWidgetCamera3);
	m_vec_widget.push_back(pWidgetCamera4);
	m_vec_widget.push_back(pWidgetCamera5);
	m_vec_widget.push_back(pWidgetCamera6);

	m_vec_widget.push_back(pWidgetResult1);
	m_vec_widget.push_back(pWidgetResult2);
	m_vec_widget.push_back(pWidgetResult3);
	m_vec_widget.push_back(pWidgetResult4);
	m_vec_widget.push_back(pWidgetResult5);
	m_vec_widget.push_back(pWidgetResult6);




#ifndef pM 
#define pM	Machine::GetIns()
#endif
	QLabel* labels[MAX_WINDOW_NUM];
	labels[0] = pLabelCamera1;
	labels[1] = pLabelCamera2;
	labels[2] = pLabelCamera3;
	labels[3] = pLabelCamera4;
	labels[4] = pLabelCamera5;
	labels[5] = pLabelCamera6;
	labels[6] = pLabelResult1;
	labels[7] = pLabelResult2;
	labels[8] = pLabelResult3;
	labels[9] = pLabelResult4;
	labels[10] = pLabelResult5;
	labels[11] = pLabelResult6;
//	pM->_open_window(labels);



	

	pM->_open_window(pLabelCamera1, pM->disp_hd);
	pM->_open_window(pLabelCamera2, pM->disp_hd1);
	pM->_open_window(pLabelCamera3, pM->disp_hd2);
	pM->_open_window(pLabelCamera4, pM->disp_hd3);
	pM->_open_window(pLabelCamera5, pM->disp_hd4);
	pM->_open_window(pLabelCamera6, pM->disp_hd5);

	pM->_open_window(pLabelResult1, pM->disp_hd6);
	pM->_open_window(pLabelResult2, pM->disp_hd7);
	pM->_open_window(pLabelResult3, pM->disp_hd8);
	pM->_open_window(pLabelResult4, pM->disp_hd9);
	pM->_open_window(pLabelResult5, pM->disp_hd10);
	pM->_open_window(pLabelResult6, pM->disp_hd11);
	
#undef pM

	static QWidget *Widget = new QWidget(this);
	//static QScrollArea *scrollArea = new QScrollArea(this);
	Widget->setBackgroundRole(QPalette::Shadow);
	Widget->setForegroundRole(QPalette::Shadow);
	//scrollArea->setWidget(Widget);
	//scrollArea->setAlignment(Qt::AlignCenter);
	pGlobalLayout->addWidget(Widget, 12, 0, 6, 24);

	//��ӵ��·��Ŀ������
	pTableLayout = new QGridLayout(Widget);

	static QWidget *Widget_Info = new QWidget(this);
	Widget_Info->setBackgroundRole(QPalette::Shadow);
	Widget_Info->setForegroundRole(QPalette::Shadow);
	static QWidget *Widget_Ctrl = new QWidget(this);
	pTableLayout->addWidget(Widget_Info,0,0,6,12);
	pTableLayout->addWidget(Widget_Ctrl, 0,12, 6, 12);
	
	static QGridLayout *GridLayout_Info = new QGridLayout(Widget_Info);
	static QGridLayout *GridLayout_Ctrl = new QGridLayout(Widget_Ctrl);

	
	QLabel *_text_yield = new QLabel(QString::fromLocal8Bit("�ϸ���"));
	_text_yield->setAlignment(Qt::AlignCenter);
	_text_yield->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_yield,0,0,1,2);

	QLabel *_text_ok = new QLabel(QString::fromLocal8Bit("�ϸ���"));
	_text_ok->setAlignment(Qt::AlignCenter);
	_text_ok->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_ok, 1, 0, 1, 2);

	QLabel *_text_ng = new QLabel(QString::fromLocal8Bit("���ϸ���"));
	_text_ng->setAlignment(Qt::AlignCenter);
	_text_ng->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_ng, 2, 0, 1, 2);

	QLabel *_text_qty = new QLabel(QString::fromLocal8Bit("�����β���"));
	_text_qty->setAlignment(Qt::AlignCenter);
	_text_qty->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_qty, 3, 0, 1, 2);

	QLabel *_text_tqty = new QLabel(QString::fromLocal8Bit("�ܲ���"));
	_text_tqty->setAlignment(Qt::AlignCenter);
	_text_tqty->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_tqty, 4, 0, 1, 2);

	QLabel *_text_oper = new QLabel(QString::fromLocal8Bit("����Ա"));
	_text_oper->setAlignment(Qt::AlignCenter);
	_text_oper->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_oper, 5, 0, 1, 2);


	QLabel *_text_tNo = new QLabel(QString::fromLocal8Bit("��������"));
	_text_tNo->setAlignment(Qt::AlignCenter);
	_text_tNo->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_tNo, 0, 5, 1, 2);


	QLabel *_text_box_counter = new QLabel(QString::fromLocal8Bit("�������"));
	_text_box_counter->setAlignment(Qt::AlignCenter);
	_text_box_counter->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_box_counter, 1, 5, 1, 2);


	QLabel *_text_current_spd = new QLabel(QString::fromLocal8Bit("��ǰ�ٶ�"));
	_text_current_spd->setAlignment(Qt::AlignCenter);
	_text_current_spd->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_current_spd, 2, 5, 1, 2);

	QLabel *_text_batch = new QLabel(QString::fromLocal8Bit("��Ʒ����"));
	_text_batch->setAlignment(Qt::AlignCenter);
	_text_batch->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_batch, 3, 5, 1, 2);

	QLabel *_text_model_name = new QLabel(QString::fromLocal8Bit("ģ������"));
	_text_model_name->setAlignment(Qt::AlignCenter);
	_text_model_name->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_model_name, 4, 5, 1, 2);

	QLabel *_text_computer_no = new QLabel(QString::fromLocal8Bit("������"));
	_text_computer_no->setAlignment(Qt::AlignCenter);
	_text_computer_no->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(_text_computer_no, 5, 5, 1, 2);

	text_yield = new QLabel(QString::fromLocal8Bit("0"));
	text_yield->setAlignment(Qt::AlignCenter);
	text_yield->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_yield, 0, 2, 1, 3);

	text_ok = new QLabel(QString::fromLocal8Bit("0"));
	text_ok->setAlignment(Qt::AlignCenter);
	text_ok->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_ok, 1, 2, 1, 3);

	text_ng = new QLabel(QString::fromLocal8Bit("0"));
	text_ng->setAlignment(Qt::AlignCenter);
	text_ng->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_ng, 2, 2, 1, 3);

	text_qty = new QLabel(QString::fromLocal8Bit("0"));
	text_qty->setAlignment(Qt::AlignCenter);
	text_qty->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_qty, 3, 2, 1, 3);

	text_tqty = new QLabel(QString::fromLocal8Bit("0"));
	text_tqty->setAlignment(Qt::AlignCenter);
	text_tqty->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_tqty, 4, 2, 1, 3);

	text_oper = new QLabel(QString::fromLocal8Bit("0"));
	text_oper->setAlignment(Qt::AlignCenter);
	text_oper->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_oper, 5, 2, 1, 3);

	text_tNo = new QLabel(QString::fromLocal8Bit("0"));
	text_tNo->setAlignment(Qt::AlignCenter);
	text_tNo->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_tNo, 0, 7, 1, 3);

	text_box_counter = new QLabel(QString::fromLocal8Bit("0"));
	text_box_counter->setAlignment(Qt::AlignCenter);
	text_box_counter->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_box_counter, 1, 7, 1, 3);

	text_current_spd = new QLabel(QString::fromLocal8Bit("0"));
	text_current_spd->setAlignment(Qt::AlignCenter);
	text_current_spd->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_current_spd, 2, 7, 1, 3);

	text_batch = new QLabel(QString::fromLocal8Bit("0"));
	text_batch->setAlignment(Qt::AlignCenter);
	text_batch->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_batch, 3, 7, 1, 3);

	text_model_name = new QLabel(QString::fromLocal8Bit("0"));
	text_model_name->setAlignment(Qt::AlignCenter);
	text_model_name->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_model_name, 4, 7, 1, 3);

	text_computer_no = new QLabel(QString::fromLocal8Bit("0"));
	text_computer_no->setAlignment(Qt::AlignCenter);
	text_computer_no->setStyleSheet("QLabel{font-size:12px;padding:3px;background:rgba(12,12,18,220)}");
	GridLayout_Info->addWidget(text_computer_no, 5, 7, 1, 3);



	Button_Start_Detect = new QPushButton(QString::fromLocal8Bit("��ʼ���"));
	Button_Start_Detect->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Start_Detect,0,0,1,2);

	Button_Param_Set = new QPushButton(QString::fromLocal8Bit("��������"));
	Button_Param_Set->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Param_Set, 0, 2, 1, 2);

	Button_Model_Mgr = new QPushButton(QString::fromLocal8Bit("ģ�����"));
	Button_Model_Mgr->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Model_Mgr, 0, 4, 1, 2);

	Button_Detect_Census = new QPushButton(QString::fromLocal8Bit("���ͳ��"));
	Button_Detect_Census->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Detect_Census, 0, 6, 1, 2);

	Button_Def_Census = new QPushButton(QString::fromLocal8Bit("ȱ��ͳ��"));
	Button_Def_Census->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Def_Census, 1, 0, 1, 2);

	Button_Start_Record = new QPushButton(QString::fromLocal8Bit("��ʼ��¼"));
	Button_Start_Record->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Start_Record, 1, 2, 1, 2);

	Button_Counter_to_Zero = new QPushButton(QString::fromLocal8Bit("��������"));
	Button_Counter_to_Zero->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Counter_to_Zero, 1, 4, 1, 2);

	Button_Quit = new QPushButton(QString::fromLocal8Bit("�˳�"));
	Button_Quit->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Quit, 1, 6, 1, 2);

	Button_Refresh_Camera = new QPushButton(QString::fromLocal8Bit("ˢ�����"));
	Button_Refresh_Camera->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Refresh_Camera, 0, 8, 1, 2);
	
	Button_Snap = new QPushButton(QString::fromLocal8Bit("��ȡ���ͼ��"));
	Button_Snap->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
	GridLayout_Ctrl->addWidget(Button_Snap, 1, 8, 1, 2);

	//��Ӽ�¼list
	
	static QScrollArea *ScrollArea_List = new QScrollArea(this);
	GridLayout_Ctrl->addWidget(ScrollArea_List, 2, 0,8, 10);
	//QWigetForList = new QWidget(ScrollArea_List);

	static QLabel *Logo = new QLabel(tr("LOGO"));
	
	//����LOGO
	Logo->setPixmap(QPixmap("logo.bmp"));
	Logo->setAlignment(Qt::AlignCenter);
	GridLayout_Ctrl->addWidget(Logo, 2, 10, 8, 8);
	//Logo->setScaledContents(true);
	//Logo->resize(Logo->width(), Logo->height());

	//��������
	lcd = new QLCDNumber();
	lcd->setDigitCount(10);
	lcd->setMode(QLCDNumber::Dec);
	lcd->setSegmentStyle(QLCDNumber::Filled);
	lcd->setStyleSheet("QLCDNumber{background:rgba(220,220,120);color:black}");
	static QTimer *timer = new QTimer();
	//���ö�ʱ��ÿ�����ٺ��뷢��һ��timeout()�ź�   
	timer->setInterval(1000);
	//������ʱ��   
	timer->start();

	connect(timer, SIGNAL(timeout()), this, SLOT(_Timer_LCD()));
	
	GridLayout_Ctrl->addWidget(lcd, 0, 10, 2, 8);
#ifdef _DEBUG
	char buff[256] = { 0 };
	sprintf(buff, "w:%d,h:%d", Logo->width(), Logo->height());
	DLOG(LOG_INFO,buff);
#endif
	


}
//�ۺ�������
void MserialsUIQt::initConnect()
{
	connect(Button_Start_Detect, SIGNAL(clicked()), this, SLOT(_Button_Start_Detect()));
	connect(Button_Param_Set, SIGNAL(clicked()), this, SLOT(_Button_Param_Set()));
	connect(Button_Model_Mgr, SIGNAL(clicked()), this, SLOT(_Button_Model_Mgr()));
	connect(Button_Detect_Census, SIGNAL(clicked()), this, SLOT(_Button_Detect_Census()));
	connect(Button_Def_Census, SIGNAL(clicked()), this, SLOT(_Button_Def_Census()));
	connect(Button_Start_Record, SIGNAL(clicked()), this, SLOT(_Button_Start_Record()));
	connect(Button_Counter_to_Zero, SIGNAL(clicked()), this, SLOT(_Button_Counter_to_Zero()));
	connect(Button_Quit, SIGNAL(clicked()), this, SLOT(_Button_Quit()));
	connect(Button_Refresh_Camera, SIGNAL(clicked()), this, SLOT(_Button_Refresh_Camera()));
	connect(Button_Snap, SIGNAL(clicked()), this, SLOT(_Button_Snap()));
}
//��ʼ���˵���
void MserialsUIQt::initMenu()
{
	//�˵�-�ļ�
	openAction = new QAction(QIcon(":/images/doc-open"), QString::fromLocal8Bit("��..."), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(QString::fromLocal8Bit("���Ѵ����ļ�..."));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	QMenu *file = menuBar()->addMenu(QString::fromLocal8Bit("&�ļ�"));
	file->addAction(openAction);

	//�˵�-����
	setModelAction = new QAction(QIcon(":/images/ModelSet"), QString::fromLocal8Bit("ģ������"), this);
	connect(setModelAction, SIGNAL(triggered()), this, SLOT(setModel()));

	setFunFlowAction = new QAction(QIcon(":/images/ModelSet"), QString::fromLocal8Bit("������������"), this);
	connect(setFunFlowAction, SIGNAL(triggered()), this, SLOT(setFuntionFlow()));

	QMenu *set = menuBar()->addMenu(QString::fromLocal8Bit("����"));
	set->addAction(setModelAction);
	set->addAction(setFunFlowAction);
}
//�˵����Ĵ򿪺���
void MserialsUIQt::open()
{

	QString path = QFileDialog::getOpenFileName(this, tr("Open XML"), ".", tr("XML Files(*.axml *.xml)"));
	if (path.length() == 0) {
		QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
	}
	else {
		//	QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
		XmlParse::GetIns()->Read(path);
	}
}

//����ģ��
void MserialsUIQt::setModel()
{
	//Machine::GetIns()->push_button(Machine::PAUSE);
	static QtModelSet QtMDlg;
	QtMDlg.setModal(true);
	QtMDlg.isParaChanged = false;
	QtMDlg.show();
	static bool first_open = true;
	if (first_open)
	{
		first_open = false;
		QtMDlg.OnInitDialog();
	}
}

//���ù�����
void MserialsUIQt::setFuntionFlow()
{
//	Machine::GetIns()->pause();
//	static FunEditDlg FEDlg;
//	FEDlg.setModal(true);
//	FEDlg.show();
}

//û����
void MserialsUIQt::btn_clicked_getxml()
{
/**
	static QtModelSet QtMDlg;
	QtMDlg.setModal(true);
	QtMDlg.show();
	return;
	*/
}

//��ʼ��ⰴť
void MserialsUIQt::_Button_Start_Detect()
{
	Machine::GetIns()->push_button(Machine::START);
	return;
#if 1
	QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.bmp *.jpg *.jpeg *.png *.gif *.tiff)"));
	if (path.length() == 0) return;

	QByteArray ba = path.toLatin1();
	cv::Mat imat, mat;

	Halcon::Hobject image;
	Halcon::read_image(&image, ba.data());
	Machine::GetIns()->h_disp_obj(image, Machine::GetIns()->hdisp_hand[2]);

#else

	QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.bmp *.jpg *.jpeg *.png *.gif *.tiff)"));
	if (path.length() == 0) return;

	QByteArray ba = path.toLatin1();
	cv::Mat imat,mat;
	
	imat = cv::imread(ba.data(), -1);
	cv::cvtColor(imat, mat, CV_BGR2RGB);
	displayMat(mat, pLabelCamera1,pWidgetCamera1);
	
#endif	

}

void MserialsUIQt::_Button_Param_Set()
{
	Machine::GetIns()->push_button(Machine::PAUSE);
	QtParamSet para_set;
	para_set.exec();
}

void MserialsUIQt::_Button_Model_Mgr()
{
	setModel();
}

void MserialsUIQt::_Button_Detect_Census()
{
}

void MserialsUIQt::_Button_Def_Census()
{
}

void MserialsUIQt::_Button_Start_Record()
{
}

void MserialsUIQt::_Button_Counter_to_Zero()
{
	printf("to zero\n");
}

void MserialsUIQt::_Button_Quit()
{
	//system pause
	Machine::GetIns()->record_state();
	Machine::GetIns()->push_button(Machine::PAUSE);
	int res = QMessageBox::question(this, "Quit", QString::fromLocal8Bit("�˳�����"),
		QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);

	if (QMessageBox::Ok != res)
	{
		Machine::GetIns()->resume_state();
		return;
	}
	OnClose();
	QApplication *app;
	app->quit();
}

void MserialsUIQt::_Button_Refresh_Camera()
{
	//disable ���button
//	Button_Counter_to_Zero->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(30,30,180);color:black}");
	Button_Snap->setDisabled(true);
	int cam_index = 0;
	int num = enum_cameras();
	vendors = get_vendors_num();
	char info[512] = { 0 };
	sprintf(info, "camera num %d vendors %d", num,vendors);
	DLOG(LOG_INFO,info);
	
#ifdef _DEBUG
	
		for (int i = 0; i < vendors; i++)
		{
			int cn = get_cameras_num_by_vendor(i);
			for (int j = 0; j < cn; j++)
			{
				Halcon::Hobject image;
				SnapHobj(image, i, j);
				try {
					Machine::GetIns()->h_disp_obj(image,Machine::GetIns()->hdisp_hand[cam_index]);
					cam_index++;
				}
				catch (std::out_of_range &exc)
				{
					DLOG(LOG_INFO, exc.what());
					return;
				}
			}
		}
	

#endif


	//�ָ���ذ�ť
		Button_Snap->setDisabled(false);
//	Button_Counter_to_Zero->setStyleSheet("QPushButton{font-size:12px;padding:3px;background:rgba(220,220,120);color:black}");
}

void MserialsUIQt::_Button_Snap()
{

	Button_Refresh_Camera->setDisabled(true);
	int cam_index = 0;
	for (int i = 0; i < vendors; i++)
	{
		int cn = get_cameras_num_by_vendor(i);
		for (int j = 0; j < cn; j++)
		{
			Halcon::Hobject image;
			SnapHobj(image, i, j,10);
			try {
				Machine::GetIns()->h_disp_obj(image, Machine::GetIns()->hdisp_hand[cam_index]);
				cam_index++;
			}
			catch (std::out_of_range &exc)
			{
				DLOG(LOG_INFO, exc.what());
				return;
			}
		}
	}

	//CV_RGB2Lab
	Button_Refresh_Camera->setDisabled(false);


}
//������mfc oninitdilog �ڽ�����ֵ�ʱ���ٽ��г�ʼ������Ϊ���滹û��ʾʱ��֪�����ڵľ����С
void MserialsUIQt::OnInitDiaog()
{
	//��������ģʽ  
	HANDLE   hMutex = ::CreateMutex(NULL, TRUE, _T("CSSegment"));
	if (hMutex != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			QMessageBox::information(NULL,"warning",QString::fromLocal8Bit("�����Ѿ�����"));
			CloseHandle(hMutex);
			exit(0);
		}
	}
	Machine::GetIns()->h_open_window(m_vec_widget);
}
//override
void MserialsUIQt::closeEvent(QCloseEvent *ev)
{
	int r = QMessageBox::question(this, tr("Hint"), QString::fromLocal8Bit("�˳�����"), QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape);
	if (r == QMessageBox::Yes)
	{
		OnClose();
		ev->accept();
	}
	else
	{
		ev->ignore();
	}
}

void MserialsUIQt::OnClose()
{
	Machine::GetIns()->push_button(Machine::STOP);
	close_device();
}
//LCDʱ����ʾ�Ĳۺ���
void MserialsUIQt::_Timer_LCD()
{
	//��ȡϵͳ��ǰʱ��   
	QTime time = QTime::currentTime();
	//���þ���ܿؼ�QLCDNumber����ʾ������   
	lcd->display(time.toString("hh:mm:ss"));
}

void MserialsUIQt::XmlParse()
{
	QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
