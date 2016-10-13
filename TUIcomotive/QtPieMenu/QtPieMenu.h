#pragma once

#include <QtWidgets/QWidget>
#include <Qtimer>
#include <QTime>
#include <Qpainter>

class QtPieMenu : public QWidget
{
    Q_OBJECT

	Q_PROPERTY(bool ToggleSecondHand READ readSecondHand WRITE setSecondHand)
	//Q_PROPERTY(QColor color READ color WRITE setColor)


public:
    QtPieMenu(QWidget *parent = Q_NULLPTR);
	bool readSecondHand();

public slots:
	void setSecondHand(bool toggle);
	void toggleSecondHand();

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	bool m_SecondHand;
};
