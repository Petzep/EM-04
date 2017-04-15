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
    QDial *volumeDail;
    QListWidget *playlistWidget;
    QRadioButton *loopOneButton;
    QRadioButton *loopAllButton;
    QCheckBox *shuffleBox;
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
        volumeDail = new QDial(Music);
        volumeDail->setObjectName(QStringLiteral("volumeDail"));
        volumeDail->setGeometry(QRect(400, 170, 50, 64));
        volumeDail->setMaximum(100);
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
        QWidget::setTabOrder(dashboardButton, canButton);
        QWidget::setTabOrder(canButton, playButton);
        QWidget::setTabOrder(playButton, stopButton);
        QWidget::setTabOrder(stopButton, prevButton);
        QWidget::setTabOrder(prevButton, nextButton);
        QWidget::setTabOrder(nextButton, volumeDail);
        QWidget::setTabOrder(volumeDail, shuffleBox);
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
        label_5->setText(QApplication::translate("TestDialog", "UserName", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
