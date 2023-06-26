#include "selfinputmain.h"
#include "ui_selfinputmain.h"


selfinputmain::selfinputmain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::selfinputmain)
{
    ui->setupUi(this);
    this->setWindowTitle("自定义");
    this->setWindowIcon(QIcon(":/icon/img/icon.ico"));
    ui ->selfinputconfirm ->setStyleSheet("background:lightblue");
    ui ->selfinputcancel ->setStyleSheet("background:lightblue");
    setMaxMine();
}

selfinputmain::~selfinputmain()
{
    delete ui;
}

void selfinputmain::on_selfinputcancel_clicked()
{
    this->hide();
    //触发cancelSignal信号
    emit cancelSignal();

}


void selfinputmain::on_selfinputconfirm_clicked()
{
    this->hide();
    emit inputSignal(ui->rowinput->value(),ui->lineinput->value(),ui->mineinput->value());
}

//背景图片

void selfinputmain::paintEvent(QPaintEvent *event)
{

    // 加载图片资源，并缩放
    QPixmap pixmap(":/image/c4.jpg");
    pixmap = pixmap.scaled(700, 600);             //图片大小

    // 创建 QPainter 对象，开始动态绘制
    QPainter painter(this);
    painter.drawPixmap(0, 0, 700, 600, pixmap);    //空间大小
}



void selfinputmain::on_lineinput_valueChanged(int arg1)
{
    setMaxMine();
}


void selfinputmain::on_rowinput_valueChanged(int arg1)
{
    setMaxMine();
}

//控制雷数
void selfinputmain::setMaxMine()
{
    this->ui->mineinput->setMaximum(ui->lineinput->value()*ui->rowinput->value()*0.9);
}
