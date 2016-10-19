#pragma once

#include <QtWidgets/QWidget>
#include <Qtimer>
#include <QTime>
#include <Qpainter>

class QtPieMenu : public QWidget
{
    Q_OBJECT

	Q_PROPERTY(int itemNumbers READ itemNumbers WRITE setItemNumbers)
	Q_PROPERTY(double selectionRadius READ selectionRadius WRITE setSelectionRadius)
	Q_PROPERTY(double gradientRadius READ gradientRadius WRITE setGradientRadius)
	Q_PROPERTY(QColor selectionInnerColor READ selectionInnerColor WRITE setSelectionInnerColor)
	Q_PROPERTY(QColor selectionOuterColor READ selectionOuterColor WRITE setSelectionOuterColor)
	Q_PROPERTY(int selection READ selection WRITE setSelection)

public:
    QtPieMenu(QWidget *parent = Q_NULLPTR);
	int itemNumbers() const;
	double selectionRadius() const;
	double gradientRadius() const;
	QColor selectionInnerColor() const;
	QColor selectionOuterColor() const;
	int selection() const;

public slots:
	void setItemNumbers(int number);
	void setSelectionRadius(double radius);
	void setGradientRadius(double radius);
	void setSelectionInnerColor(const QColor& color);
	void setSelectionOuterColor(const QColor& color);
	void setSelection(int selection);

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	int m_ItemNumbers;
	double m_SelectionRadius;
	double m_GradientRadius;
	QColor m_SelectionInnerColor;
	QColor m_SelectionOuterColor;
	int m_Selection;
};
