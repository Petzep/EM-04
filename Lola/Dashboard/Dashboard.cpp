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
		frame.setFrameId(BROADCAST_ADDRESS);
		QByteArray payload("Lina");
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
		line = frame.toString().toLatin1();

		QStringList splitList = line.split(']').first().split('[');
		canData.dlc = splitList.last().toInt();
		canData.id = frame.frameId();

		canData.data.clear();
		for(int i = 0; i < canData.dlc; i++)
			canData.data.append(frame.payload().at(i));
		for(int i = canData.dlc; i < 8; i++)
			canData.data.append(0);

		canData.time = frame.timeStamp().microSeconds();
		/*qWarning("canData.id: %d", canData.id);
		qWarning("canData.dlc: %d", canData.dlc);
		qWarning("canData.data.count: %d", canData.data.count());
		qWarning("frame.frameId(): %d", frame.frameId());
		qWarning("frame.payload().at(0) %d", frame.payload().at(0));
		qWarning("canData.data.at(1): %d", canData.data.at(0));
		qWarning("canData.data.at(1): %d", canData.data.at(1));
		qWarning("canData.data.at(2): %d", canData.data.at(2));
		qWarning("canData.robodata.at(3): %d", canData.data.at(3));*/
		if(canData.id == SPEED_ADDRESS)
			qmlObject->setProperty("kph", canData.data.at(0));
		else if(canData.id == TEMPERATURE_ADDRESS)
			qmlObject->setProperty("temperature", canData.data.at(0));
		else if(canData.id == LEFT_ADDRESS)
			qmlObject->setProperty("leftArrow", canData.data.at(0));
		else if(canData.id == RIGHT_ADDRESS)
			qmlObject->setProperty("rightArrow", canData.data.at(0));
		else if(canData.id == FRONT_ADDRESS)
		{
			qmlObject->setProperty("smallOn", canData.data.at(1));
			qmlObject->setProperty("dimOn", canData.data.at(0));
			qmlObject->setProperty("fullOn", canData.data.at(2));
		}
		else if(canData.id == BATTERY_ADDRESS)
		{
			int batteryVoltage = (canData.data.at(0) << 8) + canData.data.at(1);
			int min = 40;
			int max = 57.4;
			float batteryPercentage = 1 / ((min - max)*(batteryVoltage - min));
			qmlObject->setProperty("fuel", batteryPercentage);
			
			int battery1Amp = (canData.data.at(3) << 8) + canData.data.at(4);
			int battery2Amp = (canData.data.at(5) << 8) + canData.data.at(6);
			float batteryAmp = (battery1Amp + battery2Amp) / 2;
			qmlObject->setProperty("rpm",batteryAmp);

		}
		else if(canData.id == MC_DNR)
		{
			switch(canData.data.at(0))
			{
				case 1:
					qmlObject->setProperty("gear", "D");
					break;
				case 2:
					qmlObject->setProperty("gear", "N");
					break;
				case 3:
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

//BAT 57.4 max 40 min