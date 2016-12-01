#pragma once

#include <QDialog>
#include "ui_StyleDialog.h"

class StyleDialog : public QDialog, public Ui::StyleDialog
{
	Q_OBJECT

public:
	StyleDialog(QWidget *parent = Q_NULLPTR);
	~StyleDialog();
};
