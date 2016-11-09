#include "StackSlide.h"

StackSlide::StackSlide(QWidget *parent)
    : QStackedWidget(parent)
{
	// Now, initialize some private variables with default values
	m_vertical = false;
	// setVerticalMode(true);
	m_speed = 600;
	m_animationtype = QEasingCurve::OutCubic; // check out the QEasingCurve documentation for different styles
	m_now = 0;
	m_next = 0;
	m_wrap = false;
	m_pnow = QPoint(0, 0);
	m_active = false;
	m_menuPage = 1;
}

int StackSlide::speed() const
{
	return m_speed;
}

enum QEasingCurve::Type StackSlide::animation() const 
{
	return m_animationtype;
}

bool StackSlide::verticalMode() const
{
	return m_vertical;
}

bool StackSlide::wrap() const
{
	return m_wrap;
}

int StackSlide::menuPage() const
{
	return m_menuPage;
}

void StackSlide::setSpeed(int speed)
{
	m_speed = speed;
}


void StackSlide::setAnimation(QEasingCurve::Type animationtype)
{
	m_animationtype = animationtype;
}

void StackSlide::setVerticalMode(bool vertical)
{
	m_vertical = vertical;
}

void StackSlide::setWrap(bool wrap)
{
	m_wrap = wrap;
}

void StackSlide::setMenuPage(int page)
{
	m_menuPage = page;
}

void StackSlide::slideInNext()
{
	int now = currentIndex();
	if (m_wrap || (now < count() - 1))
		// count is inherit from QStackedWidget
		slideInIdx(now + 1);
}

void StackSlide::slideInPrev()
{
	int now = currentIndex();
	if (m_wrap || (now > 0))
		slideInIdx(now - 1);
}

void StackSlide::slideInIdx(int idx, t_direction direction)
{
	// int idx, t_direction direction=AUTOMATIC
	if (idx > count() - 1) {
		direction = m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
		idx = (idx) % count();
	}
	else if (idx < 0) {
		direction = m_vertical ? BOTTOM2TOP : LEFT2RIGHT;
		idx = (idx + count()) % count();
	}
	slideInWgt(widget(idx), direction);
	// widget() is a function inherited from QStackedWidget
}

void StackSlide::slideHome()
{
	slideInIdx(m_menuPage);
}

void StackSlide::animationDoneSlot(void)
{
	// when ready, call the QStackedWidget slot setCurrentIndex(int)
	setCurrentIndex(m_next); // this function is inherited from QStackedWidget
							 // then hide the outshifted widget now, and (may be done already implicitely by QStackedWidget)
	if (currentIndex() != m_menuPage)
		widget(m_now)->show();
	else
		widget(m_now)->hide();

	// then set the position of the outshifted widget now back to its original
	//widget(m_now)->move(m_pnow);
	// so that the application could also still call the QStackedWidget original functions/slots for changings
	// widget(m_now)->update();
	// setCurrentIndex(m_next); // this function is inherit from QStackedWidget
	m_active = false;
	emit animationFinished();
}

void StackSlide::slideInWgt(QWidget * newwidget, t_direction direction)
{
	if (m_active) {
		return; // at the moment, do not allow re-entrance before an animation is completed.
				// other possibility may be to finish the previous animation abrupt, or
				// to revert the previous animation with a counter animation, before going ahead
				// or to revert the previous animation abrupt
				// and all those only, if the newwidget is not the same as that of the previous running animation.
	}
	else m_active = true;

	enum t_direction directionhint;
	int now = currentIndex(); // currentIndex() is a function inherited from QStackedWidget
	int next = indexOf(newwidget);
	if (next == m_menuPage || now == m_menuPage)
		setVerticalMode(false);
	else
		setVerticalMode(true);

	if (now == next) {
		m_active = false;
		return;
	}
	else if (now < next) {
		directionhint = m_vertical ? TOP2BOTTOM : RIGHT2LEFT;
	}
	else {
		directionhint = m_vertical ? BOTTOM2TOP : LEFT2RIGHT;
	}
	if (direction == AUTOMATIC) {
		direction = directionhint;
	}
	// NOW....
	// calculate the shifts

	int offsetx = frameRect().width(); // inherited from mother
	int offsety = frameRect().height(); // inherited from mother

										// the following is important, to ensure that the new widget
										// has correct geometry information when sliding in first time
	widget(next)->setGeometry(0, 0, offsetx, offsety);

	if (direction == BOTTOM2TOP) {
		offsetx = 0;
		offsety = -offsety;
	}
	else if (direction == TOP2BOTTOM) {
		offsetx = 0;
		offsety = offsety;
	}
	else if (direction == RIGHT2LEFT) {
		offsetx = -offsetx;
		offsety = 0;
	}
	else if (direction == LEFT2RIGHT) {
		offsetx = offsetx;
		offsety = 0;
	}
	// re-position the next widget outside/aside of the display area
	QPoint pnext = widget(next)->pos();
	QPoint pnow = widget(now)->pos();
	m_pnow = pnow;

	widget(next)->move(pnext.x() - offsetx, pnext.y() - offsety);
	// make it visible/show
	widget(next)->show();
	widget(next)->raise();

	// animate both, the now and next widget to the side, using animation framework
	QPropertyAnimation *animnow = new QPropertyAnimation(widget(now), "pos");
	animnow->setDuration(m_speed);
	animnow->setEasingCurve(m_animationtype);
	animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
	if(now == m_menuPage)
		animnow->setEndValue(QPoint(offsetx*0.5 + pnow.x(), offsety + pnow.y()));
	else
		animnow->setEndValue(QPoint(offsetx + pnow.x(), offsety + pnow.y()));

	QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
	animnext->setDuration(m_speed);
	animnext->setEasingCurve(m_animationtype);
	if(next == m_menuPage)
		animnext->setStartValue(QPoint(-offsetx*0.5 + pnext.x(), offsety + pnext.y()));
	else
		animnext->setStartValue(QPoint(-offsetx + pnext.x(), -offsety + pnext.y()));
	animnext->setEndValue(QPoint(pnext.x(), pnext.y()));

	QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

	animgroup->addAnimation(animnow);
	animgroup->addAnimation(animnext);

	QObject::connect(animgroup, SIGNAL(finished()), this, SLOT(animationDoneSlot()));
	m_next = next;
	m_now = now;
	m_active = true;
	animgroup->start();

	// note; the rest is done via a connect from the animation ready;
	// animation->finished() provides a signal when animation is done;
	// so we connect this to some post processing slot,
	// that we implement here below in animationDoneSlot.
}