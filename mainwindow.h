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
    void keyPressEvent(QKeyEvent *event);
    void Init_SoldierState(Soldier *);
    void Init_SoldierDetail(Soldier *);
    void Init_Barriers();
    QPixmap bkg_map;
    QSound * bkm;
    QSound * atta;
    QMediaPlayer* mp4_player;
    QVideoWidget* mp4_videoWidget;
    QDateTime time;
    int Barrier_Added=0;
    int add_num=0;
    int Mine_Sol_x[10]={13,12,11,10,9,10,9,10,11,12};
    int Mine_Sol_y[10]={10,9,8,8,9,10,11,12,12,11};
    int Ag_Sol_x[9]={17,18,19,20,21,20,19,18,19};
    int Ag_Sol_y[9]={10,9,8,9,10,11,12,11,10};
    int eventId1;
    int Window_State=0;
    int isLoad[WIDTH_NUM][HEIGHT_NUM];//0:wait for use; 1:can reach; 2:my_soldiers; -2:against_soldiers; 3:cities
    bool Clor_Block[WIDTH_NUM][HEIGHT_NUM];
    bool is_BossAlive=false;
    QVector<Soldier*>Soldiers;
    QVector<Soldier*>Against_Soldiers;
    QVector<City*>Cities;
    QVector<Barrier*>Barriers;
    Location Aim;
    Soldier* Npc;
    QImage Vic_Pic;
    void Set_MenuStyle(QMenu *);
    bool Soldier_OnMove=false;
    void Init_Cities();
    void Init_Blocks();
    void Init();
    void Init_2();
    EscWidget * Esc_Widget;

public slots:
    void Set_WindowState(int);
    void Start_Window();
    void Continue_Window();
signals:

private slots:


    void on_actionMount_triggered();

    void on_actionFire_triggered();

    void on_actionWater_triggered();

    void on_actionToWin_triggered();

    void on_actionToFail_triggered();

private:
    Ui::MainWindow *ui;
    bool Click_Unit=false;
    int Set_Barrier=0;// 0: not start   1: mount  2: fire  3: water
    bool is_PrintBlock=false;
    bool has_VideoPlayed=false;
    int num_inControl=-1;
    QMenu * Soldier_State;
    QMenu * Soldier_Detail;
    QPoint Pos;
};
#endif // MAINWINDOW_H
