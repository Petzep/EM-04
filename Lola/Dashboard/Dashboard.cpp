#include "Dashboard.h"

Dashboard::Dashboard(QObject *parent)
	: QObject(parent), m_shoeSize(0)
{
}

void Dashboard::setRoot(QObject * root)
{
	m_root = root;
}

bool Dashboard::initCan(int can)
{
	if(QCanBus::instance()->plugins().contains(QStringLiteral("socketcan").toUtf8()))
	{
		QString errorString;
		canDevice = QCanBus::instance()->createDevice(QStringLiteral("socketcan").toUtf8(), QStringLiteral("can").append(can + '0'), &errorString);

		//if(!canDevice)
		//{
		//	qWarning("CANerror", (tr("Error creating device '%1', reason: '%2'").arg(QStringLiteral("can").append(can + '0')).arg(errorString)));

		//	return false;
		//}

		connect(canDevice, SIGNAL(errorOccurred()), this, SLOT(canError()));
		connect(canDevice, SIGNAL(framesReceived()), this, SLOT(canRx()));
		connect(canDevice, SIGNAL(framesWritten()), this, SLOT(canTx()));

		canDevice->setConfigurationParameter(QCanBusDevice::BitRateKey, 500000);

		if(!canDevice->connectDevice())
		{
			/*QMessageBox::StandardButton warningBox;
			qWarning("CANerror", tr("Connection error: %1\n Device: %2").arg(canDevice->errorString()).arg(QStringLiteral("can").append(can + '0')));*/
			qDebug("Cannot connect device");
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

void Dashboard::canError(void)
{
	/*qWarning("CANerror", tr("Connection error: %1").arg(canDevice->errorString()));*/
}

void Dashboard::canRx(void)
{
	if(!canDevice)
		return;

	while(canDevice->framesAvailable())
	{
		CanLogMsg canData;
		const QCanBusFrame frame = canDevice->readFrame();

		QString line;
		line = frame.toString();

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

		if(canData.dlc == 1)
		{
			QObject *qmlObject = m_root->findChild<QObject*>("valueSource");
			qmlObject->setProperty("kph", canData.data.first().toInt());
		}
		

	/*	QModelIndex Qindex = model->index(index, 0, QModelIndex());
		model->setData(Qindex, QVariant(QString("%1").arg(canData.time, 12, 10, QChar('0'))));
		Qindex = model->index(index, 1, QModelIndex());
		model->setData(Qindex, QVariant(QString("0x%1").arg(canData.id)));
		Qindex = model->index(index, 2, QModelIndex());
		model->setData(Qindex, canData.dlc);
		Qindex = model->index(index, 3, QModelIndex());
		model->setData(Qindex, canData.data.join(" "));*/
	}
}

void Dashboard::canTx(void)
{
	qDebug("Frames written");
}