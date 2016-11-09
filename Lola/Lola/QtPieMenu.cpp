#include "QtPieMenu.h"

QtPieMenu::QtPieMenu(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(tr("QtPieMenu"));
	resize(500, 500);
	m_ItemNumbers = 5;
	m_Selection = 0;
	m_SelectionRadius = 5.0;
	m_GradientRadius = 2.0;
	m_MenuColor = Qt::black;
	m_SelectionInnerColor = Qt::white;
	m_SelectionOuterColor = Qt::green;
	m_SelectionColor = QColor(144, 0, 0);
	m_DanielArrow = false;
	loadIcons();
}

void QtPieMenu::paintEvent(QPaintEvent *)
{
	QPolygon itemShape;
	itemShape << QPoint(m_SelectionRadius, -m_SelectionRadius)
		<< QPoint(-m_SelectionRadius, -m_SelectionRadius)
		<< QPoint(-m_SelectionRadius, m_SelectionRadius)
		<< QPoint(m_SelectionRadius, m_SelectionRadius);

	QPolygon danielShape;
	danielShape << QPoint(0, -15)
		<< QPoint(20, -5)
		<< QPoint(10, -5)
		<< QPoint(10, 15)
		<< QPoint(-10, 15)
		<< QPoint(-10, -5)
		<< QPoint(-20, -5);

	QRectF selectionBoundingrect = itemShape.boundingRect();
	selectionBoundingrect.adjust(-m_GradientRadius, -m_GradientRadius, m_GradientRadius, m_GradientRadius);
	QPolygonF selectionShape = selectionBoundingrect;

	int side = qMin(width(), height());

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);

	/*selectionShape.translate(QPoint(-1, (-100 + 9)));
	QRadialGradient gradient(selectionShape.boundingRect().center(), selectionShape.boundingRect().width()); // diagonal gradient from top-left to bottom-right
	//selectionShape.translate(QPointF(-m_SelectionRadius*0.1, (-100+m_SelectionRadius-(0.1*m_SelectionRadius))));
	*/

	selectionShape.translate(QPointF(-0.5, (qreal)-100 + itemShape.boundingRect().width() - 0.5));
	QRadialGradient gradient(selectionShape.boundingRect().center(), selectionShape.boundingRect().width()); // diagonal gradient from center to edge
	gradient.setColorAt(0, m_SelectionInnerColor);
	gradient.setColorAt(1, m_SelectionOuterColor);
	painter.rotate((-360.0 / m_ItemNumbers)*m_Selection);
	painter.fillRect(selectionShape.boundingRect(), gradient);

	painter.setPen(Qt::NoPen);
	painter.setBrush(m_MenuColor);
	painter.save();

	itemShape.translate(QPoint(0, (qreal)-100 + itemShape.boundingRect().width()));
	for (int i = 0; i < m_ItemNumbers; ++i) {
		if (m_Icons.at((i + m_Selection) % m_ItemNumbers))
			//m_Icons.at((i + m_Selection) % m_ItemNumbers)->paint(&painter, selectionShape.toPolygon().boundingRect());
			painter.drawPixmap(itemShape.boundingRect(), m_Icons.at((i + m_Selection) % m_ItemNumbers)->pixmap(QSize(128, 128)));
		else
			painter.drawConvexPolygon(itemShape);
		painter.rotate(-360.0 / m_ItemNumbers);
	}
	painter.restore();
	painter.setBrush(m_SelectionColor);
	//painter.drawConvexPolygon(itemShape);

	if (m_DanielArrow)
	{
		painter.setBrush(QColor(Qt::green));
		painter.drawConvexPolygon(itemShape);
		painter.drawConvexPolygon(danielShape);
	}
}

void QtPieMenu::loadIcons()
{
	for (int i = 0; i < m_ItemNumbers; i++)
	{
		QString filename = tr("Icons/icon (%1).png").arg(i+1);
		QIcon* icon = new QIcon(filename);
		if (icon->pixmap(QSize(10, 10)).isNull()) //small trick to test if the icon has loaded
		{
			delete icon;
			icon = nullptr;
		}
		m_Icons.push_back(icon);
	}
}

void QtPieMenu::reloadIcons()
{
	for(QIcon* icon : m_Icons)
		delete icon;
	
	m_Icons.clear();
	loadIcons();
}

int QtPieMenu::itemNumbers() const
{
	return m_ItemNumbers;
}

double QtPieMenu::selectionRadius() const
{
	return m_SelectionRadius;
}

double QtPieMenu::gradientRadius() const
{
	return m_GradientRadius;
}

QColor QtPieMenu::selectionColor() const
{
	return m_SelectionColor;
}

QColor QtPieMenu::menuColor() const
{
	return m_MenuColor;
}

QColor QtPieMenu::selectionInnerColor() const
{
	return m_SelectionInnerColor;
}

QColor QtPieMenu::selectionOuterColor() const
{
	return m_SelectionOuterColor;
}

int QtPieMenu::selection() const
{
	return m_Selection;
}

bool QtPieMenu::danielArrow() const
{
	return m_DanielArrow;
}

void QtPieMenu::setItemNumbers(int number)
{
	m_ItemNumbers = number;
	reloadIcons();
	update();
}

void QtPieMenu::setSelectionRadius(double radius)
{
	m_SelectionRadius = radius;
	reloadIcons();
	update();
}

void QtPieMenu::setGradientRadius(double radius)
{
	m_GradientRadius = radius;
	update();
}

void QtPieMenu::setSelectionOuterColor(const QColor & color)
{
	m_SelectionOuterColor = color;
	update();
}

void QtPieMenu::setDanielArrow(bool toggle)
{
	m_DanielArrow = toggle;
	update();
}

void QtPieMenu::select()
{
	emit itemSelect(m_Selection);
}

void QtPieMenu::setSelectionInnerColor(const QColor & color)
{
	m_SelectionInnerColor = color;
	update();
}

void QtPieMenu::setSelectionColor(const QColor & color)
{
	m_SelectionColor = color;
	update();
}

void QtPieMenu::setMenuColor(const QColor & color)
{
	m_MenuColor = color;
	update();
}

void QtPieMenu::setSelection(int selection)
{
	m_Selection = selection;
	update();
}

/* 
QIcon("icons/drag.png")

QIcon::State state = QIcon::Off;
QIcon::Mode mode = QIcon::Normal;
if (guessModeStateAct->isChecked())
{
	if (imageName.contains(QLatin1String("_act"), Qt::CaseInsensitive))
		mode = QIcon::Active;	
	else if (imageName.contains(QLatin1String("_dis"), Qt::CaseInsensitive))
		mode = QIcon::Disabled;
	else if (imageName.contains(QLatin1String("_sel"), Qt::CaseInsensitive))
		mode = QIcon::Selected;

	if (imageName.contains(QLatin1String("_on"), Qt::CaseInsensitive))
		state = QIcon::On;
}
*/