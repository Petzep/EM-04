#include "QtPieMenu.h"

QtPieMenu::QtPieMenu(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(tr("QtPieMenu"));
	resize(500, 500);
	m_ItemNumbers = 5;
	m_GradientRadius = 1.0; //unused
	m_SelectionInnerColor = Qt::red;
	m_SelectionOuterColor = Qt::blue;
	m_SelectionRadius = 1.0;
}

void QtPieMenu::paintEvent(QPaintEvent *)
{
	QPolygon itemShape;
	itemShape << QPoint(5, -5)
		<< QPoint(-5, -5)
		<< QPoint(-5, 5)
		<< QPoint(5, 5);

	QTransform selectionTrans;
	selectionTrans = selectionTrans.scale(1.0+(m_SelectionRadius*0.1), 1.0 + (m_SelectionRadius*0.1));
	QPolygon selectionBounding = itemShape.boundingRect();
	QPolygonF selectionShape = selectionTrans.map(selectionBounding);

	int side = qMin(width(), height());
	QTime time = QTime::currentTime();

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);

	/*selectionShape.translate(QPoint(-1, (-100 + 9)));
	QRadialGradient gradient(selectionShape.boundingRect().center(), selectionShape.boundingRect().width()); // diagonal gradient from top-left to bottom-right
	//selectionShape.translate(QPointF(-m_SelectionRadius*0.1, (-100+m_SelectionRadius-(0.1*m_SelectionRadius))));
	*/

	selectionShape.translate(QPoint(-1, (-100 + 9)));
	QRadialGradient gradient(selectionShape.boundingRect().center(), selectionShape.boundingRect().width()); // diagonal gradient from top-left to bottom-right
	gradient.setColorAt(0, m_SelectionInnerColor);
	gradient.setColorAt(1, m_SelectionOuterColor);
	painter.rotate((360.0 / m_ItemNumbers)*m_Selection);
	painter.fillRect(selectionShape.boundingRect(), gradient);
	painter.restore();

	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0,0,0));
	painter.save();

	itemShape.translate(QPoint(0, -90));
	for (int i = 0; i < m_ItemNumbers; ++i) {	
		painter.drawConvexPolygon(itemShape);
		painter.rotate(360.0/m_ItemNumbers);
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

void QtPieMenu::setSelectionInnerColor(const QColor & color)
{
	m_SelectionInnerColor = color;
	update();
}

void QtPieMenu::setSelectionOuterColor(const QColor & color)
{
	m_SelectionOuterColor = color;
	update();
}

void QtPieMenu::setSelection(int selection)
{
	m_Selection = selection;
	update();
}
