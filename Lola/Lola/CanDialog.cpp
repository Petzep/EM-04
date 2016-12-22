#include "CanDialog.h"

CanDialog::CanDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	model = new QStandardItemModel(10, 5, this);
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Time (ms)")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Id")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("DLC")));
	model->setHorizontalHeaderItem(3, new QStandardItem(QString("Data")));
	model->setHorizontalHeaderItem(4, new QStandardItem(QString("Message")));
	canTable->setModel(model);

	
}

CanDialog::~CanDialog()
{
}

void CanDialog::on_refreshButton_clicked(void)
{
	//open file
	//parse
	//fill table
	int test = 5;
}

void CanDialog::on_clearButton_clicked(void)
{

}

void CanDialog::on_saveButton_clicked(void)
{

}