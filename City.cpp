#include "City.h"
#include "Const.h"
City::City(int _x,int _y,int _wid,int _hei,QString _path)
{
    Loc.x=_x*PIC_WIDTH;
    Loc.y=_y*PIC_HEIGHT;
    Len.Hei=_hei*PIC_HEIGHT;
    Len.Wid=_wid*PIC_WIDTH;
    Path=_path;
    Img.load(Path);
}

QString City::Get_Path()
{
    return Path;
}

Location City::Get_Loc()
{
    return Loc;
}

Len City::Get_Len()
{
    return Len;
}
