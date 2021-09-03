#ifndef CLOR_BLOCK_H
#define CLOR_BLOCK_H
#include <QObject>
#include "Struct_Use.h"
#include <QColor>
class Clor_Block:public QObject
{
    Q_OBJECT

public:
    Clor_Block(int,int,QColor);
    ~Clor_Block(){}
public:
    bool is_print=false;
    QColor Get_Clor();
    Location Get_Loc();
private:
    Location Loc;
    QColor clor;


};

#endif // CLOR_BLOCK_H
