#include "ChartUI.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":images/shut_down_normal.png"));
    chartUI w;
    w.show();
    return a.exec();
}
