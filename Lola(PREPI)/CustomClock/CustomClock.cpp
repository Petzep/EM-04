#include "CustomClock.h"

CustomClock::CustomClock(QWidget *parent)
	: QWidget(parent)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(1000);

	setWindowTitle(tr("Analog Clock"));
	resize(200, 200);
	m_SecondHand = true;
	m_colorSecondHand = { 75, 0, 130 };
	m_colorMinuteHand = { 255, 0, 0, 191 };
	m_colorHourHand = { 255, 255, 124 };
}

void CustomClock::paintEvent(QPaintEvent *)
{
	static const QPoint hourHand[3] = {
		QPoint(7, 8),
		QPoint(-7, 8),
		QPoint(0, -40)
	};
	static const QPoint minuteHand[3] = {
		QPoint(7, 8),
		QPoint(-7, 8),
		QPoint(0, -70)
	};
	static const QPoint secondHand[3] = {
		QPoint(2, 8),
		QPoint(-2, 8),
		QPoint(0, -70)
	};
	static const QPoint quarter[3] = {
		QPoint(96, 3),
		QPoint(96, -3),
		QPoint(90, 0)
	};

	QColor secondColor = m_colorSecondHand;
	QColor minuteColor = m_colorMinuteHand;
	QColor hourColor = m_colorHourHand;

	int side = qMin(width(), height());
	QTime time = QTime::currentTime();

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);

	painter.setPen(Qt::NoPen);
	painter.setBrush(hourColor);

	painter.save();
	painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
	painter.drawConvexPolygon(hourHand, 3);
	painter.restore();

	painter.setPen(hourColor);

	for (int i = 0; i < 12; ++i) {
		if ((i % 3) != 0)
			painter.drawLine(88, 0, 96, 0);
		painter.rotate(30.0);
	}

	painter.setPen(Qt::NoPen);
	painter.setBrush(minuteColor);

	painter.save();
	painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
	painter.drawConvexPolygon(minuteHand, 3);
	painter.restore();

	painter.setPen(minuteColor);

	for (int j = 0; j < 60; ++j) {
		if (((j % 5) != 0) || ((j % 5) != 0))
			painter.drawLine(92, 0, 96, 0);
		painter.rotate(6.0);
	}

	if (m_SecondHand)
	{
		painter.setPen(Qt::NoPen);
		painter.setBrush(secondColor);

		painter.save();
		painter.rotate(6.0 * (time.second()));
		painter.drawConvexPolygon(secondHand, 3);
		painter.restore();
	}

	painter.setPen(Qt::NoPen);
	painter.setBrush(secondColor);
	painter.save();

	for (int k = 0; k < 4; ++k) {
		painter.drawConvexPolygon(quarter, 3);
		painter.rotate(90.0);
	}
	painter.restore();
}

bool CustomClock::secondHand() const
{
	return m_SecondHand;
}

QColor CustomClock::colorSecondHand() const
{
	return m_colorSecondHand;
}

QColor CustomClock::colorMinuteHand() const
{
	return m_colorMinuteHand;
}

QColor CustomClock::colorHourHand() const
{
	return m_colorHourHand;
}

void CustomClock::toggleSecondHand()
{
	m_SecondHand = !m_SecondHand;
	update();
}

void CustomClock::setSecondHand(bool toggle)
{
	m_SecondHand = toggle;
	update();
}

void CustomClock::setColorSecondHand(const QColor& color)
{
	m_colorSecondHand = color;
}

void CustomClock::setColorMinuteHand(const QColor& color)
{
	m_colorMinuteHand = color;
}

void CustomClock::setColorHourHand(const QColor& color)
{
	m_colorHourHand = color;
}
