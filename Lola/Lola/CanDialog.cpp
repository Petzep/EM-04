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

bool CanDialog::initCan(int can)
{
	if(QCanBus::instance()->plugins().contains(QStringLiteral("socketcan").toUtf8()))
	{
		QString errorString;
		canDevice = QCanBus::instance()->createDevice(QStringLiteral("socketcan").toUtf8(), QStringLiteral("can").append(can + '0'), &errorString);

		if(!canDevice)
		{
			QMessageBox::StandardButton warningBox;
			warningBox = QMessageBox::warning(this, "CANerror", (tr("Error creating device '%1', reason: '%2'").arg(QStringLiteral("can").append(can + '0')).arg(errorString)));
		
			return false;
		}

		connect(canDevice, SIGNAL(errorOccurred()), this, SLOT(canError()));
		connect(canDevice, SIGNAL(framesReceived()), this, SLOT(canRx()));
		connect(canDevice, SIGNAL(framesWritten()), this, SLOT(canTx()));

		canDevice->setConfigurationParameter(QCanBusDevice::BitRateKey, 500000);

		if(!canDevice->connectDevice())
		{
			QMessageBox::StandardButton warningBox;
			warningBox = QMessageBox::warning(this, "CANerror", tr("Connection error: %1\n Device: %2").arg(canDevice->errorString()).arg(QStringLiteral("can").append(can + '0')));
		}

		QCanBusFrame frame;
		frame.setFrameId(0x001);
		QByteArray payload("A36E");
		frame.setPayload(payload);
		canDevice->writeFrame(frame);
		
		return true;
	}
	else
		return false;
}

void CanDialog::canError(void)
{
	QMessageBox::StandardButton warningBox;
	warningBox = QMessageBox::warning(this, "CANerror", tr("Connection error: %1").arg(canDevice->errorString()));
}

void CanDialog::canRx(void)
{
	if(!canDevice)
		return;

	while(canDevice->framesAvailable())
	{
		CanLogMsg canData;
		const QCanBusFrame frame = canDevice->readFrame();
		
		int index = model->rowCount() - 1;

		QString line;
		if(!frame.frameType() == QCanBusFrame::ErrorFrame)
			line = frame.toString();

		QStandardItem *item = new QStandardItem();
		model->setItem(model->rowCount(), 0, item);

		QStringList splitList = line.split(']').first().split('[');
		canData.dlc = splitList.last().toInt();

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
		canData.time = frame.timeStamp().microSeconds();

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

void CanDialog::canTx(void)
{
	qDebug("Frames written");
}

void CanDialog::on_refreshButton_clicked(void)
{
	model->clear();
	initTable();
	if(radioCan->isChecked())
	{
		if(!initCan(0))
		{
			QMessageBox::StandardButton warningBox;
			warningBox = QMessageBox::warning(this, "CANerror", "Could not initialze CANBUS, defaulting to file modus");
			radioFile->setChecked(true);
			radioCan->setChecked(false);
			radioCan->setDisabled(true);
		}

	}
	else
		readFile(fileName);
}

void CanDialog::on_clearButton_clicked(void)
{
	checkUpdate->setChecked(false);
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

void CanDialog::on_radioFile_toggled(bool checked)
{
	if(checked)
		radioCan->setChecked(false);
}

void CanDialog::on_radioCan_toggled(bool checked)
{
	if(checked)
		radioFile->setChecked(false);
}

void CanDialog::on_checkUpdate_toggled(bool checked)
{
	if(checked)
		QObject::connect(&watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(handleFileChanged(const QString&)));
	else
		QObject::disconnect(&watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(handleFileChanged(const QString&)));
}

void CanDialog::handleFileChanged(const QString &)
{
	model->clear();
	initTable();
	readFile(fileName);
}
