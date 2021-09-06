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

void Unit::Kill_Blood(int _new)
{
    Blood-=_new;
}

void Unit::Add_Armor(double _new)
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
    for (int i=0;i<Img.width();i++)
    {
        for (int j=0;j<Img.height();j++)
        {
            QColor pixelColor=Img.pixelColor(i,j);
            if(pixelColor.red()>240 && pixelColor.green()>240 && pixelColor.blue()>240)
            {
                pixelColor.setAlpha(0);
                Img.setPixelColor(i,j,pixelColor);
            }
        }
    }
}

int Unit::Get_Movemax() const
{
    return Move_Num;
}


void Unit::Set_Attack(int _attack)
{
    Attack=_attack;
}

void Unit::Set_Armor(double _armor)
{
    Armor=_armor;
}

int Unit::Get_Attack() const
{
    return Attack;
}

double Unit::Get_Armor() const
{
    return Armor;
}

