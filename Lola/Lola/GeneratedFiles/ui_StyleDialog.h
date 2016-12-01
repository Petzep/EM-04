/********************************************************************************
** Form generated from reading UI file 'StyleDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STYLEDIALOG_H
#define UI_STYLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_StyleDialog
{
public:

    void setupUi(QDialog *StyleDialog)
    {
        if (StyleDialog->objectName().isEmpty())
            StyleDialog->setObjectName(QStringLiteral("StyleDialog"));
        StyleDialog->resize(400, 300);

        retranslateUi(StyleDialog);

        QMetaObject::connectSlotsByName(StyleDialog);
    } // setupUi

    void retranslateUi(QDialog *StyleDialog)
    {
        StyleDialog->setWindowTitle(QApplication::translate("StyleDialog", "StyleDialog", 0));
    } // retranslateUi

};

namespace Ui {
    class StyleDialog: public Ui_StyleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STYLEDIALOG_H
