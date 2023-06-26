#ifndef SELFINPUTMAIN_H
#define SELFINPUTMAIN_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QPixmap>

namespace Ui {
class selfinputmain;
}

class selfinputmain : public QMainWindow
{
    Q_OBJECT

public:
    explicit selfinputmain(QWidget *parent = nullptr);
    ~selfinputmain();

    //绘制图片
    void paintEvent(QPaintEvent *event);
    //设置标签显示最大雷数
    void setMaxMine();

private slots:
    void on_selfinputcancel_clicked();

    void on_selfinputconfirm_clicked();

    void on_lineinput_valueChanged(int arg1);

    void on_rowinput_valueChanged(int arg1);

signals:
    //定义信号
    void cancelSignal();
    void inputSignal(int line,int row,int mine);

private:
    Ui::selfinputmain *ui;
};

#endif // SELFINPUTMAIN_H
