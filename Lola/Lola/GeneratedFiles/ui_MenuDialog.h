/********************************************************************************
** Form generated from reading UI file 'MenuDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUDIALOG_H
#define UI_MENUDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CustomClock.h"
#include "QtPieMenu.h"
#include "StackSlide.h"

QT_BEGIN_NAMESPACE

class Ui_MenuDialog
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QTextBrowser *textBrowser;
    QGroupBox *controllerBox;
    QDial *controlDial;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *homeButton;
    QPushButton *okButton;
    QPushButton *backButton;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *debugCheckBox;
    QVBoxLayout *verticalLayout_2;
    StackSlide *stackSlide;
    QWidget *page;
    CustomClock *customClock;
    QProgressBar *progressBar;
    QLCDNumber *lcdNumber;
    QLabel *label;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QWidget *leftPage;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *midPage;
    QGridLayout *gridLayout;
    QtPieMenu *qtPieMenu_2;
    QLabel *selectionLabel;
    QWidget *rightPage;
    QPushButton *pushButton_12;
    QPushButton *pushButton_9;
    QPushButton *pushButton_7;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QPushButton *pushButton_11;
    QWidget *page_2;
    QDial *bassDial;
    QDial *trebDial;
    QDial *volumeDial;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QSlider *horizontalSlider;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *MenuDialog)
    {
        if (MenuDialog->objectName().isEmpty())
            MenuDialog->setObjectName(QStringLiteral("MenuDialog"));
        MenuDialog->setEnabled(true);
        MenuDialog->resize(689, 367);
        gridLayout_2 = new QGridLayout(MenuDialog);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_2 = new QGroupBox(MenuDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(251, 91));
        textBrowser = new QTextBrowser(groupBox_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setEnabled(true);
        textBrowser->setGeometry(QRect(10, 20, 221, 61));
        textBrowser->setMinimumSize(QSize(221, 61));
        textBrowser->setFocusPolicy(Qt::NoFocus);
        textBrowser->setAcceptDrops(false);

        verticalLayout_3->addWidget(groupBox_2);

        controllerBox = new QGroupBox(MenuDialog);
        controllerBox->setObjectName(QStringLiteral("controllerBox"));
        controllerBox->setMinimumSize(QSize(261, 141));
        controlDial = new QDial(controllerBox);
        controlDial->setObjectName(QStringLiteral("controlDial"));
        controlDial->setGeometry(QRect(90, 20, 61, 61));
        controlDial->setMinimumSize(QSize(61, 61));
        controlDial->setFocusPolicy(Qt::NoFocus);
        controlDial->setMinimum(2);
        controlDial->setMaximum(7);
        controlDial->setValue(2);
        controlDial->setSliderPosition(2);
        controlDial->setTracking(true);
        controlDial->setInvertedAppearance(true);
        controlDial->setInvertedControls(true);
        controlDial->setWrapping(true);
        controlDial->setNotchesVisible(true);
        layoutWidget = new QWidget(controllerBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 100, 239, 25));
        layoutWidget->setMinimumSize(QSize(239, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        homeButton = new QPushButton(layoutWidget);
        homeButton->setObjectName(QStringLiteral("homeButton"));
        homeButton->setMinimumSize(QSize(75, 23));
        homeButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(homeButton);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setMinimumSize(QSize(75, 23));
        okButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(okButton);

        backButton = new QPushButton(layoutWidget);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setMinimumSize(QSize(75, 23));
        backButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(backButton);


        verticalLayout_3->addWidget(controllerBox);

        groupBox = new QGroupBox(MenuDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(261, 81));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 20, 71, 16));
        label_2->setMinimumSize(QSize(71, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(90, 20, 51, 16));
        label_3->setMinimumSize(QSize(51, 16));
        debugCheckBox = new QCheckBox(groupBox);
        debugCheckBox->setObjectName(QStringLiteral("debugCheckBox"));
        debugCheckBox->setGeometry(QRect(20, 50, 121, 17));
        debugCheckBox->setMinimumSize(QSize(121, 17));
        debugCheckBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(groupBox);


        gridLayout_2->addLayout(verticalLayout_3, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        stackSlide = new StackSlide(MenuDialog);
        stackSlide->setObjectName(QStringLiteral("stackSlide"));
        stackSlide->setLineWidth(7);
        stackSlide->setMenuPage(2);
        stackSlide->setWrap(false);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        customClock = new CustomClock(page);
        customClock->setObjectName(QStringLiteral("customClock"));
        customClock->setGeometry(QRect(50, 80, 100, 100));
        progressBar = new QProgressBar(page);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(50, 250, 161, 20));
        progressBar->setValue(24);
        lcdNumber = new QLCDNumber(page);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(30, 30, 64, 23));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 30, 81, 21));
        pushButton_13 = new QPushButton(page);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(30, 200, 75, 23));
        pushButton_14 = new QPushButton(page);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(120, 200, 75, 23));
        stackSlide->addWidget(page);
        leftPage = new QWidget();
        leftPage->setObjectName(QStringLiteral("leftPage"));
        pushButton = new QPushButton(leftPage);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 40, 70, 23));
        pushButton_2 = new QPushButton(leftPage);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(90, 80, 75, 23));
        pushButton_3 = new QPushButton(leftPage);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(80, 120, 75, 23));
        pushButton_4 = new QPushButton(leftPage);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(80, 160, 75, 23));
        pushButton_5 = new QPushButton(leftPage);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(90, 200, 75, 23));
        pushButton_6 = new QPushButton(leftPage);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(120, 240, 75, 23));
        stackSlide->addWidget(leftPage);
        midPage = new QWidget();
        midPage->setObjectName(QStringLiteral("midPage"));
        gridLayout = new QGridLayout(midPage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        qtPieMenu_2 = new QtPieMenu(midPage);
        qtPieMenu_2->setObjectName(QStringLiteral("qtPieMenu_2"));
        qtPieMenu_2->setMinimumSize(QSize(251, 261));
        qtPieMenu_2->setFocusPolicy(Qt::ClickFocus);
        qtPieMenu_2->setSelection(2);

        gridLayout->addWidget(qtPieMenu_2, 1, 0, 1, 1);

        selectionLabel = new QLabel(midPage);
        selectionLabel->setObjectName(QStringLiteral("selectionLabel"));
        selectionLabel->setMaximumSize(QSize(16777215, 19));
        selectionLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(selectionLabel, 0, 0, 1, 1);

        stackSlide->addWidget(midPage);
        rightPage = new QWidget();
        rightPage->setObjectName(QStringLiteral("rightPage"));
        pushButton_12 = new QPushButton(rightPage);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(110, 240, 75, 23));
        pushButton_9 = new QPushButton(rightPage);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(150, 60, 75, 23));
        pushButton_7 = new QPushButton(rightPage);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(110, 30, 70, 23));
        pushButton_10 = new QPushButton(rightPage);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(180, 140, 75, 23));
        pushButton_8 = new QPushButton(rightPage);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(160, 190, 75, 23));
        pushButton_11 = new QPushButton(rightPage);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(180, 100, 75, 23));
        stackSlide->addWidget(rightPage);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        bassDial = new QDial(page_2);
        bassDial->setObjectName(QStringLiteral("bassDial"));
        bassDial->setGeometry(QRect(110, 20, 50, 64));
        bassDial->setMaximum(10);
        bassDial->setNotchTarget(17);
        bassDial->setNotchesVisible(false);
        trebDial = new QDial(page_2);
        trebDial->setObjectName(QStringLiteral("trebDial"));
        trebDial->setGeometry(QRect(110, 220, 50, 64));
        trebDial->setMaximum(10);
        trebDial->setNotchTarget(17);
        trebDial->setNotchesVisible(false);
        volumeDial = new QDial(page_2);
        volumeDial->setObjectName(QStringLiteral("volumeDial"));
        volumeDial->setGeometry(QRect(180, 90, 111, 111));
        volumeDial->setMaximum(50);
        volumeDial->setValue(10);
        volumeDial->setNotchTarget(0.75);
        volumeDial->setNotchesVisible(false);
        label_4 = new QLabel(page_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 40, 47, 13));
        label_5 = new QLabel(page_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(160, 250, 47, 13));
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(220, 70, 47, 13));
        stackSlide->addWidget(page_2);

        verticalLayout_2->addWidget(stackSlide);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalSlider = new QSlider(MenuDialog);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setEnabled(true);
        horizontalSlider->setMouseTracking(true);
        horizontalSlider->setFocusPolicy(Qt::NoFocus);
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(4);
        horizontalSlider->setValue(2);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksAbove);
        horizontalSlider->setTickInterval(1);

        horizontalLayout_2->addWidget(horizontalSlider);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout_2, 1, 2, 1, 1);

        QWidget::setTabOrder(pushButton_13, pushButton_14);
        QWidget::setTabOrder(pushButton_14, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, pushButton_3);
        QWidget::setTabOrder(pushButton_3, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_5);
        QWidget::setTabOrder(pushButton_5, pushButton_6);
        QWidget::setTabOrder(pushButton_6, pushButton_7);
        QWidget::setTabOrder(pushButton_7, pushButton_9);
        QWidget::setTabOrder(pushButton_9, pushButton_11);
        QWidget::setTabOrder(pushButton_11, pushButton_10);
        QWidget::setTabOrder(pushButton_10, pushButton_8);
        QWidget::setTabOrder(pushButton_8, pushButton_12);
        QWidget::setTabOrder(pushButton_12, bassDial);
        QWidget::setTabOrder(bassDial, volumeDial);
        QWidget::setTabOrder(volumeDial, trebDial);

        retranslateUi(MenuDialog);
        QObject::connect(okButton, SIGNAL(clicked()), qtPieMenu_2, SLOT(select()));
        QObject::connect(qtPieMenu_2, SIGNAL(itemSelect(int)), stackSlide, SLOT(slideInIdx(int)));
        QObject::connect(homeButton, SIGNAL(clicked()), stackSlide, SLOT(slideHome()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), stackSlide, SLOT(slideInIdx(int)));
        QObject::connect(qtPieMenu_2, SIGNAL(itemName(QString)), selectionLabel, SLOT(setText(QString)));
        QObject::connect(qtPieMenu_2, SIGNAL(itemSelect(int)), label_3, SLOT(setNum(int)));
        QObject::connect(debugCheckBox, SIGNAL(toggled(bool)), controllerBox, SLOT(setEnabled(bool)));
        QObject::connect(debugCheckBox, SIGNAL(toggled(bool)), horizontalSlider, SLOT(setEnabled(bool)));

        stackSlide->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MenuDialog);
    } // setupUi

    void retranslateUi(QDialog *MenuDialog)
    {
        MenuDialog->setWindowTitle(QApplication::translate("MenuDialog", "MenuDialog", 0));
        groupBox_2->setTitle(QApplication::translate("MenuDialog", "Controls", 0));
        textBrowser->setHtml(QApplication::translate("MenuDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Left:    [4]	Select:    [5]</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Right:  [6]	Back:      [7]</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">	Home:     [0]</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        controllerBox->setTitle(QApplication::translate("MenuDialog", "Controller", 0));
        homeButton->setText(QApplication::translate("MenuDialog", "&Home", 0));
        okButton->setText(QApplication::translate("MenuDialog", "&OK", 0));
        backButton->setText(QApplication::translate("MenuDialog", "&Back", 0));
        groupBox->setTitle(QApplication::translate("MenuDialog", "Debug info:", 0));
        label_2->setText(QApplication::translate("MenuDialog", "Item Number:", 0));
        label_3->setText(QString());
        debugCheckBox->setText(QApplication::translate("MenuDialog", "DebugControlers", 0));
        label->setText(QApplication::translate("MenuDialog", "Test Text", 0));
        pushButton_13->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_14->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_3->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_4->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_5->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_6->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        selectionLabel->setText(QApplication::translate("MenuDialog", "EM-04", 0));
        pushButton_12->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_9->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_7->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_10->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_8->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_11->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        label_4->setText(QApplication::translate("MenuDialog", "Bass", 0));
        label_5->setText(QApplication::translate("MenuDialog", "Trebble", 0));
        label_6->setText(QApplication::translate("MenuDialog", "Volume", 0));
    } // retranslateUi

};

namespace Ui {
    class MenuDialog: public Ui_MenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUDIALOG_H
