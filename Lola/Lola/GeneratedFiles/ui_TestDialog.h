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
    QLCDNumber *lcdMot1AmpMin;
    QLCDNumber *lcdMot1Amp;
    QLCDNumber *lcdMot2Amp;
    QLCDNumber *lcdMot2AmpMin;
    QLCDNumber *lcdMot2AmpMax;
    QLCDNumber *lcdMot1AmpMax;
    QLabel *label_3;
    QLabel *label_4;
    QLCDNumber *lcdBat1AmpMax;
    QLCDNumber *lcdBat2AmpMax;
    QLabel *label_6;
    QLCDNumber *lcdBat1Amp;
    QLCDNumber *lcdBat1AmpMin;
    QLCDNumber *lcdBat2Amp;
    QLCDNumber *lcdBat2AmpMin;
    QLabel *label_7;
    QFrame *line;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLCDNumber *lcdMos1TempMin;
    QLabel *label_11;
    QLCDNumber *lcdMos1TempMax;
    QLCDNumber *lcdMCUTempMax;
    QLCDNumber *lcdMCUTemp;
    QLabel *label_12;
    QLCDNumber *lcdMCUTempMin;
    QLCDNumber *lcdMos1Temp;
    QLCDNumber *lcdMos2TempMax;
    QLabel *label_13;
    QLCDNumber *lcdMos2Temp;
    QLCDNumber *lcdMos2TempMin;
    QLCDNumber *lcdBatSum;
    QLabel *label_14;
    QLCDNumber *lcdIntVoltMax;
    QLabel *label_5;
    QLCDNumber *lcdIntVoltMin;
    QLCDNumber *lcdIntVolt;
    QLCDNumber *lcdBatVoltMax;
    QLabel *label_15;
    QLCDNumber *lcdBatVoltMin;
    QLCDNumber *lcdBatVolt;
    QFrame *line_2;
    QFrame *line_3;
    QLCDNumber *lcdMot2PowerMax;
    QLabel *label_16;
    QLCDNumber *lcdMot1PowerMax;
    QLCDNumber *lcdMot2PowerMin;
    QLCDNumber *lcdMot1PowerMin;
    QLCDNumber *lcdMot1Power;
    QLabel *label_17;
    QLCDNumber *lcdMot2Power;
    QSplitter *splitter_2;
    QLabel *dnrLabel;
    QLabel *userLabel;
    QLCDNumber *speedLabel;
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
        lcdMot1AmpMin = new QLCDNumber(page_4);
        lcdMot1AmpMin->setObjectName(QStringLiteral("lcdMot1AmpMin"));
        lcdMot1AmpMin->setGeometry(QRect(560, 30, 64, 23));
        lcdMot1Amp = new QLCDNumber(page_4);
        lcdMot1Amp->setObjectName(QStringLiteral("lcdMot1Amp"));
        lcdMot1Amp->setGeometry(QRect(470, 30, 64, 23));
        lcdMot2Amp = new QLCDNumber(page_4);
        lcdMot2Amp->setObjectName(QStringLiteral("lcdMot2Amp"));
        lcdMot2Amp->setGeometry(QRect(470, 60, 64, 23));
        lcdMot2AmpMin = new QLCDNumber(page_4);
        lcdMot2AmpMin->setObjectName(QStringLiteral("lcdMot2AmpMin"));
        lcdMot2AmpMin->setGeometry(QRect(560, 60, 64, 23));
        lcdMot2AmpMax = new QLCDNumber(page_4);
        lcdMot2AmpMax->setObjectName(QStringLiteral("lcdMot2AmpMax"));
        lcdMot2AmpMax->setGeometry(QRect(630, 60, 64, 23));
        lcdMot1AmpMax = new QLCDNumber(page_4);
        lcdMot1AmpMax->setObjectName(QStringLiteral("lcdMot1AmpMax"));
        lcdMot1AmpMax->setGeometry(QRect(630, 30, 64, 23));
        label_3 = new QLabel(page_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(346, 30, 101, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(page_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(346, 60, 101, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdBat1AmpMax = new QLCDNumber(page_4);
        lcdBat1AmpMax->setObjectName(QStringLiteral("lcdBat1AmpMax"));
        lcdBat1AmpMax->setGeometry(QRect(630, 230, 64, 23));
        lcdBat2AmpMax = new QLCDNumber(page_4);
        lcdBat2AmpMax->setObjectName(QStringLiteral("lcdBat2AmpMax"));
        lcdBat2AmpMax->setGeometry(QRect(630, 260, 64, 23));
        label_6 = new QLabel(page_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(346, 230, 101, 20));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdBat1Amp = new QLCDNumber(page_4);
        lcdBat1Amp->setObjectName(QStringLiteral("lcdBat1Amp"));
        lcdBat1Amp->setGeometry(QRect(470, 230, 64, 23));
        lcdBat1AmpMin = new QLCDNumber(page_4);
        lcdBat1AmpMin->setObjectName(QStringLiteral("lcdBat1AmpMin"));
        lcdBat1AmpMin->setGeometry(QRect(560, 230, 64, 23));
        lcdBat2Amp = new QLCDNumber(page_4);
        lcdBat2Amp->setObjectName(QStringLiteral("lcdBat2Amp"));
        lcdBat2Amp->setGeometry(QRect(470, 260, 64, 23));
        lcdBat2AmpMin = new QLCDNumber(page_4);
        lcdBat2AmpMin->setObjectName(QStringLiteral("lcdBat2AmpMin"));
        lcdBat2AmpMin->setGeometry(QRect(560, 260, 64, 23));
        label_7 = new QLabel(page_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(346, 260, 101, 20));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line = new QFrame(page_4);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(540, 30, 16, 361));
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
        lcdMos1TempMin = new QLCDNumber(page_4);
        lcdMos1TempMin->setObjectName(QStringLiteral("lcdMos1TempMin"));
        lcdMos1TempMin->setGeometry(QRect(560, 330, 64, 23));
        label_11 = new QLabel(page_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(346, 300, 101, 20));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdMos1TempMax = new QLCDNumber(page_4);
        lcdMos1TempMax->setObjectName(QStringLiteral("lcdMos1TempMax"));
        lcdMos1TempMax->setGeometry(QRect(630, 330, 64, 23));
        lcdMCUTempMax = new QLCDNumber(page_4);
        lcdMCUTempMax->setObjectName(QStringLiteral("lcdMCUTempMax"));
        lcdMCUTempMax->setGeometry(QRect(630, 300, 64, 23));
        lcdMCUTemp = new QLCDNumber(page_4);
        lcdMCUTemp->setObjectName(QStringLiteral("lcdMCUTemp"));
        lcdMCUTemp->setGeometry(QRect(470, 300, 64, 23));
        label_12 = new QLabel(page_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(346, 330, 101, 20));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdMCUTempMin = new QLCDNumber(page_4);
        lcdMCUTempMin->setObjectName(QStringLiteral("lcdMCUTempMin"));
        lcdMCUTempMin->setGeometry(QRect(560, 300, 64, 23));
        lcdMos1Temp = new QLCDNumber(page_4);
        lcdMos1Temp->setObjectName(QStringLiteral("lcdMos1Temp"));
        lcdMos1Temp->setGeometry(QRect(470, 330, 64, 23));
        lcdMos2TempMax = new QLCDNumber(page_4);
        lcdMos2TempMax->setObjectName(QStringLiteral("lcdMos2TempMax"));
        lcdMos2TempMax->setGeometry(QRect(630, 360, 64, 23));
        label_13 = new QLabel(page_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(346, 360, 101, 20));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdMos2Temp = new QLCDNumber(page_4);
        lcdMos2Temp->setObjectName(QStringLiteral("lcdMos2Temp"));
        lcdMos2Temp->setGeometry(QRect(470, 360, 64, 23));
        lcdMos2TempMin = new QLCDNumber(page_4);
        lcdMos2TempMin->setObjectName(QStringLiteral("lcdMos2TempMin"));
        lcdMos2TempMin->setGeometry(QRect(560, 360, 64, 23));
        lcdBatSum = new QLCDNumber(page_4);
        lcdBatSum->setObjectName(QStringLiteral("lcdBatSum"));
        lcdBatSum->setGeometry(QRect(700, 250, 64, 23));
        label_14 = new QLabel(page_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(710, 230, 47, 13));
        label_14->setAlignment(Qt::AlignCenter);
        lcdIntVoltMax = new QLCDNumber(page_4);
        lcdIntVoltMax->setObjectName(QStringLiteral("lcdIntVoltMax"));
        lcdIntVoltMax->setGeometry(QRect(630, 200, 64, 23));
        label_5 = new QLabel(page_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(350, 170, 101, 20));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdIntVoltMin = new QLCDNumber(page_4);
        lcdIntVoltMin->setObjectName(QStringLiteral("lcdIntVoltMin"));
        lcdIntVoltMin->setGeometry(QRect(560, 200, 64, 23));
        lcdIntVolt = new QLCDNumber(page_4);
        lcdIntVolt->setObjectName(QStringLiteral("lcdIntVolt"));
        lcdIntVolt->setGeometry(QRect(470, 200, 64, 23));
        lcdBatVoltMax = new QLCDNumber(page_4);
        lcdBatVoltMax->setObjectName(QStringLiteral("lcdBatVoltMax"));
        lcdBatVoltMax->setGeometry(QRect(630, 170, 64, 23));
        label_15 = new QLabel(page_4);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(350, 200, 101, 20));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdBatVoltMin = new QLCDNumber(page_4);
        lcdBatVoltMin->setObjectName(QStringLiteral("lcdBatVoltMin"));
        lcdBatVoltMin->setGeometry(QRect(560, 170, 64, 23));
        lcdBatVolt = new QLCDNumber(page_4);
        lcdBatVolt->setObjectName(QStringLiteral("lcdBatVolt"));
        lcdBatVolt->setGeometry(QRect(470, 170, 64, 23));
        line_2 = new QFrame(page_4);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(350, 280, 411, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(page_4);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(340, 150, 411, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        lcdMot2PowerMax = new QLCDNumber(page_4);
        lcdMot2PowerMax->setObjectName(QStringLiteral("lcdMot2PowerMax"));
        lcdMot2PowerMax->setGeometry(QRect(630, 120, 64, 23));
        label_16 = new QLabel(page_4);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(346, 120, 101, 20));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdMot1PowerMax = new QLCDNumber(page_4);
        lcdMot1PowerMax->setObjectName(QStringLiteral("lcdMot1PowerMax"));
        lcdMot1PowerMax->setGeometry(QRect(630, 90, 64, 23));
        lcdMot2PowerMin = new QLCDNumber(page_4);
        lcdMot2PowerMin->setObjectName(QStringLiteral("lcdMot2PowerMin"));
        lcdMot2PowerMin->setGeometry(QRect(560, 120, 64, 23));
        lcdMot1PowerMin = new QLCDNumber(page_4);
        lcdMot1PowerMin->setObjectName(QStringLiteral("lcdMot1PowerMin"));
        lcdMot1PowerMin->setGeometry(QRect(560, 90, 64, 23));
        lcdMot1Power = new QLCDNumber(page_4);
        lcdMot1Power->setObjectName(QStringLiteral("lcdMot1Power"));
        lcdMot1Power->setGeometry(QRect(470, 90, 64, 23));
        label_17 = new QLabel(page_4);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(346, 90, 101, 20));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lcdMot2Power = new QLCDNumber(page_4);
        lcdMot2Power->setObjectName(QStringLiteral("lcdMot2Power"));
        lcdMot2Power->setGeometry(QRect(470, 120, 64, 23));
        stackSlide->addWidget(page_4);
        splitter_2 = new QSplitter(TestDialog);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(-10, 0, 791, 61));
        splitter_2->setOrientation(Qt::Horizontal);
        dnrLabel = new QLabel(splitter_2);
        dnrLabel->setObjectName(QStringLiteral("dnrLabel"));
        dnrLabel->setAlignment(Qt::AlignCenter);
        splitter_2->addWidget(dnrLabel);
        userLabel = new QLabel(splitter_2);
        userLabel->setObjectName(QStringLiteral("userLabel"));
        userLabel->setAlignment(Qt::AlignCenter);
        splitter_2->addWidget(userLabel);
        speedLabel = new QLCDNumber(splitter_2);
        speedLabel->setObjectName(QStringLiteral("speedLabel"));
        splitter_2->addWidget(speedLabel);
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
        label_5->setText(QApplication::translate("TestDialog", "Battery Voltage:", Q_NULLPTR));
        label_15->setText(QApplication::translate("TestDialog", "Internal Voltage", Q_NULLPTR));
        label_16->setText(QApplication::translate("TestDialog", "Motor 2 Power(L):", Q_NULLPTR));
        label_17->setText(QApplication::translate("TestDialog", "Motor 1 Power(R):", Q_NULLPTR));
        dnrLabel->setText(QApplication::translate("TestDialog", "DNR_setting", Q_NULLPTR));
        userLabel->setText(QApplication::translate("TestDialog", "TU/Ecomotive", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
