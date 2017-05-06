#pragma once

#define MENU qtPieMenu

#define DEVICE_NR			0b1000
#define	EM_04_CAN_RANGE		0x100

#define ALL_ADDRESS			(0x000 + EM_04_CAN_RANGE)
#define FAN_ADDRESS			(0x010 + EM_04_CAN_RANGE)
#define COUT_ADDRESS		(0x020 + EM_04_CAN_RANGE)			
#define LIGHT_ADDRESS		(0x001 + COUT_ADDRESS)
#define FRONT_ADDRESS		(0x002 + COUT_ADDRESS)
#define REAR_ADDRESS		(0x003 + COUT_ADDRESS)		
#define LEFT_ADDRESS		(0x004 + COUT_ADDRESS)
#define RIGHT_ADDRESS		(0x005 + COUT_ADDRESS)
#define WIPER_ADDRESS		(0x006 + COUT_ADDRESS)
#define WASHER_ADDRESS		(0x007 + COUT_ADDRESS)
#define CLAXON_ADDRESS		(0x008 + COUT_ADDRESS)
#define BLOWER_ADDRESS		(0x009 + COUT_ADDRESS)
#define HUD_ADDRESS			(0x030 + COUT_ADDRESS)
#define SPEED_ADDRESS		(0x001 + HUD_ADDRESS)
#define WARNING_ADDRESS		(0x002 + HUD_ADDRESS)
#define TEMPERATURE_ADDRESS	(0x003 + HUD_ADDRESS)
#define BATTERY_ADDRESS		(0x004 + HUD_ADDRESS)
#define DIMMER_ADDRESS		(0x005 + HUD_ADDRESS)
#define CLOCK_ADDRES		(0x00a + HUD_ADDRESS)
#define MC_ADDRESS			(0x040 + EM_04_CAN_RANGE)
#define MC_SPEED_STAT		(0x001 + MC_ADDRESS)
#define MC_MOTOR_STAT		(0x002 + MC_ADDRESS)
#define MC_I2C				(0x003 + MC_ADDRESS)
#define MC_DNR				(0x004 + MC_ADDRESS)
#define ROBOTEQ_ADDRES		(0x050)
#define BROADCAST_ADDRESS	(0x700)


#include <QDialog>
#include <QtGui>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QtQml/QtQml>
#include <QQuickWidget>
#include "SieFlyStyle.h"
#include "CanDialog.h"
#include "ui_TestDialog.h"

class TestDialog : public QDialog, public Ui::TestDialog
{
	Q_OBJECT

public:
	TestDialog(QWidget *parent = Q_NULLPTR);
	~TestDialog();
	bool event(QEvent *event);
	bool loadMusic(QString dir);
	bool loadRadio();
	void updateMetaData();

public slots:
//Dashboard
	void dashboardClose(void);
//Can
	bool initCan(int can);
	void canError(void);
	void canRx(void);
	void canTx(void);
//Debug
	void on_quitButton_clicked(void);
//Radio
	void on_prevStationButton_clicked(void);
	void on_nextStationButton_clicked(void);
	void on_radioButton_clicked(void);
	void onRadioStationChanged(int track);
//MusicPlayer
	void on_playButton_toggled(bool);
	void on_stopButton_clicked(void);
	void on_prevButton_clicked(void);
	void on_nextButton_clicked(void);
	void on_loopOneButton_clicked(void);
	void on_loopAllButton_clicked(void);
	void on_shuffleBox_clicked(void);
//Debug
	void on_dashboardButton_clicked(void);
	void on_canButton_clicked(void);
	void onPositionChanged(qint64 position);
	void on_shutdownButton_clicked(void);
	void onCurrentIndexChanged(int);
	void onStateChanged(QMediaPlayer::State);

private:
	QMediaPlayer* m_player;
	QMediaPlaylist* m_playlist;
	QMediaPlaylist* m_radiolist;
	QCanBusDevice *canDevice;


	

};
