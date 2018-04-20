#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MSerialsQtList.h"

class MSerialsQtList : public QMainWindow
{
	Q_OBJECT

public:
	MSerialsQtList(QWidget *parent = Q_NULLPTR);

private:
	Ui::MSerialsQtListClass ui;
};
