#pragma once

#include <QListWidget>

class HistoryListWidget : public QListWidget
{
	Q_OBJECT

public:
	HistoryListWidget(QWidget *parent = nullptr);
	~HistoryListWidget();
};
