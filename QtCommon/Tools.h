#include <QDir>


/*
QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
*/

#ifndef __TOOLS___
#define __TOOLS___

class QtTool
{
        QString AppPath()
	{
		return QDir::currentPath();
	}
	
};

#endif
