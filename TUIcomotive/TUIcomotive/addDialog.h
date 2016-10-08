#pragma once

#include <QDialog>
#include "ui_AddDialog.h"

class AddDialog : public QDialog, public Ui::AddDialog
{
	Q_OBJECT

public:
	AddDialog(QWidget *parent = Q_NULLPTR);
	~AddDialog();
};
