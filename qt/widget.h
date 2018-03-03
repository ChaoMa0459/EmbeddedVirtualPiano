#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QTextStream>
#include <QPalette>
#include <QtCore>
#include <QDebug>

class Widget : public QWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = 0);
    ~Widget();
    QTimer *timer;
    QTimer *timer1;
    int i,saveacc,savecombo;
    int i0,i1,t1,t2,t3,t4,t5,t6,t7,timecount,combo,gamecount,gameright,rightflag;
public slots:
    void MySlot();
    void paintEvent(QPaintEvent *);
private:
    QLabel * qlabel;
};

#endif // WIDGET_H
