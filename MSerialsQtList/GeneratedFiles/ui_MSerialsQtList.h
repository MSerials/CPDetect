/********************************************************************************
** Form generated from reading UI file 'MSerialsQtList.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSERIALSQTLIST_H
#define UI_MSERIALSQTLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MSerialsQtListClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MSerialsQtListClass)
    {
        if (MSerialsQtListClass->objectName().isEmpty())
            MSerialsQtListClass->setObjectName(QStringLiteral("MSerialsQtListClass"));
        MSerialsQtListClass->resize(600, 400);
        menuBar = new QMenuBar(MSerialsQtListClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MSerialsQtListClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MSerialsQtListClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MSerialsQtListClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MSerialsQtListClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MSerialsQtListClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MSerialsQtListClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MSerialsQtListClass->setStatusBar(statusBar);

        retranslateUi(MSerialsQtListClass);

        QMetaObject::connectSlotsByName(MSerialsQtListClass);
    } // setupUi

    void retranslateUi(QMainWindow *MSerialsQtListClass)
    {
        MSerialsQtListClass->setWindowTitle(QApplication::translate("MSerialsQtListClass", "MSerialsQtList", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MSerialsQtListClass: public Ui_MSerialsQtListClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSERIALSQTLIST_H
