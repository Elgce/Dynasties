#include <Soldier.h>
#include <QSound>

void Soldier::Set_TySt(int _type, int _stand)
{
    Type=_type;Stand=_stand;
    if(Type==1)
    {
        Path=":/images/Res/guanyu.jpg";
        Attack_Path=":/images/Res/guanyu_attack.jpg";
        Img.load(Path);

    }
    Convert_Tranparent();
    Line=Stand;


}


int Soldier::Get_Stand() const
{
    return Stand;
}

int Soldier::Get_Type() const
{
    return Type;
}

void Soldier::Set_Line(int _line)
{

    Line=_line;
}

void Soldier::To_Attack()
{
    State=1;
    Pic_State=0;
    is_Action=true;
    Img.load(Attack_Path);
    Convert_Tranparent();
    Line=2;
    Set_Attack(70);
}

void Soldier::To_Defense()
{
    Img.load(Path);
    Convert_Tranparent();
    Pic_State=0;
    State=2;
    Line=0;
    Set_Armor(0.4);
}

void Soldier::To_Static()
{
    Img.load(Path);
    Convert_Tranparent();
    Pic_State=0;
    State=0;
    Line=2;
    is_Action=false;
    Set_Armor(0.2);
    Set_Attack(50);
}

int Soldier::Get_Line() const
{
    return Line;
}
