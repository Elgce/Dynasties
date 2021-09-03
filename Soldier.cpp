#include <Soldier.h>

void Soldier::Set_TySt(int _type, int _stand)
{
    Type=_type;
    Stand=_stand;
    if(Stand==0)
    {
        Img.load(":/images/Res/Blue.bmp");
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


