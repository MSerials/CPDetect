/********************************************************************************
** Form generated from reading UI file 'QtParamSet.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPARAMSET_H
#define UI_QTPARAMSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QtParamSet
{
public:

    void setupUi(QDialog *QtParamSet)
    {
        if (QtParamSet->objectName().isEmpty())
            QtParamSet->setObjectName(QStringLiteral("QtParamSet"));
        QtParamSet->resize(400, 300);

        retranslateUi(QtParamSet);

        QMetaObject::connectSlotsByName(QtParamSet);
    } // setupUi

    void retranslateUi(QDialog *QtParamSet)
    {
        QtParamSet->setWindowTitle(QApplication::translate("QtParamSet", "QtParamSet", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtParamSet: public Ui_QtParamSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPARAMSET_H
