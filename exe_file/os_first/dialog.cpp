#include "dialog.h"
#include "ui_dialog.h"
#include "QVector"

QVector<QString> p1 ;
QVector<float> a1;
int size1;
float average1;
Dialog::Dialog(QVector<QString> p,QVector<float> a,int size,float average,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    p1 = p;
    a1 = a;
    size1 = size;
    average1 = average;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(QFont("Times",10,QFont::Bold));
    QRect *rectangles [size1];
    rectangles[0] = new QRect(50,100,50,50);
    painter.drawText(*rectangles[0],Qt::AlignBottom | Qt::AlignLeft  , QString::number(a1[0]));

for(int i = 0;i<size1;i++){

    //painter.drawText(QPoint(500,200) , "hello world");

    rectangles[i] = new QRect(50+i*50,100 ,50 , 50);
    painter.drawRect(*rectangles[i]);
    painter.drawText(*rectangles[i],Qt::AlignBottom | Qt::AlignRight  ,QString::number(a1[i+1]));
    painter.drawText(*rectangles[i],Qt::AlignCenter,p1[i]);

}

ui->label->setStyleSheet("QLabel {color : black; }");
ui->label->setText("Average waiting time = " + QString::number(average1));

}
