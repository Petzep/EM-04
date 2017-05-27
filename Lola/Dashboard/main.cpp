#include <QApplication>
#include <QFontDatabase>
#include <QQmlApplicationEngine>

#include "Dashboard.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFontDatabase::addApplicationFont(":/fonts/MsSansSerif.ttf");
	app.setFont(QFont("Microsoft Sans Serif", 8));

	qmlRegisterType<Dashboard>("org.TUecomotive.Dashboard", 1, 0, "Dashboard");

	QQmlApplicationEngine* engine = new QQmlApplicationEngine;

	engine->load(QUrl("qrc:/qml/dashboard.qml"));

	if(engine->rootObjects().isEmpty())
		return  -1;
	
	QObject *rootObject = engine->rootObjects().first();
	QObject *qmlObject = rootObject->findChild<QObject*>("valueSource");

	Dashboard *dashboard = new Dashboard();
	dashboard->setRoot(rootObject);
	dashboard->initCan(0);

	return app.exec();
}
