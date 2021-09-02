#ifndef SOLDIER_H
#define SOLDIER_H
#include "Unit.h"
#include <QImage>

//This is the child of Unit,for use of the class of Soldiers

class Soldier:public Unit
{
public:
    Soldier(int _x,int _y,int _blood,int _attack):Unit(_x,_y,_blood,_attack){}
    ~Soldier(){}
public:
    int Get_Type();
    int Get_Stand();
    void Set_TySt(int,int);
public:
    QImage Img;
public slots:


signals:

private:
    int Type;
    int Stand;
    QString Path;
};

#endif // SOLDIER_H
