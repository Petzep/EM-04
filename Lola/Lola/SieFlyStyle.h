#pragma once

#include <QProxyStyle>
#include <QPalette>

class QPainterPath;

class SieFlyStyle : public QProxyStyle
{
	Q_OBJECT

public:
	SieFlyStyle();

	void polish(QPalette &palette) Q_DECL_OVERRIDE;
	void polish(QWidget *widget) Q_DECL_OVERRIDE;
	void unpolish(QWidget *widget) Q_DECL_OVERRIDE;

private:
	static void setTexture(QPalette &palette, QPalette::ColorRole role, const QPixmap &pixmap);
	static QPainterPath roundRectPath(const QRect &rect);
};
