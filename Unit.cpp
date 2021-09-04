#include "Unit.h"

Unit::Unit(int _x,int _y,int _blood,int _attack,int _picmax,int _speed)
{    
    Loc.x=_x;
    Loc.y=_y;
    Blood=_blood;
    Attack=_attack;
    Pic_Max=_picmax;
    Speed=_speed;
}

Location Unit::Get_Loc() const
{
    return Loc;
}

int Unit::Get_Speed() const
{
    return Speed;
}

void Unit::Change_Loc(int _x,int _y)
{
    Loc.x=_x;
    Loc.y=_y;
}

void Unit::Change_Speed(int _speed)
{
    Speed=_speed;
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

int Unit::Get_Picmax()
{
    return Pic_Max;
}

void Unit::Dam_Blood(int _blood)
{
    Blood-=_blood;
}

void Unit::Convert_Tranparent()
{
    Img=Img.convertToFormat(QImage::Format_ARGB32);
    union myrgb
    {
        uint rgba;
        uchar rgba_bits[4];
    };
    myrgb * mybits=(myrgb*) Img.bits();
    int len=Img.width()*Img.height();
    while(len-->0)
    {
        mybits->rgba_bits[3]=(mybits->rgba==0xFFFFFFFF)?0:255;
        mybits++;
    }
}

