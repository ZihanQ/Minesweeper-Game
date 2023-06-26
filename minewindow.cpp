#include "minewindow.h"
#include "ui_minewindow.h"

mineWindow::mineWindow(QWidget *parent) :
    QMainWindow(parent),
    mineUi(new Ui::mineWindow)
{

    mineUi->setupUi(this);


    this->scene = new mineScene;
    this->lookScene=new QGraphicsScene;
    this->mineShowscene=new mineShowScene;
    this->timescene=new timeScene;

    this->setWindowTitle("扫雷游戏");
    this->setWindowIcon(QIcon(":/icon/img/icon.ico"));


    //设置表情
    lkItem=new lookItem;
    this->lookScene->addItem(lkItem);
    connect(lkItem,&lookItem::refresh,this,&mineWindow::restartWindow);
    connect(this->scene,&mineScene::gameVictorySignals,lkItem,&lookItem::setLook);
    connect(this->scene,&mineScene::gameOverSignals,lkItem,&lookItem::setLook);
    connect(this->scene,&mineScene::AllInitialSignals,lkItem,&lookItem::setLook);
    this->mineUi->graphicsView_look->setScene(this->lookScene);
    //待定,标雷信号
    connect(this->scene,&mineScene::ChangeMarkSignals,this->mineShowscene,&mineShowScene::updateMineScene);
    //給顯示屏初始化地雷數
    connect(this,&mineWindow::getMinesNumSignal,this->mineShowscene,&mineShowScene::initMineScene);

    connect(this->scene,&mineScene::restartGame,this,&mineWindow::restartWindow);

    this->mineUi->graphicsView->setGeometry(0,30,100,100);
    this->mineUi->graphicsView->setScene(this->scene);

    //去掉滚动框
    this->mineUi->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->mineUi->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    //开始计时
    connect(this,&mineWindow::getMinesNumSignal,this->timescene,&timeScene::refreshTimer);
    connect(this->scene,&mineScene::firstTimeSignals,this->timescene,&timeScene::startTimer);
    connect(this->timescene->timer,&QTimer::timeout,this->timescene,&timeScene::updateTimeScene);
    this->mineUi->graphicsView_time->setScene(this->timescene);
    this->mineUi->graphicsView_mine->setScene(this->mineShowscene);



}

void mineWindow::initializeGame(int w,int h,int m)
{

    this->show();
     emit getMinesNumSignal(m);
    //设置表情,剩余时间,剩余地雷
    this->mineUi->graphicsView_mine->setGeometry(0,0,60,30);
    this->mineUi->graphicsView_time->setGeometry(20*w+5-60,0,60,30);
    this->mineUi->graphicsView_look->setGeometry((20*w+5)/2-15,0,30,30);
    //设置地图

    this->scene->setMap(w,h,m);
    this->scene->initMineScene();

    this->scene->initSignals();

    this->setFixedSize(20*w+5,20*h+5+50);
    this->mineUi->graphicsView->setFixedSize(20*w+5,20*h+5);


}

void mineWindow::restartWindow()
{
    this->scene->setFirst(true);

    this->hide();
    emit toMainSignals();

}

mineWindow::~mineWindow()
{
    delete mineUi;
}


