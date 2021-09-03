#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    int eventId1;
    int Window_State=0;
    QVector<Soldier*>Soldiers;



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
