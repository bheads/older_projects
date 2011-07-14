#include <QtGui/QApplication>
#include "ulmmainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ulmMainWindow w;
    w.show();

    return a.exec();
}
