#ifndef MINEITEM_H
#define MINEITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QStyleOptionGraphicsItem>


class mineItem :public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    mineItem();
    void setColAndRow(int r,int c){row=r,col=c;}
    void setSweeped(bool s){sweeped=s;updateItem();}
    void setQuestioned(bool s){questioned=s;updateItem();}
    void setFlaged(bool s){flaged=s;updateItem();}
    void setOpened(bool s){opened=s;updateItem();}
    void setMine(bool s){isMine=s;}
    void setRoundMines(int x){roundMines=x;}
    bool getIsMine(){return isMine;}
    bool isSweeped (){return sweeped;}
    bool isFlaged(){return flaged;}
    bool isQuestioned(){return questioned;}
    bool isOpened(){return opened;}
    int getRoundMines(){return roundMines;}
    void leftClick();//左键
    void updateItem();//更新显示;

signals:
    void firstSignal(int r,int c);
    void stepMinesSignals(int r,int c);
    void stepNoneSignals(int r,int c);
    void doubleClickSignals(int r,int c);
    void markChangeSignals(int x);
    void checkVictorySignals();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;

private:
    int row;
    int col;//行、列
    int roundMines=0;
    bool sweeped=false;//初始状态
    bool flaged=false;//已经被标雷
    bool opened=false;//已经被打开
    bool isMine=false;//是地雷
    bool bomb=false;//是否踩雷

     //标记是否为问号
    bool questioned=false;
};

#endif // MINEITEM_H
