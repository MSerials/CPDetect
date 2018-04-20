/********************************************************************************
** Form generated from reading UI file 'QuitTipDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUITTIPDLG_H
#define UI_QUITTIPDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QuitTipDlg
{
public:

    void setupUi(QDialog *QuitTipDlg)
    {
        if (QuitTipDlg->objectName().isEmpty())
            QuitTipDlg->setObjectName(QStringLiteral("QuitTipDlg"));
        QuitTipDlg->resize(400, 300);

        retranslateUi(QuitTipDlg);

        QMetaObject::connectSlotsByName(QuitTipDlg);
    } // setupUi

    void retranslateUi(QDialog *QuitTipDlg)
    {
        QuitTipDlg->setWindowTitle(QApplication::translate("QuitTipDlg", "QuitTipDlg", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QuitTipDlg: public Ui_QuitTipDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUITTIPDLG_H
