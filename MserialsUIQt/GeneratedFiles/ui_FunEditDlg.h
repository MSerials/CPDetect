/********************************************************************************
** Form generated from reading UI file 'FunEditDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNEDITDLG_H
#define UI_FUNEDITDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_FunEditDlg
{
public:

    void setupUi(QDialog *FunEditDlg)
    {
        if (FunEditDlg->objectName().isEmpty())
            FunEditDlg->setObjectName(QStringLiteral("FunEditDlg"));
        FunEditDlg->resize(598, 453);

        retranslateUi(FunEditDlg);

        QMetaObject::connectSlotsByName(FunEditDlg);
    } // setupUi

    void retranslateUi(QDialog *FunEditDlg)
    {
        FunEditDlg->setWindowTitle(QApplication::translate("FunEditDlg", "FunEditDlg", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FunEditDlg: public Ui_FunEditDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNEDITDLG_H
