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
	QFile file(QString (QCoreApplication::applicationDirPath() +"/" + filename));
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	if(!watcher.directories().empty())
		watcher.addPath(QString(QCoreApplication::applicationDirPath() + "/" + filename));

	QStringList splitList;
	QTextStream in(&file);
	CanLogMsg canData;
	for(int index = 0; !in.atEnd(); index++)
	{
		QString line = in.readLine();
		splitList = line.split(')').first().split('(');
		canData.time = splitList.last().toLongLong();
		splitList.clear();

		splitList = line.split('>').first().split('x');
		canData.id = splitList.last();
		splitList.clear();

		splitList = line.split(']').first().split('[');
		canData.dlc = splitList.last().toInt();
		splitList.clear();

		QRegExp rx("(\[0-9a-f]\[0-9a-f] )");
		int pos = 0;
		canData.data.clear();
		for(int i = 0; i < canData.dlc; i++)
		{
			if((pos = rx.indexIn(line, pos)) != -1)
			{
				canData.data.append(rx.cap(1));
				pos += rx.matchedLength();
			}
		}

		QModelIndex Qindex = model->index(index, 0, QModelIndex());
		model->setData(Qindex, QVariant(QString("%1").arg(canData.time, 12, 10, QChar('0'))));
		Qindex = model->index(index, 1, QModelIndex());
		
			model->setData(Qindex, QVariant(QString("0x%1").arg(canData.id)));
		Qindex = model->index(index, 2, QModelIndex());
		model->setData(Qindex, canData.dlc);
		Qindex = model->index(index, 3, QModelIndex());
		model->setData(Qindex, canData.data.join(" "));
	}
	file.close();
}

void CanDialog::dataToTable(CanLogMsg data)
{

}

void CanDialog::on_refreshButton_clicked(void)
{
	readFile("canout.txt");
	//QString line = "(000137494712) <0x001> [8] 11 22 33 44 55 66 77 88 ";
	//QStringList splitList;
	//CanLogMsg canData;

	//splitList = line.split(')').first().split('(');
	//canData.time = splitList.last().toLongLong();
	//splitList.clear();

	//splitList = line.split('>').first().split('x');
	//canData.id = splitList.last().toInt();
	//splitList.clear();

	//splitList = line.split(']').first().split('[');
	//canData.dlc = splitList.last().toInt();
	//splitList.clear();

	//QRegExp rx("(\\d\\d )");
	//int pos = 0;

	//for(int i = 0; i < canData.dlc; i++)
	//{
	//	if((pos = rx.indexIn(line, pos)) != -1)
	//	{
	//		canData.data.append(rx.cap(1));
	//		pos += rx.matchedLength();
	//	}
	//}

	//QModelIndex Qindex = model->index(0, 0, QModelIndex());
	//model->setData(Qindex, QVariant(QString("%1").arg(canData.time, 12, 10, QChar('0'))));
	//Qindex = model->index(0, 1, QModelIndex());
	//model->setData(Qindex, QVariant(QString("0x%1").arg(canData.id, 3, 10, QChar('0'))));
	//Qindex = model->index(0, 2, QModelIndex());
	//model->setData(Qindex, canData.dlc);
	//Qindex = model->index(0, 3, QModelIndex());
	//model->setData(Qindex, canData.data.join(" "));

}



void CanDialog::on_clearButton_clicked(void)
{

}

void CanDialog::on_saveButton_clicked(void)
{

}