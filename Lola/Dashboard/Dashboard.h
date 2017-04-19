#pragma once

#include <QObject>
#include <QCanBus>
#include <qtextstream.h>
#include <QString>
#include <QMessageBox>

struct CanLogMsg
{
	long long time;
	QString id;
	int dlc;
	QStringList data;
};

class Dashboard : public QObject
{
	Q_OBJECT
public:
	Dashboard(QObject *parent = Q_NULLPTR);

	void setRoot(QObject *root);

	bool initCan(int can);

private:
	QString m_name;
	int m_shoeSize;
	QCanBusDevice *canDevice;
	QObject *m_root;

public slots:
	void canError(void);
	void canRx(void);
	void canTx(void);
};