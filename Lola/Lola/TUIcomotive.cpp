#include "TUIcomotive.h"

TUIcomotive::TUIcomotive(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//Add list entries
	addListItem(QString("Press MenuButton"), QString("Hoi"));
	addListItem(QString("to start"), QString("Doei"));
	addListItem(QString("the User Interface Protoype"), QString("Groetjes Nephtaly"));
	
	//Make the button stylish-green
	ui.menuButton->setStyleSheet("QPushButton {"
									"background-color: green;"
									"border-style: outset;"
									"border-radius: 10px;"
									"border-color: beige;"   
									"font: italic 10px;"
									"min-width: 7em;"
									"padding: 6px;}"
								"QPushButton:pressed {"
									"background-color: black;"
									"color: green;"
									"border-style: inset;}");

	ui.addButton->setFocus();
}

void TUIcomotive::on_addButton_clicked(void)
{
	AddDialog dialog(this);

	if (dialog.exec()) 
		addListItem(dialog.nameEdit->text(), dialog.emailEdit->text());
}

void TUIcomotive::on_testButton_clicked(void)
{
	TestDialog dialog(this);
	dialog.exec();
}

void TUIcomotive::on_menuButton_clicked(void)
{
	MenuDialog dialog(this);
	dialog.exec();
}

void TUIcomotive::on_styleButton_clicked(void)
{
	StyleDialog dialog(this);
	dialog.exec();
}

void TUIcomotive::on_canButton_clicked(void)
{
	CanDialog dialog(this);
	dialog.exec();
}

void TUIcomotive::on_dashboardButton_clicked(void)
{
	this->hide();
	QQmlApplicationEngine* engine = new QQmlApplicationEngine;
	engine->load(QUrl("qrc:/qml/dashboard.qml"));

	if(engine->rootObjects().isEmpty())
		return;
	QObject *rootObject = engine->rootObjects().first();
	QObject *qmlObject = rootObject->findChild<QObject*>("valueSource");
	
	qmlObject->setProperty("temperature", 0.8);
}

void TUIcomotive::on_closeButton_clicked(void)
{
	QApplication::quit();
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

void TUIcomotive::addListItem(QString name, QString email)
{
	if (!name.isEmpty() && !email.isEmpty()) {
		QListWidgetItem *item = new QListWidgetItem(name, ui.bangaList);
		item->setData(Qt::UserRole, email);
		ui.bangaList->setCurrentItem(item);
	}
}

bool TUIcomotive::event(QEvent *event)
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent *ke = static_cast<QKeyEvent *>(event);
		int cmd = ke->key();
		if(cmd >= Qt::Key_0 && cmd <= Qt::Key_9) //filter for numeric-keys
		{
			//Button event handler
			if(QString(focusWidget()->metaObject()->className()).contains(QString("Button")))
			{
				QPushButton* button = (QPushButton*)focusWidget();
				switch(cmd)
				{
					case Qt::Key_4:
					{
						focusPreviousChild();
						break;
					}
					case Qt::Key_6:
					{
						focusNextChild();
						break;
					}
					case Qt::Key_5:
					{
						button->click();
						break;
					}
					default:
						break;
				}
			}
			else
				focusPreviousChild();
		}
			
		//Always return to home and set focus
		if(ke->key() == Qt::Key_0)
		{
			QKeyEvent * eve1 = new QKeyEvent(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
			QKeyEvent * eve2 = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Tab, Qt::NoModifier);

			ui.addButton->setFocus();

			qApp->postEvent((QObject*)ui.addButton, (QEvent *)eve1);
			qApp->postEvent((QObject*)ui.addButton, (QEvent *)eve2);

			focusPreviousChild();

		}
		return true;

		}
	return QWidget::event(event);
}
