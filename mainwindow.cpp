#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Heads.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bkm=new QSound(":/Music/Music/bkm.wav");
    bkm->play();
    bkm->setLoops(-1);

    resize(960,640);
    bkg_map=QPixmap(":/images/Res/bkg.png");
    Set_Bkg(bkg_map);
    Init_Soldiers();
    Init_Blocks();
    Init_Cities();
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
        painter.drawImage(Soldiers[i]->Get_Loc().x,Soldiers[i]->Get_Loc().y,Soldiers[i]->Img,PIC_WIDTH*(Soldiers[i]->Pic_State),PIC_HEIGHT*Soldiers[i]->Get_Type(),PIC_HEIGHT,PIC_WIDTH);
        painter.setPen(QPen(Qt::white,2));
        painter.drawLine(Soldiers[i]->Get_Loc().x+4,Soldiers[i]->Get_Loc().y-8,Soldiers[i]->Get_Loc().x+20,Soldiers[i]->Get_Loc().y-8);
        painter.setPen(QPen(Qt::red,1));
        painter.drawLine(Soldiers[i]->Get_Loc().x+4,Soldiers[i]->Get_Loc().y-8,Soldiers[i]->Get_Loc().x+20*(double(Soldiers[i]->Get_Blood()/100)),Soldiers[i]->Get_Loc().y-8);

    }

    if(Against_Soldiers.size()>0)
    {
        for (int i=0;i<Against_Soldiers.size();i++)
        {
            painter.drawImage(Against_Soldiers[i]->Get_Loc().x,Against_Soldiers[i]->Get_Loc().y,Against_Soldiers[i]->Img,PIC_WIDTH*(Against_Soldiers[i]->Pic_State+Against_Soldiers[i]->Get_Picmax()+1),PIC_HEIGHT*Against_Soldiers[i]->Get_Type(),PIC_HEIGHT,PIC_WIDTH);

            painter.setPen(QPen(Qt::white,2));
            painter.drawLine(Against_Soldiers[i]->Get_Loc().x+4,Against_Soldiers[i]->Get_Loc().y-8,Against_Soldiers[i]->Get_Loc().x+20,Against_Soldiers[i]->Get_Loc().y-8);
            painter.setPen(QPen(Qt::red,1));
            painter.drawLine(Against_Soldiers[i]->Get_Loc().x+4,Against_Soldiers[i]->Get_Loc().y-8,Against_Soldiers[i]->Get_Loc().x+20*(double(Against_Soldiers[i]->Get_Blood()/100)),Against_Soldiers[i]->Get_Loc().y-8);
        }
    }
    painter.setPen(QPen(Qt::black,1));


    //draw all of the clor_blocks
    for (int i=0;i<WIDTH_NUM;i++)
    {
        for(int j=0;j<HEIGHT_NUM;j++)
        {
            if (isLoad[i][j]==1 && Clor_Block[i][j]==true)
            {
                painter.setBrush(QBrush(QColor(152,251,152,100)));
                painter.drawRect(i*PIC_WIDTH,j*PIC_HEIGHT,PIC_HEIGHT,PIC_WIDTH);
            }
        }
    }


    //draw all the cities
    if(Cities.size()>0)
    {
        for (int i=0;i<Cities.size();i++)
        {
            painter.drawImage(Cities[i]->Get_Loc().x,Cities[i]->Get_Loc().y,Cities[i]->Img,0,0,Cities[i]->Get_Len().Wid,Cities[i]->Get_Len().Hei);
        }
    }

    //draw all the barriers
    if(Barriers.size()>0)
    {
        for(int i=0;i<Barriers.size();i++)
        {
            painter.drawImage(Barriers[i]->Get_Loc().x,Barriers[i]->Get_Loc().y,Barriers[i]->Img,0,0,Barriers[i]->Get_Len().Wid,Barriers[i]->Get_Len().Hei);
        }
    }

}


void MainWindow::timerEvent(QTimerEvent * ev)
{
    bool isRepaint=false;
    for(int i=0;i<Soldiers.size();i++)
    {

        isRepaint=true;
        Soldiers[i]->Pic_State++;
        Soldiers[i]->Pic_State%=Soldiers[i]->Get_Picmax();
        if(Soldiers[i]->is_OnMove==true)
        {
            if(Soldiers[i]->Get_Loc().x>=(Aim.x-16) && Soldiers[i]->Get_Loc().y>=(Aim.y-16)
                    && Soldiers[i]->Get_Loc().x<=(Aim.x+16) && Soldiers[i]->Get_Loc().y>=Aim.y-16)
            {
                Soldiers[i]->Change_Loc(Aim.x,Aim.y);
                Aim.x=0;Aim.y=0;
                init_SoldierState(Soldiers[i]);
                Soldier_State->popup(Pos);
                Soldiers[i]->is_OnMove=false;
                Soldier_OnMove=false;
            }
            else
            {
                int dx=Aim.x-Soldiers[i]->Get_Loc().x;
                int dy=Aim.y-Soldiers[i]->Get_Loc().y;
                double dir=sqrt(dx*dx+dy+dy);
                int vx=(int)(Soldiers[i]->Get_Speed()*(dx/dir));
                int vy=(int)(Soldiers[i]->Get_Speed()*(dy/dir));
                Soldiers[i]->Change_Loc(Soldiers[i]->Get_Loc().x+vx,Soldiers[i]->Get_Loc().y+vy);

            }
        }

    }
    for (int i=0;i<Against_Soldiers.size();i++)
    {
        isRepaint=true;
        Against_Soldiers[i]->Pic_State++;
        Against_Soldiers[i]->Pic_State%=Against_Soldiers[i]->Get_Picmax();
    }

    if(isRepaint==true)
    {
        repaint();
    }

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
                    Soldiers.append(new Soldier(PIC_WIDTH*i,PIC_HEIGHT*j,100,100,5,10));
                    isLoad[i][j]=2*isLoad[i][j];
                    Soldiers[Soldiers.size()-1]->Pic_State=0;
                    Soldiers[Soldiers.size()-1]->Set_TySt(j,0);
                }
                else if (i>15 && j%3==0 && i%3==0)
                {
                    Against_Soldiers.append(new Soldier(PIC_WIDTH*i,PIC_HEIGHT*j,100,100,5,10));
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
        if(Click_Unit==false && isLoad[_x][_y]==2 && Set_Barrier==0 && Soldier_OnMove==false)
        {
            if(Soldiers.size()>0)
            {
                for (int i=0;i<Soldiers.size();i++)
                {
                    if (Soldiers[i]->Get_Loc().x==_x*PIC_WIDTH && Soldiers[i]->Get_Loc().y==_y*PIC_HEIGHT)
                    {

                        num_inControl=i;
                        if(Soldiers[num_inControl]->Time_Moved>=Soldiers[num_inControl]->Get_Movemax())
                        {
                            num_inControl=-1;
                        }
                        break;
                    }
                }
            }
            if(num_inControl!=-1)
            {
                Click_Unit=true;
                isLoad[_x][_y]=1;

                is_PrintBlock=true;



                for(int i=0;i<WIDTH_NUM;i++)
                {
                    for (int j=0;j<HEIGHT_NUM;j++)
                    {
                        if((qAbs(i-_x)+qAbs(j-_y))<=Soldiers[num_inControl]->Get_Speed() && (i!=_x || j!=_y))
                        Clor_Block[i][j]=true;
                    }
                }
            }
        }
        else if(Click_Unit==true && isLoad[_x][_y]==1 && Clor_Block[_x][_y]==true)
        {
            Click_Unit=false;
            is_PrintBlock=false;
            Aim.x=_x*PIC_WIDTH;Aim.y=_y*PIC_HEIGHT;
            Soldiers[num_inControl]->is_OnMove=true;
            Pos=event->globalPos();
            Init_Blocks();
            isLoad[_x][_y]=2;
            Soldiers[num_inControl]->Time_Moved++;
            num_inControl=-1;

        }


        if(Set_Barrier!=0 && Clor_Block[_x][_y]==true && Click_Unit==false && Soldier_OnMove==false)
        {
            Barriers.append(new Barrier(_x,_y,1,1,Set_Barrier));
            Init_Blocks();
            is_PrintBlock=false;
            isLoad[_x][_y]=3+Set_Barrier;
            Set_Barrier=0;
        }
    }
}


void MainWindow::Init_Blocks()
{
    for (int i=0;i<WIDTH_NUM;i++)
    {
        for (int j=0;j<HEIGHT_NUM;j++)
        {
            Clor_Block[i][j]=false;
        }
    }
}

void MainWindow::init_SoldierState(Soldier * _soldier)
{
    Soldier_State=new QMenu(this);
    QAction *pAction_attack=new QAction(Soldier_State);
    QAction *pAction_defense=new QAction(Soldier_State);
    QAction *pAction_static=new QAction(Soldier_State);
    pAction_attack->setText("Attack");
    Soldier_State->addAction(pAction_attack);
    connect(pAction_attack,SIGNAL(triggered()),_soldier,SLOT(To_Attack()));
    pAction_defense->setText("Defense");
    Soldier_State->addAction(pAction_defense);
    connect(pAction_defense,SIGNAL(triggered()),_soldier,SLOT(To_Defense()));
    pAction_static->setText("Static");
    Soldier_State->addAction(pAction_static);
    connect(pAction_static,SIGNAL(triggered()),_soldier,SLOT(To_Static()));
}


void MainWindow::Init_Cities()
{
    for (int i=0;i<6;i++)
    {
        for (int j=0;j<4;j++)
        {
            isLoad[i][j]=3;
        }
    }
    Cities.append(new City(0,0,6,4,":/images/Res/City_west.png"));

    for(int i=24;i<30;i++)
    {
        for (int j=0;j<4;j++)
        {
            isLoad[i][j]=3;
        }
    }
    Cities.append(new City(24,0,6,4,":/images/Res/City_east.png"));

    for (int i=0;i<4;i++)
    {
        for (int j=17;j<20;j++)
        {
            isLoad[i][j]=3;
        }
    }
    Cities.append(new City(0,17,4,3,":images/Res/Town_west.png"));

    for (int i=26;i<30;i++)
    {
        for (int j=17;j<20;j++)
        {
            isLoad[i][j]=3;
        }
    }
    Cities.append(new City(26,17,4,3,":images/Res/Town_east.png"));
}







void MainWindow::on_actionMount_triggered()
{
    Set_Barrier=1;
    is_PrintBlock=true;
    for (int i=0;i<WIDTH_NUM;i++)
    {
        for (int j=0;j<HEIGHT_NUM;j++)
        {
            if(isLoad[i][j]==1)
            Clor_Block[i][j]=true;
        }
    }
}


void MainWindow::on_actionFire_triggered()
{
    Set_Barrier=2;
    is_PrintBlock=true;
    for (int i=0;i<WIDTH_NUM;i++)
    {
        for (int j=0;j<HEIGHT_NUM;j++)
        {
            if(isLoad[i][j]==1)
            Clor_Block[i][j]=true;
        }
    }
}


void MainWindow::on_actionWater_triggered()
{
    Set_Barrier=3;
    is_PrintBlock=true;
    for (int i=0;i<WIDTH_NUM;i++)
    {
        for (int j=0;j<HEIGHT_NUM;j++)
        {
            if(isLoad[i][j]==1)
            Clor_Block[i][j]=true;
        }
    }
}

