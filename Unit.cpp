#include "Unit.h"

Unit::Unit(QString name,int _x,int _y,int _blood,int _attack)
{
    Name=name;
    Loc.x=_x;
    Loc.y=_y;
    Blood=_blood;
    Attack=_attack;
}

Location Unit::Get_Loc() const
{
    return Loc;
}

Speed Unit::Get_Spd() const
{
    return Spd;
}

void Unit::Change_Loc(int _x,int _y)
{
    Loc.x=_x;
    Loc.y=_y;
}

void Unit::Change_Speed(double _vx,double _vy)
{
    Spd.v_x=_vx;
    Spd.v_y=_vy;
}

bool Unit::is_Dead() const
{
    if (Blood <= 0)
        return true;
    else return false;
}

int Unit::Get_Blood() const
{
    return Blood;
}

void Unit::Add_Blood(int _new)
{
    Blood+=_new;
}

void Unit::Add_Armor(int _new)
{
    Armor+=_new;
}


void Unit::Set_PicMax(int _max)
{
    Pic_Max=_max;
}

void Unit::Change_Num(int _num)
{
    if (_num>Pic_Max)
        _num=_num % Pic_Max;
    Pic_Num=_num;
}

void Unit::Set_PicPath(QString _path)
{
    Pic_Path=_path;
}
