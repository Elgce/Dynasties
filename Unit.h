#ifndef UNIT_H
#define UNIT_H
#include <QObject>
#include "Struct_Use.h"
class Unit:public QObject
{
    Q_OBJECT

public:
    Unit(QString,int,int,int,int);
    ~Unit(){}
public:
    Location Get_Loc() const;
    Speed Get_Spd() const;
    int Get_Blood() const;
    bool is_Dead() const;
    void Set_PicMax(int);
    void Set_PicPath(QString);
public slots:
    void Add_Blood(int);
    void Change_Loc(int,int);
    void Change_Speed(double,double);
    void Add_Armor(int);
    void Change_Num(int);
signals:
    void Loc_Changed();
    void Num_Change();








private:

    Location Loc;
    Speed Spd;
    QString Name;
    int Blood;
    int Attack;
    int Armor=0;
    int Pic_Num=0;
    int Pic_Max;
    QString Pic_Path="";

};

#endif // UNIT_H
