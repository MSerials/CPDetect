/********************************************************************************
** Form generated from reading UI file 'QtModelSet.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMODELSET_H
#define UI_QTMODELSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QtModelSet
{
public:

    void setupUi(QDialog *QtModelSet)
    {
        if (QtModelSet->objectName().isEmpty())
            QtModelSet->setObjectName(QStringLiteral("QtModelSet"));
        QtModelSet->resize(432, 376);

        retranslateUi(QtModelSet);

        QMetaObject::connectSlotsByName(QtModelSet);
    } // setupUi

    void retranslateUi(QDialog *QtModelSet)
    {
        QtModelSet->setWindowTitle(QApplication::translate("QtModelSet", "QtModelSet", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtModelSet: public Ui_QtModelSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMODELSET_H
