#include "escwidget.h"
#include "ui_escwidget.h"
#include <QMessageBox>
EscWidget::EscWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EscWidget)
{
    ui->setupUi(this);
    setStyleSheet("QPushButton{"
                  "border: 1px solid black;"
                  "border-radius: 5px;"
                  "background-color:#F0E68C;"
                  "color:red;"
                  "font-size:20px;"
                  "text-align:mid;"
                  "font-family:STXingkai;"
                  "font-weight:bold;"
                  "}"
                    );
    setWindowFlags(Qt::Widget|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    connect(ui->StartBtn,SIGNAL(clicked()),this,SLOT(STBtn_Click()));
    connect(ui->ContinueBtn,SIGNAL(clicked()),this,SLOT(COBtn_Click()));
}

EscWidget::~EscWidget()
{
    delete ui;
}

void EscWidget::STBtn_Click()
{
    emit StartBtn_Clicked();
}

void EscWidget::COBtn_Click()
{
    emit ContinueBtn_Clicked();
}

void EscWidget::on_IntroBtn_clicked()
{
    QMessageBox::warning(this,"Introduction","Producted by Ben Qingwei\nAll rignts Reserved\nYou can remove soldiers by clicking on them\nYou will win if you kill all the against_soldiers\nThere are two different parts at all.");
}

