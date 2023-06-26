#ifndef TIMESCENE_H
#define TIMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "num_scene.h"
#include <QMessageBox>
class timeScene :public numScene
{
    Q_OBJECT
public:
    timeScene();
    QTimer *timer;
public slots:
    //未开始点击雷区的初始状态
    void refreshTimer(){rest_time=999;this->setNumer(rest_time);}
    //开始计时
    void startTimer(){rest_time=999;timer->start(1000);updateTimeScene();}
    void updateTimeScene();

private:
    int rest_time=999;
signals:
    void restart();
};

#endif // TIMESCENE_H
