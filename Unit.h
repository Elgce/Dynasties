#ifndef UNIT_H
#define UNIT_H
#include <QObject>
#include "Struct_Use.h"
//Unit is the base class of all the units in this program
//Unit includes Location,Speed,Blood,Armor
class Unit:public QObject
{
    Q_OBJECT

public:
    Unit(int,int,int,int);
    ~Unit(){}
public:
    Location Get_Loc() const;   //Get the location of this Unit
    Speed Get_Spd() const;      //Get the speed of this Unit
    int Get_Blood() const;      //Get the blood of this Unit
    bool is_Dead() const;       //bool to find if this Unit is Dead,if it's dead,then delete it
    void Set_PicMax(int);       //Set the num of Pic mode of this Unit
    void Set_PicPath(QString);  //Set the path of picture
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
    int Blood;
    int Attack;
    int Armor=0;
    int Pic_Num=0;
    int Pic_Max;
    QString Pic_Path="";

};

#endif // UNIT_H
