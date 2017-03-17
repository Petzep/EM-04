/********************************************************************************
** Form generated from reading UI file 'CanDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANDIALOG_H
#define UI_CANDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
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
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *refreshButton;
    QPushButton *clearButton;
    QPushButton *saveButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioCan;
    QRadioButton *radioFile;
    QCheckBox *checkUpdate;

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

        layoutWidget1 = new QWidget(CanDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(990, 10, 77, 83));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        refreshButton = new QPushButton(layoutWidget1);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));

        verticalLayout->addWidget(refreshButton);

        clearButton = new QPushButton(layoutWidget1);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        verticalLayout->addWidget(clearButton);

        saveButton = new QPushButton(layoutWidget1);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        verticalLayout->addWidget(saveButton);

        groupBox = new QGroupBox(CanDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(990, 110, 85, 111));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        radioCan = new QRadioButton(groupBox);
        radioCan->setObjectName(QStringLiteral("radioCan"));
        radioCan->setCheckable(true);
        radioCan->setChecked(true);

        verticalLayout_2->addWidget(radioCan);

        radioFile = new QRadioButton(groupBox);
        radioFile->setObjectName(QStringLiteral("radioFile"));

        verticalLayout_2->addWidget(radioFile);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        checkUpdate = new QCheckBox(groupBox);
        checkUpdate->setObjectName(QStringLiteral("checkUpdate"));

        gridLayout_2->addWidget(checkUpdate, 1, 0, 1, 1);


        retranslateUi(CanDialog);

        QMetaObject::connectSlotsByName(CanDialog);
    } // setupUi

    void retranslateUi(QDialog *CanDialog)
    {
        CanDialog->setWindowTitle(QApplication::translate("CanDialog", "CanDialog", Q_NULLPTR));
        tableLable->setText(QApplication::translate("CanDialog", "CAN BUS table", Q_NULLPTR));
        refreshButton->setText(QApplication::translate("CanDialog", "&Refresh", Q_NULLPTR));
        clearButton->setText(QApplication::translate("CanDialog", "&Clear", Q_NULLPTR));
        saveButton->setText(QApplication::translate("CanDialog", "&Save", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("CanDialog", "Load from:", Q_NULLPTR));
        radioCan->setText(QApplication::translate("CanDialog", "CANBUS", Q_NULLPTR));
        radioFile->setText(QApplication::translate("CanDialog", "File", Q_NULLPTR));
        checkUpdate->setText(QApplication::translate("CanDialog", "Update", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CanDialog: public Ui_CanDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANDIALOG_H
