#include "stdafx.h"
//#include "QtFunctionListView.h"

#if 0

QtFunctionListView::QtFunctionListView(QWidget *parent)
	: QListWidget(parent)
{
	setAcceptDrops(true);
	resize(300, 600);
}

QtFunctionListView::~QtFunctionListView()
{
}


void QtFunctionListView::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
		startPos = event->pos();
	QListWidget::mousePressEvent(event);
}

void QtFunctionListView::mouseMoveEvent(QMouseEvent * event)
{
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - startPos).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			startDrag();
	}
	QListWidget::mouseMoveEvent(event);
}

void QtFunctionListView::dragEnterEvent(QDragEnterEvent * event)
{
	QtFunctionListView *source =
		qobject_cast<QtFunctionListView*>(event->source());
	if (source && source != this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void QtFunctionListView::dragMoveEvent(QDragMoveEvent * event)
{
	QtFunctionListView *source =
		qobject_cast<QtFunctionListView *>(event->source());
	if (source && source != this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void QtFunctionListView::dropEvent(QDropEvent * event)
{
	QtFunctionListView *source =
		qobject_cast<QtFunctionListView*>(event->source());
	if (source && source != this) {
		addItem(event->mimeData()->text());
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}



void QtFunctionListView::startDrag()
{
	QListWidgetItem *item = currentItem();
	if (item) {
		QMimeData *mimeData = new QMimeData;
		mimeData->setText(item->text());
		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(QPixmap(":/images/person.png"));
		if (drag->start(Qt::MoveAction) == Qt::MoveAction)
			delete item;
	}
}

#endif