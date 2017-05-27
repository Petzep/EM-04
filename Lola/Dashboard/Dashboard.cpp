#include "Dashboard.h"

Dashboard::Dashboard(QObject *parent)
	: QObject(parent)
{
}

void Dashboard::setRoot(QObject * root)
{
	m_root = root;
	connect(m_root, SIGNAL(startDebug()), this, SLOT(startDebug()));
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
			qmlObject->setProperty("temperature", qMax(qMax(canData.data.at(0), canData.data.at(1)), canData.data.at(2)));
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
			float batteryVoltage = (canData.data.at(0) + (canData.data.at(1) << 8))/10;
			qmlObject->setProperty("fuel", (batteryVoltage));

			if (batteryVoltage < 48)
				qmlObject->setProperty("batOn", true);
			else
				qmlObject->setProperty("batOn", false);
			
			float battery1Amp = (canData.data.at(2) + (canData.data.at(3) << 8))/10;
			float battery2Amp = (canData.data.at(4) + (canData.data.at(5) << 8))/10;
			float batteryAmp = battery1Amp + battery2Amp;
			qmlObject->setProperty("rpm",batteryAmp);
		}
		else if(canData.id == MC_DNR)
		{
			switch(canData.data.at(0))
			{
				case 0:
					qmlObject->setProperty("gear", "-");
					break;
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
		else if(canData.id == NFC_ADDRESS)
		{
			uint8_t id[8] = { canData.data.at(7), canData.data.at(6), canData.data.at(5), canData.data.at(4), canData.data.at(3), canData.data.at(2), canData.data.at(1), canData.data.at(0) };
			uint64_t totalID = 0;
			memcpy(&totalID, &id, 8 * sizeof(uint8_t));
			typedef struct { int r; int g; int b; int w; } rgb;
			rgb color;

			if(totalID == NFC_NEPHTALY)
			{
				color.r = 86;
				color.g = 2;
				color.b = 142;
				color.w = 0;
				qmlObject->setProperty("gear", "Nephtaly");
			}
			else if(totalID == NFC_THOM)
			{
				color.r = 255;
				color.g = 128;
				color.b = 0;
				color.w = 0;
			}
			else if(totalID == NFC_DANIEL)
			{
				color.r = 255;
				color.g = 255;
				color.b = 0;
				color.w = 0;
			}
			else if(totalID == NFC_LINDSEY)
			{
				color.r = 255;
				color.g = 0;
				color.b = 128;
				color.w = 0;
			}
			else if(totalID == NFC_ROEL)
			{
				color.r = 0;
				color.g = 255;
				color.b = 255;
				color.w = 0;
			}
			else if(totalID == NFC_QUINTEN)
			{
				color.r = 0;
				color.g = 158;
				color.b = 255;
				color.w = 0;
			}
			else if(totalID == NFC_LOES)
			{
				color.r = 255;
				color.g = 0;
				color.b = 0;
				color.w = 0;
			}
			else
			{
				color.r = 0;
				color.g = 0;
				color.b = 0;
				color.w = 1;
				qmlObject->setProperty("gear", "NFC");
			}

			QProcess::startDetached(QString("echo ") + QString(color.w) + QString("> /sys/class/backlight/backlight.17/brightness")); //wit
			QProcess::startDetached(QString("echo ") + QString(color.r) + QString("> /sys/class/leds/PWM2/brightness")); //rood
			QProcess::startDetached(QString("echo ") + QString(color.g) + QString("> /sys/class/leds/PWM1/brightness")); //groen
			QProcess::startDetached(QString("echo ") + QString(color.b) + QString("> /sys/class/leds/PWM3/brightness")); //blauw
		}
	}
}

void Dashboard::canTx(void)
{
	qDebug("Frames written");
}

void Dashboard::startDebug(void)
{
	QProcess::startDetached("/home/root/Lola2");
	canDevice->disconnectDevice();
	QProcess::startDetached("killall -e Lola");

}

//BAT 58.4 max 40 min