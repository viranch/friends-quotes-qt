#include <QApplication>
#include "object.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Object obj;

    return a.exec();
}

