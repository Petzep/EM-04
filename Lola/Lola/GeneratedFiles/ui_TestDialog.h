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
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include "QtPieMenu.h"
#include "StackSlide.h"

QT_BEGIN_NAMESPACE

class Ui_TestDialog
{
public:
    StackSlide *stackSlide;
    QWidget *Debug_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *Page_1;
    QWidget *Menu;
    QSplitter *splitter;
    QtPieMenu *qtPieMenu;
    QWidget *page_3;
    QWidget *page_4;
    QSplitter *splitter_2;
    QDial *dial;
    QLabel *label_5;
    QLCDNumber *lcdNumber;

    void setupUi(QDialog *TestDialog)
    {
        if (TestDialog->objectName().isEmpty())
            TestDialog->setObjectName(QStringLiteral("TestDialog"));
        TestDialog->resize(800, 480);
        stackSlide = new StackSlide(TestDialog);
        stackSlide->setObjectName(QStringLiteral("stackSlide"));
        stackSlide->setGeometry(QRect(9, 70, 781, 401));
        stackSlide->setMenuPage(2);
        Debug_2 = new QWidget();
        Debug_2->setObjectName(QStringLiteral("Debug_2"));
        pushButton = new QPushButton(Debug_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 70, 101, 31));
        pushButton_2 = new QPushButton(Debug_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 110, 101, 31));
        stackSlide->addWidget(Debug_2);
        Page_1 = new QWidget();
        Page_1->setObjectName(QStringLiteral("Page_1"));
        stackSlide->addWidget(Page_1);
        Menu = new QWidget();
        Menu->setObjectName(QStringLiteral("Menu"));
        splitter = new QSplitter(Menu);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(0, 0, 781, 401));
        splitter->setOrientation(Qt::Horizontal);
        qtPieMenu = new QtPieMenu(splitter);
        qtPieMenu->setObjectName(QStringLiteral("qtPieMenu"));
        qtPieMenu->setSelectionRadius(16);
        splitter->addWidget(qtPieMenu);
        stackSlide->addWidget(Menu);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        stackSlide->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        stackSlide->addWidget(page_4);
        splitter_2 = new QSplitter(TestDialog);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(-10, 0, 791, 61));
        splitter_2->setOrientation(Qt::Horizontal);
        dial = new QDial(splitter_2);
        dial->setObjectName(QStringLiteral("dial"));
        splitter_2->addWidget(dial);
        label_5 = new QLabel(splitter_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        splitter_2->addWidget(label_5);
        lcdNumber = new QLCDNumber(splitter_2);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        QFont font;
        font.setStrikeOut(false);
        lcdNumber->setFont(font);
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(56.2));
        splitter_2->addWidget(lcdNumber);

        retranslateUi(TestDialog);
        QObject::connect(qtPieMenu, SIGNAL(itemSelect(int)), stackSlide, SLOT(slideInIdx(int)));

        stackSlide->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(TestDialog);
    } // setupUi

    void retranslateUi(QDialog *TestDialog)
    {
        TestDialog->setWindowTitle(QApplication::translate("TestDialog", "TestDialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("TestDialog", "Dashboard", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("TestDialog", "CAN-Bus", Q_NULLPTR));
        label_5->setText(QApplication::translate("TestDialog", "UserName", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
