#ifndef LEADER_H
#define LEADER_H
#include "Unit.h"
#include <QImage>
class Leader:public Unit
{
    Q_OBJECT

public:
    Leader(QString _name,int _x,int _y,int _blood,int _attack,int _picmax,int _speed,QString _path):Unit(_x,_y,_blood,_attack,_picmax,_speed)
    {Name=_name;State=0;Img.load(_path);}
    ~Leader(){}

public:
    QString Get_Name();
    void Explo(Unit *);

public slots:
    void State_Changed(QString);
signals:

private:
    QString Name="";
    int State=0;
};

#endif // LEADER_H
