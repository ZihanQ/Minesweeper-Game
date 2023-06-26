#ifndef MINESHOWSCENE_H
#define MINESHOWSCENE_H

#include<QObject>
#include <QGraphicsScene>
#include "num_scene.h"
#include <QMessageBox>

class mineShowScene:public numScene
{
    Q_OBJECT
public:
    mineShowScene();
public slots:
    void initMineScene(int mineNum);
    void updateMineScene(int change);
    //datasignal信号,行列雷
private:
    int rest_mine=10;
};

#endif // MINESHOWSCENE_H
