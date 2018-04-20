#include "stdafx.h"
#include "FunEditDlg.h"
#include "Common.h"
#include "ImageMgr.h"
#include "IR.h"
#include "ReadImage.h"




void ListWidget::addMyItem(QStringList &Strlst, QIcon qi)
{
	this->addItems(Strlst);
	//���Item��ʽ2  
	QListWidgetItem *pItem = new QListWidgetItem(this);
	pItem->setText("Item5");
	this->addItem(pItem);
}

//���ڼ����Ƿ�ͺ����б���һ��
void ListWidget::checkList()
{
	Execuate::GetIns()->exes.size();
}



void ListWidget::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
		dragStartPosition = event->pos();
	QListWidget::mousePressEvent(event);
}

void ListWidget::mouseMoveEvent(QMouseEvent * event)
{
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - dragStartPosition).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			performDrag();
	}
	QListWidget::mouseMoveEvent(event);
}

void ListWidget::dragEnterEvent(QDragEnterEvent * event)
{
	ListWidget *source =
		qobject_cast<ListWidget *>(event->source());
	if (source && source != this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void ListWidget::dragMoveEvent(QDragMoveEvent * event)
{
	ListWidget *source =
		qobject_cast<ListWidget *>(event->source());
	if (source && source != this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void ListWidget::dropEvent(QDropEvent * event)
{
	ListWidget *source =
		qobject_cast<ListWidget *>(event->source());
	if (source && source != this) {
		addItem(event->mimeData()->text());
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void ListWidget::performDrag()
{
	QListWidgetItem *item = currentItem();
	if (item) {
		QMimeData *mimeData = new QMimeData;
		mimeData->setText(item->text());

		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(QPixmap(":/images/person.png"));
		if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
			delete item;
	}
}
















FunEditDlg::FunEditDlg(QWidget *parent)
	: QDialog(parent)
{
	
	ui.setupUi(this); 
	resize(1024, 768);
	pGridLayout = nullptr;
	FunListWidget = nullptr;
	textEdit = nullptr;
	label = nullptr;
	ptabWidget = nullptr;
	scrollArea = nullptr;
	scrollArea1 = nullptr;
	scrollArea2 = nullptr;
	scrollArea3 = nullptr;
	UpdateUI();
}

FunEditDlg::~FunEditDlg()
{
	delete pGridLayout;
	delete textEdit;
	delete label;
	delete ptabWidget;
}




void FunEditDlg::Draw()
{
}

void FunEditDlg::Draw(QString filename)
{
	QImage image(filename);
	label->setPixmap(QPixmap::fromImage(image));
	label->resize(QSize(image.width(), image.height()));
	//ui.scrollImag->setWidget(label);
}


void FunEditDlg::initTabWidget()
{
	//if (nullptr == scrollArea2) scrollArea2 = new QScrollArea(this);
	if (nullptr == ptabWidget)
	{
		//tabWidget1
		ptabWidget = new QTabWidget(this);
		static QWidget	*widget = new QWidget();
		QHBoxLayout *hLayout = new QHBoxLayout();

		//��Ӱ�ť
		pButtonGetImage = new QPushButton(QString::fromLocal8Bit("��ȡ���ͼ��"));
		connect(pButtonGetImage, SIGNAL(clicked()), this, SLOT(GetImage()));

		pButtonSelectCamera = new QPushButton(QString::fromLocal8Bit("ѡ�����"));
		connect(pButtonSelectCamera, SIGNAL(clicked()), this, SLOT(SelectCamera()));

		pButtonGetImageFromPC = new QPushButton(QString::fromLocal8Bit("��ͼƬ"));
		connect(pButtonGetImageFromPC, SIGNAL(clicked()), this, SLOT(LoadImageFromPC()));

		hLayout->addWidget(pButtonGetImage);
		hLayout->addWidget(pButtonSelectCamera);
		hLayout->addWidget(pButtonGetImageFromPC);
		//��Ӱ�ťend
		widget->setLayout(hLayout);
		//QScrollArea *scroll1 = new QScrollArea(this);
		//scroll1->setBackgroundRole(QPalette::Dark);
		//scroll1->setWidget(widget);
		ptabWidget->addTab(widget, QString::fromLocal8Bit("��ȡͼ����"));



		//tabWidget2
		static QWidget	*widget2 = new QWidget(this);
		QHBoxLayout *hLayout2 = new QHBoxLayout();
		//��Ӱ�ť

		//ȡͼƬ��Ʒ
		//������
		pButtonDistanceDots = new QPushButton();
		//���߾���
		pButtonDistanceDotLine = new QPushButton();
		//ֱ�߼����
		pButtonDistanceLineLine = new QPushButton();

		hLayout2->addWidget(pButtonDistanceDots);
		hLayout2->addWidget(pButtonDistanceDotLine);
		hLayout2->addWidget(pButtonDistanceLineLine);



		//��Ӱ�ťend
		widget2->setLayout(hLayout2);
		//QScrollArea *scroll2 = new QScrollArea(this);
		//scroll2->setBackgroundRole(QPalette::Dark);
		//scroll2->setWidget(widget2);
		ptabWidget->addTab(widget2, QString::fromLocal8Bit("���������"));








		//ptabWidget.addTab("���������");
		//ptabWidget.addTab("����ѧϰ��");
		pGridLayout->addWidget(ptabWidget, 5, 0, 3, 5);
	}
	
}

void FunEditDlg::initLabel()
{
	if (nullptr == scrollArea) scrollArea = new QScrollArea(this);
	if (nullptr == label)
	{
		label = new QLabel(this);
		pGridLayout->addWidget(scrollArea, 0, 0, 5, 5);
		scrollArea->setBackgroundRole(QPalette::Dark);
		scrollArea->setWidget(label);
		scrollArea->setAlignment(Qt::AlignCenter);
	}
		
		
}

void FunEditDlg::initTextEdit()
{
	//if (nullptr == scrollArea1) scrollArea1 = new QScrollArea(this);
	if (nullptr == textEdit)
	{
		FunListWidget = new ListWidget();
		pGridLayout->addWidget(FunListWidget, 0, 5, 5, 3);
	}
}

void FunEditDlg::UpdateUI()
{
	if (nullptr == pGridLayout) pGridLayout = new QGridLayout(this);
	pGridLayout->setSpacing(10);    //ˮƽ���
	
	initLabel();
	initTextEdit();
	initTabWidget();

	if (nullptr == scrollArea3) scrollArea3 = new QScrollArea(this);
	pGridLayout->addWidget(scrollArea3, 5, 5, 3, 3);
	scrollArea3->setBackgroundRole(QPalette::Dark);
	return;
}






void FunEditDlg::GetImage()
{
	for (int i = 0; i < Execuate::GetIns()->exes.size(); i++)
	{
		 Execuate::GetIns()->exes[i]->Runnable();
	}
}


void FunEditDlg::SelectCamera()
{

}


void FunEditDlg::LoadImageFromPC()
{
	ReadImage * readImage = new ReadImage();
	Execuate::GetIns()->exes.push_back((AObject*)readImage);
	readImage->Method();
	displayMat(ParamMgr::GetIns()->mats.at(ParamMgr::GetIns()->mats.size()-1));
	

	
}


void FunEditDlg::displayMat(cv::Mat &image)
{
	cv::Mat rgb;
	QImage img;
	if (image.channels() == 3)
	{
		//cvt Mat BGR 2 QImage RGB
		cvtColor(image, rgb, CV_BGR2RGB);
		img = QImage((const unsigned char*)(rgb.data),
			rgb.cols, rgb.rows,
			rgb.cols*rgb.channels(),
			QImage::Format_RGB888);
	}
	else
	{
		img = QImage((const unsigned char*)(image.data),
			image.cols, image.rows,
			image.cols*image.channels(),
			QImage::Format_RGB888);
	}
	label->setPixmap(QPixmap::fromImage(img));
	label->resize(QSize(img.width(), img.height()));
	scrollArea->setWidget(label);
	scrollArea->width();
}

