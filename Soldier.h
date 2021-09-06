#ifndef SOLDIER_H
#define SOLDIER_H
#include "Unit.h"
#include <QImage>

//This is the child of Unit,for use of the class of Soldiers

class Soldier:public Unit
{
    Q_OBJECT
public:
    Soldier(int _x,int _y,int _blood,int _attack,int _maxpic,int _speed):Unit(_x,_y,_blood,_attack,_maxpic,_speed){}
    ~Soldier(){}
public:
    int Get_Type() const;
    int Get_Stand() const;
    void Set_TySt(int,int);
    bool Get_State() const;
    void to_Act();
    void to_Static();
public:
    int Pic_State;
public slots:
    void To_Attack();
    void To_Static();
    void To_Defense();

signals:

private:
    int Type;
    int Stand;
    QString Path;
    bool is_Action=false;
};

#endif // SOLDIER_H
