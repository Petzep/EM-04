#include "MenuDialog.h"

MenuDialog::MenuDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
}

MenuDialog::~MenuDialog()
{
}

void MenuDialog::on_controlDial_valueChanged(int value)
{
	this->qtPieMenu_2->setSelection(value - 2);
}

bool MenuDialog::event(QEvent *event)
{
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		if (ke->key() == Qt::Key_4 || ke->key() == Qt::Key_6)
		{
			int value;
			if(ke->key() == Qt::Key_4)
				value = qtPieMenu_2->selection() + 1;
			else if(ke->key() == Qt::Key_6)
				value = qtPieMenu_2->selection() - 1;

			int itemNumbers = qtPieMenu_2->itemNumbers();
			
			if (value > itemNumbers - 1) {
				value = (value) % itemNumbers;
			}
			else if (value  < 0) {
				value = (value + itemNumbers) % itemNumbers;
			}

			qtPieMenu_2->setSelection(value);
			return true;
		}
		if (ke->key() == Qt::Key_5)
		{
			qtPieMenu_2->select();
		}
		if (ke->key() == Qt::Key_0)
		{
			stackSlide->slideHome();
		}
	}

	return QWidget::event(event);
}
