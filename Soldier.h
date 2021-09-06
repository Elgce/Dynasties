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
    int Get_Line() const;
    void Set_TySt(int,int);
    bool Get_State() const;
    void Set_Line(int);
    bool is_Action=false;
public:
    int Pic_State;
public slots:
    void To_Attack();
    void To_Static();
    void To_Defense();

signals:

private:
    //Type: the kind of Soldier  Stand: turn right or turn left  State: attack/defense/static  Line: the line pic to show
    int Type;//3: static/ahead  2: back  3:1: guanyu  2:  zhaoyun  3: soldier1  4:
    int Stand;//1:against   2:mine
    int State;//attack static defense
    int Line;//the line to show
    QString Path;
    QString Attack_Path;

};

#endif // SOLDIER_H
