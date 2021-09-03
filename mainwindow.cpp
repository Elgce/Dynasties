#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "Const.h"
#include <QDebug>
#include "Heads.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    resize(960,640);
    bkg_map=QPixmap(":/images/Res/bkg.png");
    Set_Bkg(bkg_map);
    Init_Soldiers();
    eventId1=startTimer(50);


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);


    //draw all of the soldiers
    if(Soldiers.size()>0)
    for (int i=0;i<Soldiers.size();i++)
    {
        painter.drawImage(Soldiers[i]->Get_Loc().x,Soldiers[i]->Get_Loc().y,Soldiers[i]->Img,PIC_WIDTH*(Soldiers[i]->Pic_State+Soldiers[i]->Get_Stand()*Soldiers[i]->Get_Picmax()+1),PIC_HEIGHT*Soldiers[i]->Get_Type(),PIC_HEIGHT,PIC_WIDTH);
    }

    //draw all of the clor_blocks
    if(is_PrintBlock==true)
    for (int i=0;i<WIDTH_NUM;i++)
    {
        for(int j=0;j<HEIGHT_NUM;j++)
        {
            if (isLoad[i][j]==1)
            {
                painter.setBrush(QBrush(QColor(152,251,152,100)));
                painter.drawRect(i*PIC_WIDTH,j*PIC_HEIGHT,PIC_HEIGHT,PIC_WIDTH);
            }
        }
    }

}


void MainWindow::timerEvent(QTimerEvent * ev)
{
    if (Window_State==0)
    {
        for(int i=0;i<Soldiers.size();i++)
        {
            Soldiers[i]->Pic_State++;
            Soldiers[i]->Pic_State%=Soldiers[i]->Get_Picmax();
        }
    }
    repaint();
}


void MainWindow::Set_Bkg(QPixmap _img)
{
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(bkg_map));
    this->setPalette(palette);
}

void MainWindow::Init_Soldiers()
{
    for (int i=0;i<WIDTH_NUM;i++)
    {
        for (int j=0;j<HEIGHT_NUM;j++)
        {
            isLoad[i][j]=0;
        }
    }

    for (int i=3;i<12;i++)
    {
        for(int j=3;j<17;j++)
        {
            {
                isLoad[i][j]=1;isLoad[30-i][j]=-1;
            }
        }

    }
    for (int i=0;i<WIDTH_NUM;i++)
        for(int j=0;j<HEIGHT_NUM;j++)
        {
            if(isLoad[i][j]!=0)
            {
                if(i%5==0 && j%5==0)
                {
                    Soldiers.append(new Soldier(PIC_WIDTH*i,PIC_HEIGHT*j,100,100,5));
                    isLoad[i][j]=2*isLoad[i][j];
                }
                if(Soldiers.size()>0)
                {
                    Soldiers[Soldiers.size()-1]->Pic_State=0;
                    if(isLoad[i][j]==2)
                    {
                        Soldiers[Soldiers.size()-1]->Set_TySt(j,0);
                    }
                    else if(isLoad[i][j]==-2)
                    {
                        Soldiers[Soldiers.size()-1]->Set_TySt(j,1);
                    }
                }

            }
        }
}





void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        int _x=event->x()/PIC_WIDTH;
        int _y=event->y()/PIC_HEIGHT;
        if(Click_Unit==false && isLoad[_x][_y]==2)
        {
            Click_Unit=true;
            isLoad[_x][_y]=1;

            is_PrintBlock=true;

            if(Soldiers.size()>0)
            for (int i=0;i<Soldiers.size();i++)
            {
                if (Soldiers[i]->Get_Loc().x==_x*PIC_WIDTH && Soldiers[i]->Get_Loc().y==_y*PIC_HEIGHT)
                {
                    num_inControl=i;

                    break;
                }
            }
        }
        else if(Click_Unit==true && isLoad[_x][_y]==1)
        {
            Click_Unit=false;

            is_PrintBlock=false;

            isLoad[_x][_y]=2;
            Soldiers[num_inControl]->Change_Loc(_x*PIC_WIDTH,_y*PIC_HEIGHT);
            num_inControl=-1;
        }

    }
}
