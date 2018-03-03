#include "widget.h"
#include <QApplication>
#include <QWidget>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QPalette p = w.palette();
    p.setColor(QPalette::Window, Qt::white);
    w.setPalette(p);
    w.setAutoFillBackground(true);
    w.showFullScreen();
    w.show();

    return a.exec();
}


