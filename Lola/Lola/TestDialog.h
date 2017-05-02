#pragma once

#define MENU qtPieMenu

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
	

};
