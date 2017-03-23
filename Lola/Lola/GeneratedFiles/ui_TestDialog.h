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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include "QtPieMenu.h"
#include "StackSlide.h"

QT_BEGIN_NAMESPACE

class Ui_TestDialog
{
public:
    QGridLayout *gridLayout;
    StackSlide *stackSlide;
    QWidget *page;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QWidget *page_2;
    QSplitter *splitter_2;
    QDial *dial;
    QLabel *label_5;
    QLCDNumber *lcdNumber;
    QSplitter *splitter;
    QtPieMenu *qtPieMenu;

    void setupUi(QDialog *TestDialog)
    {
        if (TestDialog->objectName().isEmpty())
            TestDialog->setObjectName(QStringLiteral("TestDialog"));
        TestDialog->resize(1280, 720);
        gridLayout = new QGridLayout(TestDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackSlide = new StackSlide(TestDialog);
        stackSlide->setObjectName(QStringLiteral("stackSlide"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        horizontalLayout = new QHBoxLayout(page);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(688, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 2, 1, 2);

        verticalSpacer = new QSpacerItem(20, 448, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 418, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 3, 1, 1);

        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(698, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 1, 1, 2);

        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 2, 3, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        stackSlide->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        splitter_2 = new QSplitter(page_2);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setGeometry(QRect(10, 0, 1231, 61));
        splitter_2->setOrientation(Qt::Horizontal);
        dial = new QDial(splitter_2);
        dial->setObjectName(QStringLiteral("dial"));
        splitter_2->addWidget(dial);
        label_5 = new QLabel(splitter_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        splitter_2->addWidget(label_5);
        lcdNumber = new QLCDNumber(splitter_2);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        splitter_2->addWidget(lcdNumber);
        splitter = new QSplitter(page_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(10, 70, 1241, 611));
        splitter->setOrientation(Qt::Horizontal);
        qtPieMenu = new QtPieMenu(splitter);
        qtPieMenu->setObjectName(QStringLiteral("qtPieMenu"));
        splitter->addWidget(qtPieMenu);
        stackSlide->addWidget(page_2);

        gridLayout->addWidget(stackSlide, 0, 0, 1, 1);


        retranslateUi(TestDialog);

        stackSlide->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(TestDialog);
    } // setupUi

    void retranslateUi(QDialog *TestDialog)
    {
        TestDialog->setWindowTitle(QApplication::translate("TestDialog", "TestDialog", Q_NULLPTR));
        label_2->setText(QApplication::translate("TestDialog", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("TestDialog", "TextLabel", Q_NULLPTR));
        label->setText(QApplication::translate("TestDialog", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("TestDialog", "TextLabel", Q_NULLPTR));
        label_5->setText(QApplication::translate("TestDialog", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TestDialog: public Ui_TestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTDIALOG_H
