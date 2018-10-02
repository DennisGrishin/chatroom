#include "serverw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerW w;
    w.show();

    return a.exec();
}
