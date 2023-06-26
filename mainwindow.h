#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//包含自定义的文件
#include <selfinputmain.h>
#include <QMessageBox>
#include <QDebug>
#include <qobject.h>
#include <QPainter>
#include <QPixmap>
#include "minewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //绘制图片
    void paintEvent(QPaintEvent *event);

private slots:


    void on_easyButton_clicked();

    void on_middleButton_clicked();

    void on_hardButton_clicked();

    void on_selfButton_clicked();

    void dataSet(int line,int row,int mine);//自定义
    void test(int line,int row,int mine);//自定义,用于测试
    void startGame(int line,int row,int mine);
    void restartGame();
    void on_message_clicked();

signals:
    void dataSignal(int line, int row, int mine);
    void startSignals(int line, int row, int mine);

private:
    Ui::MainWindow *ui;

    //自定义取消返回主界面
    selfinputmain *setting;

    mineWindow *myMain;
};
#endif // MAINWINDOW_H
