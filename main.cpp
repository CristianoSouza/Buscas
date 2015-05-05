#include <QApplication>
#include "interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface i;
    i.show();

    return a.exec();
}
