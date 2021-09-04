#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    connect(ui->StartBtn,SIGNAL(clicked()),this,SLOT(Begin_Fight()));

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
        painter.drawImage(Soldiers[i]->Get_Loc().x,Soldiers[i]->Get_Loc().y,Soldiers[i]->Img,PIC_WIDTH*(Soldiers[i]->Pic_State),PIC_HEIGHT*Soldiers[i]->Get_Type(),PIC_HEIGHT,PIC_WIDTH);
    }

    if(Against_Soldiers.size()>0)
    {
        for (int i=0;i<Against_Soldiers.size();i++)
        {
            painter.drawImage(Against_Soldiers[i]->Get_Loc().x,Against_Soldiers[i]->Get_Loc().y,Against_Soldiers[i]->Img,PIC_WIDTH*(Against_Soldiers[i]->Pic_State+Against_Soldiers[i]->Get_Picmax()+1),PIC_HEIGHT*Against_Soldiers[i]->Get_Type(),PIC_HEIGHT,PIC_WIDTH);
        }
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
        for (int i=0;i<Against_Soldiers.size();i++)
        {
            Against_Soldiers[i]->Pic_State++;
            Against_Soldiers[i]->Pic_State%=Against_Soldiers[i]->Get_Picmax();
        }
    }
    if (Fight_State==1)
    {
        for (int i=0;i<Soldiers.size();i++)
        {
            Soldiers[i]->Change_Loc(Soldiers[i]->Get_Loc().x+Soldiers[i]->Get_Spd().v_x,Soldiers[i]->Get_Loc().y+Soldiers[i]->Get_Spd().v_y);
        }
        for (int i=0;i<Against_Soldiers.size();i++)
        {
            Against_Soldiers[i]->Change_Loc(Against_Soldiers[i]->Get_Loc().x+Against_Soldiers[i]->Get_Spd().v_x,Against_Soldiers[i]->Get_Loc().y+Against_Soldiers[i]->Get_Spd().v_y);
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
                if((i<=6 && j>=8 && j<=11))
                {
                    Soldiers.append(new Soldier(PIC_WIDTH*i,PIC_HEIGHT*j,100,100,5));
                    isLoad[i][j]=2*isLoad[i][j];
                    Soldiers[Soldiers.size()-1]->Pic_State=0;
                    Soldiers[Soldiers.size()-1]->Set_TySt(j,0);
                }
                else if (i>15 && j%3==0 && i%3==0)
                {
                    Against_Soldiers.append(new Soldier(PIC_WIDTH*i,PIC_HEIGHT*j,100,100,5));
                    isLoad[i][j]=2*isLoad[i][j];
                    Against_Soldiers[Against_Soldiers.size()-1]->Pic_State=0;
                    Against_Soldiers[Against_Soldiers.size()-1]->Set_TySt(j,1);
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

double MainWindow::Sol_Dir(Soldier *_a, Soldier *_b)
{
    double d_x=(double)(_a->Get_Loc().x-_b->Get_Loc().x);
    double d_y=(double)(_a->Get_Loc().y-_b->Get_Loc().y);
    double distance=(double)(sqrt(d_x*d_x+d_y*d_y));
    return distance;
}


void MainWindow::Begin_Fight()
{


    for(int i=0;i<Soldiers.size();i++)
    {
        Soldiers[i]->Change_Speed(1,0);
    }
    for (int i=0;i<Against_Soldiers.size();i++)
    {
        Against_Soldiers[i]->Change_Speed(-1,0);
    }
    Fight_State=1;

}
