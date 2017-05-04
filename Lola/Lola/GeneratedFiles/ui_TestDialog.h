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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include "QtPieMenu.h"
#include "QtQuickWidgets/QQuickWidget"
#include "StackSlide.h"

QT_BEGIN_NAMESPACE

class Ui_TestDialog
{
public:
    StackSlide *stackSlide;
    QWidget *Debug;
    QPushButton *dashboardButton;
    QPushButton *canButton;
    QPushButton *quitButton;
    QPushButton *shutdownButton;
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
    QDial *volumeDial;
    QListWidget *playlistWidget;
    QRadioButton *loopOneButton;
    QRadioButton *loopAllButton;
    QCheckBox *shuffleBox;
    QWidget *Menu;
    QSplitter *splitter;
    QtPieMenu *qtPieMenu;
    QWidget *Radio;
    QPushButton *nextStationButton;
    QPushButton *prevStationButton;
    QListWidget *stationWidget;
    QDial *volumeDial_2;
    QRadioButton *radioButton;
    QWidget *page_4;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_3;
    QLCDNumber *lcdNumber_4;
    QLCDNumber *lcdNumber_5;
    QLCDNumber *lcdNumber_6;
    QLCDNumber *lcdNumber_7;
    QLabel *label_3;
    QLabel *label_4;
    QLCDNumber *lcdNumber_8;
    QLCDNumber *lcdNumber_9;
    QLabel *label_6;
    QLCDNumber *lcdNumber_10;
    QLCDNumber *lcdNumber_11;
    QLCDNumber *lcdNumber_12;
    QLCDNumber *lcdNumber_13;
    QLabel *label_7;
    QFrame *line;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLCDNumber *lcdNumber_14;
    QLabel *label_11;
    QLCDNumber *lcdNumber_15;
    QLCDNumber *lcdNumber_16;
    QLCDNumber *lcdNumber_17;
    QLabel *label_12;
    QLCDNumber *lcdNumber_18;
    QLCDNumber *lcdNumber_19;
    QLCDNumber *lcdNumber_20;
    QLabel *label_13;
    QLCDNumber *lcdNumber_21;
    QLCDNumber *lcdNumber_22;
    QLCDNumber *lcdNumber_23;
    QLabel *label_14;
    QSplitter *splitter_2;
    QDial *dial;
    QLabel *label_5;
    QLCDNumber *lcdNumber;
    QQuickWidget *quickWidget;

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
        dashboardButton = new QPushButton(Debug);
        dashboardButton->setObjectName(QStringLiteral("dashboardButton"));
        dashboardButton->setGeometry(QRect(140, 70, 101, 31));
        canButton = new QPushButton(Debug);
        canButton->setObjectName(QStringLiteral("canButton"));
        canButton->setGeometry(QRect(140, 110, 101, 31));
        quitButton = new QPushButton(Debug);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(140, 150, 101, 31));
        shutdownButton = new QPushButton(Debug);
        shutdownButton->setObjectName(QStringLiteral("shutdownButton"));
        shutdownButton->setGeometry(QRect(140, 230, 101, 31));
        stackSlide->addWidget(Debug);
        Music = new QWidget();
        Music->setObjectName(QStringLiteral("Music"));
        playerBar = new QProgressBar(Music);
        playerBar->setObjectName(QStringLiteral("playerBar"));
        playerBar->setGeometry(QRect(320, 80, 241, 23));
        playerBar->setMaximum(100);
        playerBar->setValue(0);
        playerBar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        playerBar->setTextVisible(true);
        playerBar->setInvertedAppearance(false);
        playerBar->setFormat(QStringLiteral(""));
        label = new QLabel(Music);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(320, 60, 47, 13));
        label_2 = new QLabel(Music);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 40, 41, 16));
        textArtist = new QLabel(Music);
        textArtist->setObjectName(QStringLiteral("textArtist"));
        textArtist->setGeometry(QRect(360, 40, 201, 16));
        textTitle = new QLabel(Music);
        textTitle->setObjectName(QStringLiteral("textTitle"));
        textTitle->setGeometry(QRect(360, 60, 201, 16));
        playButton = new QPushButton(Music);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(340, 140, 75, 23));
        playButton->setCheckable(true);
        stopButton = new QPushButton(Music);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(450, 140, 75, 23));
        prevButton = new QPushButton(Music);
        prevButton->setObjectName(QStringLiteral("prevButton"));
        prevButton->setGeometry(QRect(300, 190, 75, 23));
        nextButton = new QPushButton(Music);
        nextButton->setObjectName(QStringLiteral("nextButton"));
        nextButton->setGeometry(QRect(480, 190, 75, 23));
        volumeDial = new QDial(Music);
        volumeDial->setObjectName(QStringLiteral("volumeDial"));
        volumeDial->setGeometry(QRect(400, 170, 50, 64));
        volumeDial->setMaximum(100);
        playlistWidget = new QListWidget(Music);
        playlistWidget->setObjectName(QStringLiteral("playlistWidget"));
        playlistWidget->setGeometry(QRect(30, 40, 221, 192));
        playlistWidget->setFocusPolicy(Qt::NoFocus);
        playlistWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        playlistWidget->setProperty("showDropIndicator", QVariant(false));
        loopOneButton = new QRadioButton(Music);
        loopOneButton->setObjectName(QStringLiteral("loopOneButton"));
        loopOneButton->setGeometry(QRect(360, 260, 82, 17));
        loopOneButton->setAutoExclusive(false);
        loopAllButton = new QRadioButton(Music);
        loopAllButton->setObjectName(QStringLiteral("loopAllButton"));
        loopAllButton->setGeometry(QRect(450, 260, 82, 17));
        loopAllButton->setAutoExclusive(false);
        shuffleBox = new QCheckBox(Music);
        shuffleBox->setObjectName(QStringLiteral("shuffleBox"));
        shuffleBox->setGeometry(QRect(280, 260, 70, 17));
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
        qtPieMenu->setSelection(2);
        splitter->addWidget(qtPieMenu);
        stackSlide->addWidget(Menu);
        Radio = new QWidget();
        Radio->setObjectName(QStringLiteral("Radio"));
        nextStationButton = new QPushButton(Radio);
        nextStationButton->setObjectName(QStringLiteral("nextStationButton"));
        nextStationButton->setGeometry(QRect(230, 60, 101, 23));
        prevStationButton = new QPushButton(Radio);
        prevStationButton->setObjectName(QStringLiteral("prevStationButton"));
        prevStationButton->setGeometry(QRect(230, 300, 101, 23));
        stationWidget = new QListWidget(Radio);
        stationWidget->setObjectName(QStringLiteral("stationWidget"));
        stationWidget->setGeometry(QRect(500, 51, 221, 291));
        stationWidget->setFocusPolicy(Qt::NoFocus);
        stationWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        stationWidget->setProperty("showDropIndicator", QVariant(false));
        volumeDial_2 = new QDial(Radio);
        volumeDial_2->setObjectName(QStringLiteral("volumeDial_2"));
        volumeDial_2->setGeometry(QRect(340, 140, 91, 81));
        volumeDial_2->setMaximum(100);
        radioButton = new QRadioButton(Radio);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(250, 170, 61, 17));
        radioButton->setAutoExclusive(false);
        stackSlide->addWidget(Radio);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        lcdNumber_2 = new QLCDNumber(page_4);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(560, 30, 64, 23));
        lcdNumber_3 = new QLCDNumber(page_4);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(470, 30, 64, 23));
        lcdNumber_4 = new QLCDNumber(page_4);
        lcdNumber_4->setObjectName(QStringLiteral("lcdNumber_4"));
        lcdNumber_4->setGeometry(QRect(470, 60, 64, 23));
        lcdNumber_5 = new QLCDNumber(page_4);
        lcdNumber_5->setObjectName(QStringLiteral("lcdNumber_5"));
        lcdNumber_5->setGeometry(QRect(560, 60, 64, 23));
        lcdNumber_6 = new QLCDNumber(page_4);
        lcdNumber_6->setObjectName(QStringLiteral("lcdNumber_6"));
        lcdNumber_6->setGeometry(QRect(630, 60, 64, 23));
        lcdNumber_7 = new QLCDNumber(page_4);
        lcdNumber_7->setObjectName(QStringLiteral("lcdNumber_7"));
        lcdNumber_7->setGeometry(QRect(630, 30, 64, 23));
        label_3 = new QLabel(page_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(346, 30, 101, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(page_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(346, 60, 101, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdNumber_8 = new QLCDNumber(page_4);
        lcdNumber_8->setObjectName(QStringLiteral("lcdNumber_8"));
        lcdNumber_8->setGeometry(QRect(630, 110, 64, 23));
        lcdNumber_9 = new QLCDNumber(page_4);
        lcdNumber_9->setObjectName(QStringLiteral("lcdNumber_9"));
        lcdNumber_9->setGeometry(QRect(630, 140, 64, 23));
        label_6 = new QLabel(page_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(346, 110, 101, 20));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdNumber_10 = new QLCDNumber(page_4);
        lcdNumber_10->setObjectName(QStringLiteral("lcdNumber_10"));
        lcdNumber_10->setGeometry(QRect(470, 110, 64, 23));
        lcdNumber_11 = new QLCDNumber(page_4);
        lcdNumber_11->setObjectName(QStringLiteral("lcdNumber_11"));
        lcdNumber_11->setGeometry(QRect(560, 110, 64, 23));
        lcdNumber_12 = new QLCDNumber(page_4);
        lcdNumber_12->setObjectName(QStringLiteral("lcdNumber_12"));
        lcdNumber_12->setGeometry(QRect(470, 140, 64, 23));
        lcdNumber_13 = new QLCDNumber(page_4);
        lcdNumber_13->setObjectName(QStringLiteral("lcdNumber_13"));
        lcdNumber_13->setGeometry(QRect(560, 140, 64, 23));
        label_7 = new QLabel(page_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(346, 140, 101, 20));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line = new QFrame(page_4);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(540, 30, 16, 341));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(page_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(480, 10, 47, 13));
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(page_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(570, 10, 47, 13));
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(page_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(640, 10, 47, 13));
        label_10->setAlignment(Qt::AlignCenter);
        lcdNumber_14 = new QLCDNumber(page_4);
        lcdNumber_14->setObjectName(QStringLiteral("lcdNumber_14"));
        lcdNumber_14->setGeometry(QRect(560, 230, 64, 23));
        label_11 = new QLabel(page_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(346, 200, 101, 20));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdNumber_15 = new QLCDNumber(page_4);
        lcdNumber_15->setObjectName(QStringLiteral("lcdNumber_15"));
        lcdNumber_15->setGeometry(QRect(630, 230, 64, 23));
        lcdNumber_16 = new QLCDNumber(page_4);
        lcdNumber_16->setObjectName(QStringLiteral("lcdNumber_16"));
        lcdNumber_16->setGeometry(QRect(630, 200, 64, 23));
        lcdNumber_17 = new QLCDNumber(page_4);
        lcdNumber_17->setObjectName(QStringLiteral("lcdNumber_17"));
        lcdNumber_17->setGeometry(QRect(470, 200, 64, 23));
        label_12 = new QLabel(page_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(346, 230, 101, 20));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdNumber_18 = new QLCDNumber(page_4);
        lcdNumber_18->setObjectName(QStringLiteral("lcdNumber_18"));
        lcdNumber_18->setGeometry(QRect(560, 200, 64, 23));
        lcdNumber_19 = new QLCDNumber(page_4);
        lcdNumber_19->setObjectName(QStringLiteral("lcdNumber_19"));
        lcdNumber_19->setGeometry(QRect(470, 230, 64, 23));
        lcdNumber_20 = new QLCDNumber(page_4);
        lcdNumber_20->setObjectName(QStringLiteral("lcdNumber_20"));
        lcdNumber_20->setGeometry(QRect(630, 260, 64, 23));
        label_13 = new QLabel(page_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(346, 260, 101, 20));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdNumber_21 = new QLCDNumber(page_4);
        lcdNumber_21->setObjectName(QStringLiteral("lcdNumber_21"));
        lcdNumber_21->setGeometry(QRect(470, 260, 64, 23));
        lcdNumber_22 = new QLCDNumber(page_4);
        lcdNumber_22->setObjectName(QStringLiteral("lcdNumber_22"));
        lcdNumber_22->setGeometry(QRect(560, 260, 64, 23));
        lcdNumber_23 = new QLCDNumber(page_4);
        lcdNumber_23->setObjectName(QStringLiteral("lcdNumber_23"));
        lcdNumber_23->setGeometry(QRect(700, 130, 64, 23));
        label_14 = new QLabel(page_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(710, 110, 47, 13));
        label_14->setAlignment(Qt::AlignCenter);
        stackSlide->addWidget(page_4);
        splitter_2 = new QSplitter(TestDialog);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(-10, 0, 791, 61));
        splitter_2->setOrientation(Qt::Horizontal);
        dial = new QDial(splitter_2);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setFocusPolicy(Qt::NoFocus);
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
        quickWidget = new QQuickWidget(TestDialog);
        quickWidget->setObjectName(QStringLiteral("quickWidget"));
        quickWidget->setGeometry(QRect(0, 0, 800, 480));
        quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        quickWidget->raise();
        stackSlide->raise();
        splitter_2->raise();
        QWidget::setTabOrder(dashboardButton, canButton);
        QWidget::setTabOrder(canButton, playButton);
        QWidget::setTabOrder(playButton, stopButton);
        QWidget::setTabOrder(stopButton, prevButton);
        QWidget::setTabOrder(prevButton, nextButton);
        QWidget::setTabOrder(nextButton, volumeDial);
        QWidget::setTabOrder(volumeDial, shuffleBox);
        QWidget::setTabOrder(shuffleBox, loopOneButton);
        QWidget::setTabOrder(loopOneButton, loopAllButton);

        retranslateUi(TestDialog);
        QObject::connect(qtPieMenu, SIGNAL(itemSelect(int)), stackSlide, SLOT(slideInIdx(int)));

        stackSlide->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(TestDialog);
    } // setupUi

    void retranslateUi(QDialog *TestDialog)
    {
        TestDialog->setWindowTitle(QApplication::translate("TestDialog", "TestDialog", Q_NULLPTR));
        dashboardButton->setText(QApplication::translate("TestDialog", "Dashboard", Q_NULLPTR));
        canButton->setText(QApplication::translate("TestDialog", "CAN-Bus", Q_NULLPTR));
        quitButton->setText(QApplication::translate("TestDialog", "Exit", Q_NULLPTR));
        shutdownButton->setText(QApplication::translate("TestDialog", "Shutdown", Q_NULLPTR));
        label->setText(QApplication::translate("TestDialog", "Title:", Q_NULLPTR));
        label_2->setText(QApplication::translate("TestDialog", "Artist:", Q_NULLPTR));
        textArtist->setText(QApplication::translate("TestDialog", "-", Q_NULLPTR));
        textTitle->setText(QApplication::translate("TestDialog", "-", Q_NULLPTR));
        playButton->setText(QApplication::translate("TestDialog", "Play", Q_NULLPTR));
        stopButton->setText(QApplication::translate("TestDialog", "Stop", Q_NULLPTR));
        prevButton->setText(QApplication::translate("TestDialog", "Previous", Q_NULLPTR));
        nextButton->setText(QApplication::translate("TestDialog", "Next", Q_NULLPTR));
        loopOneButton->setText(QApplication::translate("TestDialog", "Loop Song", Q_NULLPTR));
        loopAllButton->setText(QApplication::translate("TestDialog", "Loop All", Q_NULLPTR));
        shuffleBox->setText(QApplication::translate("TestDialog", "Shuffle", Q_NULLPTR));
        nextStationButton->setText(QApplication::translate("TestDialog", "Next Station", Q_NULLPTR));
        prevStationButton->setText(QApplication::translate("TestDialog", "Previous Station", Q_NULLPTR));
        radioButton->setText(QApplication::translate("TestDialog", "Radio", Q_NULLPTR));
        label_3->setText(QApplication::translate("TestDialog", "Motor 1 Amps(R):", Q_NULLPTR));
        label_4->setText(QApplication::translate("TestDialog", "Motor 2 Amps(L):", Q_NULLPTR));
        label_6->setText(QApplication::translate("TestDialog", "Battery 1 Amps(R):", Q_NULLPTR));
        label_7->setText(QApplication::translate("TestDialog", " Battery 2 Amps(L):", Q_NULLPTR));
        label_8->setText(QApplication::translate("TestDialog", "Value:", Q_NULLPTR));
        label_9->setText(QApplication::translate("TestDialog", "Min:", Q_NULLPTR));
        label_10->setText(QApplication::translate("TestDialog", "Max:", Q_NULLPTR));
        label_11->setText(QApplication::translate("TestDialog", "MCU Temp:", Q_NULLPTR));
        label_12->setText(QApplication::translate("TestDialog", "MOSFET 1 Temp:", Q_NULLPTR));
        label_13->setText(QApplication::translate("TestDialog", "MOSFET 2 Temp:", Q_NULLPTR));
        label_14->setText(QApplication::translate("TestDialog", "Sum:", Q_NULLPTR));
        label_5->setText(QApplication::translate("TestDialog", "UserName", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
