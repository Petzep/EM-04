#pragma once

#include <QtWidgets/QWidget>
#include <qpainter.h>

class QtPieMenu : public QWidget
{
	Q_OBJECT

		Q_PROPERTY(int itemNumbers READ itemNumbers WRITE setItemNumbers)
		Q_PROPERTY(double selectionRadius READ selectionRadius WRITE setSelectionRadius)
		Q_PROPERTY(double gradientRadius READ gradientRadius WRITE setGradientRadius)
		Q_PROPERTY(QColor menuColor READ menuColor WRITE setMenuColor)
		Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor)
		Q_PROPERTY(QColor selectionInnerColor READ selectionInnerColor WRITE setSelectionInnerColor)
		Q_PROPERTY(QColor selectionOuterColor READ selectionOuterColor WRITE setSelectionOuterColor)
		Q_PROPERTY(int selection READ selection WRITE setSelection)
		Q_PROPERTY(bool danielArrow READ danielArrow WRITE setDanielArrow)

public:
	QtPieMenu(QWidget *parent = Q_NULLPTR);
	int itemNumbers() const;
	double selectionRadius() const;
	double gradientRadius() const;
	QColor menuColor() const;
	QColor selectionColor() const;
	QColor selectionInnerColor() const;
	QColor selectionOuterColor() const;
	int selection() const;
	bool danielArrow() const;

	public slots:
	void setItemNumbers(int number);
	void setSelection(int selection);
	void setSelectionRadius(double radius);
	void setGradientRadius(double radius);
	void setMenuColor(const QColor& color);
	void setSelectionColor(const QColor& color);
	void setSelectionInnerColor(const QColor& color);
	void setSelectionOuterColor(const QColor& color);
	void setDanielArrow(bool toggle);

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	int m_ItemNumbers;
	int m_Selection;
	bool m_DanielArrow;
	double m_SelectionRadius;
	double m_GradientRadius;
	QColor m_SelectionInnerColor;
	QColor m_SelectionOuterColor;
	QColor m_SelectionColor;
	QColor m_MenuColor;
};
