#include "TestDialog.h"

TestDialog::TestDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	this->showFullScreen();
}

TestDialog::~TestDialog()
{
}
