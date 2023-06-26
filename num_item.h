#ifndef NUMITEM_H
#define NUMITEM_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>

//同时设置地雷数和计数器的时间
class numItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    numItem();
    void setNum(int a);
};

#endif // NUMITEM_H
