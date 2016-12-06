#include "MenuDialog.h"

MenuDialog::MenuDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	qtPieMenu_2->setFocus();
	debugCheckBox->setChecked(true);
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
		int cmd = ke->key();
		if(!stackSlide->inAnimation())
		{
			if (cmd >= Qt::Key_0 && cmd <= Qt::Key_9) //filter for num-keys
			{
				int value;
				int itemNumbers = qtPieMenu_2->itemNumbers();

				//Event handler for qtPieMenu
				if (qtPieMenu_2->hasFocus())
				{
					switch (cmd)
					{
					case Qt::Key_4:
					{
						value = qtPieMenu_2->selection() - 1;
						break;
					}
					case Qt::Key_6:
					{
						value = qtPieMenu_2->selection() + 1;
						break;
					}
					case Qt::Key_5:
					{
						qtPieMenu_2->select();

						break;
					}
					default:
						break;
					}

					//Only change if the value is changed
					if (cmd == Qt::Key_4 || cmd == Qt::Key_6)
					{
						if (value > itemNumbers - 1)
							value = (value) % itemNumbers;
						else if (value < 0)
							value = (value + itemNumbers) % itemNumbers;

						qtPieMenu_2->setSelection(value);
					}
				}
				//Dail event handler
				else if (volumeDial->hasFocus() || trebDial->hasFocus() || bassDial->hasFocus())
				{
					QDial* dial = (QDial*)focusWidget();
					if (dial->notchesVisible())
					{
						switch (cmd)
						{
						case Qt::Key_7:
						case Qt::Key_5:
							dial->setNotchesVisible(false);
							break;
						case Qt::Key_8:
						case Qt::Key_6:
						{
							dial->setValue(dial->value() + 1);
							break;
						}
						case Qt::Key_2:
						case Qt::Key_4:
						{
							dial->setValue(dial->value() - 1);
							break;
						}
						default:
							break;
						}
					}
					else
					{
						switch (cmd)
						{
						case Qt::Key_5:
							dial->setNotchesVisible(true);
							break;
						case Qt::Key_8:
						case Qt::Key_4:
						{
							focusPreviousChild();
							break;
						}
						case Qt::Key_2:
						case Qt::Key_6:
						{
							focusNextChild();
							break;
						}
						case Qt::Key_7:
							stackSlide->slideHome();
							qtPieMenu_2->setFocus();
							break;
						default:
							break;
						}
					}
				}
				else
				{
					switch (cmd)
					{
					case Qt::Key_8:
					case Qt::Key_4:
					{
						focusPreviousChild();
						break;
					}
					case Qt::Key_2:
					case Qt::Key_6:
					{
						focusNextChild();
						break;
					}
					default:
						break;
					}
				}
			}
		}

		//Always return to home and set focus
		if (ke->key() == Qt::Key_0)
		{
			stackSlide->slideHome();
			qtPieMenu_2->setFocus();
		}
		return true;
	}

	return QWidget::event(event);
}
