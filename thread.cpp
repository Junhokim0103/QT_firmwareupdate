#include "thread.h"
void WidgetThread::writedata(quint32 adddata)
{
    file = new QFile("test.dat");//file("test.txt");
    if (!file->open(QIODevice::WriteOnly))//QIODevice::Text))
        return;
    file->seek(wpos);
    QDataStream out(file);   // we will serialize the data into the file
    qDebug()<<"data:"<<adddata;

    out << adddata;
    wpos = wpos+sizeof(adddata);
    //out << (quint32)0x10203040;
    //out << (quint32)0x50607080;
    //out << (quint32)0xA0B0C0D0;
    qDebug()<<"wpos:"<<wpos;
    file->close();
    //QFile file("test.dat");//file("test.txt");
}


void WidgetThread::readdata(void)
{
     file = new QFile("C:/data/stm32/stm32g431rbuart/Debug/stm32g431rbuart.hex");//file("test.txt");
    if (!file->open(QIODevice::ReadOnly))//QIODevice::Text))
        return;
    //file->seek(rpos);
    QDataStream in(file);
    //QString str;
    quint32 a;
    in >> a;
    qDebug()<<a;
    qint64 i = 0;

    //rpos = rpos + sizeof(rpos);
    while(!in.atEnd())
    {

        in >> a;
        i++;
        qDebug()<<"a:"<<a;
        qDebug()<<"i:"<<i;

    }
    file->close();
}
void WidgetThread::readdata2(void)
{
    QFile *file2;
    file2 = new QFile("test.dat");
    if (!file2->open(QIODevice::ReadOnly | QIODevice::Text))
        return;
#if 0
    while (!file2.atEnd()) {
        QByteArray line = file2.readLine();
        //process_line(line);
    }
#endif
    file2->seek(5);
    //char data[4];
    QByteArray data = file2->readAll();
    //file2->read()
    uint8_t chardata[20];
    chardata[0] = data.front();

    file2->seek(6);
    //char data[4];
    data = file2->readAll();
    chardata[1] = data.front();

    file2->seek(7);
    //char data[4];
    data = file2->readAll();
    chardata[2] = data.front();

    file2->seek(8);
    //char data[4];
    data = file2->readAll();
    chardata[3] = data.front();

    qDebug()<<(uint8_t)chardata[0]<<(uint8_t)chardata[1]<<(uint8_t)chardata[2]<<(uint8_t)chardata[3];

}
