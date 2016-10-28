#pragma once

#include <QtWidgets/QMainWindow>
#include "AddDialog.h"
#include "TestDialog.h"
#include "MenuDialog.h"
#include "ui_TUIcomotive.h"

class TUIcomotive : public QMainWindow
{
    Q_OBJECT

public:
    TUIcomotive(QWidget *parent = Q_NULLPTR);

private:
    Ui::TUIcomotiveClass ui;

public slots:
	void on_addButton_clicked(void);
	void on_bangaList_currentItemChanged(void);
	void on_deleteButton_clicked(void);
	void on_testButton_clicked(void);
	void on_menuButton_clicked(void);
};
