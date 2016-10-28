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
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "CustomClock.h"
#include "QtPieMenu.h"

QT_BEGIN_NAMESPACE

class Ui_MenuDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    CustomClock *customClock;
    QWidget *tab_2;
    QtPieMenu *qtPieMenu;
    QStackedWidget *stackedWidget;
    QWidget *page;
    CustomClock *customClock_2;
    QWidget *page_2;
    QtPieMenu *qtPieMenu_2;

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
        stackedWidget = new QStackedWidget(MenuDialog);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(350, 10, 341, 331));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        customClock_2 = new CustomClock(page);
        customClock_2->setObjectName(QStringLiteral("customClock_2"));
        customClock_2->setGeometry(QRect(130, 60, 100, 100));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        qtPieMenu_2 = new QtPieMenu(page_2);
        qtPieMenu_2->setObjectName(QStringLiteral("qtPieMenu_2"));
        qtPieMenu_2->setGeometry(QRect(150, 70, 100, 100));
        stackedWidget->addWidget(page_2);

        retranslateUi(MenuDialog);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuDialog);
    } // setupUi

    void retranslateUi(QDialog *MenuDialog)
    {
        MenuDialog->setWindowTitle(QApplication::translate("MenuDialog", "MenuDialog", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MenuDialog", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MenuDialog", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class MenuDialog: public Ui_MenuDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUDIALOG_H
