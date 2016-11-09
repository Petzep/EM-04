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
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CustomClock.h"
#include "QtPieMenu.h"
#include "StackSlide.h"

QT_BEGIN_NAMESPACE

class Ui_MenuDialog
{
public:
    QSlider *horizontalSlider;
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
    QtPieMenu *qtPieMenu_2;
    QWidget *rightPage;
    QPushButton *pushButton_12;
    QPushButton *pushButton_9;
    QPushButton *pushButton_7;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QPushButton *pushButton_11;
    QWidget *page_2;
    QPushButton *pushButton_24;
    QPushButton *pushButton_19;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QGroupBox *controllerBox;
    QDial *dial;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *homeButton;
    QPushButton *okButton;
    QPushButton *backButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *MenuDialog)
    {
        if (MenuDialog->objectName().isEmpty())
            MenuDialog->setObjectName(QStringLiteral("MenuDialog"));
        MenuDialog->resize(704, 368);
        horizontalSlider = new QSlider(MenuDialog);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(420, 340, 160, 22));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(4);
        horizontalSlider->setValue(2);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksAbove);
        horizontalSlider->setTickInterval(1);
        stackSlide = new StackSlide(MenuDialog);
        stackSlide->setObjectName(QStringLiteral("stackSlide"));
        stackSlide->setGeometry(QRect(350, 30, 321, 301));
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
        qtPieMenu_2 = new QtPieMenu(midPage);
        qtPieMenu_2->setObjectName(QStringLiteral("qtPieMenu_2"));
        qtPieMenu_2->setGeometry(QRect(30, 30, 251, 261));
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
        pushButton_24 = new QPushButton(page_2);
        pushButton_24->setObjectName(QStringLiteral("pushButton_24"));
        pushButton_24->setGeometry(QRect(150, 190, 75, 23));
        pushButton_19 = new QPushButton(page_2);
        pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
        pushButton_19->setGeometry(QRect(100, 30, 70, 23));
        pushButton_22 = new QPushButton(page_2);
        pushButton_22->setObjectName(QStringLiteral("pushButton_22"));
        pushButton_22->setGeometry(QRect(100, 240, 75, 23));
        pushButton_23 = new QPushButton(page_2);
        pushButton_23->setObjectName(QStringLiteral("pushButton_23"));
        pushButton_23->setGeometry(QRect(170, 140, 75, 23));
        pushButton_20 = new QPushButton(page_2);
        pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
        pushButton_20->setGeometry(QRect(170, 100, 75, 23));
        pushButton_21 = new QPushButton(page_2);
        pushButton_21->setObjectName(QStringLiteral("pushButton_21"));
        pushButton_21->setGeometry(QRect(140, 60, 75, 23));
        stackSlide->addWidget(page_2);
        controllerBox = new QGroupBox(MenuDialog);
        controllerBox->setObjectName(QStringLiteral("controllerBox"));
        controllerBox->setGeometry(QRect(60, 100, 251, 141));
        dial = new QDial(controllerBox);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(90, 20, 61, 61));
        dial->setMaximum(5);
        dial->setValue(3);
        dial->setSliderPosition(3);
        dial->setTracking(true);
        dial->setWrapping(true);
        layoutWidget = new QWidget(controllerBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 100, 239, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        homeButton = new QPushButton(layoutWidget);
        homeButton->setObjectName(QStringLiteral("homeButton"));

        horizontalLayout->addWidget(homeButton);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);

        backButton = new QPushButton(layoutWidget);
        backButton->setObjectName(QStringLiteral("backButton"));

        horizontalLayout->addWidget(backButton);

        layoutWidget1 = new QWidget(MenuDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget->raise();
        controllerBox->raise();
        horizontalSlider->raise();
        stackSlide->raise();
        QWidget::setTabOrder(horizontalSlider, dial);
        QWidget::setTabOrder(dial, pushButton_2);
        QWidget::setTabOrder(pushButton_2, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_3);
        QWidget::setTabOrder(pushButton_3, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_5);
        QWidget::setTabOrder(pushButton_5, pushButton_6);
        QWidget::setTabOrder(pushButton_6, pushButton_12);
        QWidget::setTabOrder(pushButton_12, pushButton_9);
        QWidget::setTabOrder(pushButton_9, pushButton_7);
        QWidget::setTabOrder(pushButton_7, pushButton_10);
        QWidget::setTabOrder(pushButton_10, pushButton_8);
        QWidget::setTabOrder(pushButton_8, pushButton_11);
        QWidget::setTabOrder(pushButton_11, pushButton_24);
        QWidget::setTabOrder(pushButton_24, pushButton_19);
        QWidget::setTabOrder(pushButton_19, pushButton_22);
        QWidget::setTabOrder(pushButton_22, pushButton_23);
        QWidget::setTabOrder(pushButton_23, pushButton_20);
        QWidget::setTabOrder(pushButton_20, pushButton_21);

        retranslateUi(MenuDialog);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), stackSlide, SLOT(slideInIdx(int)));
        QObject::connect(dial, SIGNAL(valueChanged(int)), qtPieMenu_2, SLOT(setSelection(int)));
        QObject::connect(okButton, SIGNAL(clicked()), qtPieMenu_2, SLOT(select()));
        QObject::connect(qtPieMenu_2, SIGNAL(itemSelect(int)), stackSlide, SLOT(slideInIdx(int)));
        QObject::connect(homeButton, SIGNAL(clicked()), stackSlide, SLOT(slideHome()));

        stackSlide->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuDialog);
    } // setupUi

    void retranslateUi(QDialog *MenuDialog)
    {
        MenuDialog->setWindowTitle(QApplication::translate("MenuDialog", "MenuDialog", 0));
        label->setText(QApplication::translate("MenuDialog", "Test Text", 0));
        pushButton_13->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_14->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_3->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_4->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_5->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_6->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_12->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_9->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_7->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_10->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_8->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_11->setText(QApplication::translate("MenuDialog", "PushButton", 0));
        pushButton_24->setText(QApplication::translate("MenuDialog", "Bottom Page", 0));
        pushButton_19->setText(QApplication::translate("MenuDialog", "Bottom Page", 0));
        pushButton_22->setText(QApplication::translate("MenuDialog", "Bottom Page", 0));
        pushButton_23->setText(QApplication::translate("MenuDialog", "Bottom Page", 0));
        pushButton_20->setText(QApplication::translate("MenuDialog", "Bottom Page", 0));
        pushButton_21->setText(QApplication::translate("MenuDialog", "Bottom Page", 0));
        controllerBox->setTitle(QApplication::translate("MenuDialog", "Controller", 0));
        homeButton->setText(QApplication::translate("MenuDialog", "&Home", 0));
        okButton->setText(QApplication::translate("MenuDialog", "&OK", 0));
        backButton->setText(QApplication::translate("MenuDialog", "&Back", 0));
    } // retranslateUi

};

namespace Ui {
    class MenuDialog: public Ui_MenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUDIALOG_H
