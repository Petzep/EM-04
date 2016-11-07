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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "CustomClock.h"
#include "QtPieMenu.h"
#include "StackSlide.h"

QT_BEGIN_NAMESPACE

class Ui_MenuDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    CustomClock *customClock;
    QWidget *tab_2;
    QtPieMenu *qtPieMenu;
    QSlider *horizontalSlider;
    StackSlide *stackSlide;
    QWidget *page;
    QPushButton *pushButton_18;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_17;
    QPushButton *pushButton_13;
    QPushButton *pushButton_16;
    QWidget *leftPage;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *midPage;
    QtPieMenu *qtPieMenu_2;
    QDial *dial;
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

    void setupUi(QDialog *MenuDialog)
    {
        if (MenuDialog->objectName().isEmpty())
            MenuDialog->setObjectName(QStringLiteral("MenuDialog"));
        MenuDialog->resize(704, 368);
        tabWidget = new QTabWidget(MenuDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 341, 351));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        customClock = new CustomClock(tab);
        customClock->setObjectName(QStringLiteral("customClock"));
        customClock->setGeometry(QRect(100, 80, 100, 100));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        qtPieMenu = new QtPieMenu(tab_2);
        qtPieMenu->setObjectName(QStringLiteral("qtPieMenu"));
        qtPieMenu->setGeometry(QRect(90, 70, 100, 100));
        tabWidget->addTab(tab_2, QString());
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
        stackSlide->setSpeed(600);
        stackSlide->setWrap(false);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        pushButton_18 = new QPushButton(page);
        pushButton_18->setObjectName(QStringLiteral("pushButton_18"));
        pushButton_18->setGeometry(QRect(100, 200, 75, 23));
        pushButton_14 = new QPushButton(page);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(130, 40, 70, 23));
        pushButton_15 = new QPushButton(page);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setGeometry(QRect(90, 160, 75, 23));
        pushButton_17 = new QPushButton(page);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
        pushButton_17->setGeometry(QRect(130, 240, 75, 23));
        pushButton_13 = new QPushButton(page);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(100, 80, 75, 23));
        pushButton_16 = new QPushButton(page);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setGeometry(QRect(90, 120, 75, 23));
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
        dial = new QDial(midPage);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(120, 140, 50, 64));
        dial->setMaximum(5);
        dial->setValue(3);
        dial->setSliderPosition(3);
        dial->setTracking(true);
        dial->setWrapping(true);
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
        QWidget::setTabOrder(pushButton_11, pushButton_18);
        QWidget::setTabOrder(pushButton_18, pushButton_14);
        QWidget::setTabOrder(pushButton_14, pushButton_15);
        QWidget::setTabOrder(pushButton_15, pushButton_17);
        QWidget::setTabOrder(pushButton_17, pushButton_13);
        QWidget::setTabOrder(pushButton_13, pushButton_16);
        QWidget::setTabOrder(pushButton_16, tabWidget);
        QWidget::setTabOrder(tabWidget, pushButton_24);
        QWidget::setTabOrder(pushButton_24, pushButton_19);
        QWidget::setTabOrder(pushButton_19, pushButton_22);
        QWidget::setTabOrder(pushButton_22, pushButton_23);
        QWidget::setTabOrder(pushButton_23, pushButton_20);
        QWidget::setTabOrder(pushButton_20, pushButton_21);

        retranslateUi(MenuDialog);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), stackSlide, SLOT(slideInIdx(int)));
        QObject::connect(dial, SIGNAL(valueChanged(int)), qtPieMenu_2, SLOT(setSelection(int)));

        tabWidget->setCurrentIndex(0);
        stackSlide->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MenuDialog);
    } // setupUi

    void retranslateUi(QDialog *MenuDialog)
    {
        MenuDialog->setWindowTitle(QApplication::translate("MenuDialog", "MenuDialog", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MenuDialog", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MenuDialog", "Tab 2", 0));
        pushButton_18->setText(QApplication::translate("MenuDialog", "Upper Button", 0));
        pushButton_14->setText(QApplication::translate("MenuDialog", "Upper Button", 0));
        pushButton_15->setText(QApplication::translate("MenuDialog", "Upper Button", 0));
        pushButton_17->setText(QApplication::translate("MenuDialog", "Upper Button", 0));
        pushButton_13->setText(QApplication::translate("MenuDialog", "Upper Button", 0));
        pushButton_16->setText(QApplication::translate("MenuDialog", "Upper Button", 0));
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
    } // retranslateUi

};

namespace Ui {
    class MenuDialog: public Ui_MenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUDIALOG_H
