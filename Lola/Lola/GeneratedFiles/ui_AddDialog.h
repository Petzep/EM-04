/********************************************************************************
** Form generated from reading UI file 'AddDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDIALOG_H
#define UI_ADDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddDialog
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QLabel *nameText;
    QLineEdit *nameEdit;
    QLabel *emailText;
    QLineEdit *emailEdit;

    void setupUi(QDialog *AddDialog)
    {
        if (AddDialog->objectName().isEmpty())
            AddDialog->setObjectName(QStringLiteral("AddDialog"));
        AddDialog->resize(330, 114);
        layoutWidget = new QWidget(AddDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 60, 311, 44));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(238, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout_2->addWidget(okButton, 1, 1, 1, 1);

        layoutWidget_2 = new QWidget(AddDialog);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 10, 311, 48));
        gridLayout = new QGridLayout(layoutWidget_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        nameText = new QLabel(layoutWidget_2);
        nameText->setObjectName(QStringLiteral("nameText"));

        gridLayout->addWidget(nameText, 0, 0, 1, 1);

        nameEdit = new QLineEdit(layoutWidget_2);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        gridLayout->addWidget(nameEdit, 0, 1, 1, 1);

        emailText = new QLabel(layoutWidget_2);
        emailText->setObjectName(QStringLiteral("emailText"));

        gridLayout->addWidget(emailText, 1, 0, 1, 1);

        emailEdit = new QLineEdit(layoutWidget_2);
        emailEdit->setObjectName(QStringLiteral("emailEdit"));

        gridLayout->addWidget(emailEdit, 1, 1, 1, 1);


        retranslateUi(AddDialog);
        QObject::connect(okButton, SIGNAL(clicked()), AddDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(AddDialog);
    } // setupUi

    void retranslateUi(QDialog *AddDialog)
    {
        AddDialog->setWindowTitle(QApplication::translate("AddDialog", "AddDialog", Q_NULLPTR));
        okButton->setText(QApplication::translate("AddDialog", "OK", Q_NULLPTR));
        nameText->setText(QApplication::translate("AddDialog", "Name:", Q_NULLPTR));
        emailText->setText(QApplication::translate("AddDialog", "E-mail:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddDialog: public Ui_AddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDIALOG_H
