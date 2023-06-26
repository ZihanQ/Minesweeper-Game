#ifndef NUMSCENE_H
#define NUMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "num_item.h"

class numScene : public QGraphicsScene//它本身就继承于QObject
{
    Q_OBJECT
public:
    explicit numScene(QObject *parent = nullptr);
public:
    void setNumer(int num);//设置显示数字
private:
    numItem *hunItem,*tenItem,*oneItem;
};

#endif // NUMSCENE_H
