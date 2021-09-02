#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "Const.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1280,640);
    curIndex=0;
    eventId1=startTimer(100);
    Initpixmap();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(100,100,pixmap,64*curIndex,0,64,64);
}

void MainWindow::timerEvent(QTimerEvent * ev)
{
    curIndex++;
    if(curIndex>=5)
    {
        curIndex=0;
    }
    repaint();
}

void MainWindow::Initpixmap()
{
        QString fileName=QString(":/images/Res/Red.bmp");
        qDebug("%s\n",qPrintable(fileName));
        pixmap.load(fileName);
}
