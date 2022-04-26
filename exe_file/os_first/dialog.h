#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>
#include <QVector>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QVector<QString> p,QVector<float> a,int size , float average,QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void paintEvent(QPaintEvent *event);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
