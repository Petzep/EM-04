#pragma once

#include <QDialog>
#include "ui_MenuDialog.h"

class MenuDialog : public QDialog, public Ui::MenuDialog
{
	Q_OBJECT

public:
	MenuDialog(QWidget *parent = Q_NULLPTR);
	~MenuDialog();
};
