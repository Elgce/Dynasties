#ifndef CITY_H
#define CITY_H

#include <QObject>
#include <QImage>
#include "Struct_Use.h"
class City:public QObject
{
    Q_OBJECT
public:
    City(int,int,int,int,QString);
    ~City(){}
public:
    Location Get_Loc();
    Len Get_Len();
    QString Get_Path();
    QImage Img;

private:
    Location Loc;
    Len Len;
    QString Path;


};

#endif // CITY_H
