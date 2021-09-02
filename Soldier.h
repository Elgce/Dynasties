#ifndef SOLDIER_H
#define SOLDIER_H
#include "Unit.h"

class Soldier:public Unit
{
public:
    Soldier(QString _name,int _x,int _y,int _blood,int _attack):Unit(_name,_x,_y,_blood,_attack){}
    ~Soldier(){}
public:

public slots:


signals:

private:


};

#endif // SOLDIER_H
