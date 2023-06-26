#include "num_item.h"

numItem::numItem(){
    this->setPixmap(QPixmap(":/num/pic/num0.png"));
}


void numItem::setNum(int a){
   
    QString path(":/num/pic/num");
    path +=QString::number(a);
    path += ".png";
    QPixmap pix(path);
    this->setPixmap(pix);

}
