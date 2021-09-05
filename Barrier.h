#ifndef BARRIER_H
#define BARRIER_H
#include <QObject>
#include "Const.h"
#include "Struct_Use.h"
#include <QImage>
class Barrier:public QObject
{
    Q_OBJECT

public:
    Barrier(int,int,int,int,int);
    ~Barrier(){}
public:
    Location Get_Loc();

    QImage Img;
    Len Get_Len();
private:
    QString Path;
    Location Loc;
    Len Len;
};

#endif // BARRIER_H
