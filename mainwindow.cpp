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
    QPixmap pixmap(":/images/Res/bkg.png");
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    eventId1=startTimer(50);
    for (int i=0;i<5;i++)
    {
        Soldiers.append(new Soldier(64*i,64,100,100,5));
        Soldiers[i]->Pic_State=0;
        Soldiers[i]->Set_TySt(i,0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (int i=0;i<5;i++)
    {
        painter.drawImage(Soldiers[i]->Get_Loc().x,Soldiers[i]->Get_Loc().y,Soldiers[i]->Img,64*Soldiers[i]->Pic_State,64*Soldiers[i]->Get_Type(),64,64);
    }
}

void MainWindow::timerEvent(QTimerEvent * ev)
{
    if (Window_State==0)
    {
        for(int i=0;i<5;i++)
        {
            Soldiers[i]->Pic_State++;
            if (Soldiers[i]->Pic_State==Soldiers[i]->Get_Picmax())
                Soldiers[i]->Pic_State=0;
            repaint();
        }
    }
}


