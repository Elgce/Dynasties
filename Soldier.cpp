#include <Soldier.h>


void Soldier::Set_TySt(int _type, int _stand)
{
    Type=_type % 5;
    Stand=_stand % 2;



    if(Stand==0)
    {
        Img.load(":/images/Res/guanyu_attack.jpg");
        Img_Attack.load(":/images/Res/guanyu_attack.jpg");
    }
    else
    {
        Img.load(":/images/Res/Red.bmp");

    }
    Convert_Tranparent();

}


int Soldier::Get_Stand() const
{
    return Stand;
}

int Soldier::Get_Type() const
{
    return Type;
}

void Soldier::to_Act()
{
    is_Action=true;
}

void Soldier::to_Static()
{
    is_Action=false;
}

void Soldier::To_Attack()
{
    Set_TySt(0,Stand);
}

void Soldier::To_Defense()
{
    Set_TySt(3,Stand);
}

void Soldier::To_Static()
{
    Set_TySt(4,Stand);
}
