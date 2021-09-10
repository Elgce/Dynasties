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
    else if(Type==2)
    {
        Path=":/images/Res/zhaoyun.png";
        Attack_Path=":/images/Res/zhaoyun_attack.jpg";
        Img.load(Path);
    }
    else if (Type==3)
    {
        Path=":/images/Res/soldier.png";
        Attack_Path=":/images/Res/soldier.png";
        Img.load(Path);
    }
    else if(Type==4)
    {
        Path=":/images/Res/man.jpg";
        Attack_Path=":/images/Res/man.jpg";
        Img.load(Path);
    }
    else if(Type==5)
    {
        Path=":/images/Res/bubing.png";
        Attack_Path=":/images/Res/bubing.png";
        Img.load(Path);
    }
    else if(Type==6)
    {
        Path=":/images/Res/arrow.png";
        Attack_Path=":/images/Res/arrow.png";
        Img.load(Path);
    }
    else if(Type==7)
    {
        Path=":/images/Res/Boss.jpg";
        Attack_Path=":/images/Res/Boss/jpg";
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
    Set_Attack(50);
    if(Type==4 || Type==5)
    {
        Set_Attack(20);
    }
    else if(Type==6)
    {
        Set_Attack(60);
    }
    else if(Type==7)
    {
        Set_Attack(50);
    }
}

void Soldier::To_Defense()
{
    Img.load(Path);
    Convert_Tranparent();
    Pic_State=0;
    State=2;
    Line=0;
    Set_Armor(0.3);
    if(Type==4 || Type==5)
    {
        Set_Armor(0.5);
    }
    else if(Type==6)
    {
        Set_Armor(0.2);
    }
    else if(Type==7)
    {
        Set_Armor(0.5);
    }
}

void Soldier::To_Static()
{
    Img.load(Path);
    Convert_Tranparent();
    Pic_State=0;
    State=0;
    if(Stand==2)
        Line=2;
    else Line=1;
    is_Action=false;
    Set_Armor(0.2);
    Set_Attack(25);
    if(Type==4 || Type==5)
    {
        Set_Armor(0.3);
        Set_Attack(20);
    }
    else if(Type==6)
    {
        Set_Armor(0.1);
        Set_Attack(60);
    }
    else if(Type==7)
    {
        Set_Armor(0.5);
        Set_Attack(50);
    }
}

int Soldier::Get_Line() const
{
    return Line;
}

QString Soldier::Get_Name() const
{
    return Name;
}
