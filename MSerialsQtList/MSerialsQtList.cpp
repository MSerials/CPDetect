#include "MSerialsQtList.h"
#include "HistoryListWidget.h"

MSerialsQtList::MSerialsQtList(QWidget *parent)
	: QMainWindow(parent)
{

	static QWidget *p = new QWidget(this);
	HistoryListWidget *o = new HistoryListWidget(p);
	ui.setupUi(this);

}
