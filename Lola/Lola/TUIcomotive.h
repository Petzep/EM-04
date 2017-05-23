#pragma once

#include <QtWidgets/QMainWindow>
#include <QtQuick/QtQuick>
#include <QtQml/QtQml>
#include "AddDialog.h"
#include "TestDialog.h"
#include "MenuDialog.h"
#include "StyleDialog.h"
#include "CanDialog.h"
#include "ui_TUIcomotive.h"



class TUIcomotive : public QMainWindow
{
    Q_OBJECT

public:
    TUIcomotive(QWidget *parent = Q_NULLPTR);
	bool event(QEvent *event);

private:
    Ui::TUIcomotiveClass ui;

public slots:
	void on_addButton_clicked(void);
	void on_bangaList_currentItemChanged(void);
	void on_deleteButton_clicked(void);
	void on_testButton_clicked(void);
	void on_menuButton_clicked(void);
	void on_styleButton_clicked(void);
	void on_canButton_clicked(void);
	void on_dashboardButton_clicked(void);
	void on_closeButton_clicked(void);
	void addListItem(QString name, QString email);
};
