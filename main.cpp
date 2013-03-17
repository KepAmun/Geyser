#include <QtGui/QApplication>
#include "GeyserWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GeyserWindow w;
    w.show();

    return a.exec();
}
