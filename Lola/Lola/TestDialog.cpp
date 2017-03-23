#include "TestDialog.h"

TestDialog::TestDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	this->setFixedSize(QSize(1280, 720));
}

TestDialog::~TestDialog()
{
}

bool TestDialog::event(QEvent *event)
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		int cmd = ke->key();
		switch(cmd)
		{
			case Qt::Key_4:
				stackSlide->slideInPrev();
				break;
			case Qt::Key_6:
				stackSlide->slideInNext();
				break;
			case Qt::Key_5:
				stackSlide->slideHome();
				break;
			default:
				break;
		}
		return true;
	}

	return QWidget::event(event);
}
