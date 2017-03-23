#pragma once

#define MENU qtPieMenu

#include <QDialog>
#include <QtGui>
#include "ui_TestDialog.h"

class TestDialog : public QDialog, public Ui::TestDialog
{
	Q_OBJECT

public:
	TestDialog(QWidget *parent = Q_NULLPTR);
	~TestDialog();
	bool event(QEvent *event);
};
