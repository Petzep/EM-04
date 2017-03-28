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
	m_SelectionOuterColor = palette().color(QPalette::Highlight);
	m_SelectionInnerColor = palette().color(QPalette::Highlight).lighter();
	m_SelectionOuterColor.setAlpha(128);
	m_SelectionInnerColor.setAlpha(200);
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

	//make the coordinate system from -100 to 100 with origin in the middle
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);

	//Paint selector
	selectionShape.translate(QPointF(-0.5, (qreal)-100 + itemShape.boundingRect().width() - 0.5));
	QRadialGradient gradient(selectionShape.boundingRect().center(), selectionShape.boundingRect().width());
	gradient.setColorAt(0, m_SelectionInnerColor);
	gradient.setColorAt(1, m_SelectionOuterColor);
	painter.rotate((360.0 / m_ItemNumbers)*(m_Selection-2));
	painter.fillRect(selectionShape.boundingRect(), gradient);

	painter.setPen(Qt::NoPen);
	painter.setBrush(m_MenuColor);
	painter.save();

	//Paint items
	itemShape.translate(QPoint(0, (qreal)-100 + itemShape.boundingRect().width()));
	painter.rotate((360.0 / m_ItemNumbers)*2); //rotate in such a way that the rotation is clockwise starting from the bottom
	for (int i = 0; i < m_ItemNumbers; ++i) {
		if (m_Icons.at((i + m_Selection) % m_ItemNumbers))
			painter.drawPixmap(itemShape.boundingRect(), m_Icons.at((i + m_Selection) % m_ItemNumbers)->pixmap(QSize(128, 128)).transformed(QTransform().rotate(-360/(i % m_ItemNumbers))));
		else
			painter.drawConvexPolygon(itemShape);
		painter.rotate(360.0 / m_ItemNumbers);
	}
	painter.restore();
	painter.setBrush(m_SelectionColor);


	//Paint DanielArrow
	if (m_DanielArrow)
	{
		painter.setBrush(QColor(Qt::green));
		painter.drawConvexPolygon(itemShape);
		painter.drawConvexPolygon(danielShape);
	}
}

void QtPieMenu::loadIcons()
{
	QFile inputFile(":menuIcons/Icons/iconLabel.txt");
	if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&inputFile);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			m_IconNames.push_back(line);

		}
		inputFile.close();
	}

	for (int i = 0; i < m_ItemNumbers; i++)
	{
		QString filename = tr(":menuIcons/Icons/icon (%1).png").arg(i+1);
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
	QString name;
	if (selection > m_IconNames.count() - 1)
		emit itemName("NaN");
	else
		emit itemName(m_IconNames.at(selection)); 
	update();
}