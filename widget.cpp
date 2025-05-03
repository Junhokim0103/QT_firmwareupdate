#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)   
    , ui(new Ui::Widget)
    , port(new QSerialPort(this))
{
    ui->setupUi(this);
    i = 0;
    endoffile = 0;
    connect(ui->pushButton, &QPushButton::released, this, &Widget::ledon);
    connect(ui->pushButton_2, &QPushButton::released, this, &Widget::ledoff);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Widget::SendData);

    openport();
    fileopen();
    //thread = new WidgetThread();

    //connect(thread, &WidgetThread::resultReady, this, &Widget::threadcomm);
    //connect(thread, SIGNAL(resultReady(const QString&)), this, SLOT(threadcomm(const QString&)));
    //thread->start();
    //connect(ui->pushButton_3, &QPushButton::released, this, &Widget::writeslotfunc);
    //connect(ui->pushButton_4, &QPushButton::released, this, &Widget::readslotfunc);

}

Widget::~Widget()
{
    delete ui;
    fileclose();
}

void Widget::ledon(void)
{

    //port->open(QIODevice::ReadWrite);
    //    serial.close();
    //char * data = "test\n";
    //senddata.replace(0,5,"ledo\n");
    strcpy_s(senddata,"oledon");
    port->write(senddata, 16);//qstrlen(senddata));
    qDebug()<<qstrlen(senddata) <<"byte senddata";
}
void Widget::ledoff(void)
{

    //port->open(QIODevice::ReadWrite);
    //    serial.close();
    //char * data = "test\n";
    //senddata.replace(0,5,"ledo\n");
    strcpy_s(senddata,"fledof");
    port->write(senddata, 16);//qstrlen(senddata));
    qDebug()<<qstrlen(senddata) <<"byte senddata";
}
void Widget::readData(void)
{
    //qDebug()<< "readdata";
    //qint32 i = 0;
    AvailableData = port->bytesAvailable();
#if 0
    while(AvailableData != 5)
    {
        qDebug()<<AvailableData<<" byte come";
        AvailableData = port->bytesAvailable();
        i++;
        if(i > 5)
        {
            break;
        }
    }

    //QByteArray temp = port->readLine();
    if(AvailableData == 12)
    {
        static const char mydata[] = {
            '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
            '\x00', '\x00', '\x00', '\x00'
        };

        QByteArray temp = QByteArray::fromRawData(mydata, sizeof(mydata));
        //QByteArray temp("            ");//((qsizetype)12,Qt::Initialization);
        temp.replace(0,12,port->readAll());    //port->readAll();
        qDebug()<<"rcv data:"<<temp;
        ui->textEdit->setPlainText((QString)temp);
        //ui->label->setText((QString)temp);
    }
    //qDebug()<<"readdata";

    //qint64 QSerialPort::readLineData(char *data, qint64 maxSize)
    //m_console->putData(data);
#endif
    if(AvailableData == 16)
    {
        //readfile();
        QByteArray temp = port->readAll();
        qDebug()<<"rcv data:"<<temp;
        uartData();
    }


}

void Widget::openport(void)
{
    port = new QSerialPort();
    port->setPortName("COM11");
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->open(QIODevice::ReadWrite);
    connect(port, &QSerialPort::readyRead, this, &Widget::readData);
}



void Widget::SendData(void)
{
#if 0
    //QString SendData = ui->lineEdit_3->text();
    //QString SendData2 = "w"+SendData;
    //strcpy_s(senddata,"ledon");
    //QString str1 = "Test";
    static const char mydata[] = {
        'w',0x1,0x2,0x3,0x4,0x5,0x6,0x7,//'w', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07',
        0x8,0x9,0x10,0x11//'\x08', '\x09', '\x10', '\x11'
    };

    QByteArray temp = QByteArray::fromRawData(mydata, sizeof(mydata));
    //QByteArray ba = temp.toLocal8Bit();
    const char *c_str2 = temp.data();
    port->write(c_str2, 12);//qstrlen(senddata));
    //port->
    qDebug()<<temp <<"byte senddata";
#endif
    readfile();
    //port->write(cstr,16);
}
void Widget::fileopen(void)
{
    file = new QFile("C:/data/stm32/stm32g431rbuart/Debug/stm32g431rbuart.bin");//file("test.txt");
    if (!file->open(QIODevice::ReadOnly))//QIODevice::Text))
        return;
    in.setDevice(file);
    //file->seek(rpos);
#if 0
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
 //file->close();
#endif

}
void Widget::fileclose(void)
{
     file->close();
}
void Widget::readfile(void)
{
     //QDataStream in(file);
        quint64 a;
     //QString str;
     //qDebug()<<in.atEnd();
        if(endoffile == 0)
        {
     if(!in.atEnd())
     {

        in >> a;
        qDebug()<<"a:"<<a;
        qDebug()<<"i:"<<i;


     //cstr = (char *)&a;
     cstr[0] = 'b';
     cstr[1] = 'o';
     cstr[2] = 'o';
     cstr[3] = 't';
     cstr[4] = (i>>24)&0xff;//sequence i data
     cstr[5] = (i>>16)&0xff;
     cstr[6] = (i>>8)&0xff;
     cstr[7] = (i>>0)&0xff;
     cstr[8] = (a>>0)&0xff;//file data
     cstr[9] = (a>>8)&0xff;
     cstr[10] = (a>>16)&0xff;
     cstr[11] = (a>>24)&0xff;
     cstr[12] = (a>>32)&0xff;
     cstr[13] = (a>>40)&0xff;
     cstr[14] = (a>>48)&0xff;
     cstr[15] = (a>>56)&0xff;
     qDebug()<<cstr[0]<<cstr[1]<<cstr[2]<<cstr[3]<<cstr[4]<<cstr[5]<<cstr[6]<<cstr[7];
     qDebug()<<cstr[8]<<cstr[9]<<cstr[10]<<cstr[11]<<cstr[12]<<cstr[13]<<cstr[14]<<cstr[15];
     //qint64 i = 0;
    //port->write(c_str2, 12);
     //port->write()
     //rpos = rpos + sizeof(rpos);
     i++;
     port->write(cstr,16);
     }else {
     in >> a;
     qDebug()<<"a:"<<a;
     qDebug()<<"i:"<<i;


     //cstr = (char *)&a;
     cstr[0] = 'c';
     cstr[1] = 'o';
     cstr[2] = 'o';
     cstr[3] = 't';
     cstr[4] = (i>>24)&0xff;//sequence i data
     cstr[5] = (i>>16)&0xff;
     cstr[6] = (i>>8)&0xff;
     cstr[7] = (i>>0)&0xff;
     cstr[8] = (a>>0)&0xff;//file data
     cstr[9] = (a>>8)&0xff;
     cstr[10] = (a>>16)&0xff;
     cstr[11] = (a>>24)&0xff;
     cstr[12] = (a>>32)&0xff;
     cstr[13] = (a>>40)&0xff;
     cstr[14] = (a>>48)&0xff;
     cstr[15] = (a>>56)&0xff;
     qDebug()<<cstr[0]<<cstr[1]<<cstr[2]<<cstr[3]<<cstr[4]<<cstr[5]<<cstr[6]<<cstr[7];
     qDebug()<<cstr[8]<<cstr[9]<<cstr[10]<<cstr[11]<<cstr[12]<<cstr[13]<<cstr[14]<<cstr[15];
     //qint64 i = 0;
     //port->write(c_str2, 12);
     //port->write()
     //rpos = rpos + sizeof(rpos);
     i++;
     port->write(cstr,16);
     endoffile = 1;
     }
        }

}
void Widget::uartData(void)
{
#if 0
    //QString SendData = ui->lineEdit_3->text();
    //QString SendData2 = "w"+SendData;
    //strcpy_s(senddata,"ledon");
    //QString str1 = "Test";
    static const char mydata[] = {
        'w',0x1,0x2,0x3,0x4,0x5,0x6,0x7,//'w', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07',
        0x8,0x9,0x10,0x11//'\x08', '\x09', '\x10', '\x11'
    };

    QByteArray temp = QByteArray::fromRawData(mydata, sizeof(mydata));
    //QByteArray ba = temp.toLocal8Bit();
    const char *c_str2 = temp.data();
    port->write(c_str2, 12);//qstrlen(senddata));
    //port->
    qDebug()<<temp <<"byte senddata";
#endif
       readfile();

}
