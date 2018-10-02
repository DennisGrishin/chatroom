#include "clientw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientW w;
    w.show();

    return a.exec();
}
