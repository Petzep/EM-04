#pragma once

#define MENU qtPieMenu

#include <QDialog>
#include <QtGui>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QMediaPlaylist>
#include <QListWidget>
#include "SieFlyStyle.h"
#include "ui_TestDialog.h"

class TestDialog : public QDialog, public Ui::TestDialog
{
	Q_OBJECT

public:
	TestDialog(QWidget *parent = Q_NULLPTR);
	~TestDialog();
	bool event(QEvent *event);
	bool loadMusic(QString dir);
	void updateMetaData();

public slots:
	void on_playButton_toggled(bool);
	void on_stopButton_clicked(void);
	void on_prevButton_clicked(void);
	void on_nextButton_clicked(void);
	void on_loopOneButton_clicked(void);
	void on_loopAllButton_clicked(void);
	void on_shuffleBox_clicked(void);
	void onPositionChanged(qint64 position);
	void onCurrentIndexChanged(int);
	void onStateChanged(QMediaPlayer::State);

private:
	QMediaPlayer* m_player;
	QMediaPlaylist* m_playlist;
	

};
