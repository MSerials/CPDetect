#include "stdafx.h"
#include "QuitTipDlg.h"
#include <qgridlayout.h>
#include <qpushbutton.h>

QuitTipDlg::QuitTipDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	resize(400,50);
	//进行界面初始化就可以了
	//setWindowFlags(windowFlags()&~(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint));
	setWindowFlags(Qt::FramelessWindowHint);
	QGridLayout *pGridLayout = new QGridLayout(this);
	QPushButton* pButtonLQ = new QPushButton(QString::fromLocal8Bit("加载并退出"));
	QPushButton* pButtonQ = new QPushButton(QString::fromLocal8Bit("直接退出"));
	QPushButton* pButtonC = new QPushButton(QString::fromLocal8Bit("取消"));
	pGridLayout->addWidget(pButtonLQ, 0, 0, 2, 3);
	pGridLayout->addWidget(pButtonQ, 0, 3, 2, 3);
	pGridLayout->addWidget(pButtonC, 0, 6, 2, 3);
	connect(pButtonLQ, SIGNAL(clicked()), this, SLOT(Load_Quit()));
	connect(pButtonQ, SIGNAL(clicked()), this, SLOT(Quit()));
	connect(pButtonC, SIGNAL(clicked()), this, SLOT(Cancel()));
}

QuitTipDlg::~QuitTipDlg()
{
}

int QuitTipDlg::Sel()
{
	return sel;
}

void QuitTipDlg::Load_Quit(){
	sel = QUITANDSAVE;
	this->close();
}

void QuitTipDlg::Quit() {
	sel = QUIT;
	this->close();
}

void QuitTipDlg::Cancel() {
	sel = CANCEL;
	this->close();
}

