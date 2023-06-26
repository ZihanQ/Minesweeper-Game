#ifndef MINEWINDOW_H
#define MINEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QGraphicsItem>
#include <QTimer>
#include "mine_scene.h"
#include "time_scene.h"
#include "look_item.h"
#include "mineshow_scene.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class mineWindow; }
QT_END_NAMESPACE

class mineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mineWindow(QWidget *parent = nullptr);
    ~mineWindow();



public slots:
    void initializeGame(int h,int w,int m);

private:
    Ui::mineWindow *mineUi;

    mineScene *scene;
    QGraphicsScene *lookScene;//表情
    timeScene *timescene;//剩余时间(从999秒倒计时)
    mineShowScene *mineShowscene;//剩余地雷数(全部地雷数-已标记数)
    lookItem *lkItem;


public:
    //QPushButton *minesButton[30][30];

    //void initButton(void);
private:
    //QPushButton *restartButton;
    //QPushButton *tryButton;


private slots:

    void restartWindow(void);
signals:
    void getMinesNumSignal(int m);
    void toMainSignals();
};
#endif // MAINWINDOW_H
