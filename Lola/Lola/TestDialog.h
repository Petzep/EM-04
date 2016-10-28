#pragma once

#include <QDialog>
#include "ui_TestDialog.h"

class TestDialog : public QDialog, public Ui::TestDialog
{
	Q_OBJECT

public:
	TestDialog(QWidget *parent = Q_NULLPTR);
	~TestDialog();
};
