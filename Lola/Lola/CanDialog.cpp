#include "CanDialog.h"

CanDialog::CanDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	model = new QStandardItemModel(0, 5, this);
	canTable->setModel(model);

	fileName = "canout.txt";

	watcher.addPath(QString(QCoreApplication::applicationDirPath() + "/" + fileName));
	QObject::connect(&watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(handleFileChanged(const QString&)));
}

CanDialog::~CanDialog()
{
}

void CanDialog::initTable()
{
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Time (ms)")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Id")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("DLC")));
	model->setHorizontalHeaderItem(3, new QStandardItem(QString("Data")));
	model->setHorizontalHeaderItem(4, new QStandardItem(QString("Message")));
}

void CanDialog::readFile(QString filename)
{ 
	QFile file(QString (QCoreApplication::applicationDirPath() +"/" + filename));
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QStringList splitList;
	QTextStream in(&file);
	CanLogMsg canData;
	for(int index = 0; !in.atEnd(); index++)
	{
		QString line = in.readLine();
		if(line.size() != 0)
		{
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

			QStandardItem *item = new QStandardItem();
			model->setItem(model->rowCount(), 0, item);

			QModelIndex Qindex = model->index(index, 0, QModelIndex());
			model->setData(Qindex, QVariant(QString("%1").arg(canData.time, 12, 10, QChar('0'))));
			Qindex = model->index(index, 1, QModelIndex());
			model->setData(Qindex, QVariant(QString("0x%1").arg(canData.id)));
			Qindex = model->index(index, 2, QModelIndex());
			model->setData(Qindex, canData.dlc);
			Qindex = model->index(index, 3, QModelIndex());
			model->setData(Qindex, canData.data.join(" "));
		}
	}
	file.close();
}

void CanDialog::dataToTable(CanLogMsg data)
{

}

void CanDialog::on_refreshButton_clicked(void)
{
	model->clear();
	initTable();
	readFile("canout.txt");
}

void CanDialog::on_clearButton_clicked(void)
{
	model->clear();
	initTable();
}

void CanDialog::on_saveButton_clicked(void)
{
	for(int column = 0; column < 5; ++column)
	{
		QStandardItem *item = new QStandardItem();
		model->setItem(model->rowCount(), column, item);
	}
}

void CanDialog::handleFileChanged(const QString &)
{
	model->clear();
	initTable();
	readFile(fileName);
}
