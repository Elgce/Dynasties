#include "Leader.h"

void Leader::State_Changed(QString _path)
{
    Img.load(_path);
    if(State==1)
        State=0;
    else State=1;
    Convert_Tranparent();
}

QString Leader::Get_Name()
{
    return Name;
}
