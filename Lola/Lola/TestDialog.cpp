#include "TestDialog.h"

TestDialog::TestDialog(QWidget *parent)
	: QDialog(parent)
{
	QApplication::setStyle(new SieFlyStyle);
	setupUi(this);
	this->setFixedSize(QSize(800, 480));
	m_player = new QMediaPlayer(this);
	m_playlist = new QMediaPlaylist(m_player);
	m_radiolist = new QMediaPlaylist(m_player);
	m_player->setPlaylist(m_playlist);
	m_player->setVolume(50);
	playerBar->setMaximum(m_player->duration()/1000);
	volumeDial->setValue(m_player->volume());
	volumeDial_2->setValue(m_player->volume());
	connect(volumeDial, SIGNAL(valueChanged(int)), m_player, SLOT(setVolume(int)));
	connect(volumeDial_2, SIGNAL(valueChanged(int)), m_player, SLOT(setVolume(int)));
	connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
	connect(m_playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
	connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onStateChanged(QMediaPlayer::State)));
	connect(m_radiolist, SIGNAL(currentIndexChanged(int)), this, SLOT(onRadioStationChanged(int)));

	if(!loadMusic("/media") | !loadRadio())
		QApplication::beep();

	quickWidget->setSource(QUrl("qrc:/qml/dashboardRect.qml"));
	quickWidget->hide();
	connect((QObject*)quickWidget->rootObject(), SIGNAL(exit()), this, SLOT(dashboardClose()));

	//miniFix for broken QtStyle
	QKeyEvent * eve1 = new QKeyEvent(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
	QKeyEvent * eve2 = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Tab, Qt::NoModifier);

	MENU->setFocus();

	qApp->postEvent((QObject*)MENU, (QEvent *)eve1);
	qApp->postEvent((QObject*)MENU, (QEvent *)eve2);

	focusPreviousChild();

	stackSlide->slideHome();
}

TestDialog::~TestDialog()
{
	delete m_player;
}

bool TestDialog::event(QEvent *event)
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		int cmd = ke->key();
		if(!stackSlide->inAnimation())
		{
			if(cmd >= Qt::Key_0 && cmd <= Qt::Key_9) //filter for numeric-keys
			{
				int value;
				int itemNumbers = MENU->itemNumbers();

				//Event handler for qtPieMenu
				if(MENU->hasFocus())
				{
					switch(cmd)
					{
						case Qt::Key_4:
						{
							value = MENU->selection() - 1;
							break;
						}
						case Qt::Key_6:
						{
							value = MENU->selection() + 1;
							break;
						}
						case Qt::Key_5:
						{
							MENU->select();
							break;
						}
						default:
							break;
					}

					//Only change if the value is changed
					if(cmd == Qt::Key_4 || cmd == Qt::Key_6)
					{
						if(value > itemNumbers - 1)
							value = (value) % itemNumbers;
						else if(value < 0)
							value = (value + itemNumbers) % itemNumbers;

						MENU->setSelection(value);
					}
				}
				//Button event handler
				else if(QString(focusWidget()->metaObject()->className()).contains(QString("Button")) || QString(focusWidget()->metaObject()->className()).contains(QString("Box")))
				{
					QPushButton* button = (QPushButton*)focusWidget();
					switch(cmd)
					{
						case Qt::Key_4:
						{
							focusPreviousChild();
							break;
						}
						case Qt::Key_6:
						{
							focusNextChild();
							break;
						}
						case Qt::Key_5:
						{
							button->click();
							break;
						}
						default:
							break;
					}
				}
				//Dail event handler
				else if(QString(focusWidget()->metaObject()->className()).contains(QString("Dial")))
				{
					QDial* dial = (QDial*)focusWidget();
					if(dial->notchesVisible())
					{
						switch(cmd)
						{
							case Qt::Key_7:
							case Qt::Key_5:
								dial->setNotchesVisible(false);
								break;
							case Qt::Key_8:
							case Qt::Key_6:
							{
								dial->setValue(dial->value() + 1);
								break;
							}
							case Qt::Key_2:
							case Qt::Key_4:
							{
								dial->setValue(dial->value() - 1);
								break;
							}
							default:
								break;
						}
					}
					else
					{
						switch(cmd)
						{
							case Qt::Key_5:
								dial->setNotchesVisible(true);
								break;
							case Qt::Key_8:
							case Qt::Key_4:
							{
								focusPreviousChild();
								break;
							}
							case Qt::Key_2:
							case Qt::Key_6:
							{
								focusNextChild();
								break;
							}
							case Qt::Key_7:
								stackSlide->slideHome();
								MENU->setFocus();
								break;
							default:
								break;
						}
					}
				}
				else
				{
					switch(cmd)
					{
						case Qt::Key_8:
						case Qt::Key_4:
						{
							focusPreviousChild();
							break;
						}
						case Qt::Key_2:
						case Qt::Key_6:
						{
							focusNextChild();
							break;
						}
						default:
							break;
					}
				}
			}
		}

		//Always return to home and set focus
		if(ke->key() == Qt::Key_0)
		{
			if(quickWidget->isVisible())
			{
				quickWidget->setVisible(false);
				quickWidget->lower();
			}
			stackSlide->slideHome();
			MENU->setFocus();
		}
		return true;
	}
	return QWidget::event(event);
}

//////////////////////
/////Debug Events/////
//////////////////////
void TestDialog::dashboardClose(void)
{
	if(quickWidget->status() == QQuickWidget::Status::Null)
		qInfo("This QQuickWidget has no source set.");
	if(quickWidget->status() == QQuickWidget::Status::Ready)
		qInfo("This QQuickWidget has loaded and created the QML component.");
	if(quickWidget->status() == QQuickWidget::Status::Loading)
		qInfo("This QQuickWidget is loading network data.");
	if(quickWidget->status() == QQuickWidget::Status::Error)
		qInfo("	One or more errors occurred. Call errors() to retrieve a list of errors.");
	quickWidget->show();
	quickWidget->lower();
	stackSlide->slideHome();
	MENU->setFocus();
}

//////////////////////
//////Can Events/////
//////////////////////
bool TestDialog::initCan(int can)
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

void TestDialog::canRx(void)
{
	if(!canDevice)
		return;

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

		if(canData.id == BATTERY_ADDRESS)
		{
			float batteryVoltage = ((canData.data.at(0) << 8) + canData.data.at(1)) / 10.0;
			float battery1Amp = ((canData.data.at(2) << 8) + canData.data.at(3)) / 10.0;
			float battery2Amp = ((canData.data.at(4) << 8) + canData.data.at(5)) / 10.0;
			float internalVoltage = ((canData.data.at(6) << 8) + canData.data.at(7)) / 10.0;

			//Battery Stats
			lcdBatVolt->display(batteryVoltage);
			if(batteryVoltage < lcdBatVoltMin->value())
				lcdBatVoltMin->display(batteryVoltage);
			if(batteryVoltage > lcdBatVoltMax->value())
				lcdBatVoltMax->display(batteryVoltage);
			if(batteryVoltage > 57.4)
				lcdBatVolt->setPalette(Qt::yellow);
			if(batteryVoltage > 58)
				lcdBatVolt->setPalette(Qt::red);
			else
				lcdBatVolt->setPalette(this->style()->standardPalette());

			lcdBat1Amp->display(battery1Amp);
			if(battery1Amp < lcdBat1AmpMin->value())
				lcdBat1AmpMin->display(battery1Amp);
			if(battery1Amp > lcdBat1AmpMax->value())
				lcdBat1AmpMax->display(battery1Amp);

			lcdBat2Amp->display(battery2Amp);
			if(battery2Amp < lcdBat2AmpMin->value())
				lcdBat2AmpMin->display(battery2Amp);
			if(battery2Amp > lcdBat2AmpMax->value())
				lcdBat2AmpMax->display(battery2Amp);

			lcdIntVolt->display(internalVoltage);
			if(internalVoltage < lcdIntVoltMin->value())
				lcdIntVoltMin->display(internalVoltage);
			if(internalVoltage > lcdIntVoltMax->value())
				lcdIntVoltMax->display(internalVoltage);

			lcdBatSum->display(battery1Amp + battery2Amp);
			if((battery1Amp + battery2Amp) > 130)
				lcdBatSum->setPalette(Qt::yellow);
			if((battery1Amp + battery2Amp) > 150)
				lcdBatSum->setPalette(Qt::red);
			else
				lcdBatSum->setPalette(this->style()->standardPalette());
		}
		else if(canData.id == MC_MOTOR_STAT)
		{
			float motor1Amp = ((canData.data.at(0) << 8) + canData.data.at(1)) / 10.0;
			float motor2Amp = ((canData.data.at(2) << 8) + canData.data.at(3)) / 10.0;
			float motor1Power = ((canData.data.at(4) << 8) + canData.data.at(5)) / 10.0;
			float motor2Power = ((canData.data.at(6) << 8) + canData.data.at(7)) / 10.0;

			//MotorStats
			lcdMot1Amp->display(motor1Amp);
			if(motor1Amp < lcdMot1AmpMin->value())
				lcdMot1AmpMin->display(motor1Amp);
			if(motor1Amp > lcdMot1AmpMax->value())
				lcdMot1AmpMax->display(motor1Amp);

			lcdMot2Amp->display(motor2Amp);
			if(motor2Amp < lcdMot2AmpMin->value())
				lcdMot2AmpMin->display(motor2Amp);
			if(motor2Amp > lcdMot2AmpMax->value())
				lcdMot2AmpMax->display(motor2Amp);

			lcdMot1Power->display(motor1Power);
			if(motor1Power < lcdMot1PowerMin->value())
				lcdMot1PowerMin->display(motor1Power);
			if(motor1Power > lcdMot1PowerMax->value())
				lcdMot1PowerMax->display(motor1Power);

			lcdMot2Power->display(motor2Power);
			if(motor2Power < lcdMot2PowerMin->value())
				lcdMot2PowerMin->display(motor2Power);
			if(motor2Power > lcdMot2PowerMax->value())
				lcdMot2PowerMax->display(motor2Power);
		}
		else if(canData.id == TEMPERATURE_ADDRESS)
		{
			float MCUTemp = ((canData.data.at(0) << 8) + canData.data.at(1)) / 10.0;
			float heatSink1Temp = ((canData.data.at(2) << 8) + canData.data.at(3)) / 10.0;
			float heatSink2Temp = ((canData.data.at(4) << 8) + canData.data.at(5)) / 10.0;

			//Temperature
			lcdMCUTemp->display(MCUTemp);
			if(MCUTemp < lcdMCUTempMin->value())
				lcdMCUTempMin->display(MCUTemp);
			if(MCUTemp > lcdMCUTempMax->value())
				lcdMCUTempMax->display(MCUTemp);
			if(MCUTemp == 0)
				lcdMCUTemp->setPalette(Qt::yellow);
			if(MCUTemp > 40)
				lcdMCUTemp->setPalette(Qt::red);

			lcdMos1Temp->display(heatSink1Temp);
			if(heatSink1Temp < lcdMos1TempMin->value())
				lcdMos1TempMin->display(heatSink1Temp);
			if(heatSink1Temp > lcdMos1TempMax->value())
				lcdMos1TempMax->display(heatSink1Temp);
			if(heatSink1Temp > 50)
				lcdMos1Temp->setPalette(Qt::yellow);
			if(heatSink1Temp > 60)
				lcdMos1Temp->setPalette(Qt::red);
			else
				lcdMos1Temp->setPalette(this->style()->standardPalette());


			lcdMos2Temp->display(heatSink2Temp);
			if(heatSink2Temp < lcdMos2TempMin->value())
				lcdMos2TempMin->display(heatSink2Temp);
			if(heatSink2Temp > lcdMos2TempMax->value())
				lcdMos2TempMax->display(heatSink2Temp);
			if(heatSink2Temp > 50)
				lcdMos2Temp->setPalette(Qt::yellow);
			if(heatSink2Temp > 60)
				lcdMos2Temp->setPalette(Qt::red);
			else
				lcdMos2Temp->setPalette(this->style()->standardPalette());
		}
	}
}

void TestDialog::canError(void)
{
	QMessageBox::StandardButton warningBox;
	warningBox = QMessageBox::warning(this, "CANerror", tr("Connection error: %1").arg(canDevice->errorString()));
}

void TestDialog::canTx(void)
{
	qDebug("Frames written");
}

//////////////////////
/////Debug Events/////
//////////////////////
void TestDialog::on_quitButton_clicked(void)
{
	this->close();
}

void TestDialog::on_shutdownButton_clicked(void)
{
	QProcess::startDetached("shutdown now");
}

void TestDialog::on_dashboardButton_clicked(void)
{
	quickWidget->setVisible(true);
	quickWidget->raise();
}

void TestDialog::on_canButton_clicked(void)
{
	CanDialog dialog(this);
	dialog.exec();
}

//////////////////////
/////Radio Events/////
//////////////////////
void TestDialog::on_nextStationButton_clicked(void)
{
	m_player->playlist()->next();
}

void TestDialog::on_prevStationButton_clicked(void)
{
	m_player->playlist()->previous();
}
void TestDialog::on_radioButton_clicked(void)
{
	m_player->setPlaylist(m_radiolist);
	m_player->play();
}

void TestDialog::onRadioStationChanged(int track)
{
	stationWidget->setCurrentRow(track);
}
//////////////////////
/////Music Events/////
//////////////////////
void TestDialog::onCurrentIndexChanged(int track)
{
	playlistWidget->setCurrentRow(track);
	updateMetaData();
}

void TestDialog::updateMetaData()
{
	playerBar->setMaximum(m_player->duration() / 1000);

	if(m_player->isMetaDataAvailable())
	{
		textArtist->setText(m_player->metaData(QMediaMetaData::ContributingArtist).toString());
		textTitle->setText(m_player->metaData(QMediaMetaData::Title).toString());
	}
	update();
}

void TestDialog::onStateChanged(QMediaPlayer::State state)
{
	if(state == QMediaPlayer::State::StoppedState)
		playButton->setChecked(false);
}

void TestDialog::onPositionChanged(qint64 pos)
{
	qint64 duration = (m_player->duration()) / 1000;
	qint64 position = pos / 1000;

	playerBar->setValue(position);

	QTime currentTime((position / 3600) % 60, (position / 60) % 60, position % 60, (position * 1000) % 1000);
	QTime totalTime((duration / 3600) % 60, (duration / 60) % 60, duration%60, (duration * 1000) % 1000);

	QString format = "mm:ss";
	if(duration > 3600)
		format = "hh:mm:ss";
	playerBar->setFormat(QString(currentTime.toString(format) + " / " + totalTime.toString(format)));

	updateMetaData();//Q&D FIX
}

void TestDialog::on_playButton_toggled(bool)
{
	if(m_player->playlist() != m_playlist)
		m_player->setPlaylist(m_playlist);

	if(playButton->isChecked())
		m_player->play();
	else
		m_player->pause();
	updateMetaData();
}

void TestDialog::on_prevButton_clicked(void)
{
	m_player->playlist()->previous();
	if(!(m_player->playlist()->currentIndex()) && m_player->playlist()->playbackMode() == QMediaPlaylist::PlaybackMode::Sequential)
	{
		nextButton->setFocus();
		prevButton->setEnabled(false);
	}
	else
		nextButton->setEnabled(true);
	updateMetaData();
}

void TestDialog::on_nextButton_clicked(void)
{
	m_player->playlist()->next();
	if(!(m_player->playlist()->currentIndex() < m_player->playlist()->mediaCount() - 1) && m_player->playlist()->playbackMode() == QMediaPlaylist::PlaybackMode::Sequential)
	{
		prevButton->setFocus();
		nextButton->setEnabled(false);
	}
	else
		prevButton->setEnabled(true);
	updateMetaData();
}

void TestDialog::on_loopOneButton_clicked(void)
{
	if(!loopOneButton->isChecked())
	{
		loopOneButton->setChecked(false);
		m_player->playlist()->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
	}
	else
	{
		loopAllButton->setChecked(false);
		m_player->playlist()->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemOnce);
	}
}

void TestDialog::on_loopAllButton_clicked(void)
{
	if(!loopAllButton->isChecked())
	{
		loopAllButton->setChecked(false);
		m_player->playlist()->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
	}
	else
	{
		loopOneButton->setChecked(false);
		m_player->playlist()->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
		nextButton->setEnabled(true);
		prevButton->setEnabled(true);
	}
}

void TestDialog::on_shuffleBox_clicked(void)
{
	if(shuffleBox->isChecked())
		m_player->playlist()->setPlaybackMode(QMediaPlaylist::PlaybackMode::Random);
	else
		m_player->playlist()->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
}

void TestDialog::on_stopButton_clicked(void)
{
	m_player->stop();
}

bool TestDialog::loadMusic(QString musicFolder)
{
	QDir dir(QString(QDir::currentPath() + musicFolder));
	QStringList files = dir.entryList(QStringList() << "*.mp3", QDir::Files);
	if(files.isEmpty())
		return false;
	QList<QMediaContent> content;
	for(const QString& f : files)
	{
		content.push_back(QUrl::fromLocalFile(dir.path() + "/" + f));
		QFileInfo fi(f);
		QListWidgetItem *item = new QListWidgetItem(fi.fileName().remove(".mp3"), playlistWidget);
	}

	m_playlist->addMedia(content);
	playlistWidget->setCurrentRow(0);

	return true;
}

bool TestDialog::loadRadio()
{
	QDir dir(QString(QDir::currentPath() + "/radio"));
	QStringList files = dir.entryList(QStringList() << "*.mp3", QDir::Files);
	if(files.isEmpty())
		return false;
	QList<QMediaContent> content;
	for(const QString& f : files)
	{
		content.push_back(QUrl::fromLocalFile(dir.path() + "/" + f));
		QFileInfo fi(f);
		QListWidgetItem *item = new QListWidgetItem(fi.fileName().remove(".mp3"), stationWidget);
	}

	m_radiolist->addMedia(content);
	stationWidget->setCurrentRow(0);

	return true;
}