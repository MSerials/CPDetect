#include "stdafx.h"
#include "QtModelSet.h"
#include "Ini.h"
#include "../../../MSerialsCore/Tools/Tools.h"
#include "ImageMgr.h"
#include "Common.h"
#include "global.h"
//#include <thread.h>
//C++11 标准开启线程，目的是为了linux和windows尽量统一
#include <thread>
#include <Windows.h>
#include <QListWidget>
#include "QuitTipDlg.h"
#include "QString.h"
#include <memory>

QtModelSet::QtModelSet(QWidget *parent)
	: QDialog(parent)
{
	ui->setupUi(this);
	resize(1024, 768);
	pGridLayout = nullptr;
	tabWidget = nullptr;
	tabWidget1 = nullptr;
	InitUI();
	ConnetSlot();

}

QtModelSet::~QtModelSet()
{
	delete ui;
}


void QtModelSet::UpDataUI()
{

}

void QtModelSet::InitUI()
{
	if (nullptr == pGridLayout) pGridLayout = new QGridLayout(this);
	InitWidget();
	initSetParamsControl();
	ChangeList(0);
}

//new 在widget上显示
void QtModelSet::InitWidgets()
{
	
}


//old 在scroll上显示
void QtModelSet::InitWidget()
{
	//用于浏览在线图像
	if (nullptr == tabWidget)
	{
		tabWidget = new QTabWidget(this);

		//先铺一个widget在外部的grid上面
		static QWidget *widget1 = new QWidget(this);
		static QGridLayout *gridLayout = new QGridLayout(widget1);
		label = new QLabel(this);
		scrollArea = new QScrollArea(this);
		scrollArea->setBackgroundRole(QPalette::Dark);
		scrollArea->setWidget(label);
		scrollArea->setAlignment(Qt::AlignCenter);
		gridLayout->addWidget(scrollArea, 0, 0, 4, 6);
		Button_Show_Model = new QPushButton(QString::fromLocal8Bit("显示模板图像"));
		gridLayout->addWidget(Button_Show_Model, 6, 0, 1, 1);
		Button_Show_Online = new QPushButton(QString::fromLocal8Bit("显示在线图像"));
		gridLayout->addWidget(Button_Show_Online, 6, 2, 1, 1);
		Button_Set_As_Model = new QPushButton(QString::fromLocal8Bit("设为模板图像"));
		gridLayout->addWidget(Button_Set_As_Model, 6, 4, 1, 1);
		tabWidget->addTab(widget1, QString::fromLocal8Bit("线路1"));

		static QWidget *widget2 = new QWidget(this);
		static QGridLayout *gridLayout1 = new QGridLayout(widget2);
		label1 = new QLabel(this);
		scrollArea1 = new QScrollArea(this);
		scrollArea1->setBackgroundRole(QPalette::Dark);
		scrollArea1->setWidget(label1);
		scrollArea1->setAlignment(Qt::AlignCenter);
		gridLayout1->addWidget(scrollArea1, 0, 0, 4, 6);
		Button_Show_Model1 = new QPushButton(QString::fromLocal8Bit("显示模板图像"));
		gridLayout1->addWidget(Button_Show_Model1, 6, 0, 1, 1);
		Button_Show_Online1 = new QPushButton(QString::fromLocal8Bit("显示在线图像"));
		gridLayout1->addWidget(Button_Show_Online1, 6, 2, 1, 1);
		Button_Set_As_Model1 = new QPushButton(QString::fromLocal8Bit("设为模板图像"));
		gridLayout1->addWidget(Button_Set_As_Model1, 6, 4, 1, 1);
		tabWidget->addTab(widget2, QString::fromLocal8Bit("线路2"));

		static QWidget *widget3 = new QWidget(this);
		static QGridLayout *gridLayout2 = new QGridLayout(widget3);
		label2 = new QLabel(this);
		scrollArea2 = new QScrollArea(this);
		scrollArea2->setBackgroundRole(QPalette::Dark);
		scrollArea2->setWidget(label2);
		scrollArea2->setAlignment(Qt::AlignCenter);
		gridLayout2->addWidget(scrollArea2, 0, 0, 4, 6);
		Button_Show_Model2 = new QPushButton(QString::fromLocal8Bit("显示模板图像"));
		gridLayout2->addWidget(Button_Show_Model2, 6, 0, 1, 1);
		Button_Show_Online2 = new QPushButton(QString::fromLocal8Bit("显示在线图像"));
		gridLayout2->addWidget(Button_Show_Online2, 6, 2, 1, 1);
		Button_Set_As_Model2 = new QPushButton(QString::fromLocal8Bit("设为模板图像"));
		gridLayout2->addWidget(Button_Set_As_Model2, 6, 4, 1, 1);
		tabWidget->addTab(widget3, QString::fromLocal8Bit("线路3"));

		pGridLayout->addWidget(tabWidget,1, 0, 7, 6);
	}



	//第二个界面，
	ParaWidget = new QScrollArea(this);
	pGridLayout->addWidget(ParaWidget, 0, 6, 13, 4);
	/**
	if (nullptr == tabWidget1)
	{
		tabWidget1 = new QTabWidget(this);
		pGridLayout->addWidget(tabWidget1, 0, 6, 13, 4);
	}  
	*/


	//下方检测按钮
	{
		Button_One_Key_Detect = new QPushButton(QString::fromLocal8Bit("一键检测"));
		pGridLayout->addWidget(Button_One_Key_Detect, 13, 2, 1, 1);

		Button_Save_Current_Line_Model = new QPushButton(QString::fromLocal8Bit("保存当前路模板"));
		pGridLayout->addWidget(Button_Save_Current_Line_Model, 13, 3, 1, 2);

		Button_Save_Model = new QPushButton(QString::fromLocal8Bit("保存模板"));
		pGridLayout->addWidget(Button_Save_Model, 13, 5, 1, 1);

		Button_Quit = new QPushButton(QString::fromLocal8Bit("退出"));
		pGridLayout->addWidget(Button_Quit, 13, 6, 1, 1);

		Button_Load_Current_Model = new QPushButton(QString::fromLocal8Bit("加载当前模板"));
		pGridLayout->addWidget(Button_Load_Current_Model, 13, 7, 1, 1);

		Button_Model_List = new QPushButton(QString::fromLocal8Bit("模板列表"));
		pGridLayout->addWidget(Button_Model_List, 13, 8, 1, 1);
	}

	//第三个界面本地浏览器
	{
		fileListWidget = std::auto_ptr<QListWidget>(new QListWidget(this));
		label_brower = new QLabel(this);
		fileLineEdit = std::auto_ptr<QLineEdit>(new QLineEdit("C:/", this));
		DiskDir = std::auto_ptr<QComboBox>(new QComboBox(this));

		pGridLayout->addWidget(DiskDir.get(), 0, 12, 1, 3);
		pGridLayout->addWidget(fileLineEdit.get(), 1, 12, 1, 3);
		pGridLayout->addWidget(fileListWidget.get(), 2, 12, 10, 3);

		//--设置对应信号与槽
		connect(fileLineEdit.get(), SIGNAL(returnPressed()),
			this, SLOT(slotDirShow(QDir)));
		connect(fileListWidget.get(), SIGNAL(itemDoubleClicked(QListWidgetItem *)),
			this, SLOT(slotDirShow(QListWidgetItem*)));
		connect(DiskDir.get(), SIGNAL(activated(const QString &)),
			this, SLOT(slotDiskDirShow()));


		//盘符选择
		QFileInfoList drivers = QDir::drives();
		for (auto d : drivers)
		{
			DiskDir.get()->addItem(d.filePath());
		}

		//文件浏览
		QString rootStr = "C:/";
		QDir rootDir(rootStr);
		QDir rootDir1 = rootDir;
		QStringList stringlist;
		QStringList stringlist1;
	
		stringlist << "*.jpg" << "*.bmp" << "*.png";
		stringlist1 << "*" ;
		list = rootDir.entryInfoList(stringlist, QDir::AllEntries, QDir::DirsFirst);
		list1 = rootDir1.entryInfoList(stringlist1, QDir::Dirs, QDir::DirsFirst);
		QFileInfoList list2 = list1 + list;
		showFileInfoList(list2);
	}

}

//--显示当前目录下的所有文件
void QtModelSet::slotShow(QDir dir)
{
	QDir dir1 = dir;
	QStringList stringList;
	QStringList stringList1;
	stringList << "*.jpg" << "*.bmp" << "*.png" ;
	stringList1 << "*";
	QFileInfoList InfoList = dir.entryInfoList(stringList, QDir::AllEntries, QDir::DirsFirst);
	QFileInfoList InfoList1 = dir1.entryInfoList(stringList1, QDir::Dirs, QDir::DirsFirst);
	QFileInfoList InfoList2 = InfoList1+ InfoList;
	showFileInfoList(InfoList2);

}
//---用双击浏览器中显示的目录进入下一级，或者返回上一级目录。
void QtModelSet::showFileInfoList(QFileInfoList list)
{
	//--清空列表控件
	fileListWidget->clear();

	//----取出所有项，按照目录，文件方式添加到控件内
	for (unsigned int i = 0; i < list.count(); i++)
	{
		QFileInfo tmpFileInfo = list.at(i);
		if (tmpFileInfo.isDir())
		{
			QIcon icon("dir.png");
			QString fileName = tmpFileInfo.fileName();
			QListWidgetItem*tmpListWidgetItem = new QListWidgetItem(icon, fileName);
			fileListWidget->addItem(tmpListWidgetItem);
		}
		else
		{
			QIcon icon("pic.png");
			QString fileName = tmpFileInfo.fileName();
			QListWidgetItem*tmpListWidgetItem = new QListWidgetItem(icon, fileName);
			fileListWidget->addItem(tmpListWidgetItem);
		}
	}
}

//----根据用户的选择显示下一级目录下的文件，
void QtModelSet::slotDirShow(QListWidgetItem *Item)
{
	//----保存下一级目录名
	QString string = Item->text();
	QDir dir;
	//----设置路径为当前目录路径
	dir.setPath(fileLineEdit->text());
	//-----重新设置路径
	dir.cd(string);
	//----更新当前显示路径， 这里获取的是绝对路径
	fileLineEdit->setText(dir.absolutePath());
	//---显示当前文件目录下的所有文件
	slotShow(dir);
	//判断选中是否为图片
	//读取选中的图片
	QFileInfo IspicInfo = dir.absoluteFilePath(string);
	if (IspicInfo.isFile() == true) {
		std::cout << dir.absoluteFilePath(string).toLatin1().data() << std::endl;
		try { read_image(&m_disp_image.at(0), dir.absoluteFilePath(string).toLocal8Bit().data()); 
		h_disp_obj(m_disp_image.at(0), m_disp_hd.at(0));
		}
		catch (Halcon::HException &except)
		{
			Halcon::set_check("give_error");
			Halcon::set_tposition(m_disp_hd.at(0), 0, 1);
			Halcon::write_string(m_disp_hd.at(0), "no image");
		}
	}
}

void QtModelSet::slotDiskDirShow()
{
	//----保存目前选定的目录名
	QString string = DiskDir->currentText();
	QDir dir;
	//----设置路径为当前目录路径
	dir.setPath(fileLineEdit->text());
	//-----重新设置路径
	dir.cd(string);
	//----更新当前显示路径， 这里获取的是绝对路径
	fileLineEdit->setText(dir.absolutePath());
	//---显示当前文件目录下的所有文件
	slotShow(dir);
}


void QtModelSet::initSetParamsControl()
{
#define COL_WIDTH 317
#define COL_HEIGHT 720
	//线路一的tab设置
	tabWidget_Set_Line1  = new  QTabWidget(ParaWidget);
	tabWidget_Set_Line1->resize(COL_WIDTH, COL_HEIGHT);
	//线路二的tab设置
	tabWidget_Set_Line2 = new  QTabWidget(ParaWidget);
	tabWidget_Set_Line2->resize(COL_WIDTH, COL_HEIGHT);
//	static QWidget *widget2 = new QWidget(this);
//	tabWidget_Set_Line1->addTab(widget2, QString::fromLocal8Bit("线路55"));
//	static QWidget *widget3 = new QWidget(this);
//	tabWidget_Set_Line1->addTab(widget3, QString::fromLocal8Bit("线路55"));
	//线路三的tab设置
	tabWidget_Set_Line3 = new  QTabWidget(ParaWidget);
	tabWidget_Set_Line3->resize(COL_WIDTH, COL_HEIGHT);

	Line1_Settings();
	Line2_Settings();
	Line3_Settings();

	//设置面板隐藏和显示
	tabWidget_Set_Line2->setHidden(true);
	tabWidget_Set_Line3->setHidden(true);
	tabWidget_Set_Line1->setHidden(true);
}

//线路1的设置
void QtModelSet::Line1_Settings()
{
	static QWidget *widget1 = new QWidget();
	//widget->resize(300, 680);
	pTreeWidget_line1_checking_params_stting = new QTreeWidget(widget1);
	pTreeWidget_line1_checking_params_stting->setHeaderLabels(QStringList() << QString::fromLocal8Bit("参数") << QString::fromLocal8Bit("值"));

	pTreeWidget_line1_checking_params_stting->setColumnWidth(0,2*COL_WIDTH/3 -10);
	pTreeWidget_line1_checking_params_stting->setColumnWidth(1, COL_WIDTH / 3);

	root_item_line1_checking_params_setting = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖底面检测参数"));
	pTreeWidget_line1_checking_params_stting->addTopLevelItem(root_item_line1_checking_params_setting);


		//变形检测
		root_item_shape = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("变形检测"));
		root_item_line1_checking_params_setting->addChild(root_item_shape);

		QTreeWidgetItem* child = new QTreeWidgetItem(QStringList()<< QString::fromLocal8Bit("变形检测"));
		root_item_shape->addChild(child);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child, 1, pComboBox_bianxingjiance = new QComboBox);//将QSpinBox显示到child项的第一列里
		pComboBox_bianxingjiance->addItem(QString::fromLocal8Bit("开启"));
		pComboBox_bianxingjiance->addItem(QString::fromLocal8Bit("关闭"));
		if (0 == Preference::GetIns()->prj->para.b_bianxingjiance)
			pComboBox_bianxingjiance->setCurrentIndex(0);
		else
			pComboBox_bianxingjiance->setCurrentIndex(1);
		connect(pComboBox_bianxingjiance, SIGNAL(currentIndexChanged(int)), this, SLOT(bianxingjianceChanged()));

		child_silakou = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("撕拉口屏蔽"));
		root_item_shape->addChild(child_silakou);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_silakou, 1, pComboBox_silakoupingbi = new QComboBox);//将QSpinBox显示到child项的第一列里
		pComboBox_silakoupingbi->addItem(QString::fromLocal8Bit("开启"));
		pComboBox_silakoupingbi->addItem(QString::fromLocal8Bit("关闭"));
		if (0 == Preference::GetIns()->prj->para.b_silakoupingbi)
			pComboBox_silakoupingbi->setCurrentIndex(0);
		else
			pComboBox_silakoupingbi->setCurrentIndex(1);
		connect(pComboBox_silakoupingbi, SIGNAL(currentIndexChanged(int)), this, SLOT(silakoupingbi()));





		child_pingkouyuandu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("瓶口圆度(C)<="));
		root_item_shape->addChild(child_pingkouyuandu);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_pingkouyuandu, 1, LE_pingkouyuandu  = new QLineEdit);//将QSpinBox显示到child项的第一列里

		child_pingkoubianxingdu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("瓶口变形度(D0)>="));
		root_item_shape->addChild(child_pingkoubianxingdu);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_pingkoubianxingdu, 1, LE_pingkoubianxingdu = new QLineEdit);//将QSpinBox显示到child项的第一列里

		child_waitujuli = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("外凸距离(D1)>="));
		root_item_shape->addChild(child_waitujuli);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_waitujuli, 1, LE_waitujuli = new QLineEdit);//将QSpinBox显示到child项的第一列里

		child_neiaojuli= new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("内凹距离(D1)>="));
		root_item_shape->addChild(child_neiaojuli);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_neiaojuli, 1, new QLineEdit);//将QSpinBox显示到child项的第一列里

		child_shangbiaopipei = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("商标匹配度"));
		root_item_shape->addChild(child_shangbiaopipei);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_shangbiaopipei, 1, new QLineEdit);//将QSpinBox显示到child项的第一列里

		QTreeWidgetItem *root_item_white_dots = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白异色点检测"));
		root_item_line1_checking_params_setting->addChild(root_item_white_dots);

		child_baiyisedian = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白异色点检测"));
		root_item_white_dots->addChild(child_baiyisedian);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_baiyisedian, 1, new QLineEdit);//将QSpinBox显示到child项的第一列里

		child_secha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
		root_item_white_dots->addChild(child_secha);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_secha, 1, slider = new QSlider(Qt::Horizontal));//将QSpinBox显示到child项的第一列里
		slider->setMinimum(0);
		slider->setMaximum(255);
		slider->setSingleStep(255);
		connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
		//connect(pSlider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));

		child_mianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(LA)>="));
		root_item_white_dots->addChild(child_mianji);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_mianji, 1, new QLineEdit);//将QSpinBox显示到child项的第一列里

		QTreeWidgetItem *root_item_yellow_spot = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("黄斑检测"));
		root_item_line1_checking_params_setting->addChild(root_item_yellow_spot);

		child_huangban = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("黄斑检测"));
		root_item_yellow_spot->addChild(child_huangban);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_huangban, 1, new QLineEdit);

		child_secha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
		root_item_yellow_spot->addChild(child_secha);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_secha, 1, new QSlider(Qt::Horizontal));

		child_mianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(YA)>="));
		root_item_yellow_spot->addChild(child_mianji);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_mianji, 1, new QLineEdit);
		//小凹坑检测
		QTreeWidgetItem *root_item_small_pits = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("小凹坑检测"));
		root_item_line1_checking_params_setting->addChild(root_item_small_pits);

		child_xiaoaokeng = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("小凹坑检测"));
		root_item_small_pits->addChild(child_xiaoaokeng);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_xiaoaokeng, 1, new QLineEdit);

		child_secha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
		root_item_small_pits->addChild(child_secha);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_secha, 1, new QSlider(Qt::Horizontal));

		child_mianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(PA)>="));
		root_item_small_pits->addChild(child_mianji);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_mianji, 1, new QLineEdit);

		//顶部凹陷检测列表
		QTreeWidgetItem *root_dingbuaokengjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("顶部凹陷检测"));
		root_item_line1_checking_params_setting->addChild(root_dingbuaokengjiance);

		QTreeWidgetItem *child_dingaojiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("顶凹检测"));
		root_dingbuaokengjiance->addChild(child_dingaojiance);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_dingaojiance, 1, pComboBox_dingaojiance = new QComboBox);
		pComboBox_dingaojiance->addItem(QString::fromLocal8Bit("开启"));
		pComboBox_dingaojiance->addItem(QString::fromLocal8Bit("关闭"));
		if (0 == Preference::GetIns()->prj->para.b_dingaojiance)
			pComboBox_dingaojiance->setCurrentIndex(0);
		else
			pComboBox_dingaojiance->setCurrentIndex(1);
		connect(pComboBox_dingaojiance, SIGNAL(currentIndexChanged(int)), this, SLOT(dingaojianceChanged()));


		child_dingaosecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
		root_dingbuaokengjiance->addChild(child_dingaosecha);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_dingaosecha, 1, slider_dingaosecha = new QSlider(Qt::Horizontal));
		connect(slider_dingaosecha, SIGNAL(valueChanged(int)), this, SLOT(dingaosechaChanged(int)));

		//穿刺检测列表
		QTreeWidgetItem *root_chuancijiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("穿刺检测"));
		root_item_line1_checking_params_setting->addChild(root_chuancijiance);

		QTreeWidgetItem *child_chuancijiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("穿刺检测"));
		root_chuancijiance->addChild(child_chuancijiance);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_chuancijiance, 1, pComboBox_chuancijiance = new QComboBox);
		pComboBox_chuancijiance->addItem(QString::fromLocal8Bit("开启"));
		pComboBox_chuancijiance->addItem(QString::fromLocal8Bit("关闭"));
		if (0 == Preference::GetIns()->prj->para.b_chuancijiance)
			pComboBox_chuancijiance->setCurrentIndex(0);
		else
			pComboBox_chuancijiance->setCurrentIndex(1);
		connect(pComboBox_chuancijiance, SIGNAL(currentIndexChanged(int)), this, SLOT(chuancijianceChanged()));

		QTreeWidgetItem *child_jiancebanjing = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("检测半径"));
		root_chuancijiance->addChild(child_jiancebanjing);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_jiancebanjing, 1, new QLineEdit);

		QTreeWidgetItem *child_mianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积>="));
		root_chuancijiance->addChild(child_mianji);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_mianji, 1, new QLineEdit);
		
		child_jiancebanjing = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("阈值<="));
		root_chuancijiance->addChild(child_jiancebanjing);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_jiancebanjing, 1, new QSlider(Qt::Horizontal));

		//白盖检测列表fake
		QTreeWidgetItem *root_baigaijiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白盖检测"));
		root_item_line1_checking_params_setting->addChild(root_baigaijiance);

		QTreeWidgetItem *child_baigaijiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白盖检测"));
		root_baigaijiance->addChild(child_baigaijiance);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_baigaijiance, 1, pComboBox_baigaijiance = new QComboBox);
		pComboBox_baigaijiance->addItem(QString::fromLocal8Bit("开启"));
		pComboBox_baigaijiance->addItem(QString::fromLocal8Bit("关闭"));

		//白盖混型检测列表fake
		QTreeWidgetItem *root_hunxingjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("混型检测"));
		root_item_line1_checking_params_setting->addChild(root_hunxingjiance);

		QTreeWidgetItem *child_hunxingjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("混型检测"));
		root_hunxingjiance->addChild(child_hunxingjiance);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_hunxingjiance, 1, pComboBox_hunxingjiance = new QComboBox);
		pComboBox_hunxingjiance->addItem(QString::fromLocal8Bit("开启"));
		pComboBox_hunxingjiance->addItem(QString::fromLocal8Bit("关闭"));

		QTreeWidgetItem *child_tichulvgai = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("剔除铝盖类型"));
		root_hunxingjiance->addChild(child_tichulvgai);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_tichulvgai, 1, pComboBox_tichulvgai = new QComboBox);
		pComboBox_tichulvgai->addItem(QString::fromLocal8Bit("单环"));
		pComboBox_tichulvgai->addItem(QString::fromLocal8Bit("双环"));

		QTreeWidgetItem *child_tichuyuzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("剔除阈值"));
		root_hunxingjiance->addChild(child_tichuyuzhi);
		pTreeWidget_line1_checking_params_stting->setItemWidget(child_tichuyuzhi, 1, new QLineEdit);


	tabWidget_Set_Line1->addTab(pTreeWidget_line1_checking_params_stting, QString::fromLocal8Bit("检测参数设置"));



	
	pTreeWidget_line1_model_params_stting = new QTreeWidget(widget1);//新建一个QTreeWidget对象，名为pTreeWidget_line1_model_params_stting
	//设定QTreeWidget树状选项的顶层标题，左边为参数，右边为值
	pTreeWidget_line1_model_params_stting->setHeaderLabels(QStringList() << QString::fromLocal8Bit("参数") << QString::fromLocal8Bit("值"));

	pTreeWidget_line1_model_params_stting->setColumnWidth(0, 2 * COL_WIDTH / 3 - 10);
	pTreeWidget_line1_model_params_stting->setColumnWidth(1, COL_WIDTH / 3);//设定树状选项控件的宽度
	//新建一个QTreeWidgetItem对象，名为root_item_line1_model_params_setting，此层为第一层
	root_item_line1_model_params_setting = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖底面模板参数"));

	pTreeWidget_line1_model_params_stting->addTopLevelItem(root_item_line1_model_params_setting);//将上面创建的QTreeWidgetItem添加到pTreeWidget_line1_model_params_stting的顶层
	
	//铝盖类型设定列表
	root_item_type = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖类型"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line1_model_params_setting->addChild(root_item_type);//将第二层加到第一层下面

	QTreeWidgetItem* child_lvgaileixing = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖类型"));//用指针方式新建一个QTreeWidgetItem（第三层）
	root_item_type->addChild(child_lvgaileixing);//将第三层加到第二层下面
	pTreeWidget_line1_model_params_stting->setItemWidget(child_lvgaileixing, 1, pComboBox_lvgaileixing = new QComboBox);//将QSpinBox显示到child_lvgaileixing子项的第一列里
	pComboBox_lvgaileixing->addItem(QString::fromLocal8Bit("直插"));
	pComboBox_lvgaileixing->addItem(QString::fromLocal8Bit("撕拉"));
	pComboBox_lvgaileixing->addItem(QString::fromLocal8Bit("商标"));
	//
	pComboBox_lvgaileixing->setCurrentIndex(Preference::GetIns()->prj->para.sel_lvgaileixing);
	connect(pComboBox_lvgaileixing, SIGNAL(currentIndexChanged(int)), this, SLOT(lvgaileixingChanged()));

	

	QTreeWidgetItem* child_lvgaiyanse = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖颜色"));
	root_item_type->addChild(child_lvgaiyanse);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_lvgaiyanse, 1, pComboBox_lvgaiyanse = new QComboBox);//将QSpinBox显示到child项的第一列里
	pComboBox_lvgaiyanse->addItem(QString::fromLocal8Bit("白色"));
	pComboBox_lvgaiyanse->addItem(QString::fromLocal8Bit("黄色"));

	pComboBox_lvgaiyanse->setCurrentIndex(Preference::GetIns()->prj->para.sel_lvgaiyanse);
	connect(pComboBox_lvgaiyanse, SIGNAL(currentIndexChanged(int)), this, SLOT(lvgaiyanseChanged()));



	QTreeWidgetItem* child_tiqvfangshi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("提取方式"));
	root_item_type->addChild(child_tiqvfangshi);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_tiqvfangshi, 1, pComboBox_tiqvfangshi = new QComboBox);//将QSpinBox显示到child项的第一列里
	pComboBox_tiqvfangshi->addItem(QString::fromLocal8Bit("盖底"));
	pComboBox_tiqvfangshi->addItem(QString::fromLocal8Bit("盖壁"));
	pComboBox_tiqvfangshi->addItem(QString::fromLocal8Bit("压环"));

	pComboBox_tiqvfangshi->setCurrentIndex(Preference::GetIns()->prj->para.sel_tiqvfangshi);
	connect(pComboBox_tiqvfangshi, SIGNAL(currentIndexChanged(int)), this, SLOT(tiqvfangshiChanged()));

	//皮带颜色设定列表
	root_item_pidaiyanse = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("皮带颜色设定"));
	root_item_line1_model_params_setting->addChild(root_item_pidaiyanse);

	QTreeWidgetItem* child_pidaiyanse = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("皮带颜色"));
	root_item_pidaiyanse->addChild(child_pidaiyanse);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_pidaiyanse, 1, pComboBox_pidaiyanse = new QComboBox);//将QSpinBox显示到child项的第一列里
	pComboBox_pidaiyanse->addItem(QString::fromLocal8Bit("白皮带"));
	pComboBox_pidaiyanse->addItem(QString::fromLocal8Bit("黑皮带"));

	pComboBox_pidaiyanse->setCurrentIndex(Preference::GetIns()->prj->para.sel_pidaiyanse);
	connect(pComboBox_pidaiyanse, SIGNAL(currentIndexChanged(int)), this, SLOT(pidaiyanseChanged()));

	//铝盖区域划定列表
	root_item_lvgaiqvyuhuading = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖区域划定"));
	root_item_line1_model_params_setting->addChild(root_item_lvgaiqvyuhuading);

	QTreeWidgetItem* child_chicunjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖尺寸检测"));
	root_item_lvgaiqvyuhuading->addChild(child_chicunjiance);
	Button_line1_model_chicunceliang = new QPushButton(QString::fromLocal8Bit("测量铝盖尺寸"));//创建按钮
	pTreeWidget_line1_model_params_stting->setItemWidget(child_chicunjiance, 1, Button_line1_model_chicunceliang);

	QTreeWidgetItem* child_chuanciqvyu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("穿刺区域划定"));
	root_item_lvgaiqvyuhuading->addChild(child_chuanciqvyu);
	Button_line1_model_chuancibanjing = new QPushButton(QString::fromLocal8Bit("穿刺半径"));//创建按钮
	pTreeWidget_line1_model_params_stting->setItemWidget(child_chuanciqvyu, 1, Button_line1_model_chuancibanjing);

	QTreeWidgetItem* child_qvyubanjing = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖商标区划定"));
	root_item_lvgaiqvyuhuading->addChild(child_qvyubanjing);
	Button_line1_model_qvyubanjing = new QPushButton(QString::fromLocal8Bit("区域半径"));//创建按钮
	pTreeWidget_line1_model_params_stting->setItemWidget(child_qvyubanjing, 1, Button_line1_model_qvyubanjing);

	//铝盖区域分割列表
	root_item_lvgaiqvyufenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖区域分割"));
	root_item_line1_model_params_setting->addChild(root_item_lvgaiqvyufenge);




	child_huiduzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖灰度值"));
	root_item_lvgaiqvyufenge->addChild(child_huiduzhi);
	QSlider * Slider_pinggaihuiduzhi = nullptr;
	pTreeWidget_line1_model_params_stting->setItemWidget(child_huiduzhi, 1, Slider_pinggaihuiduzhi = new QSlider(Qt::Horizontal));//将QSlider显示到child项的第一列里
	Slider_pinggaihuiduzhi->setMinimum(0);
	Slider_pinggaihuiduzhi->setMaximum(255);
	Slider_pinggaihuiduzhi->setSingleStep(255);
	Slider_pinggaihuiduzhi->setValue(Preference::GetIns()->prj->para.threshold_back_cap);
	connect(Slider_pinggaihuiduzhi, SIGNAL(valueChanged(int)), this, SLOT(pinggaihuiduzhiChanged(int)));



	child_dibuhuiduzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖底部灰度值"));
	root_item_lvgaiqvyufenge->addChild(child_dibuhuiduzhi);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_dibuhuiduzhi, 1, slider = new QSlider(Qt::Horizontal));//将QSlider显示到child项的第一列里

	QSlider *Slider_dibuhuiduzhi = nullptr;
	pTreeWidget_line1_model_params_stting->setItemWidget(child_huiduzhi, 1, Slider_dibuhuiduzhi = new QSlider(Qt::Horizontal));//将QSlider显示到child项的第一列里
	Slider_dibuhuiduzhi->setMinimum(0);
	Slider_dibuhuiduzhi->setMaximum(255);
	Slider_dibuhuiduzhi->setSingleStep(255);
	Slider_dibuhuiduzhi->setValue(Preference::GetIns()->prj->para.dibuhuiduzhi);
	connect(Slider_dibuhuiduzhi, SIGNAL(valueChanged(int)), this, SLOT(dibuhuiduzhiChanged(int)));





	child_dibufuzhuhuiduzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖底部辅助灰度值"));
	root_item_lvgaiqvyufenge->addChild(child_dibufuzhuhuiduzhi);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_dibufuzhuhuiduzhi, 1, slider = new QSlider(Qt::Horizontal));//将QSlider显示到child项的第一列里

	child_pinbifengebaocuo = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("屏蔽底部分割报错"));
	root_item_lvgaiqvyufenge->addChild(child_pinbifengebaocuo);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_pinbifengebaocuo, 1, pComboBox_pinbifengebaocuo = new QComboBox);
	pComboBox_pinbifengebaocuo->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_pinbifengebaocuo->addItem(QString::fromLocal8Bit("关闭"));

	child_cunzaishangbiao = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("是否存在商标"));
	root_item_lvgaiqvyufenge->addChild(child_cunzaishangbiao);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_cunzaishangbiao, 1, pComboBox_cunzaishangbiao = new QComboBox);
	pComboBox_cunzaishangbiao->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_cunzaishangbiao->addItem(QString::fromLocal8Bit("关闭"));

	child_shangbiaojianmo = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("商标建模"));
	root_item_lvgaiqvyufenge->addChild(child_shangbiaojianmo);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_shangbiaojianmo, 1, slider = new QSlider(Qt::Horizontal));//将QSlider显示到child项的第一列里

	//铝盖压环区域划定列表
	root_item_lvgaiyahuanqvyu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖压环区域划定"));
	root_item_line1_model_params_setting->addChild(root_item_lvgaiyahuanqvyu);
	child_yitianjiayahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("已添加压环数"));
	root_item_lvgaiyahuanqvyu->addChild(child_yitianjiayahuan);
	pTreeWidget_line1_model_params_stting->setItemWidget(child_yitianjiayahuan, 1,new QLabel(QString::fromLocal8Bit("1")));//需要调用变量，目前用文字代替

	QTreeWidgetItem* child_tianjiayahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("添加压环"));
	root_item_lvgaiyahuanqvyu->addChild(child_tianjiayahuan);
	Button_line1_model_tianjiayahuan = new QPushButton(QString::fromLocal8Bit("添加压环"));//创建按钮
	pTreeWidget_line1_model_params_stting->setItemWidget(child_tianjiayahuan, 1, Button_line1_model_tianjiayahuan);

	QTreeWidgetItem* child_xiugaiyahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("修改压环"));
	root_item_lvgaiyahuanqvyu->addChild(child_xiugaiyahuan);
	Button_line1_model_xiugaiyahuan = new QPushButton(QString::fromLocal8Bit("修改压环"));//创建按钮
	pTreeWidget_line1_model_params_stting->setItemWidget(child_xiugaiyahuan, 1, Button_line1_model_xiugaiyahuan);

	QTreeWidgetItem* child_shanchuyahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("删除压环"));
	root_item_lvgaiyahuanqvyu->addChild(child_shanchuyahuan);
	Button_line1_model_shanchuyahuan = new QPushButton(QString::fromLocal8Bit("删除压环"));//创建按钮
	pTreeWidget_line1_model_params_stting->setItemWidget(child_shanchuyahuan, 1, Button_line1_model_shanchuyahuan);

	QTreeWidgetItem* child_xianshiyahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("显示压环"));
	root_item_lvgaiyahuanqvyu->addChild(child_xianshiyahuan);
	Button_line1_model_xianshiyahuan = new QPushButton(QString::fromLocal8Bit("显示压环"));//创建按钮
	pTreeWidget_line1_model_params_stting->setItemWidget(child_xianshiyahuan, 1, Button_line1_model_xianshiyahuan);

	tabWidget_Set_Line1->addTab(pTreeWidget_line1_model_params_stting, QString::fromLocal8Bit("模板参数设置"));
}

//线路一所有的槽函数
void QtModelSet::bianxingjianceChanged()
{
	isParaChanged = true;
	int value = pComboBox_bianxingjiance->currentIndex();
	if (value == 0)
	{
		//开启                                                                                                                               
		Preference::GetIns()->prj->para_bak.b_bianxingjiance = 0;
		child_pingkouyuandu->setDisabled(false);
		LE_pingkouyuandu->setDisabled(false);

		child_pingkoubianxingdu->setDisabled(false);
		LE_pingkoubianxingdu->setDisabled(false);

		child_waitujuli->setDisabled(false);
		LE_waitujuli->setDisabled(false);

		child_neiaojuli->setDisabled(false);
		child_shangbiaopipei->setDisabled(false);
	}
	else
	{
		//关闭
		Preference::GetIns()->prj->para_bak.b_bianxingjiance = 1;
		child_pingkouyuandu->setDisabled(true);
		LE_pingkouyuandu->setDisabled(true);

		child_pingkoubianxingdu->setDisabled(true);
		LE_pingkoubianxingdu->setDisabled(true);

		child_waitujuli->setDisabled(true);
		LE_waitujuli->setDisabled(true);

		child_neiaojuli->setDisabled(true);
		child_shangbiaopipei->setDisabled(true);
	}


}


void QtModelSet::lvgaileixingChanged()
{
	isParaChanged = true;
	int value = pComboBox_lvgaileixing->currentIndex();
	Preference::GetIns()->prj->para_bak.sel_lvgaileixing = 0;
}

void QtModelSet::silakoupingbi() {
	isParaChanged = true;
	int value =  pComboBox_bianxingjiance->currentIndex();
	if (value == 0)
	{
		Preference::GetIns()->prj->para_bak.b_silakoupingbi = 0;
	}
	else
	{
		Preference::GetIns()->prj->para_bak.b_silakoupingbi = 1;
	}
}


void QtModelSet::pinggaihuiduzhiChanged(int a)
{
	isParaChanged = true;
	using namespace Halcon;
	Hobject  Image, Regions, Red, Green, Blue, Hue, inner, ConnectedRegions, MaxArea;
	Hobject  Saturation, Intensity, Saturated, ContoursSplit;
	Hobject  SortedContours, ObjectSelected;
	try {
		set_check("~give_error");
		set_draw(m_disp_hd.at(0), "fill");
		set_color(m_disp_hd.at(0), "red");
		Halcon::Hobject hobj, GrayImage;


		Halcon::decompose3(m_disp_image.at(0), &Red, &Green, &Blue);
		trans_from_rgb(Red, Green, Blue, &Hue, &Saturation, &Intensity, "hsv");
		threshold(Saturation, &inner, a, 255);
		h_disp_obj(m_disp_image.at(0), m_disp_hd.at(0));
		h_disp_obj(inner, m_disp_hd.at(0));

		Preference::GetIns()->prj->para_bak.threshold_back_cap = a;
		std::cout << "value:" << a << std::endl;
	}
	catch (Halcon::HException e)
	{
		std::cout << "error" << std::endl;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
}


//线路2的设置
void QtModelSet::Line2_Settings()
{
	static QWidget *widget2 = new QWidget(this);
	pTreeWidget_line2_checking_params_stting = new QTreeWidget(widget2);//新建一个QTreeWidget对象
																	//设定QTreeWidget树状选项的顶层标题，左边为参数，右边为值
	pTreeWidget_line2_checking_params_stting->setHeaderLabels(QStringList() << QString::fromLocal8Bit("参数") << QString::fromLocal8Bit("值"));

	pTreeWidget_line2_checking_params_stting->setColumnWidth(0, 2 * COL_WIDTH / 3 - 10);
	pTreeWidget_line2_checking_params_stting->setColumnWidth(1, COL_WIDTH / 3);//设定树状选项控件的宽度
	//此层为第一层
	root_item_line2_checking_params_setting = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖侧面检测参数"));

	pTreeWidget_line2_checking_params_stting->addTopLevelItem(root_item_line2_checking_params_setting);

	//压痕分割
	root_item_yahenfenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("压痕分割"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_yahenfenge);//将第二层加到第一层下面

	child_yahenfenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("压痕分割"));
	root_item_yahenfenge->addChild(child_yahenfenge);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_yahenfenge, 1, pComboBox_yahenfenge = new QComboBox);
	pComboBox_yahenfenge->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_yahenfenge->addItem(QString::fromLocal8Bit("关闭"));

	//滚花检测
	root_item_genhuajiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("滚花检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_genhuajiance);//将第二层加到第一层下面

	child_gunhuajiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("滚花检测"));
	root_item_genhuajiance->addChild(child_gunhuajiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_gunhuajiance, 1, pComboBox_gunhuajiance = new QComboBox);
	pComboBox_gunhuajiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_gunhuajiance->addItem(QString::fromLocal8Bit("关闭"));
	
	child_gunhuasecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差<="));
	root_item_genhuajiance->addChild(child_gunhuasecha);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_gunhuasecha, 1, new QSlider(Qt::Horizontal));

	//铝盖口部形状检测
	root_item_koubuxingzhuangjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖口部形状检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_koubuxingzhuangjiance);//将第二层加到第一层下面

	child_koubuxingzhuangjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("口部形状检测"));
	root_item_koubuxingzhuangjiance->addChild(child_koubuxingzhuangjiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_koubuxingzhuangjiance, 1, pComboBox_koubuxingzhuangjiance = new QComboBox);
	pComboBox_koubuxingzhuangjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_koubuxingzhuangjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_koubujiaodu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖口部角度(Phi)>="));
	root_item_koubuxingzhuangjiance->addChild(child_koubujiaodu);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_koubujiaodu, 1, Phi_koubujiaodu = new QLineEdit);

	child_koububianxingdu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("口部变形度(DF)>="));
	root_item_koubuxingzhuangjiance->addChild(child_koububianxingdu);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_koububianxingdu, 1, DF_koububianxingdu = new QLineEdit);

	child_bianxingmianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("变形面积(DFA)>="));
	root_item_koubuxingzhuangjiance->addChild(child_bianxingmianji);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_bianxingmianji, 1, DFA_bianxingmianji = new QLineEdit);

	//铝盖口部缺料检测
	root_item_koubuqueliaojiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖口部缺料检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_koubuqueliaojiance);//将第二层加到第一层下面

	child_queliaojiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖缺料检测"));
	root_item_koubuqueliaojiance->addChild(child_queliaojiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_queliaojiance, 1, pComboBox_queliaojiance = new QComboBox);
	pComboBox_queliaojiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_queliaojiance->addItem(QString::fromLocal8Bit("关闭"));

	child_queliaomianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("缺料面积(GA)>="));
	root_item_koubuqueliaojiance->addChild(child_queliaomianji);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_queliaomianji, 1, GA_queliaomianji = new QLineEdit);

	//大皱检测
	root_item_dazhoujiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("大皱检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_dazhoujiance);//将第二层加到第一层下面

	child_dazhoujiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("大皱检测"));
	root_item_dazhoujiance->addChild(child_dazhoujiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_dazhoujiance, 1, pComboBox_dazhoujiance = new QComboBox);
	pComboBox_dazhoujiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_dazhoujiance->addItem(QString::fromLocal8Bit("关闭"));

	child_dazhousecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("大皱色差>="));
	root_item_dazhoujiance->addChild(child_dazhousecha);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_dazhousecha, 1, new QSlider(Qt::Horizontal));

	//白斑检测
	root_item_baibanjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白斑检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_baibanjiance);//将第二层加到第一层下面

	child_baibanjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白斑检测"));
	root_item_baibanjiance->addChild(child_baibanjiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_baibanjiance, 1, pComboBox_baibanjiance = new QComboBox);
	pComboBox_baibanjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_baibanjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_baibanhuidu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白斑灰度值"));
	root_item_baibanjiance->addChild(child_baibanhuidu);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_baibanhuidu, 1, new QSlider(Qt::Horizontal));

	child_baibanhuidu2 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白斑灰度值2"));
	root_item_baibanjiance->addChild(child_baibanhuidu2);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_baibanhuidu2, 1, new QSlider(Qt::Horizontal));

	child_baibansecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白斑色差>="));
	root_item_baibanjiance->addChild(child_baibansecha);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_baibansecha, 1, baibansecha = new QLineEdit);

	child_mianjiWSA = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(WSA)>="));
	root_item_baibanjiance->addChild(child_mianjiWSA);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_mianjiWSA, 1, WSA_mianji = new QLineEdit);

	//外侧脏检测
	root_item_waicezangjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("外侧脏检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_waicezangjiance);//将第二层加到第一层下面

	child_waicezangjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("外侧脏检测"));
	root_item_waicezangjiance->addChild(child_waicezangjiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_waicezangjiance, 1, pComboBox_waicezangjiance = new QComboBox);
	pComboBox_waicezangjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_waicezangjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_waicehuiduzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("灰度值<="));
	root_item_waicezangjiance->addChild(child_waicehuiduzhi);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_waicehuiduzhi, 1, new QSlider(Qt::Horizontal));

	child_mianjiBA = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(BA)>="));
	root_item_waicezangjiance->addChild(child_mianjiBA);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_mianjiBA, 1, BA_mianji = new QLineEdit);

	child_waicesecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
	root_item_waicezangjiance->addChild(child_waicesecha);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_waicesecha, 1, waice_seca = new QLineEdit);

	//铝盖外侧氧化痕检测
	root_item_waiceyanghuahenjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖外侧氧化痕检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_waiceyanghuahenjiance);//将第二层加到第一层下面

	child_yanghuahenjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("外侧脏检测"));
	root_item_waiceyanghuahenjiance->addChild(child_yanghuahenjiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_yanghuahenjiance, 1, pComboBox_waicezangjiance = new QComboBox);
	pComboBox_waicezangjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_waicezangjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_yanghuahensecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
	root_item_waiceyanghuahenjiance->addChild(child_yanghuahensecha);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_yanghuahensecha, 1, yanghuahen_seca = new QLineEdit);

	child_yanghuahenmianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(DA)>="));
	root_item_waiceyanghuahenjiance->addChild(child_yanghuahenmianji);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_yanghuahenmianji, 1, DA_mianji = new QLineEdit);

	child_yanghuahenzmianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("总面积(DAS)>="));
	root_item_waiceyanghuahenjiance->addChild(child_yanghuahenzmianji);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_yanghuahenzmianji, 1, DAS_mianji = new QLineEdit);

	//铝盖外侧划伤检测
	root_item_waicehuashangjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖外侧划伤检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_waicehuashangjiance);//将第二层加到第一层下面

	child_waicehuashangjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("外侧划伤检测"));
	root_item_waicehuashangjiance->addChild(child_waicehuashangjiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_waicehuashangjiance, 1, pComboBox_waicehuashangjiance = new QComboBox);
	pComboBox_waicehuashangjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_waicehuashangjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_waicehuangshangsecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("划伤色差>="));
	root_item_waicehuashangjiance->addChild(child_waicehuangshangsecha);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_waicehuangshangsecha, 1, new QSlider(Qt::Horizontal));

	child_huangshangchangdu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("划伤长度(OW)>="));
	root_item_waicehuashangjiance->addChild(child_huangshangchangdu);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_huangshangchangdu, 1, OW_huashangchangdu = new QLineEdit);

	//铝盖内侧脏检测
	root_item_neicezangjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖内侧脏检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_checking_params_setting->addChild(root_item_neicezangjiance);//将第二层加到第一层下面

	child_baizangdianjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白脏点检测"));
	root_item_neicezangjiance->addChild(child_baizangdianjiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_baizangdianjiance, 1, pComboBox_baizangdianjiance = new QComboBox);
	pComboBox_baizangdianjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_baizangdianjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_baisecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白色差>="));
	root_item_neicezangjiance->addChild(child_baisecha);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_baisecha, 1, new QSlider(Qt::Horizontal));

	child_baimianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白面积(IDA)>="));
	root_item_neicezangjiance->addChild(child_baimianji);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_baimianji, 1, IDA_baimianji = new QLineEdit);

	child_heizangdianjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("黑脏点检测"));
	root_item_neicezangjiance->addChild(child_heizangdianjiance);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_heizangdianjiance, 1, pComboBox_heizangdianjiance = new QComboBox);
	pComboBox_heizangdianjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_heizangdianjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_heisecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("黑色差<="));
	root_item_neicezangjiance->addChild(child_heisecha);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_heisecha, 1, new QSlider(Qt::Horizontal));

	child_heimianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("黑面积(IBA)>="));
	root_item_neicezangjiance->addChild(child_heimianji);
	pTreeWidget_line2_checking_params_stting->setItemWidget(child_heimianji, 1, IBA_heimianji = new QLineEdit);

	tabWidget_Set_Line2->addTab(pTreeWidget_line2_checking_params_stting, QString::fromLocal8Bit("检测参数设置"));

//模板参数设置
	pTreeWidget_line2_model_params_stting = new QTreeWidget(widget2);//新建一个QTreeWidget对象
																		//设定QTreeWidget树状选项的顶层标题，左边为参数，右边为值
	pTreeWidget_line2_model_params_stting->setHeaderLabels(QStringList() << QString::fromLocal8Bit("参数") << QString::fromLocal8Bit("值"));

	pTreeWidget_line2_model_params_stting->setColumnWidth(0, 2 * COL_WIDTH / 3 - 10);
	pTreeWidget_line2_model_params_stting->setColumnWidth(1, COL_WIDTH / 3);//设定树状选项控件的宽度
																			   //此层为第一层
	root_item_line2_model_params_setting = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖侧面模板参数"));

	pTreeWidget_line2_model_params_stting->addTopLevelItem(root_item_line2_model_params_setting);

	//铝盖类型设定列表
	root_item_lvgaileixing2 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖类型"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_model_params_setting->addChild(root_item_lvgaileixing2);//将第二层加到第一层下面

	QTreeWidgetItem* child_lvgaileixing2 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖类型"));//用指针方式新建一个QTreeWidgetItem（第三层）
	root_item_lvgaileixing2->addChild(child_lvgaileixing2);//将第三层加到第二层下面
	pTreeWidget_line2_model_params_stting->setItemWidget(child_lvgaileixing2, 1, pComboBox_lvgaileixing2 = new QComboBox);//将QSpinBox显示到child_lvgaileixing子项的第一列里
	pComboBox_lvgaileixing2->addItem(QString::fromLocal8Bit("直插"));
	pComboBox_lvgaileixing2->addItem(QString::fromLocal8Bit("撕拉"));

	QTreeWidgetItem* child_lvgaiyanse2 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖颜色"));
	root_item_lvgaileixing2->addChild(child_lvgaiyanse2);
	pTreeWidget_line2_model_params_stting->setItemWidget(child_lvgaiyanse2, 1, pComboBox_lvgaiyanse2 = new QComboBox);//将QSpinBox显示到child项的第一列里
	pComboBox_lvgaiyanse2->addItem(QString::fromLocal8Bit("白色"));
	pComboBox_lvgaiyanse2->addItem(QString::fromLocal8Bit("黄色"));

	//铝盖区域划定列表
	root_item_lvgaiqvyuhuading2 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖区域划定"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_model_params_setting->addChild(root_item_lvgaiqvyuhuading2);//将第二层加到第一层下面

	QTreeWidgetItem* child_lvgaileixing3 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖类型"));//用指针方式新建一个QTreeWidgetItem（第三层）
	root_item_lvgaiqvyuhuading2->addChild(child_lvgaileixing3);//将第三层加到第二层下面
	pTreeWidget_line2_model_params_stting->setItemWidget(child_lvgaileixing3, 1, pComboBox_cemianlvgaileixing = new QComboBox);//将QSpinBox显示到child_lvgaileixing子项的第一列里
	pComboBox_cemianlvgaileixing->addItem(QString::fromLocal8Bit("侧面有压痕"));
	pComboBox_cemianlvgaileixing->addItem(QString::fromLocal8Bit("侧面无压痕"));

	QTreeWidgetItem* child_cemianlvgaiqvyu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("划定铝盖区域"));
	root_item_lvgaiqvyuhuading2->addChild(child_cemianlvgaiqvyu);
	Button_line2_model_cemianlvgaiqvyu = new QPushButton(QString::fromLocal8Bit("划定铝盖区域"));//创建按钮
	pTreeWidget_line2_model_params_stting->setItemWidget(child_cemianlvgaiqvyu, 1, Button_line2_model_cemianlvgaiqvyu);

	QTreeWidgetItem* child_cemianlvgaiqvse = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖取色"));
	root_item_lvgaiqvyuhuading2->addChild(child_cemianlvgaiqvse);
	Button_line2_model_cemianlvgaiqvse = new QPushButton(QString::fromLocal8Bit("铝盖取色"));//创建按钮
	pTreeWidget_line2_model_params_stting->setItemWidget(child_cemianlvgaiqvse, 1, Button_line2_model_cemianlvgaiqvse);

	//铝盖整体分割
	root_item_lvgaizhengtifenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖整体分割"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_model_params_setting->addChild(root_item_lvgaizhengtifenge);//将第二层加到第一层下面

	child_lvgaizhengtifenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分割灰度值"));
	root_item_lvgaizhengtifenge->addChild(child_lvgaizhengtifenge);
	pTreeWidget_line2_model_params_stting->setItemWidget(child_lvgaizhengtifenge, 1, new QSlider(Qt::Horizontal));

	//铝盖口部分割
	root_item_lvgaikoubufenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖口部分割"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_model_params_setting->addChild(root_item_lvgaikoubufenge);//将第二层加到第一层下面

	child_lvgaikoubufenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分割灰度值"));
	root_item_lvgaikoubufenge->addChild(child_lvgaikoubufenge);
	pTreeWidget_line2_model_params_stting->setItemWidget(child_lvgaikoubufenge, 1, new QSlider(Qt::Horizontal));

	child_lvgaikoubufengefuzhu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分割辅助灰度值"));
	root_item_lvgaikoubufenge->addChild(child_lvgaikoubufengefuzhu);
	pTreeWidget_line2_model_params_stting->setItemWidget(child_lvgaikoubufengefuzhu, 1, new QSlider(Qt::Horizontal));

	//铝盖底部分割
	root_item_lvgaidibufenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖底部分割"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_model_params_setting->addChild(root_item_lvgaidibufenge);//将第二层加到第一层下面

	child_lvgaidibufenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分割灰度值"));
	root_item_lvgaidibufenge->addChild(child_lvgaidibufenge);
	pTreeWidget_line2_model_params_stting->setItemWidget(child_lvgaidibufenge, 1, new QSlider(Qt::Horizontal));

	//撕拉口分割
	root_item_silakoufenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("撕拉口分割"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line2_model_params_setting->addChild(root_item_silakoufenge);//将第二层加到第一层下面

	child_silakoufenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分割灰度值"));
	root_item_silakoufenge->addChild(child_silakoufenge);
	pTreeWidget_line2_model_params_stting->setItemWidget(child_silakoufenge, 1, slider_silakoufenge=new QSlider(Qt::Horizontal));

	tabWidget_Set_Line2->addTab(pTreeWidget_line2_model_params_stting, QString::fromLocal8Bit("模板参数设置"));
}

//线路3的设置
void QtModelSet::Line3_Settings()
{
	static QWidget *widget3 = new QWidget(this);
	pTreeWidget_line3_checking_params_stting = new QTreeWidget(widget3);//新建一个QTreeWidget对象
																		//设定QTreeWidget树状选项的顶层标题，左边为参数，右边为值
	pTreeWidget_line3_checking_params_stting->setHeaderLabels(QStringList() << QString::fromLocal8Bit("参数") << QString::fromLocal8Bit("值"));

	pTreeWidget_line3_checking_params_stting->setColumnWidth(0, 2 * COL_WIDTH / 3 - 10);
	pTreeWidget_line3_checking_params_stting->setColumnWidth(1, COL_WIDTH / 3);//设定树状选项控件的宽度
																			   //此层为第一层
	root_item_line3_checking_params_setting = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖底面检测参数"));

	pTreeWidget_line3_checking_params_stting->addTopLevelItem(root_item_line3_checking_params_setting);

	//变形检测
	root_item_dibubianxingjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("变形检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_dibubianxingjiance);//将第二层加到第一层下面

	child_dibubianxingjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("变形检测"));
	root_item_dibubianxingjiance->addChild(child_dibubianxingjiance);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibubianxingjiance, 1, pComboBox_dibubianxingjiance = new QComboBox);
	pComboBox_dibubianxingjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_dibubianxingjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_pingkouyuanduC = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("瓶口圆度(C)<="));
	root_item_dibubianxingjiance->addChild(child_pingkouyuanduC);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_pingkouyuanduC, 1, C_pingkouyuandu = new QLineEdit);

	child_waitujuliD1 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("外凸距离(D1)>="));
	root_item_dibubianxingjiance->addChild(child_waitujuliD1);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_waitujuliD1, 1, D1_waitujuli = new QLineEdit);

	child_neiaojuliD2 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("内凹距离(D2)>="));
	root_item_dibubianxingjiance->addChild(child_neiaojuliD2);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_neiaojuliD2, 1, D2_neiaojuli = new QLineEdit);

	child_shangbiaopipeidu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("商标匹配度"));
	root_item_dibubianxingjiance->addChild(child_shangbiaopipeidu);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_shangbiaopipeidu, 1, shangbiaopipeidu = new QLineEdit);

	//混盖检测
	root_item_hungaijiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("混盖检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_hungaijiance);//将第二层加到第一层下面

	child_hungaijiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("混盖检测"));
	root_item_hungaijiance->addChild(child_hungaijiance);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_hungaijiance, 1, pComboBox_hungaijiance = new QComboBox);
	pComboBox_hungaijiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_hungaijiance->addItem(QString::fromLocal8Bit("关闭"));

	child_hungaisecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差(CD)>="));
	root_item_hungaijiance->addChild(child_hungaisecha);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_hungaisecha, 1, CD_hungaisecha = new QLineEdit);

	child_shangbiaogaodu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("商标高度(TH)>="));
	root_item_hungaijiance->addChild(child_shangbiaogaodu);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_shangbiaogaodu, 1, TH_shangbiaogaodu = new QLineEdit);

	//色差检测
	root_item_dibusechajiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_dibusechajiance);//将第二层加到第一层下面

	child_dibusechajiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差检测"));
	root_item_dibusechajiance->addChild(child_dibusechajiance);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusechajiance, 1, pComboBox_dibusechajiance = new QComboBox);
	pComboBox_dibusechajiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_dibusechajiance->addItem(QString::fromLocal8Bit("关闭"));

	child_dibusecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差(CD)>="));
	root_item_dibusechajiance->addChild(child_dibusecha);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusecha, 1, CD_dibusecha = new QLineEdit);

	//半边花盖检测
	root_item_banbianhuagaijiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("半边花盖检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_banbianhuagaijiance);//将第二层加到第一层下面

	child_banbianhuagaijiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("半边花盖检测"));
	root_item_banbianhuagaijiance->addChild(child_banbianhuagaijiance);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_banbianhuagaijiance, 1, pComboBox_banbianhuagaijiance = new QComboBox);
	pComboBox_banbianhuagaijiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_banbianhuagaijiance->addItem(QString::fromLocal8Bit("关闭"));

	//白异色点检测
	root_item_baiyisedianjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白异色点检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_baiyisedianjiance);//将第二层加到第一层下面

	child_baiyisedianjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白异色点检测"));
	root_item_baiyisedianjiance->addChild(child_baiyisedianjiance);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_baiyisedianjiance, 1, pComboBox_baiyisedianjiance = new QComboBox);
	pComboBox_baiyisedianjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_baiyisedianjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_baiyisedianhuiduzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("灰度值"));
	root_item_baiyisedianjiance->addChild(child_baiyisedianhuiduzhi);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_baiyisedianhuiduzhi, 1, new QSlider(Qt::Horizontal));

	child_baiyisediansecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
	root_item_baiyisedianjiance->addChild(child_baiyisediansecha);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_baiyisediansecha, 1, baiyisediansecha = new QLineEdit);

	child_baiyisedianmianji= new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(LA)>="));
	root_item_baiyisedianjiance->addChild(child_baiyisedianmianji);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_baiyisedianmianji, 1, LA_baiyisedianmianji = new QLineEdit);

	child_baiyisedianzongmianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("总面积(LAS)>="));
	root_item_baiyisedianjiance->addChild(child_baiyisedianzongmianji);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_baiyisedianzongmianji, 1, LAS_baiyisedianzongmianji = new QLineEdit);

	//黑异色点检测
	root_item_heiyisedianjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("白异色点检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_heiyisedianjiance);//将第二层加到第一层下面

	child_heiyisedianjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("黑异色点检测"));
	root_item_heiyisedianjiance->addChild(child_heiyisedianjiance);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_heiyisedianjiance, 1, pComboBox_heiyisedianjiance = new QComboBox);
	pComboBox_heiyisedianjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_heiyisedianjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_heiyisediansecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
	root_item_heiyisedianjiance->addChild(child_heiyisediansecha);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_heiyisediansecha, 1, heiyisediansecha = new QLineEdit);

	child_heiyisedianmianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(LA)>="));
	root_item_heiyisedianjiance->addChild(child_heiyisedianmianji);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_heiyisedianmianji, 1, DA_heiyisedianmianji = new QLineEdit);

	child_heiyisedianzongmianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("总面积(LAS)>="));
	root_item_heiyisedianjiance->addChild(child_heiyisedianzongmianji);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_heiyisedianzongmianji, 1, DAS_heiyisedianzongmianji = new QLineEdit);


	//底部氧化痕检测
	root_item_dibuyanghuahenjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("底部氧化痕检测"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_dibuyanghuahenjiance);//将第二层加到第一层下面

	child_dibuyanghuahenjiance = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("底部氧化痕检测"));
	root_item_dibuyanghuahenjiance->addChild(child_dibuyanghuahenjiance);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibuyanghuahenjiance, 1, pComboBox_dibuyanghuahenjiance = new QComboBox);
	pComboBox_dibuyanghuahenjiance->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_dibuyanghuahenjiance->addItem(QString::fromLocal8Bit("关闭"));

	child_dibuyanghuahensecha = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差>="));
	root_item_dibuyanghuahenjiance->addChild(child_dibuyanghuahensecha);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibuyanghuahensecha, 1, yanghuahensecha = new QLineEdit);

	child_dibuyanghuahenmianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("面积(OA)>="));
	root_item_dibuyanghuahenjiance->addChild(child_dibuyanghuahenmianji);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibuyanghuahenmianji, 1, OA_yanghuahenmianji = new QLineEdit);

	child_dibuyanghuahenzongmianji = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("总面积(OAS)>="));
	root_item_dibuyanghuahenjiance->addChild(child_dibuyanghuahenzongmianji);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibuyanghuahenzongmianji, 1, OAS_yanghuahenzongmianji = new QLineEdit);

	//底部分色（深）
	root_item_dibufenseshen = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分色（深）"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_dibufenseshen);//将第二层加到第一层下面

	child_dibufenseshen = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分色（深）"));
	root_item_dibufenseshen->addChild(child_dibufenseshen);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibufenseshen, 1, pComboBox_dibufenseshen = new QComboBox);
	pComboBox_dibufenseshen->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_dibufenseshen->addItem(QString::fromLocal8Bit("关闭"));

	child_dibusechashen0 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差0(剔除)"));
	root_item_dibufenseshen->addChild(child_dibusechashen0);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusechashen0, 1, dibusechashen0 = new QLineEdit);

	child_dibusechashen1 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差1"));
	root_item_dibufenseshen->addChild(child_dibusechashen1);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusechashen1, 1, dibusechashen1 = new QLineEdit);

	child_dibusechashen2 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差2"));
	root_item_dibufenseshen->addChild(child_dibusechashen2);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusechashen2, 1, dibusechashen2 = new QLineEdit);

	child_dibusechashen3 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差3"));
	root_item_dibufenseshen->addChild(child_dibusechashen3);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusechashen3, 1, dibusechashen3 = new QLineEdit);

	//底部分色（浅）
	root_item_dibufenseqian = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分色（浅）"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_checking_params_setting->addChild(root_item_dibufenseqian);//将第二层加到第一层下面

	child_dibufenseqian = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("分色（浅）"));
	root_item_dibufenseqian->addChild(child_dibufenseqian);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibufenseqian, 1, pComboBox_dibufenseqian = new QComboBox);
	pComboBox_dibufenseqian->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_dibufenseqian->addItem(QString::fromLocal8Bit("关闭"));

	child_dibusechaqian0 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差0(剔除)"));
	root_item_dibufenseqian->addChild(child_dibusechaqian0);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusechaqian0, 1, dibusechaqian0 = new QLineEdit);

	child_dibufensePRG = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("PRG<=(剔除)"));
	root_item_dibufenseqian->addChild(child_dibufensePRG);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibufensePRG, 1, dibufensePRG = new QLineEdit);

	child_dibufensePB = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("PB<=(剔除)"));
	root_item_dibufenseqian->addChild(child_dibufensePB);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibufensePB, 1, dibufensePB = new QLineEdit);

	child_dibufensePR = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("PR>=(剔除)"));
	root_item_dibufenseqian->addChild(child_dibufensePR);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibufensePR, 1, dibufensePR = new QLineEdit);

	child_dibufensePG = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("PG>=(剔除)"));
	root_item_dibufenseqian->addChild(child_dibufensePG);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibufensePG, 1, dibufensePG = new QLineEdit);

	child_Rdibufense = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("是否重新分色"));
	root_item_dibufenseqian->addChild(child_Rdibufense);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_Rdibufense, 1, pComboBox_Rdibufense = new QComboBox);
	pComboBox_Rdibufense->addItem(QString::fromLocal8Bit("开启"));
	pComboBox_Rdibufense->addItem(QString::fromLocal8Bit("关闭"));

	child_dibusechaqian1 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差1"));
	root_item_dibufenseqian->addChild(child_dibusechaqian1);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusechaqian1, 1, dibusechaqian1 = new QLineEdit);

	child_dibusechaqian2 = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("色差2"));
	root_item_dibufenseqian->addChild(child_dibusechaqian2);
	pTreeWidget_line3_checking_params_stting->setItemWidget(child_dibusechaqian2, 1, dibusechaqian2 = new QLineEdit);

	tabWidget_Set_Line3->addTab(pTreeWidget_line3_checking_params_stting, QString::fromLocal8Bit("检测参数设置"));


	pTreeWidget_line3_model_params_stting = new QTreeWidget(widget3);//新建一个QTreeWidget对象
																	 //设定QTreeWidget树状选项的顶层标题，左边为参数，右边为值
	pTreeWidget_line3_model_params_stting->setHeaderLabels(QStringList() << QString::fromLocal8Bit("参数") << QString::fromLocal8Bit("值"));

	pTreeWidget_line3_model_params_stting->setColumnWidth(0, 2 * COL_WIDTH / 3 - 10);
	pTreeWidget_line3_model_params_stting->setColumnWidth(1, COL_WIDTH / 3);//设定树状选项控件的宽度
																			//此层为第一层
	root_item_line3_model_params_setting = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖底面模板参数"));

	pTreeWidget_line3_model_params_stting->addTopLevelItem(root_item_line3_model_params_setting);

	//皮带颜色设定
	root_item_dibupidaiyanse = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("皮带颜色设定"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_model_params_setting->addChild(root_item_dibupidaiyanse);//将第二层加到第一层下面

	child_dibupidaiyanse = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("皮带颜色"));
	root_item_dibupidaiyanse->addChild(child_dibupidaiyanse);
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibupidaiyanse, 1, pComboBox_dibupidaiyanse = new QComboBox);
	pComboBox_dibupidaiyanse->addItem(QString::fromLocal8Bit("黑皮带"));
	pComboBox_dibupidaiyanse->addItem(QString::fromLocal8Bit("白皮带"));

	//铝盖区域划定及取色
	root_item_dibulvgaiqvyuhuading= new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖区域划定及取色"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_model_params_setting->addChild(root_item_dibulvgaiqvyuhuading);//将第二层加到第一层下面

	QTreeWidgetItem* child_dibuchicunceliangshen = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("尺寸测量及取色(深)"));
	root_item_dibulvgaiqvyuhuading->addChild(child_dibuchicunceliangshen);
	Button_line3_model_dibuchicunceliangshen = new QPushButton(QString::fromLocal8Bit("测量及取色"));//创建按钮
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibuchicunceliangshen, 1, Button_line3_model_dibuchicunceliangshen);

	QTreeWidgetItem* child_dibuchicunceliangqian = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("尺寸测量及取色(浅)"));
	root_item_dibulvgaiqvyuhuading->addChild(child_dibuchicunceliangqian);
	Button_line3_model_dibuchicunceliangqian = new QPushButton(QString::fromLocal8Bit("测量及取色"));//创建按钮
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibuchicunceliangqian, 1, Button_line3_model_dibuchicunceliangqian);

	//铝盖区域分割
	root_item_dibulvgaiqvyufenge = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖区域分割"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_model_params_setting->addChild(root_item_dibulvgaiqvyufenge);//将第二层加到第一层下面

	child_dibulvgaihuiduzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖灰度值"));
	root_item_dibulvgaiqvyufenge->addChild(child_dibulvgaihuiduzhi);
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibulvgaihuiduzhi, 1, new QSlider(Qt::Horizontal));

	child_dibuyahuanhuiduzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("压环灰度值"));
	root_item_dibulvgaiqvyufenge->addChild(child_dibuyahuanhuiduzhi);
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibuyahuanhuiduzhi, 1, new QSlider(Qt::Horizontal));

	//商标建模
	root_item_shangbiaojianmo = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("商标建模"));//创建一个新的QTreeWidgetItem（第二层）
	root_item_line3_model_params_setting->addChild(root_item_shangbiaojianmo);//将第二层加到第一层下面

	child_dibushangbiaojianmo = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("是否存在商标"));
	root_item_shangbiaojianmo->addChild(child_dibushangbiaojianmo);
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibushangbiaojianmo, 1, pComboBox_dibupidaiyanse = new QComboBox);
	pComboBox_dibupidaiyanse->addItem(QString::fromLocal8Bit("是"));
	pComboBox_dibupidaiyanse->addItem(QString::fromLocal8Bit("否"));

	QTreeWidgetItem* child_huadingchuanciqv = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("划定穿刺区"));
	root_item_shangbiaojianmo->addChild(child_huadingchuanciqv);
	Button_line3_model_huadingchuanciqv = new QPushButton(QString::fromLocal8Bit("划定穿刺区"));//创建按钮
	pTreeWidget_line3_model_params_stting->setItemWidget(child_huadingchuanciqv, 1, Button_line3_model_huadingchuanciqv);

	child_dibujianmohuiduzhi = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("建模灰度值"));
	root_item_shangbiaojianmo->addChild(child_dibujianmohuiduzhi);
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibujianmohuiduzhi, 1, new QSlider(Qt::Horizontal));

	//铝盖压环区域划定列表
	root_item_dibulvgaiyahuanqvyu = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("铝盖压环区域划定"));
	root_item_line3_model_params_setting->addChild(root_item_dibulvgaiyahuanqvyu);

	child_dibuyitianjiayahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("已添加压环数"));
	root_item_dibulvgaiyahuanqvyu->addChild(child_dibuyitianjiayahuan);
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibuyitianjiayahuan, 1, new QLabel(QString::fromLocal8Bit("1")));//需要调用变量，目前用文字代替

	QTreeWidgetItem* child_dibutianjiayahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("添加压环"));
	root_item_dibulvgaiyahuanqvyu->addChild(child_dibutianjiayahuan);
	Button_line3_model_tianjiayahuan = new QPushButton(QString::fromLocal8Bit("添加压环"));//创建按钮
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibutianjiayahuan, 1, Button_line3_model_tianjiayahuan);

	QTreeWidgetItem* child_dibuxiugaiyahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("修改压环"));
	root_item_dibulvgaiyahuanqvyu->addChild(child_dibuxiugaiyahuan);
	Button_line3_model_xiugaiyahuan = new QPushButton(QString::fromLocal8Bit("修改压环"));//创建按钮
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibuxiugaiyahuan, 1, Button_line3_model_xiugaiyahuan);

	QTreeWidgetItem* child_dibushanchuyahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("删除压环"));
	root_item_dibulvgaiyahuanqvyu->addChild(child_dibushanchuyahuan);
	Button_line3_model_shanchuyahuan = new QPushButton(QString::fromLocal8Bit("删除压环"));//创建按钮
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibushanchuyahuan, 1, Button_line3_model_shanchuyahuan);

	QTreeWidgetItem* child_dibuxianshiyahuan = new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("显示压环"));
	root_item_dibulvgaiyahuanqvyu->addChild(child_dibuxianshiyahuan);
	Button_line3_model_xianshiyahuan = new QPushButton(QString::fromLocal8Bit("显示压环"));//创建按钮
	pTreeWidget_line3_model_params_stting->setItemWidget(child_dibuxianshiyahuan, 1, Button_line3_model_xianshiyahuan);

	tabWidget_Set_Line3->addTab(pTreeWidget_line3_model_params_stting, QString::fromLocal8Bit("模板参数设置"));

}

void QtModelSet::ConnetSlot()
{
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(ChangeList(int)));
	connect(Button_Show_Model, SIGNAL(clicked()), this, SLOT(_Button_Show_Model()));
	connect(Button_Show_Online, SIGNAL(clicked()), this, SLOT(_Button_Show_Online()));
	connect(Button_Set_As_Model, SIGNAL(clicked()), this, SLOT(_Button_Set_As_Model()));
	connect(Button_Show_Model1, SIGNAL(clicked()), this, SLOT(_Button_Show_Model1()));
	connect(Button_Show_Online1, SIGNAL(clicked()), this, SLOT(_Button_Show_Online1()));
	connect(Button_Set_As_Model1, SIGNAL(clicked()), this, SLOT(_Button_Set_As_Model1()));
	connect(Button_Show_Model2, SIGNAL(clicked()), this, SLOT(_Button_Show_Model2()));
	connect(Button_Show_Online2, SIGNAL(clicked()), this, SLOT(_Button_Show_Online2()));
	connect(Button_Set_As_Model2, SIGNAL(clicked()), this, SLOT(_Button_Set_As_Model2()));
	connect(Button_One_Key_Detect, SIGNAL(clicked()), this, SLOT(_Button_One_Key_Detect()));
	connect(Button_Save_Current_Line_Model, SIGNAL(clicked()), this, SLOT(_Button_Save_Current_Line_Model()));
	connect(Button_Save_Model, SIGNAL(clicked()), this, SLOT(_Button_Save_Model()));
	connect(Button_Quit, SIGNAL(clicked()), this, SLOT(_Button_Quit()));
	connect(Button_Load_Current_Model, SIGNAL(clicked()), this, SLOT(_Button_Load_Current_Model()));
	connect(Button_Model_List, SIGNAL(clicked()), this, SLOT(_Button_Model_List()));
}

//当点击widget的时候更换设置列表
void QtModelSet::ChangeList(int selected)
{
	switch (selected)
	{
	case 0:
		tabWidget_Set_Line2->setHidden(true);
		tabWidget_Set_Line3->setHidden(true);
		tabWidget_Set_Line1->setHidden(false); break;
	case 1:
		tabWidget_Set_Line2->setHidden(false);
		tabWidget_Set_Line3->setHidden(true);
		tabWidget_Set_Line1->setHidden(true); break;
	case 2:
		tabWidget_Set_Line2->setHidden(true);
		tabWidget_Set_Line3->setHidden(false);
		tabWidget_Set_Line1->setHidden(true); break;
	default:break;
	}
}

void QtModelSet::_Button_Show_Model()
{

//	QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
}

void QtModelSet::setValue(int a){
	isParaChanged = true;
	using namespace Halcon;
	Hobject  Image, Regions, Red, Green, Blue, Hue, inner, ConnectedRegions, MaxArea;
	Hobject  Saturation, Intensity, Saturated, ContoursSplit;
	Hobject  SortedContours, ObjectSelected;
	try {
		set_check("~give_error");
		set_draw(m_disp_hd.at(0), "fill");
		set_color(m_disp_hd.at(0),"red");
		Halcon::Hobject hobj, GrayImage;

		Halcon::decompose3(m_disp_image.at(0), &Red, &Green, &Blue);
		trans_from_rgb(Red, Green, Blue, &Hue, &Saturation, &Intensity, "hsv");
		threshold(Saturation, &inner, a, 255);
		h_disp_obj(m_disp_image.at(0), m_disp_hd.at(0));
		h_disp_obj(inner, m_disp_hd.at(0));

		Preference::GetIns()->prj->para_bak.threshold_back_cap = a;
		std::cout << "value:" << a << std::endl;
	}
	catch (Halcon::HException e)
	{
		std::cout << "error" << std::endl;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
}


void QtModelSet::_Show_Online_Effect() {

}

void QtModelSet::_Button_Show_Online()
{

	Machine::GetIns()->m_mc->Write_Output_Ex(0, OUT_CAM1, 1);
	try {
		Halcon::set_check("~give_error");
		//很奇怪的问题，上升沿和下降沿都能够充足曝光？？？？？
		Sleep(1);
		SnapHobj(m_disp_image.at(0), 0, 0, 10);
		h_disp_obj(m_disp_image.at(0), m_disp_hd.at(0));
	} 
	catch (Halcon::HException e)
	{
		std::cout << "failed to capture" << std::endl;
	}
	catch (std::out_of_range out)
	{
		std::cout << out.what() << std::endl;
	}
	Machine::GetIns()->m_mc->Write_Output_Ex(0, OUT_CAM1, 0);
}

void QtModelSet::_Button_Set_As_Model()
{
	QString image_path = Preference::GetIns()->sys->para.Project_Name + "/line1";
	QDir dir(image_path);
	if (!dir.exists())
	{
		QDir d; d.mkdir(image_path);
		std::cout <<" making " <<image_path.toLatin1().data() << " directory"<< std::endl;
	}
	
	try {
		Halcon::set_check("~give_error");
		MSerials::Tools::h_write_image(m_disp_image.at(0),image_path.toLatin1().data());
	}
	catch (Halcon::HException he)
	{
		std::cout << "can not save image" << std::endl;
	}
	return;

	QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.bmp *.jpg *.jpeg *.png *.gif *.tiff)"));
	if (path.length() == 0) return;
	QByteArray ba = path.toLocal8Bit();
	Halcon::Hobject image;
	Halcon::read_image(&image, ba.data());
	Machine::GetIns()->h_disp_obj(image, m_disp_hd.at(0));
}

void QtModelSet::_Button_Show_Model1()
{
}

void QtModelSet::_Show_Online_Effect1()
{
}

void QtModelSet::_Button_Show_Online1()
{
	Machine::GetIns()->m_mc->Write_Output_Ex(0, OUT_CAM2, 1);
	try {
		Halcon::set_check("~give_error");
		Sleep(1);
		SnapHobj(m_disp_image.at(1), 0, 1, 10);
		h_disp_obj(m_disp_image.at(1), m_disp_hd.at(1));
	}
	catch (Halcon::HException e)
	{
		Halcon::set_tposition(m_disp_hd.at(1),1,1);
		Halcon::write_string(m_disp_hd.at(1),"no image");
		std::cout << "failed to capture" << std::endl;
	}
	catch (std::out_of_range out)
	{
		std::cout << out.what() << std::endl;
	}
	Machine::GetIns()->m_mc->Write_Output_Ex(0, OUT_CAM2, 0);

}

void QtModelSet::_Button_Set_As_Model1()
{
}

void QtModelSet::_Button_Show_Model2()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.bmp *.jpg *.jpeg *.png *.gif *.tiff)"));
	if (path.length() == 0) return;

	QByteArray ba = path.toLocal8Bit();

	Halcon::Hobject image;
	Halcon::read_image(&image, ba.data());
	Machine::GetIns()->h_disp_obj(image, m_disp_hd.at(2));
}

void QtModelSet::_Show_Online_Effect2()
{
}

void QtModelSet::_Button_Show_Online2()
{
	//bug
	//bug 3  OUT_CAM2 | OUT_CAM3 应该替换成OUT_CAM3
	Machine::GetIns()->m_mc->Write_Output_Ex(0, OUT_CAM2 | OUT_CAM3, 1);
	int disp = 2;
	try {
		Halcon::set_check("~give_error");
		Sleep(1);
		SnapHobj(m_disp_image.at(1), 0, 1, 10);
		h_disp_obj(m_disp_image.at(1), m_disp_hd.at(disp));
	}
	catch (Halcon::HException e)
	{
		Halcon::set_tposition(m_disp_hd.at(disp), 1, 1);
		Halcon::write_string(m_disp_hd.at(disp), "no image");
		std::cout << "failed to capture" << std::endl;
	}
	catch (std::out_of_range out)
	{
		std::cout << out.what() << std::endl;
	}
	Machine::GetIns()->m_mc->Write_Output_Ex(0, OUT_CAM2 | OUT_CAM3, 0);
}

void QtModelSet::_Button_Set_As_Model2()
{
	QString image_path = Preference::GetIns()->sys->para.Project_Name + "/line3";
	QDir dir(image_path);
	if (!dir.exists())
	{
		QDir d; d.mkdir(image_path);
		std::cout << " making " << image_path.toLatin1().data() << " directory" << std::endl;
	}

	try {
		Halcon::set_check("~give_error");
		MSerials::Tools::h_write_image(m_disp_image.at(1), image_path.toLatin1().data());
	}
	catch (Halcon::HException he)
	{
		std::cout << "can not save image" << std::endl;
	}
	return;

#define POS_DETECT_COLOR 2
	using namespace Halcon;
	if (Machine::NO_RECT != Machine::GetIns()->RectInfo)
	{
		QMessageBox::information(NULL, tr("information"), Machine::show_rect_info(Machine::GetIns()->RectInfo));
		return;
	}
#if 0
	EndThread(5);
	Halcon::HTuple  Exception;
	set_check("~give_error");
	try
	{
		Machine::GetIns()->RectInfo = Machine::CRICLE;
		double row, col, radius;
		Hobject ROI;
		Halcon::set_color(m_disp_hd[POS_DETECT_COLOR], "green");
		set_draw(m_disp_hd[POS_DETECT_COLOR], "margin");
		draw_circle(m_disp_hd[POS_DETECT_COLOR], &row, &col, &radius);
		gen_circle(&ROI, row, col, radius);
		disp_obj(ROI, m_disp_hd[POS_DETECT_COLOR]);
		Preference::GetIns()->prj->Color_Circle.r = row;
		Preference::GetIns()->prj->Color_Circle.c = col;
		Preference::GetIns()->prj->Color_Circle.radius = radius;
		Preference::GetIns()->prj->WriteSettings(PARA_IMAGE);
		Machine::GetIns()->RectInfo = Machine::NO_RECT;
	}
	catch (HException except)
	{
		write_string(m_disp_hd[POS_DETECT_COLOR], except.message);
	}
#endif
}


void QtModelSet::_Button_One_Key_Detect()
{
	//一键检测
	try {
		clock_t tick = clock();
		Machine::GetIns()->back_cap_detect(m_disp_image.at(0), m_disp_hd.at(0), Preference::GetIns()->prj->para);
		std::cout << "cost first camera time is " << (clock() - tick) << " ms" << std::endl;
	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << std::endl;
	}
}

void QtModelSet::_Button_Save_Current_Line_Model()
{
}

void QtModelSet::_Button_Save_Model()
{
}

void QtModelSet::_Button_Quit()
{
}

void QtModelSet::_Button_Load_Current_Model()
{
}

void QtModelSet::_Button_Model_List()
{
}




//初始化界面
void QtModelSet::OnInitDialog()
{
	m_vec_scrollArea.push_back(scrollArea);
	m_vec_scrollArea.push_back(scrollArea1);
	m_vec_scrollArea.push_back(scrollArea2);
	Halcon::set_check("give_error");
	for (size_t i = 0; i < m_vec_scrollArea.size(); i++){
		HTuple disp_hand;
		Halcon::set_check("~father");
		Halcon::open_window(0,0,m_vec_scrollArea[0]->width(), m_vec_scrollArea[0]->height(),(Hlong)m_vec_scrollArea[i]->winId(),"visible","",&disp_hand);
		m_disp_hd.push_back(disp_hand);

	}	
	for (int i = 0; i < MAX_CAM; i++){
		Hobject a;
		m_disp_image.push_back(a);
	}
}

//关闭按钮进行选择
void QtModelSet::closeEvent(QCloseEvent *ev)
{
	if (isParaChanged != true) {
		ev->accept();
		return;
	}
	QuitTipDlg QtMDlg;
	QtMDlg.exec();
	int res = QtMDlg.Sel();
	switch (res) {
	case QuitTipDlg::CANCEL:ev->ignore();break;
	case QuitTipDlg::QUIT:ev->accept(); break;
	case QuitTipDlg::QUITANDSAVE:
		//进行参数更新
		Preference::GetIns()->prj->para = Preference::GetIns()->prj->para_bak;
		Preference::GetIns()->prj->WriteSettings();
		ev->accept();
		break;
	default:ev->ignore(); break;
	}
}
