#include "Clor_Block.h"

Clor_Block::Clor_Block(int _x,int _y,QColor _clor)
{
    Loc.x=_x;
    Loc.y=_y;
    clor=_clor;
}

QColor Clor_Block::Get_Clor()
{
    return clor;
}

Location Clor_Block::Get_Loc()
{
    return Loc;
}
