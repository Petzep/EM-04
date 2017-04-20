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

	QObject *qmlObject = m_root->findChild<QObject*>("valueSource");
	while(canDevice->framesAvailable())
	{
		CanLogMsg canData;
		const QCanBusFrame frame = canDevice->readFrame();

		QString line;
		line = frame.toString();

		QStringList splitList = line.split(']').first().split('[');
		canData.dlc = splitList.last().toInt();
		canData.id = splitList.first().toInt();

		canData.data.clear();
		QRegExp rx("(\[0-9a-f]\[0-9a-f] )");
		int pos = line.lastIndexOf("]"); //only searches after the id
		for(int i = 0; i < canData.dlc; i++)
			if((pos = rx.indexIn(line, pos)) != -1)
			{
				canData.data.append(rx.cap(1).toInt(Q_NULLPTR, 16));
				pos += rx.matchedLength();
		}
		canData.time = frame.timeStamp().microSeconds();

		if(canData.id == SPEED_ADDRESS)
			qmlObject->setProperty("kph", canData.data.at(0));
		else if(canData.id == TEMPERATURE_ADDRESS)
			qmlObject->setProperty("temperature", canData.data.at(0));
		else if(canData.id == LEFT_ADDRESS)
			qmlObject->setProperty("turnSignal", canData.data.at(0) ? Qt::LeftArrow : -1);
		else if(canData.id == RIGHT_ADDRESS)
			qmlObject->setProperty("turnSignal", canData.data.at(0) ? Qt::RightArrow : -1);
		else if(canData.id == FRONT_ADDRESS)
		{
			qmlObject->setProperty("smallOn", canData.data.at(0));
			qmlObject->setProperty("dimOn", canData.data.at(1));
			qmlObject->setProperty("fullOn", canData.data.at(3));
		}
		else if(canData.id == MC_DNR)
		{
			switch(canData.data.at(0))
			{
				case 0:
					qmlObject->setProperty("gear", "D");
					break;
				case 1:
					qmlObject->setProperty("gear", "N");
					break;
				case 2:
					qmlObject->setProperty("gear", "R");
					break;
				default:
					qmlObject->setProperty("gear", "Error");
					break;
			}
		}
	}
}

void Dashboard::canTx(void)
{
	qDebug("Frames written");
}