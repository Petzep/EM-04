#include "TUIcomotive.h"

TUIcomotive::TUIcomotive(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void TUIcomotive::on_addButton_clicked(void)
{
	AddDialog dialog(this);

	if (dialog.exec()) {
		QString name = dialog.nameEdit->text();
		QString email = dialog.emailEdit->text();

		if (!name.isEmpty() && !email.isEmpty()) {
			QListWidgetItem *item = new QListWidgetItem(name, ui.bangaList);
			item->setData(Qt::UserRole, email);
			ui.bangaList->setCurrentItem(item);
		}
	}
}

void TUIcomotive::on_testButton_clicked(void)
{
	TestDialog dialog(this);
	dialog.exec();
}

void TUIcomotive::on_bangaList_currentItemChanged()
{
	QListWidgetItem *curItem = ui.bangaList->currentItem();

	if (curItem) {
		ui.nameLabel->setText("Name: " + curItem->text());
		ui.emailLabel->setText("Email: " +
			curItem->data(Qt::UserRole).toString());
	}
	else {
		ui.nameLabel->setText("<No item selected>");
		ui.emailLabel->clear();
	}
}

void TUIcomotive::on_deleteButton_clicked()
{
	QListWidgetItem *curItem = ui.bangaList->currentItem();

	if (curItem)
	{
		int row = ui.bangaList->row(curItem);
		ui.bangaList->takeItem(row);
		delete curItem;

		if (ui.bangaList->count() > 0)
			ui.bangaList->setCurrentRow(0);
		else
			on_bangaList_currentItemChanged();
	}
}
