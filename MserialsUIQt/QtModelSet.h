#pragma once


#include <QDialog>
#include "ui_QtModelSet.h"
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QTextEdit>
#include <qcombobox>
#include <memory>
#include "Machine.h"
#include "../MSerialsCommon/common.h"

class QSlider;


class QtModelSet : public QDialog
{
	Q_OBJECT

public:
	QtModelSet(QWidget *parent = Q_NULLPTR);
	~QtModelSet();

	bool isParaChanged = false;

	void UpDataUI();

	void InitUI();

	void InitWidgets();

	void InitWidget();

	void initSetParamsControl();

	void Line1_Settings();

	void Line2_Settings();

	void Line3_Settings();

	void ConnetSlot();
	void OnInitDialog();
	void closeEvent(QCloseEvent * ev);
	void showFileInfoList(QFileInfoList list);

private:	

	Ui::QtModelSet *ui;
	//
	QGridLayout *pGridLayout;
	///<视频widget
	QTabWidget	*tabWidget;

	QSlider *slider;
	
	QSlider *slider_pinggaihuiduzhi = nullptr;


	//线路一的tab设置
	QTabWidget	*tabWidget_Set_Line1;
	//线路二的tab设置
	QTabWidget	*tabWidget_Set_Line2;
	//线路三的tab设置
	QTabWidget	*tabWidget_Set_Line3;

	QScrollArea *scrollArea;
	QScrollArea *scrollArea1;
	QScrollArea *scrollArea2;
	///<线路1显示图片
	QLabel	*label;
	QPushButton *Button_Show_Model;
	QPushButton *Button_Show_Online;
	QPushButton *Button_Set_As_Model;
	QPushButton *Button_Set_As_Draw;

	//图像浏览器
	std::auto_ptr<QLineEdit> fileLineEdit;
	std::auto_ptr<QListWidget> fileListWidget;
	std::auto_ptr<QVBoxLayout> vLayout;
	QFileInfoList list;
	QFileInfoList list1;
	QFileInfoList listroot;
	QLabel *label_brower;
	std::auto_ptr<QComboBox> DiskDir;


	QLabel	*label1;
	QPushButton *Button_Show_Model1;
	QPushButton *Button_Show_Online1;
	QPushButton *Button_Set_As_Model1;

	QLabel *label2;
	QPushButton *Button_Show_Model2;
	QPushButton *Button_Show_Online2;
	QPushButton *Button_Set_As_Model2;
	///<参数设置widget
	QScrollArea *ParaWidget;
	QTabWidget *tabWidget1;

	///<下方检测按钮
	QPushButton *Button_One_Key_Detect;
	QPushButton *Button_Save_Current_Line_Model;
	QPushButton *Button_Save_Model;
	QPushButton *Button_Quit;
	QPushButton *Button_Load_Current_Model;
	QPushButton *Button_Model_List;


	//线路一按钮
	QPushButton *Button_line1_model_chicunceliang;
	QPushButton *Button_line1_model_chuancibanjing;
	QPushButton *Button_line1_model_qvyubanjing;
	QPushButton *Button_line1_model_tianjiayahuan;
	QPushButton *Button_line1_model_xiugaiyahuan;
	QPushButton *Button_line1_model_shanchuyahuan;
	QPushButton *Button_line1_model_xianshiyahuan;		

public slots:
	void bianxingjianceChanged();
	void lvgaileixingChanged();
	void silakoupingbi();
	void pinggaihuiduzhiChanged(int);
	void ChangeList(int);

	void _Button_Show_Model();
	void setValue(int a);
	//线路1显示图片处理效果
	void _Show_Online_Effect();
	//线路1按钮显示图片
	void _Button_Show_Online();
	//线路1设置模型
	void _Button_Set_As_Model();
	

	void _Button_Show_Model1();
	//线路2显示图片处理效果
	void _Show_Online_Effect1();

	void _Button_Show_Online1();
	void _Button_Set_As_Model1();

	void _Button_Show_Model2();
	//线路3显示图片处理效果
	void _Show_Online_Effect2();

	void _Button_Show_Online2();
	void _Button_Set_As_Model2();
	///<参数设置widget

	///<下方检测按钮
	void _Button_One_Key_Detect();
	void _Button_Save_Current_Line_Model();
	void _Button_Save_Model();
	void _Button_Quit();
	void _Button_Load_Current_Model();
	void _Button_Model_List();
	//本地图片浏览器
	//--显示当前目录下的所有文件
	void slotShow(QDir dir);

	//----根据选择显示下一级目录下的文件，
	void slotDirShow(QListWidgetItem *Item);
	void slotDiskDirShow();

private:
	std::vector<QScrollArea*> m_vec_scrollArea;
	//每个相机给定一个disp_hand
	std::vector<Halcon::HTuple> m_disp_hd;
	std::vector<Halcon::Hobject> m_disp_image;
	Halcon::Hobject Image;


	HANDLE hThread[MAX_DEVICE_NUM];
	//终止线程
	int hThreadExit[MAX_DEVICE_NUM];

	//第一路检测参数设置
	QTreeWidgetItem * root_item_line1_checking_params_setting = nullptr;
	QTreeWidget		* pTreeWidget_line1_checking_params_stting = nullptr;
	//第一路模板参数设置
	QTreeWidgetItem * root_item_line1_model_params_setting = nullptr;
	QTreeWidget		* pTreeWidget_line1_model_params_stting = nullptr;

	//变形监测，root
	QTreeWidgetItem * root_item_shape = nullptr;
	//铝盖类型，root
	QTreeWidgetItem * root_item_type = nullptr;
	//皮带颜色设定
	QTreeWidgetItem * root_item_pidaiyanse = nullptr;

	//铝盖区域划定
	QTreeWidgetItem * root_item_lvgaiqvyuhuading = nullptr;
	//铝盖区域分割
	QTreeWidgetItem * root_item_lvgaiqvyufenge = nullptr;
	//铝盖压环区域划定列表
	QTreeWidgetItem * root_item_lvgaiyahuanqvyu = nullptr;



	//铝盖类型
	QComboBox*	pComboBox_lvgaileixing = nullptr;



	//铝盖颜色
	QComboBox*	pComboBox_lvgaiyanse = nullptr;

	//铝盖颜色
	QComboBox*	pComboBox_tiqvfangshi = nullptr;

	//皮带颜色
	QComboBox*	pComboBox_pidaiyanse = nullptr;

	//瓶口圆度 指更改

	//瓶口变形度

	//外凸距离

	//内凹距离

	//商标匹配度

	//线路1设置参数列表

	//变形检测，开启关闭
	QComboBox*	pComboBox_bianxingjiance = nullptr;
	QTreeWidgetItem* child_silakou = nullptr;

	//撕拉口屏蔽，开启关闭
	QComboBox* pComboBox_silakoupingbi = nullptr;

	QTreeWidgetItem* child_pingkouyuandu = nullptr;
	QLineEdit* LE_pingkouyuandu = nullptr;

	QTreeWidgetItem* child_pingkoubianxingdu = nullptr;
	QLineEdit *LE_pingkoubianxingdu = nullptr;

	QTreeWidgetItem* child_waitujuli = nullptr;
	QLineEdit *LE_waitujuli = nullptr;

	QTreeWidgetItem* child_neiaojuli = nullptr;
	QLineEdit *LE_neiaojuli = nullptr;


	QTreeWidgetItem* child_shangbiaopipei = nullptr;

	QTreeWidgetItem* child_baiyisedian = nullptr;

	QTreeWidgetItem* child_secha = nullptr;

	QTreeWidgetItem* child_mianji = nullptr;

	QTreeWidgetItem* child_huangban = nullptr;

	QTreeWidgetItem* child_xiaoaokeng = nullptr;

	QTreeWidgetItem* child_huiduzhi = nullptr;

	QTreeWidgetItem* child_dibuhuiduzhi = nullptr;

	QTreeWidgetItem* child_dibufuzhuhuiduzhi = nullptr;

	QTreeWidgetItem* child_pinbifengebaocuo = nullptr;

	QTreeWidgetItem* child_cunzaishangbiao = nullptr;

	QTreeWidgetItem* child_shangbiaojianmo = nullptr;

	QTreeWidgetItem* child_yitianjiayahuan = nullptr;

	QTreeWidgetItem* child_tianjiayahuan = nullptr;

	QTreeWidgetItem* child_xiugaijiayahuan = nullptr;

	QTreeWidgetItem* child_shanchujiayahuan = nullptr;

	QTreeWidgetItem* child_xiugaiyahuan = nullptr;

	QComboBox* pComboBox_dingaojiance = nullptr;
	QTreeWidgetItem* child_dingaosecha = nullptr;
	QSlider* slider_dingaosecha = nullptr;

	QComboBox* pComboBox_chuancijiance = nullptr;
	QComboBox* pComboBox_baigaijiance = nullptr;
	QComboBox* pComboBox_hunxingjiance = nullptr;
	QComboBox* pComboBox_tichulvgai = nullptr;
	QComboBox* pComboBox_cunzaishangbiao = nullptr;
	QComboBox* pComboBox_pinbifengebaocuo = nullptr;

	//第二路检测参数设置
	QTreeWidgetItem * root_item_line2_checking_params_setting = nullptr;
	QTreeWidget		* pTreeWidget_line2_checking_params_stting = nullptr;
	QTreeWidgetItem * root_item_line2_model_params_setting = nullptr;
	QTreeWidget		* pTreeWidget_line2_model_params_stting = nullptr;

	//树状列表项目2
	QTreeWidgetItem* child_yahenfenge = nullptr;
	QTreeWidgetItem* child_gunhuajiance = nullptr;
	QTreeWidgetItem* child_gunhuasecha = nullptr;
	QTreeWidgetItem* child_koubuxingzhuangjiance = nullptr;
	QTreeWidgetItem* child_koubujiaodu = nullptr;
	QTreeWidgetItem* child_koububianxingdu = nullptr;
	QTreeWidgetItem* child_bianxingmianji = nullptr;
	QTreeWidgetItem* child_queliaojiance = nullptr;
	QTreeWidgetItem* child_queliaomianji = nullptr;
	QTreeWidgetItem* child_dazhoujiance = nullptr;
	QTreeWidgetItem* child_dazhousecha= nullptr;
	QTreeWidgetItem* child_baibanjiance = nullptr;
	QTreeWidgetItem* child_baibanhuidu = nullptr;
	QTreeWidgetItem* child_baibanhuidu2 = nullptr;
	QTreeWidgetItem* child_baibansecha = nullptr;
	QTreeWidgetItem* child_mianjiBA = nullptr;
	QTreeWidgetItem* child_mianjiWSA = nullptr;
	QTreeWidgetItem* child_waicezangjiance = nullptr;
	QTreeWidgetItem* child_waicehuiduzhi = nullptr;
	QTreeWidgetItem* child_waicesecha = nullptr;
	QTreeWidgetItem* child_yanghuahenjiance = nullptr;
	QTreeWidgetItem* child_yanghuahensecha = nullptr;
	QTreeWidgetItem* child_yanghuahenmianji = nullptr;
	QTreeWidgetItem* child_yanghuahenzmianji = nullptr;
	QTreeWidgetItem* child_waicehuashangjiance = nullptr;	
	QTreeWidgetItem* child_waicehuangshangsecha = nullptr;
	QTreeWidgetItem* child_huangshangchangdu = nullptr;
	QTreeWidgetItem* child_baizangdianjiance = nullptr;
	QTreeWidgetItem* child_baisecha = nullptr;
	QTreeWidgetItem* child_baimianji = nullptr;
	QTreeWidgetItem* child_heizangdianjiance = nullptr;
	QTreeWidgetItem* child_heisecha = nullptr;
	QTreeWidgetItem* child_heimianji = nullptr;
	QTreeWidgetItem* child_lvgaizhengtifenge = nullptr;
	QTreeWidgetItem* child_lvgaikoubufenge = nullptr;
	QTreeWidgetItem* child_lvgaikoubufengefuzhu = nullptr;
	QTreeWidgetItem* child_lvgaidibufenge = nullptr;
	QTreeWidgetItem* child_silakoufenge = nullptr;

	//树状列表项目root2

	//压痕分割
	QTreeWidgetItem*  root_item_yahenfenge = nullptr;
	//滚花检测
	QTreeWidgetItem*  root_item_genhuajiance = nullptr;
	//铝盖口部形状检测
	QTreeWidgetItem*  root_item_koubuxingzhuangjiance = nullptr;
	//铝盖口部缺料检测
	QTreeWidgetItem*  root_item_koubuqueliaojiance = nullptr;
	//大皱检测
	QTreeWidgetItem*  root_item_dazhoujiance = nullptr;
	//白斑检测
	QTreeWidgetItem*  root_item_baibanjiance = nullptr;
	//外侧脏检测
	QTreeWidgetItem*  root_item_waicezangjiance = nullptr;
	//铝盖外侧氧化痕检测
	QTreeWidgetItem*  root_item_waiceyanghuahenjiance = nullptr;
	//铝盖外侧划伤检测
	QTreeWidgetItem*  root_item_waicehuashangjiance = nullptr;
	//铝盖内侧脏检测
	QTreeWidgetItem*  root_item_neicezangjiance = nullptr;
	//铝盖类型设定列表
	QTreeWidgetItem*  root_item_lvgaileixing2 = nullptr;
	//铝盖区域划定列表
	QTreeWidgetItem*  root_item_lvgaiqvyuhuading2 = nullptr;
	//铝盖整体分割
	QTreeWidgetItem*  root_item_lvgaizhengtifenge = nullptr;
	//铝盖口部分割
	QTreeWidgetItem*  root_item_lvgaikoubufenge = nullptr;
	//铝盖底部分割
	QTreeWidgetItem*  root_item_lvgaidibufenge = nullptr;
	//撕拉口分割
	QTreeWidgetItem*  root_item_silakoufenge = nullptr;



	//下拉框2
	QComboBox* pComboBox_yahenfenge = nullptr;
	QComboBox* pComboBox_gunhuajiance = nullptr;
	QComboBox* pComboBox_koubuxingzhuangjiance = nullptr;
	QComboBox* pComboBox_queliaojiance = nullptr;
	QComboBox* pComboBox_dazhoujiance = nullptr;
	QComboBox* pComboBox_baibanjiance = nullptr;
	QComboBox* pComboBox_waicezangjiance = nullptr;
	QComboBox* pComboBox_yanghuahenjiance = nullptr;
	QComboBox* pComboBox_waicehuashangjiance = nullptr;
	QComboBox* pComboBox_baizangdianjiance = nullptr;
	QComboBox* pComboBox_heizangdianjiance = nullptr;
	QComboBox* pComboBox_lvgaileixing2 = nullptr;
	QComboBox* pComboBox_lvgaiyanse2 = nullptr;
	QComboBox* pComboBox_cemianlvgaileixing = nullptr;





	//文本输入框2
	QLineEdit *Phi_koubujiaodu = nullptr;
	QLineEdit *DF_koububianxingdu = nullptr;
	QLineEdit *DFA_bianxingmianji = nullptr;
	QLineEdit *GA_queliaomianji = nullptr;
	QLineEdit *baibansecha = nullptr;
	QLineEdit *BA_mianji = nullptr;
	QLineEdit *WSA_mianji = nullptr;
	QLineEdit *waice_seca = nullptr;
	QLineEdit *yanghuahen_seca = nullptr;
	QLineEdit *DA_mianji = nullptr;
	QLineEdit *DAS_mianji = nullptr;
	QLineEdit *OW_huashangchangdu = nullptr;
	QLineEdit *IDA_baimianji = nullptr;
	QLineEdit *IBA_heimianji = nullptr;

	//按钮2
	QPushButton *Button_line2_model_cemianlvgaiqvyu;
	QPushButton *Button_line2_model_cemianlvgaiqvse;

	//滑动条2
	QSlider* slider_silakoufenge = nullptr;

	//第三路检测参数设置
	QTreeWidgetItem * root_item_line3_checking_params_setting = nullptr;
	QTreeWidget		* pTreeWidget_line3_checking_params_stting = nullptr;
	QTreeWidgetItem * root_item_line3_model_params_setting = nullptr;
	QTreeWidget		* pTreeWidget_line3_model_params_stting = nullptr;

	//树状选项项目root3
	QTreeWidgetItem*  root_item_dibubianxingjiance = nullptr;
	QTreeWidgetItem*  root_item_hungaijiance = nullptr;
	QTreeWidgetItem*  root_item_dibusechajiance = nullptr;
	QTreeWidgetItem*  root_item_banbianhuagaijiance = nullptr;
	QTreeWidgetItem*  root_item_baiyisedianjiance = nullptr;
	QTreeWidgetItem*  root_item_heiyisedianjiance = nullptr;
	QTreeWidgetItem*  root_item_dibuyanghuahenjiance = nullptr;
	QTreeWidgetItem*  root_item_dibufenseshen = nullptr;
	QTreeWidgetItem*  root_item_dibufenseqian = nullptr;
	QTreeWidgetItem*  root_item_dibupidaiyanse = nullptr;
	QTreeWidgetItem*  root_item_dibulvgaiqvyuhuading = nullptr;
	QTreeWidgetItem*  root_item_dibulvgaiqvyufenge = nullptr;
	QTreeWidgetItem*  root_item_shangbiaojianmo = nullptr;
	QTreeWidgetItem * root_item_dibulvgaiyahuanqvyu = nullptr;


	//树状选项项目3
	QTreeWidgetItem* child_dibubianxingjiance = nullptr;
	QTreeWidgetItem* child_pingkouyuanduC = nullptr;
	QTreeWidgetItem* child_waitujuliD1 = nullptr;
	QTreeWidgetItem* child_neiaojuliD2 = nullptr;
	QTreeWidgetItem* child_shangbiaopipeidu = nullptr;
	QTreeWidgetItem* child_hungaijiance = nullptr;
	QTreeWidgetItem* child_hungaisecha = nullptr;
	QTreeWidgetItem* child_shangbiaogaodu = nullptr;
	QTreeWidgetItem* child_dibusechajiance = nullptr;
	QTreeWidgetItem* child_dibusecha = nullptr;
	QTreeWidgetItem* child_banbianhuagaijiance = nullptr;
	QTreeWidgetItem* child_baiyisedianjiance = nullptr;
	QTreeWidgetItem* child_baiyisedianhuiduzhi = nullptr;
	QTreeWidgetItem* child_baiyisediansecha = nullptr;
	QTreeWidgetItem* child_baiyisedianmianji = nullptr;
	QTreeWidgetItem* child_baiyisedianzongmianji = nullptr;
	QTreeWidgetItem* child_heiyisedianjiance = nullptr;
	QTreeWidgetItem* child_heiyisediansecha = nullptr;
	QTreeWidgetItem* child_heiyisedianmianji = nullptr;
	QTreeWidgetItem* child_heiyisedianzongmianji = nullptr;
	QTreeWidgetItem* child_dibuyanghuahenjiance = nullptr;
	QTreeWidgetItem* child_dibuyanghuahensecha = nullptr;
	QTreeWidgetItem* child_dibuyanghuahenmianji = nullptr;
	QTreeWidgetItem* child_dibuyanghuahenzongmianji = nullptr;
	QTreeWidgetItem* child_dibufenseshen = nullptr;
	QTreeWidgetItem* child_dibusechashen0 = nullptr;
	QTreeWidgetItem* child_dibusechashen1 = nullptr;
	QTreeWidgetItem* child_dibusechashen2 = nullptr;
	QTreeWidgetItem* child_dibusechashen3 = nullptr;
	QTreeWidgetItem* child_dibufenseqian = nullptr;
	QTreeWidgetItem* child_dibusechaqian0 = nullptr;
	QTreeWidgetItem* child_dibusechaqian1 = nullptr;
	QTreeWidgetItem* child_dibusechaqian2 = nullptr;
	QTreeWidgetItem* child_dibufensePRG = nullptr;
	QTreeWidgetItem* child_dibufensePB = nullptr;
	QTreeWidgetItem* child_dibufensePG = nullptr;
	QTreeWidgetItem* child_dibufensePR = nullptr;
	QTreeWidgetItem* child_Rdibufense = nullptr;
	QTreeWidgetItem* child_dibupidaiyanse = nullptr;
	QTreeWidgetItem* child_dibuchicunceliangshen = nullptr;
	QTreeWidgetItem* child_dibulvgaihuiduzhi = nullptr;
	QTreeWidgetItem* child_dibuyahuanhuiduzhi = nullptr;
	QTreeWidgetItem* child_dibushangbiaojianmo = nullptr;
	QTreeWidgetItem* child_dibujianmohuiduzhi = nullptr;
	QTreeWidgetItem* child_dibuyitianjiayahuan = nullptr;



	//下拉框3
	QComboBox* pComboBox_dibubianxingjiance = nullptr;
	QComboBox* pComboBox_hungaijiance = nullptr;
	QComboBox* pComboBox_dibusechajiance = nullptr;
	QComboBox* pComboBox_banbianhuagaijiance = nullptr;
	QComboBox* pComboBox_baiyisedianjiance = nullptr;
	QComboBox* pComboBox_heiyisedianjiance = nullptr;
	QComboBox* pComboBox_dibuyanghuahenjiance = nullptr;
	QComboBox* pComboBox_dibufenseshen = nullptr;
	QComboBox* pComboBox_dibufenseqian = nullptr;
	QComboBox* pComboBox_Rdibufense = nullptr;
	QComboBox* pComboBox_dibupidaiyanse = nullptr;
	QComboBox* pComboBox_shangbiaojianmo = nullptr;



	//文本输入框3	
	QLineEdit *C_pingkouyuandu = nullptr;
	QLineEdit *D1_waitujuli = nullptr;
	QLineEdit *D2_neiaojuli = nullptr;
	QLineEdit *shangbiaopipeidu = nullptr;
	QLineEdit *CD_hungaisecha = nullptr;
	QLineEdit *TH_shangbiaogaodu = nullptr;
	QLineEdit *CD_dibusecha = nullptr;
	QLineEdit *baiyisediansecha = nullptr;
	QLineEdit *DA_heiyisedianmianji = nullptr;
	QLineEdit *DAS_heiyisedianzongmianji = nullptr;
	QLineEdit *LA_baiyisedianmianji = nullptr;
	QLineEdit *LAS_baiyisedianzongmianji = nullptr;
	QLineEdit *heiyisediansecha = nullptr;
	QLineEdit *OA_yanghuahenmianji = nullptr;
	QLineEdit *OAS_yanghuahenzongmianji = nullptr;
	QLineEdit *yanghuahensecha = nullptr;
	QLineEdit *dibusechashen0 = nullptr;
	QLineEdit *dibusechashen1 = nullptr;
	QLineEdit *dibusechashen2 = nullptr;
	QLineEdit *dibusechashen3 = nullptr;
	QLineEdit *dibusechaqian0 = nullptr;
	QLineEdit *dibusechaqian1 = nullptr;
	QLineEdit *dibusechaqian2 = nullptr;
	QLineEdit *dibufensePRG = nullptr;
	QLineEdit *dibufensePB= nullptr;
	QLineEdit *dibufensePG = nullptr;
	QLineEdit *dibufensePR = nullptr;

	//按钮3
	QPushButton *Button_line3_model_dibuchicunceliangshen;
	QPushButton *Button_line3_model_dibuchicunceliangqian;
	QPushButton *Button_line3_model_huadingchuanciqv;
	QPushButton *Button_line3_model_tianjiayahuan;
	QPushButton *Button_line3_model_xiugaiyahuan;
	QPushButton *Button_line3_model_shanchuyahuan;
	QPushButton *Button_line3_model_xianshiyahuan;
};
