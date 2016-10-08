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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TUIcomotiveClass
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *bangaList;
    QVBoxLayout *verticalLayout_2;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QSpacerItem *verticalSpacer;
    QLabel *nameLabel;
    QLabel *emailLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TUIcomotiveClass)
    {
        if (TUIcomotiveClass->objectName().isEmpty())
            TUIcomotiveClass->setObjectName(QStringLiteral("TUIcomotiveClass"));
        TUIcomotiveClass->resize(390, 306);
        TUIcomotiveClass->setAcceptDrops(true);
        centralWidget = new QWidget(TUIcomotiveClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 341, 232));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        bangaList = new QListWidget(widget);
        bangaList->setObjectName(QStringLiteral("bangaList"));

        gridLayout->addWidget(bangaList, 1, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        addButton = new QPushButton(widget);
        addButton->setObjectName(QStringLiteral("addButton"));

        verticalLayout_2->addWidget(addButton);

        deleteButton = new QPushButton(widget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        verticalLayout_2->addWidget(deleteButton);

        verticalSpacer = new QSpacerItem(20, 128, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_2, 1, 2, 1, 1);

        nameLabel = new QLabel(widget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        gridLayout->addWidget(nameLabel, 2, 0, 1, 1);

        emailLabel = new QLabel(widget);
        emailLabel->setObjectName(QStringLiteral("emailLabel"));

        gridLayout->addWidget(emailLabel, 2, 1, 1, 1);

        TUIcomotiveClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TUIcomotiveClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 390, 21));
        TUIcomotiveClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TUIcomotiveClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TUIcomotiveClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TUIcomotiveClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TUIcomotiveClass->setStatusBar(statusBar);

        retranslateUi(TUIcomotiveClass);

        QMetaObject::connectSlotsByName(TUIcomotiveClass);
    } // setupUi

    void retranslateUi(QMainWindow *TUIcomotiveClass)
    {
        TUIcomotiveClass->setWindowTitle(QApplication::translate("TUIcomotiveClass", "TUIcomotive", 0));
        label->setText(QApplication::translate("TUIcomotiveClass", "Banga list", 0));
        addButton->setText(QApplication::translate("TUIcomotiveClass", "skADDje", 0));
        deleteButton->setText(QApplication::translate("TUIcomotiveClass", "sletXIT", 0));
        nameLabel->setText(QApplication::translate("TUIcomotiveClass", "<No item selected>", 0));
        emailLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TUIcomotiveClass: public Ui_TUIcomotiveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUICOMOTIVE_H
