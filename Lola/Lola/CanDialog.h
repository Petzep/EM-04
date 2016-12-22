#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <qtableview.h>
#include "ui_CanDialog.h"

class CanDialog : public QDialog, public Ui::CanDialog
{
	Q_OBJECT

public:
	CanDialog(QWidget *parent = Q_NULLPTR);
	~CanDialog();

private:
	QStandardItemModel *model;

public slots:
	void on_refreshButton_clicked(void);
	void on_clearButton_clicked(void);
	void on_saveButton_clicked(void);
};
