#ifndef CLOR_BLOCK_H
#define CLOR_BLOCK_H
#include <QObject>
#include "Struct_Use.h"
class Clor_Block:public QObject
{
    Q_OBJECT

public:
    Clor_Block(int,int);
    ~Clor_Block(){}
public:
    bool is_print=false;
private:
    Location Loc;



};

#endif // CLOR_BLOCK_H
