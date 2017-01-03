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

void CanDialog::readFile(QString filename)
{ 
	QFile file("canout.txt");
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QStringList splitList;
	QTextStream in(&file);
	CanLogMsg canData;
	while(!in.atEnd())
	{
		QString line = in.readLine();
		splitList = line.split(')').first().split('(');
		canData.time = splitList.last().toLongLong();
		splitList.clear();

		splitList = line.split('>').first().split('<');
		canData.id = splitList.last().toInt();
		splitList.clear();

		splitList = line.split(']').first().split('[');
		canData.dlc = splitList.last().toInt();
		splitList.clear();

		QRegExp rx("(\\d\\d )");
		int pos = 0;
		for(int i = 0; i < canData.dlc; i++)
		{
			if((pos = rx.indexIn(line, pos)) != -1)
			{
				canData.msg[i] = rx.cap(1).toInt();
				pos += rx.matchedLength();
			}
		}

		QModelIndex Qindex = model->index(0, 0, QModelIndex());
		model->setData(Qindex, canData.dlc);

	}
}

void CanDialog::dataToTable(CanLogMsg data)
{

}

void CanDialog::on_refreshButton_clicked(void)
{
	QString line = "(000137494712) <0x001> [8] 11 22 33 44 55 66 77 88 ";
	QStringList splitList;
	CanLogMsg canData;

	splitList = line.split(')').first().split('(');
	canData.time = splitList.last().toLongLong();
	splitList.clear();

	splitList = line.split('>').first().split('<');
	canData.id = splitList.last().toInt();
	splitList.clear();

	splitList = line.split(']').first().split('[');
	canData.dlc = splitList.last().toInt();
	splitList.clear();

	QRegExp rx("(\\d\\d )");
	int pos = 0;
	int index = 0;

	for(int i = 0; i < canData.dlc; i++)
	{
		if((pos = rx.indexIn(line, pos)) != -1)
		{
			canData.msg[i] = rx.cap(1).toInt();
			pos += rx.matchedLength();
		}
	}

	QModelIndex Qindex = model->index(0, 0, QModelIndex());
	model->setData(Qindex, canData.time);
	Qindex = model->index(0, 1, QModelIndex());
	model->setData(Qindex, canData.id);
	Qindex = model->index(0, 2, QModelIndex());
	model->setData(Qindex, canData.dlc);
	Qindex = model->index(0, 3, QModelIndex());
	model->setData(Qindex, canData.msg[1]);

}



void CanDialog::on_clearButton_clicked(void)
{

}

void CanDialog::on_saveButton_clicked(void)
{

}