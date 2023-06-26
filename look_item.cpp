#include "look_item.h"

lookItem :: lookItem()
{
    setLook(0);
}

void lookItem::setLook(int type)
{
    QString path(":/look/pic/");
    if(type==0) path+="happy";
    else if(type==1) path+="unhappy";
    else if(type==2) path+="victory";
    path+=".png";
    QPixmap pix(path);
    this->setPixmap(pix);
}

void lookItem::mousePressEvent(QGraphicsSceneMouseEvent * event){
    setLook(0);
    emit refresh();
}
