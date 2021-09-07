#ifndef ESCWIDGET_H
#define ESCWIDGET_H

#include <QWidget>

namespace Ui {
class EscWidget;
}

class EscWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EscWidget(QWidget *parent = nullptr);
    ~EscWidget();

public slots:
    void STBtn_Click();
    void COBtn_Click();
signals:
    void StartBtn_Clicked();
    void ContinueBtn_Clicked();
public:
    Ui::EscWidget *ui;
private slots:
    void on_IntroBtn_clicked();
};

#endif // ESCWIDGET_H
