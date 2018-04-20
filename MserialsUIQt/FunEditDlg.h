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
	//Drag and Drop������


public slots:
	void GetImage();

	void SelectCamera();

	void LoadImageFromPC();

	void displayMat(cv::Mat & image);

	//�����źţ�����Ҫʵ��
signals:
	void GetImages();

private:
	Ui::FunEditDlg ui;






	QGridLayout *pGridLayout;
	//����tab
	QTabWidget	*tabWidget;
	//�ı���ʾִ��״̬
	ListWidget	*FunListWidget;
	QTextEdit	*textEdit;
	//ʹ��QLabel��ʾͼƬ�������QLabel����һ��ScrollArea���棬����ͼƬ�����ʱ����Զ�����ӹ������������ʹ��ˮƽ���֣�����ScrollArea�Ĵ�С�����Ŵ��ڵĴ�С�Զ��ı䡣
	QLabel		*label;
	//ͼ��������ʾ��
	QLabel		*label_property;


	//ͼ��������
	QTabWidget	*ptabWidget;
	QPushButton	*pButtonGetImage;
	QPushButton	*pButtonSelectCamera;
	QPushButton *pButtonGetImageFromPC;

	//������
	QPushButton	*pButtonDistanceDots;
	//���߾���
	QPushButton	*pButtonDistanceDotLine;
	//ֱ�߼����
	QPushButton *pButtonDistanceLineLine;

	//ȡͼƬ��Ʒ
	QPushButton *pButtonGetColorSample;
	//ȡͼƬ��Ʒ
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
	QWidget* baseWidget;     //����ǰ�Ի�����,����Ϊָ��
	QWidget* detailWidget;   //��չ��Ի�����,����Ϊָ��
	
};
