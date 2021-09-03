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
    for (int i=0;i<Soldiers.size();i++)
    {
        painter.drawImage(Soldiers[i]->Get_Loc().x,Soldiers[i]->Get_Loc().y,Soldiers[i]->Img,PIC_WIDTH*(Soldiers[i]->Pic_State+Soldiers[i]->Get_Stand()*Soldiers[i]->Get_Picmax()+1),PIC_HEIGHT*Soldiers[i]->Get_Type(),PIC_HEIGHT,PIC_WIDTH);
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
            isLoad[i][j]=1;
        }
    }

    for (int i=3;i<12;i++)
    {
        for(int j=3;j<17;j++)
        {
            if(i%5==0 && j%5==0)
            {
                isLoad[i][j]=0;isLoad[30-i][j]=0;
            }
        }

    }
    for (int i=0;i<WIDTH_NUM;i++)
        for(int j=0;j<HEIGHT_NUM;j++)
        {
            if(isLoad[i][j]==0)
            {
                qDebug("%d %d\n",i,j);

                Soldiers.append(new Soldier(PIC_WIDTH*i,PIC_HEIGHT*j,100,100,5));
                Soldiers[Soldiers.size()-1]->Pic_State=0;
                if(i<15)
                {
                    Soldiers[Soldiers.size()-1]->Set_TySt(j,0);
                }
                else
                {
                    Soldiers[Soldiers.size()-1]->Set_TySt(j,1);
                }

            }
        }
}
