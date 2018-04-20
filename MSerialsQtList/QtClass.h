#pragma once

#include <QWidgetList>

class QtClass : public QWidgetList
{
	Q_OBJECT

public:
	QtClass(QObject *parent);
	~QtClass();
};
