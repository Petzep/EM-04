#include "QtPieMenu.h"

QtPieMenu::QtPieMenu(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(tr("QtPieMenu"));
	resize(500, 500);
	m_ItemNumbers = 5;
	m_SelectionRadius = 5.0;
	m_GradientRadius = 2.0;
	m_MenuColor = Qt::black;
	m_SelectionInnerColor = Qt::white;
	m_SelectionOuterColor = Qt::green;
	m_SelectionColor = QColor(144, 0, 0);
	m_DanielArrow = false;
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
	QRadialGradient gradient(selectionShape.boundingRect().center(), selectionShape.boundingRect().width()); // diagonal gradient from top-left to bottom-right
	gradient.setColorAt(0, m_SelectionInnerColor);
	gradient.setColorAt(1, m_SelectionOuterColor);
	painter.rotate((360.0 / m_ItemNumbers)*m_Selection);
	painter.fillRect(selectionShape.boundingRect(), gradient);
	painter.restore();

	painter.setPen(Qt::NoPen);
	painter.setBrush(m_MenuColor);
	painter.save();

	itemShape.translate(QPoint(0, (qreal)-100 + itemShape.boundingRect().width()));
	for (int i = 0; i < m_ItemNumbers; ++i) {
		painter.drawConvexPolygon(itemShape);
		painter.rotate(360.0 / m_ItemNumbers);
	}
	painter.restore();
	painter.setBrush(m_SelectionColor);
	painter.drawConvexPolygon(itemShape);

	if (m_DanielArrow)
	{
		painter.setBrush(QColor(Qt::green));
		painter.drawConvexPolygon(itemShape);
		painter.drawConvexPolygon(danielShape);
	}

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
	update();
}

void QtPieMenu::setSelectionRadius(double radius)
{
	m_SelectionRadius = radius;
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
