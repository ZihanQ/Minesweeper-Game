#include "time_scene.h"

timeScene::timeScene()
{
    timer=new QTimer;
}
void timeScene::updateTimeScene()
{
    this->setNumer(rest_time);
    if(this->rest_time==0)
    {
        
        QMessageBox msg;
        msg.setText("很抱歉,你没有获胜!");
        msg.setIcon(QMessageBox::Critical);
        msg.setStandardButtons(QMessageBox::Yes);
        msg.exec();
        emit restart();
    }
    else
        rest_time--;
}
