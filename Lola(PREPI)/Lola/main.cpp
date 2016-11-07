#include "TUIcomotive.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TUIcomotive w;
    w.show();
    return a.exec();
}
