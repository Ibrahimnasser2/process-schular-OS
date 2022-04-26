#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <string>
#include <QString>
#include <QVector>
#include <vector>
#include <iostream>
#include<sstream>
#include <queue>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



  // 0:fcfs - 1:sjf_non
  void insertionSort(QVector<QString> &arr1,QVector<float> &arr2 , QVector<float> &arr3 , QVector<float> &arr4 , int size , int type) {
if(size != 1){

     int j;
     QString key1 ;
     float key , key2 , key3 , key4;
     for(int i = 1; i<size; i++) {
        key1 = arr1[i];//take value
        key2 = arr2[i];
        key3 = arr3[i];
        key4 = arr4[i];

        if(type == 0) key = arr2[i];
        else if(type == 1) key = arr3[i];
        else if (type == 2) key = arr4[i];

        j = i;

        while(j > 0 && arr2[j-1]>key) {
           arr2[j] = arr2[j-1];
           arr1[j] = arr1[j-1];
           arr3[j] = arr3[j-1];
           arr4[j] = arr4[j-1];
           j--;
        }
        arr1[j] = key1;
        arr2[j] = key2;
        arr3[j] = key3;
        arr4[j] = key4;
     }

}
  }

QVector<float> extract_float(string str)
{
    stringstream ss;
    QVector<float> arr ;
    ss << str;
    string temp;
    while (!ss.eof()) {

        ss >> temp;
        arr.push_back(stof(temp));
        temp = "";
    }
    return arr;
}
QVector<QString> MainWindow:: processes(){
    QVector<QString> arr;
for(int i = 0 ;i < ui->textEdit->toPlainText().toInt();i++){
    arr.append(QString::fromStdString("P" + to_string(i+1)));
}
return arr;
}

QVector<float> MainWindow:: arrival(){
   QVector<float> arr =  extract_float((ui->textEdit_4->toPlainText()).toStdString());
    return arr;
}


QVector<float> MainWindow:: burst(){
    QVector<float> arr =  extract_float((ui->textEdit_2->toPlainText()).toStdString());
    return arr;
}


QVector<float> MainWindow:: priority(){
    QVector<float> arr =  extract_float((ui->textEdit_3->toPlainText()).toStdString());
    return arr;
}

QVector<float> MainWindow:: quantum(){
    QVector<float> arr =  extract_float((ui->textEdit_5->toPlainText()).toStdString());
    return arr;
}



void MainWindow::on_FCFS_clicked()
{
    QVector<QString> arr1 = processes();
    QVector <float> arr2 = arrival();
    QVector <float> burst1 = burst();
    QVector <QString> process_order;
    QVector <float> time;


    //selectionSort(arr1, arr2,burst1,ui->textEdit->toPlainText().toInt(),0);
    insertionSort(arr1, arr2,burst1,burst1,ui->textEdit->toPlainText().toInt(),0);
    time.push_back(arr2[0]);
    process_order.push_back(arr1[0]);
    float sum = arr2[0] + burst1[0];
    time.push_back( sum);
    int k = 1;
    for(int i = 1 ;k < arr1.size();i++){
    if(arr2[k]<= time[i]){

        sum = sum + burst1[k];
        process_order.push_back(arr1[k]);
        k = k + 1;

    }
    else{
        sum = sum + arr2[k]-time[i];
        process_order.push_back("") ;
    }
    time.push_back(sum);
}
float average = 0;
for(int i = 0;i < ui->textEdit->toPlainText().toInt()  ;i++){
   int dep = process_order.lastIndexOf(QString::fromStdString("P"+to_string(i+1)));
   average = average + time[dep+1] - arr2[i] - burst1[i];

}
average = average/ (ui->textEdit->toPlainText().toInt());
// don't forget to change the last parameter

if(time[0]!=0){
process_order.push_front("");
time.push_front(0);
}
    Dialog d(process_order,time,process_order.size(),average);
    d.setModal(true);
    d.exec();

}





void MainWindow::on_sjf_non_clicked()
{

    QVector<QString> arr1 = processes();
    QVector <float> arr2 = arrival();
    QVector <float> burst1 = burst();
    QVector <QString> process_order;
    QVector <float> time;
    QVector <QString> stage1;
    QVector <float> stage1burst;
    QVector <float> stage1arrival;

    QVector<QString> arr11 = processes();
    QVector <float> arr22 = arrival();
    QVector <float> burst11 = burst();


    insertionSort(arr1, arr2,burst1,burst1,ui->textEdit->toPlainText().toInt(),0);


    time.push_back(arr2[0]);
    stage1.push_back(arr1[0]);
    stage1burst.push_back(burst1[0]);
    stage1arrival.push_back(arr2[0]);
    float sum = arr2[0];
    arr1.pop_front();
    arr2.pop_front();
    burst1.pop_front();


    for(;!(arr1.isEmpty()) ;){

    int kk = 0;

        for(int i = 0;i < arr2.size();i++){
if(arr2[i-kk]<=time.back()){
            stage1.push_back(arr1[0]);
            stage1burst.push_back(burst1[0]);
            stage1arrival.push_back(arr2[0]);
            arr1.pop_front();
            arr2.pop_front();
            burst1.pop_front();
            kk++;
        }
        }
        insertionSort(stage1, stage1arrival,stage1burst,stage1burst,stage1.size(),1);
        process_order.push_back(stage1[0]);
        sum = sum + stage1burst[0];
        time.push_back(sum);

        stage1.pop_front();
        stage1arrival.pop_front();
        stage1burst.pop_front();

if((stage1.isEmpty()) && !(arr1.isEmpty()) && arr2[0] > time.back()  ){
    sum = sum + arr2[0]-time.back();
    process_order.push_back("") ;
    time.push_back(sum);
}


}

    float average = 0;
    for(int i = 0;i < ui->textEdit->toPlainText().toInt()  ;i++){
       int dep = process_order.lastIndexOf(QString::fromStdString("P"+to_string(i+1)));
       average = average + time[dep+1] - arr22[i] - burst11[i];

    }
    average = average/ (ui->textEdit->toPlainText().toInt());

    if(time[0]!=0){
    process_order.push_front("");
    time.push_front(0);
    }

    Dialog d(process_order,time,process_order.size(),average);
    d.setModal(true);
    d.exec();
}

// round robin
void MainWindow::on_pushButton_2_clicked()
{
    QVector<QString> arr1 = processes();
           QVector <float> arr2 = arrival();
           QVector <float> burst1 = burst();
           QVector <float> quan1 = quantum();
           QVector <QString> process_order;
           QVector <float> time;
           float q = quan1[0] ;
           insertionSort(arr1, arr2,burst1,burst1,ui->textEdit->toPlainText().toInt(),0);



           queue<QString> process;
           queue<float> duration;

           int i = 0;

           while (arr2[i] == arr2[0] ){

              process.push(arr1[i]);
              duration.push(burst1[i]);
              i++;
           }


           float sum = arr2[0];

           time.push_back(sum);

           while ((!(process.empty())&& !(duration.empty())) || i < arr1.size() ){

               while (  i < arr1.size()){
                  if (arr2[i] <= sum){
                  process.push(arr1[i]);
                  duration.push(burst1[i]);
                  i++;
               }
                  else{
                      break;
                  }
               }
               if(process.empty()){
                   process_order.push_back("") ;
                   sum = arr2[i];
                   time.push_back(sum);

               }
               else{

               process_order.push_back(process.front());

              if((duration.front()-q) > 0){

                   sum = sum + q;
                   time.push_back(sum);
                   while (  i < arr1.size()){
                      if (arr2[i] <= sum){
                      process.push(arr1[i]);
                      duration.push(burst1[i]);
                      i++;
                   }
                      else{
                          break;
                      }
                   }
                   process.push(process.front());
                   duration.push(duration.front()- q);
               }
               else{
                   sum = sum + duration.front();
                   time.push_back(sum);
               }
               process.pop();
               duration.pop();
               }
           }
           float average = 0;
           for(int i = 0;i < ui->textEdit->toPlainText().toInt()  ;i++){
              int dep = process_order.lastIndexOf(QString::fromStdString("P"+to_string(i+1)));
              average = average + time[dep+1] - arr2[i] - burst1[i];

           }
           average = average/ (ui->textEdit->toPlainText().toInt());

           if(time[0]!=0){
           process_order.push_front("");
           time.push_front(0);
           }

           Dialog d(process_order,time,process_order.size(),average);
           d.setModal(true);
           d.exec();
}

// priority
void MainWindow::on_pushButton_6_clicked()
{
    QVector<QString> arr1 = processes();
    QVector <float> arr2 = arrival();
    QVector <float> burst1 = burst();
    QVector <float> priority1 = priority();
    QVector <QString> process_order;
    QVector <float> time;
    QVector <QString> stage1;
    QVector <float> stage1burst;
    QVector <float> stage1priority;
    QVector <float> stage1arrival;

    QVector<QString> arr11 = processes();
    QVector <float> arr22 = arrival();
    QVector <float> burst11 = burst();


    insertionSort(arr1, arr2,burst1, priority1,ui->textEdit->toPlainText().toInt(),0);


    time.push_back(arr2[0]);
    stage1.push_back(arr1[0]);
    stage1burst.push_back(burst1[0]);
    stage1arrival.push_back(arr2[0]);
    stage1priority.push_back( priority1[0]);

    float sum = arr2[0];
    arr1.pop_front();
    arr2.pop_front();
    burst1.pop_front();
    priority1.pop_front();


    for(;!(arr1.isEmpty()) ;){

    int kk = 0;

        for(int i = 0;i < arr2.size();i++){
if(arr2[i-kk]<=time.back()){
            stage1.push_back(arr1[0]);
            stage1burst.push_back(burst1[0]);
            stage1arrival.push_back(arr2[0]);
            stage1priority.push_back(priority1[0]);
            arr1.pop_front();
            arr2.pop_front();
            burst1.pop_front();
            priority1.pop_front();
            kk++;
        }
        }
        insertionSort(stage1, stage1arrival,stage1burst,stage1priority,stage1.size(),2);
        process_order.push_back(stage1[0]);
        sum = sum + stage1burst[0];
        time.push_back(sum);

        stage1.pop_front();
        stage1arrival.pop_front();
        stage1burst.pop_front();
        stage1priority.pop_front();

if((stage1.isEmpty()) && !(arr1.isEmpty()) && arr2[0] > time.back()  ){
    sum = sum + arr2[0]-time.back();
    process_order.push_back("") ;
    time.push_back(sum);
}


}

    float average = 0;
    for(int i = 0;i < ui->textEdit->toPlainText().toInt()  ;i++){
       int dep = process_order.lastIndexOf(QString::fromStdString("P"+to_string(i+1)));
       average = average + time[dep+1] - arr22[i] - burst11[i];

    }
    average = average/ (ui->textEdit->toPlainText().toInt());

    if(time[0]!=0){
    process_order.push_front("");
    time.push_front(0);
    }

    Dialog d(process_order,time,process_order.size(),average);
    d.setModal(true);
    d.exec();
}







// sjf preemptive
void MainWindow::on_pushButton_3_clicked()
{
    QVector<QString> arr1 = processes();
    QVector <float> arr2 = arrival();
    QVector <float> burst1 = burst();
    QVector <QString> process_order;
    QVector <float> time;




    //////////////////////////////////////////////////////////////////

    QVector <float> wt;


    int n = arr1.size();
    float complete = 0, t=*min_element(arr2.begin(), arr2.end()), minm = 3.40282e+038;
    int shortest1 = 0,shortest2= -1 ,finish_time;
    bool check = false;

    while (complete != n) {


            for (int j = 0; j < n; j++) {
                if ((arr2[j] <= t) &&
                (burst1[j] < minm) && burst1[j] > 0) {
                    minm = burst1[j];
                    shortest1 = j;
                    check = true;

                }
            }
            if(shortest1 != shortest2){
            process_order.push_back(arr1[shortest1]);
            time.push_back(t);
            }


            if (check == false) {

                if(shortest1 == shortest2){
                process_order.push_back("") ;
                time.push_back(t);
                }
                t++;
                continue;
            }
            shortest2 = shortest1;

            burst1[shortest1]--;
            minm = burst1[shortest1];
            if (minm == 0)
                minm = 3.40282e+038;


            if (burst1[shortest1] == 0) {


                complete++;
                check = false;


                finish_time = t + 1;
                int sum = finish_time -burst1[shortest1] -arr2[shortest1];
                wt.push_back(sum);
                //if (wt[shortest1] < 0)
                    //wt[shortest1] = 0;
            }

            t++;
        }
    time.push_back(t);
    float sum3 = 0;
    for(int i = 0;i<wt.size();i++){

        sum3 = sum3 + wt[i];

    }
    float average = 0;
    average = sum3 / n;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////


QVector<QString> pr;
QVector<float> ti;

for(int i = 0; i < process_order.size() ;i++){
pr.push_back(process_order[i]);
ti.push_back(time[i]);

if(process_order[i] == ""){
while(process_order[i]==""){
    i++ ;
}
i--;
}
}

ti.push_back(time[time.size()-1]);

    //time = {0 , 2 , 4 , 5 , 7 , 11 , 16};

if(ti[0]!=0){
pr.push_front("");
ti.push_front(0);

}

    Dialog d(pr,ti,pr.size(),average);
    d.setModal(true);
    d.exec();
}


// priority preemptive
void MainWindow::on_pushButton_5_clicked()
{



/////////////////////////////////////////////////////////////////

    QVector<QString> arr1 = processes();
        QVector <float> arr2 = arrival();
        QVector <float> burst1 = burst();
        QVector <float> priority1 = priority();
        QVector <QString> process_order;
        QVector <float> time;
        QVector <float> wt;



        QVector <float> arr22 = arrival();
        QVector <float> burst11 = burst();


        int n = arr1.size();
        float complete = 0, t=*min_element(arr2.begin(), arr2.end()), minm = 3.40282e+038;
        int lowest1 = 0,lowest2= -1, finish_time ;
        bool check = false;

        while (complete != n) {


                for (int j = 0; j < n; j++) {
                    if ((arr2[j] <= t) &&
                    (priority1[j] < minm) && burst1[j] > 0) {
                        minm = priority1[j];
                        lowest1 = j;
                        check = true;

                    }
                }
                if(lowest1 != lowest2){
                process_order.push_back(arr1[lowest1]);
                time.push_back(t);
                }


                if (check == false) {

                    if(lowest1 == lowest2){
                    process_order.push_back("") ;
                    time.push_back(t);
                    }
                    t++;
                    continue;
                }
                lowest2 = lowest1;
                burst1[lowest1]--;

                if (burst1[lowest1] == 0) {

                    complete++;
                    check = false;
                    minm = 3.40282e+038;
/*

                    finish_time = t + 1;
                    int sum = finish_time -burst1[lowest1] -arr2[lowest1];
                    wt.push_back(sum);
*/
                }


                t++;
            }
        time.push_back(t);
/*
        float sum3 = 0;
        for(int i = 0;i<wt.size();i++){

            sum3 = sum3 + wt[i];

        }
        float average = 0;
        average = sum3 / n;
*/



    QVector<QString> pr;
    QVector<float> ti;

    for(int i = 0; i < process_order.size() ;i++){
        pr.push_back(process_order[i]);
        ti.push_back(time[i]);

        if(process_order[i] == ""){
            while(process_order[i]==""){
                i++ ;
            }
            i--;
            }
    }

    ti.push_back(time[time.size()-1]);




    float average = 0;
    for(int i = 0;i < ui->textEdit->toPlainText().toInt()  ;i++){
       int dep = pr.lastIndexOf(QString::fromStdString("P"+to_string(i+1)));
       average = average + ti[dep + 1] - arr22[i] - burst11[i];

    }
    average = average/ (ui->textEdit->toPlainText().toInt());




    if(ti[0]!=0){
    pr.push_front("");
    ti.push_front(0);
    }


        Dialog d(pr,ti,pr.size(),average);
        d.setModal(true);
        d.exec();
    }















/*

/////////////////////////////////////////////////////////////////////
    float average = 0;
    for(int i = 0;i < ui->textEdit->toPlainText().toInt()  ;i++){
       int dep = process_order.lastIndexOf(QString::fromStdString("P"+to_string(i+1)));
       average = average + time[dep+1] - arr22[i] - burst11[i];

    }
    average = average/ (ui->textEdit->toPlainText().toInt());
    Dialog d(process_order,time,process_order.size(),average);
    d.setModal(true);
    d.exec();

}

*/
