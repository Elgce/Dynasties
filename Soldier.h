#ifndef SOLDIER_H
#define SOLDIER_H
#include "Unit.h"
#include <QImage>

//This is the child of Unit,for use of the class of Soldiers

class Soldier:public Unit
{
    Q_OBJECT
public:
    Soldier(int _x,int _y,int _blood,int _attack,int _maxpic):Unit(_x,_y,_blood,_attack,_maxpic){}
    ~Soldier(){}
public:
    int Get_Type() const;
    int Get_Stand() const;
    void Set_TySt(int,int);
public:
    int Pic_State;
public slots:


signals:

private:
    int Type;
    int Stand;
    QString Path;
};

#endif // SOLDIER_H
