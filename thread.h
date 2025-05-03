#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include "file.h"
class WidgetThread : public QThread
{
    Q_OBJECT
    void run() override {
        QString result;
        /* ... here is the expensive or blocking operation ... */
        //writedata(0x34343434);

        //readdata();
        //readdata2();

        while(1)
        {
            qDebug()<<"thread";
            unsigned long sleep_msec = 6000;
            this->msleep(sleep_msec );
            //result.setNum(0x34343434);
            //emit resultReady(result);
        }

    }
public:
    void writedata(quint32 adddata);
    void readdata(void);
    void readdata2(void);
signals:
    void resultReady(const QString &s);
private:
    QFile *file;
    QByteArray dataarray;
    quint32 wpos = 0;
    quint32 rpos = 0;



};
#endif // THREAD_H
