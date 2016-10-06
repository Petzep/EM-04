#pragma once

#include <QWidget>
#include "ui_addDialog.h"

class addDialog : public QWidget, public Ui::addDialog
{
	Q_OBJECT

public:
	addDialog(QWidget *parent = Q_NULLPTR);
	~addDialog();
};
