#pragma once

#include <QtWidgets/QWidget>
#include <qstackedwidget.h>
#include <qeasingcurve.h>
#include <qpropertyanimation.h>
#include <qparallelanimationgroup.h>

class StackSlide : public QStackedWidget
{
	Q_OBJECT
		Q_PROPERTY(int menuPage READ menuPage WRITE setMenuPage)
		Q_PROPERTY(int speed READ speed WRITE setSpeed)
		Q_PROPERTY(enum QEasingCurve::Type animation READ animation WRITE setAnimation)
		//Q_PROPERTY(bool verticalMode READ verticalMode WRITE setVerticalMode)
		Q_PROPERTY(bool wrap READ wrap WRITE setWrap)

public:
    StackSlide(QWidget *parent = Q_NULLPTR);

	// This enumeration is used to define the animation direction
	enum t_direction {
		LEFT2RIGHT,
		RIGHT2LEFT,
		TOP2BOTTOM,
		BOTTOM2TOP,
		AUTOMATIC
	};

	int speed() const;
	enum QEasingCurve::Type animation() const;
	bool verticalMode() const;
	bool wrap() const;
	int menuPage() const;

	public slots:
	// Some basic settings API
	void setSpeed(int speed); // animation duration in milliseconds
	void setAnimation(enum QEasingCurve::Type animationtype); // check out the QEasingCurve documentation for different styles
	void setVerticalMode(bool vertical = true);
	void setWrap(bool wrap); // wrapping is related to slideInNext/Prev;it defines the behaviour when reaching last/first page
	void setMenuPage(int page);

	// The Animation / Page Change API
	void slideInNext();
	void slideInPrev();
	void slideInIdx(int idx, enum t_direction direction = AUTOMATIC);

signals:
	// this is used for internal purposes in the class engine
	void animationFinished(void);

	protected slots:
	// this is used for internal purposes in the class engine
	void animationDoneSlot(void);

protected:
	// this is used for internal purposes in the class engine
	void slideInWgt(QWidget *widget, enum t_direction direction = AUTOMATIC);

	int m_speed;
	enum QEasingCurve::Type m_animationtype;
	bool m_vertical;
	int m_now;
	int m_next;
	int m_menuPage;
	bool m_wrap;
	QPoint m_pnow;
	bool m_active;

	QList<QWidget*> blockedPageList;
};
