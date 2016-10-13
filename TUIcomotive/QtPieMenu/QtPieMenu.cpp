#include "QtPieMenu.h"

QtPieMenu::QtPieMenu(QWidget *parent)
    : QWidget(parent)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(1000);

	setWindowTitle(tr("Analog Clock"));
	resize(200, 200);
}

void QtPieMenu::paintEvent(QPaintEvent *)
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

	QColor hourColor(75, 0, 130);
	QColor minuteColor(255, 0, 0, 191);
	QColor secondColor(255, 255, 124);

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
		if ((j % 5) != 0)
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
}

bool QtPieMenu::readSecondHand()
{
	return m_SecondHand;
}

void QtPieMenu::toggleSecondHand()
{
	m_SecondHand = !m_SecondHand;
	update();
}

void QtPieMenu::setSecondHand(bool toggle)
{
	m_SecondHand = toggle;
	update();
}
