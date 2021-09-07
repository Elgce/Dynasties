#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Heads.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Esc_Widget=new EscWidget;
    connect(Esc_Widget,SIGNAL(StartBtn_Clicked()),this,SLOT(Start_Window()));
    connect(Esc_Widget,SIGNAL(ContinueBtn_Clicked()),this,SLOT(Continue_Window()));
    resize(960,640);
    bkg_map=QPixmap(":/images/Res/bkg.png");
    Set_Bkg(bkg_map);
    bkm=new QSound(":/Music/Music/bkm.wav");
    bkm->play();
    bkm->setLoops(-1);
    atta=new QSound(":/Music/Music/atta.wav");



    Esc_Widget->show();

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Continue_Window()
{
    Window_State=1;
    Esc_Widget->close();
    eventId1=startTimer(200);
}

void MainWindow::Start_Window()
{

    Window_State=1;
    Init();
    Esc_Widget->close();
}

void MainWindow::Init()
{
    num_inControl=-1;
    Set_Barrier=0;
    Click_Unit=false;
    is_PrintBlock=false;

    if(Soldiers.size()>0)
    {
        for (int i=0;i<Soldiers.size();i++)
        {
            delete Soldiers[i];

        }
    }
    Soldiers.clear();
    if(Cities.size()>0)
    {
        for (int i=0;i<Cities.size();i++)
        {
            delete Cities[i];

        }
    }
    Cities.clear();
    if(Barriers.size()>0)
    {
        for (int i=0;i<Barriers.size();i++)
        {
            delete Barriers[i];

        }
    }
    Barriers.clear();
    Init_Soldiers();
    Init_Blocks();
    Init_Cities();
    Init_Barriers();
    eventId1=startTimer(200);
}



void MainWindow::Set_WindowState(int _state)
{
    Window_State=_state;
}



void MainWindow::paintEvent(QPaintEvent *event)
{

    if(Window_State==0)
    {
        return;
    }
    QPainter painter(this);
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

    //draw all of the soldiers
    if(Soldiers.size()>0)
    for (int i=0;i<Soldiers.size();i++)
    {
        painter.drawImage(Soldiers[i]->Get_Loc().x,Soldiers[i]->Get_Loc().y,Soldiers[i]->Img,PIC_WIDTH*(Soldiers[i]->Pic_State),PIC_HEIGHT*Soldiers[i]->Get_Line(),PIC_HEIGHT,PIC_WIDTH);
        painter.setPen(QPen(Qt::white,2));
        painter.drawLine(Soldiers[i]->Get_Loc().x+4,Soldiers[i]->Get_Loc().y-8,Soldiers[i]->Get_Loc().x+20,Soldiers[i]->Get_Loc().y-8);
        painter.setPen(QPen(Qt::red,1));
        painter.drawLine(Soldiers[i]->Get_Loc().x+4,Soldiers[i]->Get_Loc().y-8,Soldiers[i]->Get_Loc().x+20*(double((double)Soldiers[i]->Get_Blood()/100.0)),Soldiers[i]->Get_Loc().y-8);

    }

    if(Against_Soldiers.size()>0)
    {
        for (int i=0;i<Against_Soldiers.size();i++)
        {
            painter.drawImage(Against_Soldiers[i]->Get_Loc().x,Against_Soldiers[i]->Get_Loc().y,Against_Soldiers[i]->Img,PIC_WIDTH*(Against_Soldiers[i]->Pic_State),PIC_HEIGHT*Against_Soldiers[i]->Get_Line(),PIC_HEIGHT,PIC_WIDTH);

            painter.setPen(QPen(Qt::white,2));
            painter.drawLine(Against_Soldiers[i]->Get_Loc().x+4,Against_Soldiers[i]->Get_Loc().y-8,Against_Soldiers[i]->Get_Loc().x+20,Against_Soldiers[i]->Get_Loc().y-8);
            painter.setPen(QPen(Qt::red,1));
            painter.drawLine(Against_Soldiers[i]->Get_Loc().x+4,Against_Soldiers[i]->Get_Loc().y-8,Against_Soldiers[i]->Get_Loc().x+20*(double((double)Against_Soldiers[i]->Get_Blood()/100.0)),Against_Soldiers[i]->Get_Loc().y-8);
        }
    }
    painter.setPen(QPen(Qt::black,1));




}


void MainWindow::timerEvent(QTimerEvent * ev)
{
    if(Window_State==0)
    {
        return;
    }
    if(Against_Soldiers.size()==0)
    {
        QMessageBox::warning(this,"Game Over","You Win!");
        killTimer(eventId1);

    }
    if(Soldiers.size()==0)
    {
        QMessageBox::warning(this,"Game Over","You Lose");
        killTimer(eventId1);
    }
    for(int i=0;i<Soldiers.size();i++)
    {
        if(Soldiers[i]->Get_Blood()<=0)
        {
            delete Soldiers[i];
            Soldiers.erase(Against_Soldiers.begin()+i);
        }
        if(Soldiers[i]->is_Action==true)
        {
            if(Soldiers[i]->Pic_State==0)
            {
                atta->play();
                atta->setLoops(1);
            }
            Soldiers[i]->Pic_State++;
            if(Soldiers[i]->Pic_State==Soldiers[i]->Get_Picmax())
            {
                if(Against_Soldiers.size()>0)
                for (int k=0;k<Against_Soldiers.size();k++)
                {
                    if ((((Against_Soldiers[k]->Get_Loc().x==Soldiers[i]->Get_Loc().x-PIC_WIDTH)||(Against_Soldiers[k]->Get_Loc().x==Soldiers[i]->Get_Loc().x+PIC_WIDTH))
                            && ((Against_Soldiers[k]->Get_Loc().y==Soldiers[i]->Get_Loc().y)))
                            ||
                            (((Against_Soldiers[k]->Get_Loc().y==Soldiers[i]->Get_Loc().y-PIC_HEIGHT)||(Against_Soldiers[k]->Get_Loc().y==Soldiers[i]->Get_Loc().y+PIC_HEIGHT))
                                                        && ((Against_Soldiers[k]->Get_Loc().x==Soldiers[i]->Get_Loc().x))))
                    {
                        Against_Soldiers[k]->Kill_Blood(Soldiers[i]->Get_Attack()*(1-double(Against_Soldiers[k]->Get_Armor())));

                        if(Against_Soldiers[k]->Get_Blood()<=0)
                        {
                            isLoad[Against_Soldiers[k]->Get_Loc().x/PIC_WIDTH][Against_Soldiers[k]->Get_Loc().y/PIC_HEIGHT]=1;
                            delete Against_Soldiers[k];
                            Against_Soldiers.erase(Against_Soldiers.begin()+k);
                        }
                        else
                        {
                            Against_Soldiers[k]->To_Attack();
                        }

                    }
                }
                Soldiers[i]->is_Action=false;
                Soldiers[i]->To_Defense();
                Soldiers[i]->To_Static();
            }
        }
        if(Soldiers[i]->is_OnMove==true)
        {
            if(Soldiers[i]->Get_Loc().x>=(Aim.x-16) && Soldiers[i]->Get_Loc().y>=(Aim.y-16)
                    && Soldiers[i]->Get_Loc().x<=(Aim.x+16) && Soldiers[i]->Get_Loc().y>=Aim.y-16)
            {
                Soldiers[i]->Change_Loc(Aim.x,Aim.y);
                Aim.x=0;Aim.y=0;
                Init_SoldierState(Soldiers[i]);
                Soldier_State->popup(Pos);
                Soldiers[i]->is_OnMove=false;
                Soldier_OnMove=false;
                Soldiers[i]->To_Static();
            }
            else
            {

                Soldiers[i]->Pic_State++;
                Soldiers[i]->Pic_State%=Soldiers[i]->Get_Picmax();
                int dx=Aim.x-Soldiers[i]->Get_Loc().x;
                if (dx>=0)
                {
                    Soldiers[i]->Set_Line(2);
                }
                else if(dx<0)
                {
                    Soldiers[i]->Set_Line(1);
                }
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
        if(Against_Soldiers[i]->Get_Blood()<=0)
        {
            delete Against_Soldiers[i];
            Against_Soldiers.erase(Against_Soldiers.begin()+i);
        }

        for (int i=0;i<Against_Soldiers.size();i++)
        {
            if(Against_Soldiers[i]->is_Action==true)
            {
                if(Against_Soldiers[i]->Pic_State==0)
                {
                    atta->play();
                    atta->setLoops(1);
                }
                Against_Soldiers[i]->Pic_State++;
                if(Against_Soldiers[i]->Pic_State==Against_Soldiers[i]->Get_Picmax())
                {
                    if(Soldiers.size()>0)
                    for (int k=0;k<Soldiers.size();k++)
                    {
                        if ((((Soldiers[k]->Get_Loc().x==Against_Soldiers[i]->Get_Loc().x-PIC_WIDTH)||(Soldiers[k]->Get_Loc().x==Against_Soldiers[i]->Get_Loc().x+PIC_WIDTH))
                                && ((Soldiers[k]->Get_Loc().y==Against_Soldiers[i]->Get_Loc().y)))
                                ||
                                (((Soldiers[k]->Get_Loc().y==Against_Soldiers[i]->Get_Loc().y-PIC_HEIGHT)||(Soldiers[k]->Get_Loc().y==Against_Soldiers[i]->Get_Loc().y+PIC_HEIGHT))
                                                            && ((Soldiers[k]->Get_Loc().x==Against_Soldiers[i]->Get_Loc().x))))
                        {
                            Soldiers[k]->Kill_Blood(Against_Soldiers[i]->Get_Attack()*(1-double(Soldiers[k]->Get_Armor())));

                            if(Soldiers[k]->Get_Blood()<=0)
                            {
                                isLoad[Soldiers[k]->Get_Loc().x/PIC_WIDTH][Soldiers[k]->Get_Loc().y/PIC_HEIGHT]=1;
                                delete Soldiers[k];
                                Soldiers.erase(Soldiers.begin()+k);
                            }


                        }
                    }
                    Against_Soldiers[i]->is_Action=false;
                    Against_Soldiers[i]->To_Defense();
                    Against_Soldiers[i]->To_Static();
                }
            }
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

    for(int k=0;k<10;k++)
    {
        int i=Mine_Sol_x[k];
        int j=Mine_Sol_y[k];
        Soldiers.append(new Soldier(PIC_WIDTH*i,PIC_HEIGHT*j,100,100,4,10));
        isLoad[i][j]=2;
        Soldiers[Soldiers.size()-1]->Pic_State=0;
        Soldiers[Soldiers.size()-1]->Set_TySt(1,2);
    }

    for (int k=0;k<9;k++)
    {
        int i=Ag_Sol_x[k];
        int j=Ag_Sol_y[k];
        Against_Soldiers.append(new Soldier(PIC_WIDTH*i,PIC_HEIGHT*j,100,100,4,10));
        isLoad[i][j]=-2;
        Against_Soldiers[Against_Soldiers.size()-1]->Pic_State=0;
        Against_Soldiers[Against_Soldiers.size()-1]->Set_TySt(2,1);
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(Window_State==0)
        return;
    if(event->key()==Qt::Key_Escape)
    {
        Window_State=0;
        Esc_Widget->show();
        killTimer(eventId1);
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(Window_State==0)
    {
        return;
    }
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
            Soldier_OnMove=true;
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

void MainWindow::Init_SoldierState(Soldier * _soldier)
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

    for (int i=12;i<18;i++)
    {
        for (int j=0;j<4;j++)
        {
            isLoad[i][j]=3;
        }
    }
    Cities.append(new City(12,0,18,4,":/images/Res/City_north.png"));


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
    if(Window_State==0)
    {
        return;
    }
    if (Soldier_OnMove==false)
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
}


void MainWindow::on_actionFire_triggered()
{
    if(Window_State==0)
    {
        return;
    }
    if(Soldier_OnMove==false)
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
}


void MainWindow::on_actionWater_triggered()
{
    if(Window_State==0)
    {
        return;
    }
    if(Soldier_OnMove==false)
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
}



void MainWindow::Init_Barriers()
{
    for (int i=0;i<20;i++)
    {
        int b_x=QRandomGenerator::global()->generate() % 30;
        int b_y=QRandomGenerator::global()->generate() % 19+1;
        int type=QRandomGenerator::global()->generate() % 3+1;
        if(isLoad[b_x][b_y]==1)
        {
            Barriers.append(new Barrier(b_x,b_y,1,1,type));
            Init_Blocks();
            is_PrintBlock=false;
            isLoad[b_x][b_y]=3+type;
        }
    }

}
