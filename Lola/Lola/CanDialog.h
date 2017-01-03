#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <qtableview.h>
#include "ui_CanDialog.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include <QItemDelegate>

struct CanLogMsg
{
	long long time;
	int id;
	int dlc;
	int *msg;
};

class CanDialog : public QDialog, public Ui::CanDialog
{
	Q_OBJECT

public:
	CanDialog(QWidget *parent = Q_NULLPTR);
	~CanDialog();
	void readFile(QString filename);
	void dataToTable(CanLogMsg data);

private:
	QStandardItemModel *model;

public slots:
	void on_refreshButton_clicked(void);
	void on_clearButton_clicked(void);
	void on_saveButton_clicked(void);
};
