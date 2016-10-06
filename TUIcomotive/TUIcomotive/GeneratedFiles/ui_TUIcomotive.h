/********************************************************************************
** Form generated from reading UI file 'TUIcomotive.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUICOMOTIVE_H
#define UI_TUICOMOTIVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TUIcomotiveClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TUIcomotiveClass)
    {
        if (TUIcomotiveClass->objectName().isEmpty())
            TUIcomotiveClass->setObjectName(QStringLiteral("TUIcomotiveClass"));
        TUIcomotiveClass->resize(600, 400);
        menuBar = new QMenuBar(TUIcomotiveClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TUIcomotiveClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TUIcomotiveClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TUIcomotiveClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TUIcomotiveClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TUIcomotiveClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TUIcomotiveClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TUIcomotiveClass->setStatusBar(statusBar);

        retranslateUi(TUIcomotiveClass);

        QMetaObject::connectSlotsByName(TUIcomotiveClass);
    } // setupUi

    void retranslateUi(QMainWindow *TUIcomotiveClass)
    {
        TUIcomotiveClass->setWindowTitle(QApplication::translate("TUIcomotiveClass", "TUIcomotive", 0));
    } // retranslateUi

};

namespace Ui {
    class TUIcomotiveClass: public Ui_TUIcomotiveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUICOMOTIVE_H
