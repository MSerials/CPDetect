#include "MSerialsQtList.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MSerialsQtList w;
	w.show();
	return a.exec();
}
