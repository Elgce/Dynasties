#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Heads.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent * event);
    void timerEvent(QTimerEvent *);
    void Set_Bkg(QPixmap);
    void Init_Soldiers();
    void mousePressEvent(QMouseEvent* event);
    void init_SoldierState(Soldier *);
    QPixmap bkg_map;

    int eventId1;
    int Window_State=0;
    int isLoad[WIDTH_NUM][HEIGHT_NUM];//0:wait for use; 1:can reach; 2:my_soldiers; -2:against_soldiers; 3:cities
    bool Clor_Block[WIDTH_NUM][HEIGHT_NUM];
    QVector<Soldier*>Soldiers;
    QVector<Soldier*>Against_Soldiers;
    QVector<City*>Cities;
    void Init_Cities();
    void Init_Blocks();
public slots:

signals:

private:
    Ui::MainWindow *ui;
    bool Click_Unit=false;
    bool is_PrintBlock=false;
    int num_inControl=-1;
    QMenu * Soldier_State;
};
#endif // MAINWINDOW_H
