#include <qfile.h>
#ifndef FILE_H
#define FILE_H
class widgetfile : public QFile
{
    Q_OBJECT

public:
    void readusrdata(char *data,qint64 len);
};
#endif // FILE_H
