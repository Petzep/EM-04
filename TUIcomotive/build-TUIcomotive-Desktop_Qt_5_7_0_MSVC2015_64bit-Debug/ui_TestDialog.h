/********************************************************************************
** Form generated from reading UI file 'TestDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include "CustomClock.h"
#include "QtPieMenu.h"

QT_BEGIN_NAMESPACE

class Ui_TestDialog
{
public:
    QPushButton *pushButton;
    QtPieMenu *qtPieMenu;
    QCheckBox *checkBox;
    CustomClock *customClock;
    QDial *dial;
    QCheckBox *checkBox_2;

    void setupUi(QDialog *TestDialog)
    {
        if (TestDialog->objectName().isEmpty())
            TestDialog->setObjectName(QStringLiteral("TestDialog"));
        TestDialog->resize(674, 420);
        pushButton = new QPushButton(TestDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 70, 75, 23));
        qtPieMenu = new QtPieMenu(TestDialog);
        qtPieMenu->setObjectName(QStringLiteral("qtPieMenu"));
        qtPieMenu->setGeometry(QRect(300, 30, 281, 341));
        qtPieMenu->setItemNumbers(20);
        qtPieMenu->setSelectionColor(QColor(144, 0, 0));
        qtPieMenu->setSelectionInnerColor(QColor(255, 255, 255));
        qtPieMenu->setSelectionOuterColor(QColor(0, 255, 0));
        qtPieMenu->setProperty("ToggleSecondHand", QVariant(true));
        qtPieMenu->setProperty("colorSecondHand", QVariant(QColor(45, 130, 0)));
        checkBox = new QCheckBox(TestDialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(30, 20, 70, 17));
        customClock = new CustomClock(TestDialog);
        customClock->setObjectName(QStringLiteral("customClock"));
        customClock->setGeometry(QRect(40, 180, 161, 141));
        customClock->setProperty("ToggleSecondHand", QVariant(true));
        customClock->setColorMinuteHand(QColor(255, 0, 0, 191));
        dial = new QDial(TestDialog);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(20, 90, 50, 64));
        dial->setMinimum(1);
        dial->setMaximum(20);
        dial->setPageStep(10);
        checkBox_2 = new QCheckBox(TestDialog);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(30, 40, 121, 17));

        retranslateUi(TestDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), customClock, SLOT(toggleSecondHand()));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), customClock, SLOT(setSecondHand(bool)));
        QObject::connect(dial, SIGNAL(sliderMoved(int)), qtPieMenu, SLOT(setSelection(int)));
        QObject::connect(checkBox_2, SIGNAL(clicked(bool)), qtPieMenu, SLOT(setDanielArrow(bool)));

        QMetaObject::connectSlotsByName(TestDialog);
    } // setupUi

    void retranslateUi(QDialog *TestDialog)
    {
        TestDialog->setWindowTitle(QApplication::translate("TestDialog", "TestDialog", 0));
        pushButton->setText(QApplication::translate("TestDialog", "PushButton", 0));
        checkBox->setText(QApplication::translate("TestDialog", "CheckBox", 0));
        checkBox_2->setText(QApplication::translate("TestDialog", "DANIEL ARROW!!!!!", 0));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
