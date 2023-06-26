#include "num_scene.h"

numScene::numScene(QObject *parent) : QGraphicsScene(parent)
{

}

void numScene::setNumer(int num){
    if(num>=0){
        this->clear();

        int hundred,ten,one;//百位,十位,个位
        hundred=num/100;
        ten=(num%100)/10;
        one=num%10;


        hunItem=new numItem;
        tenItem=new numItem;
        oneItem=new numItem;

        hunItem->setPos(1,0);
        tenItem->setPos(20,0);
        oneItem->setPos(39,0);
        hunItem->setNum(hundred);
        tenItem->setNum(ten);
        oneItem->setNum(one);
        //将图形项添加到场景中
        this->addItem(hunItem);
        this->addItem(tenItem);
        this->addItem(oneItem);
    }
}
