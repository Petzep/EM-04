#pragma once

#include <QObject>
#include <QCanBus>
#include <qtextstream.h>
#include <QString>
#include <QMessageBox>

#define DEVICE_NR			0b1000
#define	EM_04_CAN_RANGE		0x100

#define ALL_ADDRESS			(0x000 + EM_04_CAN_RANGE)
#define FAN_ADDRESS			(0x010 + EM_04_CAN_RANGE)
#define COUT_ADDRESS		(0x020 + EM_04_CAN_RANGE)
#define FRONT_ADDRESS		(0x002 + COUT_ADDRESS)
#define REAR_ADDRESS		(0x003 + COUT_ADDRESS)
#define LEFT_ADDRESS		(0x004 + COUT_ADDRESS)
#define RIGHT_ADDRESS		(0x005 + COUT_ADDRESS)
#define WIPER_ADDRESS		(0x006 + COUT_ADDRESS)
#define CLAXON_ADDRESS		(0x007 + COUT_ADDRESS)
#define BLOWER_ADDRESS		(0x008 + COUT_ADDRESS)
#define HUD_ADDRESS			(0x030 + COUT_ADDRESS)
#define SPEED_ADDRESS		(0x001 + HUD_ADDRESS)
#define WARNING_ADDRESS		(0x002 + HUD_ADDRESS)
#define TEMPERATURE_ADDRESS	(0x003 + HUD_ADDRESS)
#define BATTERY_ADDRESS		(0x004 + HUD_ADDRESS)
#define DIMMER_ADDRESS		(0x005 + HUD_ADDRESS)
#define CLOCK_ADDRES		(0x00a + HUD_ADDRESS)
#define MC_ADDRESS			(0x040 + EM_04_CAN_RANGE)
#define MC_SIGNAL1			(0x001 + MC_ADDRESS)
#define MC_SIGNAL2			(0x002 + MC_ADDRESS)
#define MC_I2C				(0x003 + MC_ADDRESS)
#define MC_DNR				(0x004 + MC_ADDRESS)
#define BROADCAST_ADDRESS	(0x050 + EM_04_CAN_RANGE)

struct CanLogMsg
{
	long long time;
	uint32_t id; //extended data frame suport
	int dlc;
	QVector<uint32_t> data;
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