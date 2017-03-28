#include "TUIcomotive.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	
	QFontDatabase::addApplicationFont(":/fonts/MsSansSerif.ttf");
	app.setFont(QFont("Microsoft Sans Serif", 8));

    TUIcomotive window;
    window.show();
    return app.exec();
}
