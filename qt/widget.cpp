#include "widget.h"
#include <fstream>
#include <iostream>
#include <string>
#include <QDebug>
#include <QFont>
#include <QPainter>


using namespace std;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    i=0;
    timecount=0;
    t1=0;
    t2=0;
    t3=0;
    t4=0;
    t5=0;
    combo=0;
    gamecount=0;
    gameright=0;
    i0=3;
    i1=1;
    i=31;
    rightflag=0;
    timer = new QTimer(this);
    qlabel = new QLabel(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot()));
    timer -> start(100);
//Set the text every 0.1s
    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(update()));
    timer1 -> start(100);
//Update all the pattern every 0.1s

}
void Widget::MySlot()
{
   
QFile file("/dev/mygpio");


    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString string = in.readLine();
    i=string.toInt();
//Read from mygpio and turn it to number
    if(gamecount>0){
        saveacc=gameright/gamecount;
    }
//If game start, calculate accuracy
    if (i0<9){
        QString line1="Ode To Joy";
        QString line2;
        QString line3;
        if (gamecount>0){
            line2=QString ("\n\nAccuracy: %1").arg(gameright/gamecount);
            line1.append(line2);
        }
        qlabel->setText(line1);
        QFont f("MS Shell Dlg 2",15);
        qlabel->setFont(f);
        qlabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        qlabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        qlabel->setFixedSize(500,300);
        qlabel->show();
    }
//In game mode, show the anme of the song and the accuracy
    if (i0==8){
         QString finishline;
         QString finishline1;
         finishline=QString ("<h2><i><font color=blue>Finish!</font></i></h2>\n<h2><i><font color=blue>Accuracy: %1% </font></i></h2>").arg(saveacc);
         if(saveacc>=95){
             finishline1="\n<h2><i><font color=blue>Prefect!!</font></i></h2>";
             finishline.append(finishline1);
         }
         if((saveacc<95)&&(saveacc>=80)){
             finishline1="\n<h2><i><font color=blue>Great!!</font></i></h2>";
             finishline.append(finishline1);
         }
         if((saveacc<80)&&(saveacc>=60)){
             finishline1="\n<h2><i><font color=blue>Good</font></i></h2>";
             finishline.append(finishline1);
         }
         if(saveacc<60){
             finishline1="\n<h2><i><font color=blue>You need more practice</font></i></h2>";
             finishline.append(finishline1);
         }
         qlabel->setText(finishline);
         QFont f("MS Shell Dlg 2",10);
         qlabel->setFont(f);
         qlabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
         qlabel->setAlignment(Qt::AlignTop);
         qlabel->setFixedSize(500,300);
         qlabel->show();
         gamecount=0;
         gameright=0;
    }
//When game mode finishes, show "Finish", accuracy and comment.
    if ((i0==9)&&(i1<9)){
        QString noline;
        noline=QString ("Play mode");
        qlabel->setText(noline);
        //QFont f("Arial",15,QFont::Bold);
	QFont f("MS Shell Dlg 2",15);
        qlabel->setFont(f);
        qlabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        qlabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        qlabel->setFixedSize(500,300);
        qlabel->show();
    }
//In play mode, show the text "Play mode"
}


void Widget::paintEvent(QPaintEvent *)
{
    i0=i/10;
    i1=i-i0*10;
//Seperate the two number
    if(i0==9){
        gamecount=0;
        gameright=0;
//In play mode, set the parameters of game as 0.
      if(i1==1){
        QPainter painter(this);
        QPen pen;
        pen.setColor(QColor(0,0,0));
        QBrush brush(QColor(150,150,150,255));
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawRect(100,100,60,200);
      }else{
          QPainter painter(this);
          QPen pen;
          pen.setColor(QColor(0,0,0));
          QBrush brush(QColor(255,255,255,255));
          painter.setPen(pen);
          painter.setBrush(brush);
          painter.drawRect(100,100,60,200);
      }
      if(i1==2){
        QPainter painter2(this);
        QPen pen2;
        pen2.setColor(QColor(0,0,0));
        QBrush brush2(QColor(150,150,150,255));
        painter2.setPen(pen2);
        painter2.setBrush(brush2);
        painter2.drawRect(160,100,60,200);
      }else{
          QPainter painter2(this);
          QPen pen2;
          pen2.setColor(QColor(0,0,0));
          QBrush brush2(QColor(255,255,255,255));
          painter2.setPen(pen2);
          painter2.setBrush(brush2);
          painter2.drawRect(160,100,60,200);
      }
      if(i1==3){
        QPainter painter3(this);
        QPen pen3;
        pen3.setColor(QColor(0,0,0));
        QBrush brush3(QColor(150,150,150,255));
        painter3.setPen(pen3);
        painter3.setBrush(brush3);
        painter3.drawRect(220,100,60,200);
      }else{
          QPainter painter3(this);
          QPen pen3;
          pen3.setColor(QColor(0,0,0));
          QBrush brush3(QColor(255,255,255,255));
          painter3.setPen(pen3);
          painter3.setBrush(brush3);
          painter3.drawRect(220,100,60,200);
      }if(i1==4){
          QPainter painter4(this);
          QPen pen4;
          pen4.setColor(QColor(0,0,0));
          QBrush brush4(QColor(150,150,150,255));
          painter4.setPen(pen4);
          painter4.setBrush(brush4);
          painter4.drawRect(280,100,60,200);
        }else{
            QPainter painter4(this);
            QPen pen4;
            pen4.setColor(QColor(0,0,0));
            QBrush brush4(QColor(255,255,255,255));
            painter4.setPen(pen4);
            painter4.setBrush(brush4);
            painter4.drawRect(280,100,60,200);
        }
      if(i1==5){
        QPainter painter5(this);
        QPen pen5;
        pen5.setColor(QColor(0,0,0));
        QBrush brush5(QColor(150,150,150,255));
        painter5.setPen(pen5);
        painter5.setBrush(brush5);
        painter5.drawRect(340,100,60,200);
      }else{
          QPainter painter5(this);
          QPen pen5;
          pen5.setColor(QColor(0,0,0));
          QBrush brush5(QColor(255,255,255,255));
          painter5.setPen(pen5);
          painter5.setBrush(brush5);
          painter5.drawRect(340,100,60,200);
      }
    }
//When a keyboard is pressed, show blue color, otherwise show white color
    ////////////////game mode////////////////////////////////


    if(i0<9){
        timecount=timecount+1;
        if(timecount==10){
            t7=t6;
            t6=t5;
            t5=t4;
            t4=t3;
            t3=t2;
            t2=t1;
            t1=i0;
            timecount=0;
	    rightflag=0;
        }
//The above will run once every second, these variables are for the block
        if((t1<9)&&(t1>0)){
            QPainter paintert1(this);
            QBrush brusht1(QColor(0,255,255,255));
            paintert1.setBrush(brusht1);
            paintert1.drawRect(40+t1*60,0,60,20);
        }
        if((t2<9)&&(t2>0)){
            QPainter paintert2(this);
            QBrush brusht2(QColor(0,255,255,255));
            paintert2.setBrush(brusht2);
            paintert2.drawRect(40+t2*60,20,60,20);
        }
        if((t3<9)&&(t3>0)){
            QPainter paintert3(this);
            QBrush brusht3(QColor(0,255,255,255));
            paintert3.setBrush(brusht3);
            paintert3.drawRect(40+t3*60,40,60,20);
        }
        if((t4<9)&&(t4>0)){
            QPainter paintert4(this);
            QBrush brusht4(QColor(0,255,255,255));
            paintert4.setBrush(brusht4);
            paintert4.drawRect(40+t4*60,60,60,20);
        }
        if((t5<9)&&(t5>0)){
            QPainter paintert5(this);
            QBrush brusht5(QColor(0,255,255,255));
            paintert5.setBrush(brusht5);
            paintert5.drawRect(40+t5*60,80,60,20);
        }
//Plot the block
        if(((i1==t5)||(i1==t6)||(i1==t7)||(i1==t4))&&(i1==1)){
          QPainter painterg1(this);
          QBrush brushg1(QColor(0,255,255,255));
          painterg1.setBrush(brushg1);
          painterg1.drawRect(100,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	  rightflag=1;
        }
	else if(rightflag==1){
          QPainter painterg1(this);
          QBrush brushg1(QColor(0,255,255,255));
          painterg1.setBrush(brushg1);
          painterg1.drawRect(100,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	}
        else if((i1!=t6)&&(i1!=t5)&&(i1!=t4)&&(i1!=t7)&&(t6==1)){
          QPainter painterg1(this);
          QBrush brushg1(QColor(255,255,0,255));
          painterg1.setBrush(brushg1);
          painterg1.drawRect(100,100,60,200);
          gamecount=gamecount+1;
        }
        else{
            QPainter painterg1(this);
            QBrush brushg1(QColor(255,255,255,255));
            painterg1.setBrush(brushg1);
            painterg1.drawRect(100,100,60,200);
        }
        if(((i1==t5)||(i1==t6)||(i1==t7)||(i1==t4))&&(t6==2)){
          QPainter painterg2(this);
          QBrush brushg2(QColor(0,255,255,255));
          painterg2.setBrush(brushg2);
          painterg2.drawRect(160,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	  rightflag=2;
        }
	else if(rightflag==2){
          QPainter painterg2(this);
          QBrush brushg2(QColor(0,255,255,255));
          painterg2.setBrush(brushg2);
          painterg2.drawRect(160,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	}
        else if((i1!=t6)&&(i1!=t5)&&(i1!=t4)&&(i1!=t7)&&(t6==2)){
          QPainter painterg2(this);
          QBrush brushg2(QColor(255,255,0,255));
          painterg2.setBrush(brushg2);
          painterg2.drawRect(160,100,60,200);
          gamecount=gamecount+1;
        }
        else{
            QPainter painterg2(this);
            QBrush brushg2(QColor(255,255,255,255));
            painterg2.setBrush(brushg2);
            painterg2.drawRect(160,100,60,200);
        }
        if(((i1==t5)||(i1==t6)||(i1==t7)||(i1==t4))&&(t6==3)){
          QPainter painterg3(this);
          QBrush brushg3(QColor(0,255,255,255));
          painterg3.setBrush(brushg3);
          painterg3.drawRect(220,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
          rightflag=3;
        }
	else if(rightflag==3){
          QPainter painterg3(this);
          QBrush brushg3(QColor(0,255,255,255));
          painterg3.setBrush(brushg3);
          painterg3.drawRect(220,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	}
        else if((i1!=t6)&&(i1!=t5)&&(i1!=t4)&&(i1!=t7)&&(t6==3)){
          QPainter painterg3(this);
          QBrush brushg3(QColor(255,255,0,255));
          painterg3.setBrush(brushg3);
          painterg3.drawRect(220,100,60,200);
          gamecount=gamecount+1;
        }
        else{
            QPainter painterg3(this);
            QBrush brushg3(QColor(255,255,255,255));
            painterg3.setBrush(brushg3);
            painterg3.drawRect(220,100,60,200);
        }
        if(((i1==t5)||(i1==t6)||(i1==t7)||(i1==t4))&&(t6==4)){
          QPainter painterg4(this);
          QBrush brushg4(QColor(0,255,255,255));
          painterg4.setBrush(brushg4);
          painterg4.drawRect(280,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	  rightflag=4;
        }
	else if(rightflag==4){
          QPainter painterg4(this);
          QBrush brushg4(QColor(0,255,255,255));
          painterg4.setBrush(brushg4);
          painterg4.drawRect(280,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	}
        else if((i1!=t6)&&(i1!=t5)&&(i1!=t4)&&(i1!=t7)&&(t6==4)){
          QPainter painterg4(this);
          QBrush brushg4(QColor(255,255,0,255));
          painterg4.setBrush(brushg4);
          painterg4.drawRect(280,100,60,200);
          gamecount=gamecount+1;
        }
        else{
            QPainter painterg4(this);
            QBrush brushg4(QColor(255,255,255,255));
            painterg4.setBrush(brushg4);
            painterg4.drawRect(280,100,60,200);
        }
        if(((i1==t5)||(i1==t6)||(i1==t7)||(i1==t4))&&(t6==5)){
          QPainter painterg5(this);
          QBrush brushg5(QColor(0,255,255,255));
          painterg5.setBrush(brushg5);
          painterg5.drawRect(340,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	  rightflag=5;
        }
	else if(rightflag==4){
          QPainter painterg5(this);
          QBrush brushg5(QColor(0,255,255,255));
          painterg5.setBrush(brushg5);
          painterg5.drawRect(340,100,60,200);
          gameright=gameright+100;
          gamecount=gamecount+1;
	  rightflag=5;
	}
        else if((i1!=t6)&&(i1!=t4)&&(i1!=t7)&&(i1!=t5)&&(t6==5)){
          QPainter painterg5(this);
          QBrush brushg5(QColor(255,255,0,255));
          painterg5.setBrush(brushg5);
          painterg5.drawRect(340,100,60,200);
          gamecount=gamecount+1;
        }
        else{
            QPainter painterg5(this);
            QBrush brushg5(QColor(255,255,255,255));
            painterg5.setBrush(brushg5);
            painterg5.drawRect(340,100,60,200);
        }
//If the right keyboard is pressed, show blue; if wrong, show yellow
    }

    QPainter painter6(this);
    QBrush brush6(QColor(0,0,0,255));
    painter6.setBrush(brush6);
    painter6.drawRect(140,100,40,100);

    QPainter painter7(this);
    QBrush brush7(QColor(0,0,0,255));
    painter7.setBrush(brush7);
    painter7.drawRect(200,100,40,100);

    QPainter painter8(this);
    QBrush brush8(QColor(0,0,0,255));
    painter8.setBrush(brush8);
    painter8.drawRect(320,100,40,100);
//Plot the black unused keyboard
    }
Widget::~Widget()
{

}
