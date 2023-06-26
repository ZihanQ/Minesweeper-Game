#ifndef LOOKITEM_H
#define LOOKITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QString>

class lookItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    lookItem();
    //默认是笑脸
    void setLook(int type);

protected:
           //进行虚函数的重写
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

signals:
    void refresh();

};
#endif // LOOKITEM_H
