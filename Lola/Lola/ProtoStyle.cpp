#include <QtWidgets>

#include "ProtoStyle.h"

ProtoStyle::ProtoStyle()
	: QProxyStyle(QStyleFactory::create("fusion"))
{
}

void ProtoStyle::polish(QPalette &palette)
{
	QColor blackish(36, 30, 32);
	QColor greyish(92, 93, 95);
	QColor slightlyOpaqueBlack(0, 0, 0, 63);

	QPainter painter;

	palette = QPalette(blackish);

	palette.setBrush(QPalette::BrightText, Qt::white);
	palette.setBrush(QPalette::Base, greyish);
	palette.setBrush(QPalette::Highlight, Qt::darkGreen);

	QBrush brush = palette.background();
	brush.setColor(brush.color().light());

	palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
	palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
	palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
	palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
	palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
	palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);
}

void ProtoStyle::polish(QWidget *widget)
{
	if(qobject_cast<QPushButton *>(widget) || qobject_cast<QComboBox *>(widget))
		widget->setAttribute(Qt::WA_Hover, true);
}

void ProtoStyle::unpolish(QWidget *widget)
{
	if(qobject_cast<QPushButton *>(widget) || qobject_cast<QComboBox *>(widget))
		widget->setAttribute(Qt::WA_Hover, false);
}

void ProtoStyle::setTexture(QPalette &palette, QPalette::ColorRole role,
							 const QPixmap &pixmap)
{
	for(int i = 0; i < QPalette::NColorGroups; ++i)
	{
		QColor color = palette.brush(QPalette::ColorGroup(i), role).color();
		palette.setBrush(QPalette::ColorGroup(i), role, QBrush(color, pixmap));
	}
}

QPainterPath ProtoStyle::roundRectPath(const QRect &rect)
{
	int radius = qMin(rect.width(), rect.height()) / 2;
	int diam = 2 * radius;

	int x1, y1, x2, y2;
	rect.getCoords(&x1, &y1, &x2, &y2);

	QPainterPath path;
	path.moveTo(x2, y1 + radius);
	path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
	path.lineTo(x1 + radius, y1);
	path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
	path.lineTo(x1, y2 - radius);
	path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
	path.lineTo(x1 + radius, y2);
	path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
	path.closeSubpath();
	return path;
}