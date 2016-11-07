#pragma once

#include <QtWidgets/QWidget>
#include <qtimer.h>
#include <QTime>
#include <qpainter.h>

class CustomClock : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(bool ToggleSecondHand READ secondHand WRITE setSecondHand)
		Q_PROPERTY(QColor colorSecondHand READ colorSecondHand WRITE setColorSecondHand)
		Q_PROPERTY(QColor colorMinuteHand READ colorMinuteHand WRITE setColorMinuteHand)
		Q_PROPERTY(QColor colorHourHand READ colorHourHand WRITE setColorHourHand)


public:
	CustomClock(QWidget *parent = Q_NULLPTR);
	bool secondHand() const;
	QColor colorSecondHand() const;
	QColor colorMinuteHand() const;
	QColor colorHourHand() const;

	public slots:
	void toggleSecondHand();
	void setSecondHand(bool toggle);
	void setColorSecondHand(const QColor& color);
	void setColorMinuteHand(const QColor& color);
	void setColorHourHand(const QColor& color);

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	bool m_SecondHand;
	QColor m_colorSecondHand;
	QColor m_colorMinuteHand;
	QColor m_colorHourHand;
};
