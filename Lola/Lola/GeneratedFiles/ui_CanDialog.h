/********************************************************************************
** Form generated from reading UI file 'CanDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANDIALOG_H
#define UI_CANDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CanDialog
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *tableLable;
    QSpacerItem *horizontalSpacer;
    QTableView *canTable;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *refreshButton;
    QPushButton *clearButton;
    QPushButton *saveButton;

    void setupUi(QDialog *CanDialog)
    {
        if (CanDialog->objectName().isEmpty())
            CanDialog->setObjectName(QStringLiteral("CanDialog"));
        CanDialog->resize(1096, 395);
        layoutWidget = new QWidget(CanDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 961, 371));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableLable = new QLabel(layoutWidget);
        tableLable->setObjectName(QStringLiteral("tableLable"));

        gridLayout->addWidget(tableLable, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(518, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        canTable = new QTableView(layoutWidget);
        canTable->setObjectName(QStringLiteral("canTable"));
        canTable->setProperty("showDropIndicator", QVariant(false));
        canTable->setDragDropOverwriteMode(false);

        gridLayout->addWidget(canTable, 1, 0, 1, 2);

        widget = new QWidget(CanDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(990, 10, 77, 83));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        refreshButton = new QPushButton(widget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));

        verticalLayout->addWidget(refreshButton);

        clearButton = new QPushButton(widget);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        verticalLayout->addWidget(clearButton);

        saveButton = new QPushButton(widget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        verticalLayout->addWidget(saveButton);


        retranslateUi(CanDialog);

        QMetaObject::connectSlotsByName(CanDialog);
    } // setupUi

    void retranslateUi(QDialog *CanDialog)
    {
        CanDialog->setWindowTitle(QApplication::translate("CanDialog", "CanDialog", 0));
        tableLable->setText(QApplication::translate("CanDialog", "CAN BUS table", 0));
        refreshButton->setText(QApplication::translate("CanDialog", "&Refresh", 0));
        clearButton->setText(QApplication::translate("CanDialog", "&Clear", 0));
        saveButton->setText(QApplication::translate("CanDialog", "&Save", 0));
    } // retranslateUi

};

namespace Ui {
    class CanDialog: public Ui_CanDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANDIALOG_H
