/********************************************************************************
** Form generated from reading UI file 'MserialsUIQt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSERIALSUIQT_H
#define UI_MSERIALSUIQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MserialsUIQtClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_GetXml;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MserialsUIQtClass)
    {
        if (MserialsUIQtClass->objectName().isEmpty())
            MserialsUIQtClass->setObjectName(QStringLiteral("MserialsUIQtClass"));
        MserialsUIQtClass->resize(704, 870);
        centralWidget = new QWidget(MserialsUIQtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_GetXml = new QPushButton(centralWidget);
        pushButton_GetXml->setObjectName(QStringLiteral("pushButton_GetXml"));
        pushButton_GetXml->setGeometry(QRect(280, 760, 75, 23));
        MserialsUIQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MserialsUIQtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 704, 23));
        MserialsUIQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MserialsUIQtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MserialsUIQtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MserialsUIQtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MserialsUIQtClass->setStatusBar(statusBar);

        retranslateUi(MserialsUIQtClass);
        QObject::connect(pushButton_GetXml, SIGNAL(clicked()), MserialsUIQtClass, SLOT(btn_clicked_getxml()));

        QMetaObject::connectSlotsByName(MserialsUIQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *MserialsUIQtClass)
    {
        MserialsUIQtClass->setWindowTitle(QApplication::translate("MserialsUIQtClass", "MserialsUIQt", Q_NULLPTR));
        pushButton_GetXml->setText(QApplication::translate("MserialsUIQtClass", "\350\216\267\345\217\226xml", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MserialsUIQtClass: public Ui_MserialsUIQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSERIALSUIQT_H
