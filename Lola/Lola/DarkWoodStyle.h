#pragma once
#include <QProxyStyle>
#include <QPalette>

class QPainterPath;

class DarkWoodStyle : public QProxyStyle
{
	Q_OBJECT

public:
	DarkWoodStyle();

	void polish(QPalette &palette) Q_DECL_OVERRIDE;
	void polish(QWidget *widget) Q_DECL_OVERRIDE;
	void unpolish(QWidget *widget) Q_DECL_OVERRIDE;
	int pixelMetric(PixelMetric metric, const QStyleOption *option,
					const QWidget *widget) const Q_DECL_OVERRIDE;
	int styleHint(StyleHint hint, const QStyleOption *option,
				  const QWidget *widget, QStyleHintReturn *returnData) const Q_DECL_OVERRIDE;
	void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
					   QPainter *painter, const QWidget *widget) const Q_DECL_OVERRIDE;
	void drawControl(ControlElement control, const QStyleOption *option,
					 QPainter *painter, const QWidget *widget) const Q_DECL_OVERRIDE;

private:
	static void setTexture(QPalette &palette, QPalette::ColorRole role,
						   const QPixmap &pixmap);
	static QPainterPath roundRectPath(const QRect &rect);
};