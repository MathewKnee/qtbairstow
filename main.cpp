#include "mainwindow.h"

#include <QApplication>
#include <bairstowMethod.h>
#include <Interval.h>

int main(int argc, char *argv[])
{
    interval_arithmetic::Interval<long double> test_int;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
