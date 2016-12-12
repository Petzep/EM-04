#pragma once

#define MENU qtPieMenu_2

#include <QDialog>
#include <qevent.h>
#include "ui_MenuDialog.h"

class MenuDialog : public QDialog, public Ui::MenuDialog
{
	Q_OBJECT

public:
	MenuDialog(QWidget *parent = Q_NULLPTR);
	~MenuDialog();
	bool event(QEvent *event);

public slots:
	void on_controlDial_valueChanged(int);
};
