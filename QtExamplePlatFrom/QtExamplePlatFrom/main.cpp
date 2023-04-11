#include "QtExamplePlatFrom.h"
#include <QGuiApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QtExamplePlatFrom w;
    w.show();

    return a.exec();
}
