#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include <qtableview.h>
#include "ui_CanDialog.h"
#include <qfile.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include <qfilesystemwatcher.h>
#include <qcanbus.h>

struct CanLogMsg
{
	long long time;
	QString id;
	int dlc;
	QStringList data;
};

class CanDialog : public QDialog, public Ui::CanDialog
{
	Q_OBJECT

public:
	CanDialog(QWidget *parent = Q_NULLPTR);
	~CanDialog();
	void initTable();
	void readFile(QString filename);
	void dataToTable(CanLogMsg data);
	bool initCan(int can);	

private:
	QStandardItemModel *model;
	QFileSystemWatcher watcher;
	QString fileName;
	QCanBusDevice *canDevice;

public slots:
	void on_refreshButton_clicked(void);
	void on_clearButton_clicked(void);
	void on_saveButton_clicked(void);
	void on_radioFile_clicked(void);
	void on_radioCan_clicked(void);
	void handleFileChanged(const QString&);
};
