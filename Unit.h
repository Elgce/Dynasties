#ifndef UNIT_H
#define UNIT_H
#include <QObject>
#include "Struct_Use.h"
#include <QImage>


/*Unit is the base class of all the units in this program
Unit includes Location,Speed,Blood,Armor*/


class Unit:public QObject
{
    Q_OBJECT

public:
    Unit(int,int,int,int,int,int);
    ~Unit(){}
public:
    Location Get_Loc() const;   //Get the location of this Unit
    int Get_Blood() const;      //Get the blood of this Unit
    bool is_Dead() const;       //bool to find if this Unit is Dead,if it's dead,then delete it
    void Set_PicPath(QString);  //Set the path of picture
    int Get_Picmax();
    void Convert_Tranparent();
    void Change_Loc(int,int);
    void Change_Speed(int);
    int Get_Speed() const;
    int Get_Movemax() const;
    int Time_Moved=0;
    void Set_Attack(int);
    void Set_Armor(double);
    bool is_OnMove=false;
    double Get_Armor() const;
    int Get_Attack() const;
    void Kill_Blood(int);
public:
    QImage Img;


public slots:



    void Add_Armor(double);
    void Change_Num(int);
    void Dam_Blood(int);

signals:
    void Loc_Changed();
    void Num_Change();






private:

    int Move_Num=2;
    Location Loc;
    int Speed;
    int Blood;
    int Attack=50;
    double Armor=0.4;
    int Pic_Num=0;
    int Pic_Max;
    QString Pic_Path="";

};

#endif // UNIT_H
