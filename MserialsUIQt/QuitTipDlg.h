#pragma once

#include <QDialog>
#include "ui_QuitTipDlg.h"

class QuitTipDlg : public QDialog
{
	Q_OBJECT

public:
	enum {
		CANCEL,QUIT,QUITANDSAVE
	};
	QuitTipDlg(QWidget *parent = Q_NULLPTR);
	~QuitTipDlg();
	int Sel();
public slots:

	void Load_Quit();

	void Quit();

	void Cancel();

private:
	Ui::QuitTipDlg ui;
	int sel = 0;
};
