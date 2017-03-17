/********************************************************************************
** Form generated from reading UI file 'TestDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTDIALOG_H
#define UI_TESTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "CustomClock.h"
#include "QtPieMenu.h"

QT_BEGIN_NAMESPACE

class Ui_TestDialog
{
public:
    QPushButton *pushButton;
    QtPieMenu *qtPieMenu;
    QCheckBox *checkBox;
    QDial *dial;
    CustomClock *customClock;
    QCheckBox *checkBox_2;
    QLabel *label;
    QWidget *widget;
    QGridLayout *gridLayout;
    QDial *dial_4;
    QDial *dial_5;
    QDial *dial_2;
    QDial *dial_3;

    void setupUi(QDialog *TestDialog)
    {
        if (TestDialog->objectName().isEmpty())
            TestDialog->setObjectName(QStringLiteral("TestDialog"));
        TestDialog->resize(899, 562);
        pushButton = new QPushButton(TestDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 60, 75, 23));
        qtPieMenu = new QtPieMenu(TestDialog);
        qtPieMenu->setObjectName(QStringLiteral("qtPieMenu"));
        qtPieMenu->setGeometry(QRect(290, 40, 281, 341));
        qtPieMenu->setItemNumbers(20);
        qtPieMenu->setSelectionColor(QColor(144, 0, 0));
        qtPieMenu->setSelectionInnerColor(QColor(255, 255, 255));
        qtPieMenu->setSelectionOuterColor(QColor(0, 255, 0));
        qtPieMenu->setProperty("ToggleSecondHand", QVariant(true));
        qtPieMenu->setProperty("colorSecondHand", QVariant(QColor(45, 130, 0)));
        checkBox = new QCheckBox(TestDialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 10, 70, 17));
        dial = new QDial(TestDialog);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(0, 80, 50, 64));
        dial->setMinimum(1);
        dial->setMaximum(20);
        dial->setPageStep(10);
        dial->setInvertedAppearance(true);
        dial->setWrapping(true);
        customClock = new CustomClock(TestDialog);
        customClock->setObjectName(QStringLiteral("customClock"));
        customClock->setGeometry(QRect(20, 170, 161, 141));
        customClock->setProperty("ToggleSecondHand", QVariant(true));
        customClock->setColorMinuteHand(QColor(255, 0, 0, 191));
        checkBox_2 = new QCheckBox(TestDialog);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(10, 30, 121, 17));
        label = new QLabel(TestDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(400, 30, 47, 311));
        widget = new QWidget(TestDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(580, 330, 208, 208));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        dial_4 = new QDial(widget);
        dial_4->setObjectName(QStringLiteral("dial_4"));

        gridLayout->addWidget(dial_4, 1, 0, 1, 1);

        dial_5 = new QDial(widget);
        dial_5->setObjectName(QStringLiteral("dial_5"));

        gridLayout->addWidget(dial_5, 1, 1, 1, 1);

        dial_2 = new QDial(widget);
        dial_2->setObjectName(QStringLiteral("dial_2"));

        gridLayout->addWidget(dial_2, 0, 0, 1, 1);

        dial_3 = new QDial(widget);
        dial_3->setObjectName(QStringLiteral("dial_3"));

        gridLayout->addWidget(dial_3, 0, 1, 1, 1);


        retranslateUi(TestDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), customClock, SLOT(toggleSecondHand()));
        QObject::connect(checkBox_2, SIGNAL(clicked(bool)), qtPieMenu, SLOT(setDanielArrow(bool)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), customClock, SLOT(setSecondHand(bool)));
        QObject::connect(dial, SIGNAL(valueChanged(int)), qtPieMenu, SLOT(setSelection(int)));
        QObject::connect(qtPieMenu, SIGNAL(itemName(QString)), label, SLOT(setText(QString)));
        QObject::connect(qtPieMenu, SIGNAL(itemSelect(int)), label, SLOT(clear()));

        QMetaObject::connectSlotsByName(TestDialog);
    } // setupUi

    void retranslateUi(QDialog *TestDialog)
    {
        TestDialog->setWindowTitle(QApplication::translate("TestDialog", "TestDialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("TestDialog", "PushButton", Q_NULLPTR));
        checkBox->setText(QApplication::translate("TestDialog", "CheckBox", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("TestDialog", "DANIEL ARROW!!!!!", Q_NULLPTR));
        label->setText(QApplication::translate("TestDialog", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
