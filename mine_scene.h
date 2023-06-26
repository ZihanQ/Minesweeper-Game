#ifndef MINESCENE_H
#define MINESCENE_H

#include <QObject>
#include<QGraphicsScene>
#include <QRandomGenerator>
#include <QMessageBox>
#include "mine_item.h"


class mineScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit mineScene(QObject *parent = nullptr);
    void initMineScene();
    void initSignals();
    void setFirst(bool s){isFirst=s;}
    void setMap(int w,int h,int m){width=w,height=h,minesNum=m;}

signals:
    void gameOverSignals(int emotion);
    void gameVictorySignals(int emotion);
    void ChangeMarkSignals(int x);
    void AllInitialSignals(int emotion);
    void restartGame();
    void firstTimeSignals();

public slots:
    void gameOver(int row,int col);
    void recursionOpen(int row,int col);
    void doubleClick(int row,int col);
    void markChange(int x);
    void getRandomMines(int row,int col);
    void checkVictory();

private:
    static const int MAX_HEIGHT=24;
    static const int MAX_WIDTH=30;

    mineItem *mines[MAX_WIDTH+1][MAX_HEIGHT+1];
    bool isFirst=true;
    int height=9;
    int width=9;
    int minesNum=10;

};

#endif // MINESCENE_H
