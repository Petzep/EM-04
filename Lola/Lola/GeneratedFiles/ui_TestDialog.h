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
#include <QtWidgets/QProgressBar>
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
    QWidget *Debug;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *Music;
    QProgressBar *playerBar;
    QLabel *label;
    QLabel *label_2;
    QLabel *textArtist;
    QLabel *textTitle;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QDial *volumeDail;
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
        Debug = new QWidget();
        Debug->setObjectName(QStringLiteral("Debug"));
        pushButton = new QPushButton(Debug);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 70, 101, 31));
        pushButton_2 = new QPushButton(Debug);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 110, 101, 31));
        stackSlide->addWidget(Debug);
        Music = new QWidget();
        Music->setObjectName(QStringLiteral("Music"));
        playerBar = new QProgressBar(Music);
        playerBar->setObjectName(QStringLiteral("playerBar"));
        playerBar->setGeometry(QRect(120, 70, 241, 23));
        playerBar->setMaximum(100);
        playerBar->setValue(0);
        playerBar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        playerBar->setTextVisible(true);
        playerBar->setInvertedAppearance(false);
        playerBar->setFormat(QStringLiteral(""));
        label = new QLabel(Music);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 50, 47, 13));
        label_2 = new QLabel(Music);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 30, 41, 16));
        textArtist = new QLabel(Music);
        textArtist->setObjectName(QStringLiteral("textArtist"));
        textArtist->setGeometry(QRect(160, 30, 201, 16));
        textTitle = new QLabel(Music);
        textTitle->setObjectName(QStringLiteral("textTitle"));
        textTitle->setGeometry(QRect(160, 50, 201, 16));
        playButton = new QPushButton(Music);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(140, 130, 75, 23));
        playButton->setCheckable(true);
        stopButton = new QPushButton(Music);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(250, 130, 75, 23));
        prevButton = new QPushButton(Music);
        prevButton->setObjectName(QStringLiteral("prevButton"));
        prevButton->setGeometry(QRect(100, 180, 75, 23));
        nextButton = new QPushButton(Music);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        nextButton->setGeometry(QRect(280, 180, 75, 23));
        volumeDail = new QDial(Music);
        volumeDail->setObjectName(QStringLiteral("volumeDail"));
        volumeDail->setGeometry(QRect(200, 160, 50, 64));
        volumeDail->setMaximum(100);
        stackSlide->addWidget(Music);
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
        label->setText(QApplication::translate("TestDialog", "Title:", Q_NULLPTR));
        label_2->setText(QApplication::translate("TestDialog", "Artist:", Q_NULLPTR));
        textArtist->setText(QApplication::translate("TestDialog", "-", Q_NULLPTR));
        textTitle->setText(QApplication::translate("TestDialog", "-", Q_NULLPTR));
        playButton->setText(QApplication::translate("TestDialog", "Play", Q_NULLPTR));
        stopButton->setText(QApplication::translate("TestDialog", "Stop", Q_NULLPTR));
        prevButton->setText(QApplication::translate("TestDialog", "Previous", Q_NULLPTR));
        nextButton->setText(QApplication::translate("TestDialog", "Next", Q_NULLPTR));
        label_5->setText(QApplication::translate("TestDialog", "UserName", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
