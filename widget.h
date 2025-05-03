#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <string.h>
#include <stdio.h>
//#include <QIODevice>
//#include <QSerialPort>
#include "thread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void openport(void);
    void fileopen(void);
    void fileclose(void);
    void readfile(void);
    void uartData(void);
    //QSerialPort *serial; //plus

private slots:
    void ledon(void);
    void ledoff(void);
    void readData(void);
    void SendData(void);


private:
    Ui::Widget *ui;
    QSerialPort *port;
    char senddata[16];
    qint64 AvailableData = 0;
    QFile *file;
    quint32 i;
    QDataStream in;
    char cstr[16];
    quint32 endoffile;
};


#endif // WIDGET_H
