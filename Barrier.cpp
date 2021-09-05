#include "Barrier.h"
Barrier::Barrier(int _x,int _y,int _wid,int _hei,int _vary)
{

    Loc.x=_x*PIC_WIDTH;
    Loc.y=_y*PIC_HEIGHT;
    Len.Hei=_hei*PIC_HEIGHT;
    Len.Wid=_wid*PIC_WIDTH;
    if(_vary==1)
    {
        Path=":/images/Res/mount.png";
    }
    else if(_vary==2)
    {
        Path=":/images/Res/fire.png";
    }
    else if(_vary==3)
    {
        Path=":/images/Res/water.png";
    }

    Img.load(Path);

}

Len Barrier::Get_Len()
{
    return Len;
}

Location Barrier::Get_Loc()
{
    return Loc;
}
