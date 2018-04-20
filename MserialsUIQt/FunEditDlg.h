#pragma once

#include <QDialog>
#include "ui_FunEditDlg.h"
#include "ImageMgr.h"



class ListWidget : public QListWidget
{
	Q_OBJECT
		;
public:
	ListWidget() { setAcceptDrops(true);
	
	};
	~ListWidget() {};
	void addMyItem(QStringList &Strlst, QIcon qi = QIcon());

	void checkList();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
private:
	void performDrag();
	QPoint dragStartPosition;
};




class FunEditDlg : public QDialog
{
	Q_OBJECT

public:
	FunEditDlg(QWidget *parent = Q_NULLPTR);
	~FunEditDlg();

	void Draw();
	void Draw(QString filename);
	void initTabWidget();
	void initLabel();
	void initTextEdit();
	void UpdateUI();
	//Drag and Drop功能区


public slots:
	void GetImage();

	void SelectCamera();

	void LoadImageFromPC();

	void displayMat(cv::Mat & image);

	//声明信号，不需要实现
signals:
	void GetImages();

private:
	Ui::FunEditDlg ui;






	QGridLayout *pGridLayout;
	//工具tab
	QTabWidget	*tabWidget;
	//文本显示执行状态
	ListWidget	*FunListWidget;
	QTextEdit	*textEdit;
	//使用QLabel显示图片，把这个QLabel放在一个ScrollArea上面，这样图片过大的时候会自动的添加滚动条，最后窗体使用水平布局，这样ScrollArea的大小会随着窗口的大小自动改变。
	QLabel		*label;
	//图像属性显示框
	QLabel		*label_property;


	//图像处理工具类
	QTabWidget	*ptabWidget;
	QPushButton	*pButtonGetImage;
	QPushButton	*pButtonSelectCamera;
	QPushButton *pButtonGetImageFromPC;

	//点间距离
	QPushButton	*pButtonDistanceDots;
	//点线距离
	QPushButton	*pButtonDistanceDotLine;
	//直线间距离
	QPushButton *pButtonDistanceLineLine;

	//取图片样品
	QPushButton *pButtonGetColorSample;
	//取图片样品
	QPushButton *pButtonGetShaderSample;









	QScrollArea *scrollArea;
	QScrollArea *scrollArea1;
	QScrollArea *scrollArea2;
	QScrollArea *scrollArea3;

	QFormLayout *formLayout;/// = new QFormLayout;
	QLineEdit * nameLineEdit; //= new QLineEdit;
	QLineEdit * emailLineEdit;// = new QLineEdit;
	QLineEdit * ageSpinBox;// = new QLineEdit;
//	QTabWidget *tabWidget;
	
private:
	QWidget* baseWidget;     //伸缩前对话框窗体,必须为指针
	QWidget* detailWidget;   //扩展后对话框窗体,必须为指针
	
};
