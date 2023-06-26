#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //初始化
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("扫雷游戏");
    this->setWindowIcon(QIcon(":/icon/img/icon.ico"));
    myMain=new mineWindow;
    connect(myMain,&mineWindow::toMainSignals,this,&MainWindow::restartGame);

    connect(this,&MainWindow::startSignals,myMain,&mineWindow::initializeGame);
    //改变按钮背景色
    ui ->easyButton ->setStyleSheet("background:lightblue");
    ui ->middleButton ->setStyleSheet("background:lightblue");
    ui ->hardButton ->setStyleSheet("background:lightblue");
    ui ->selfButton ->setStyleSheet("background:lightblue");
    ui ->message ->setStyleSheet("background:lightyellow");
    //dataSignal信号激发
    connect(this,&MainWindow::dataSignal,this,&MainWindow::test);




    //开始游戏

    connect(this,&MainWindow::dataSignal,this,&MainWindow::startGame);

}

//析构函数

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_easyButton_clicked()
{
    emit dataSignal(9,9,10);
    this->hide();
}


void MainWindow::on_middleButton_clicked()
{
    emit dataSignal(16,16,40);
    this->hide();
}


void MainWindow::on_hardButton_clicked()
{
    emit dataSignal(16,30,99);
    this->hide();
}


void MainWindow::on_selfButton_clicked()
{
    //隐藏原有界面
    this ->hide();
    //在堆中创建对象
    selfinputmain *c = new selfinputmain();
    c->show();

    //按取消键
    connect(c,&selfinputmain::cancelSignal,this,&MainWindow::show);
    connect(c,&selfinputmain::inputSignal,this,&MainWindow::dataSet);

}

void MainWindow::dataSet(int l,int r,int m)
{

    int line = l;
    int row = r;
    int mine = m;
    emit dataSignal(row,line,mine);
}

void MainWindow::startGame(int line,int row,int mine)
{
    emit startSignals(row,line,mine);
}

void MainWindow::restartGame()
{
    this->show();
    //delete aaa;
}

void MainWindow::test(int l,int r,int m)
{
    qDebug() << "line:" << l << ", row:" << r << ", mine:" << m;
}


//背景图片

void MainWindow::paintEvent(QPaintEvent *event)
{

    // 加载图片资源，并缩放
    QPixmap pixmap(":/image/a2.jpg");
    pixmap = pixmap.scaled(700, 600);             //图片大小

    // 创建 QPainter 对象，开始动态绘制
    QPainter painter(this);
    painter.drawPixmap(0, 0, 700, 600, pixmap);    //空间大小
}

void MainWindow::on_message_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle("开发相关");
    msg.setWindowIcon(QIcon(":/icon/img/icon.ico"));
    msg.setIcon(QMessageBox::Information);
    msg.setText("开发者:\n邱梓涵\n王子轩\n范家玮.\n祝您玩得开心=）");
    msg.exec();
}



