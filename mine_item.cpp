#include "mine_item.h"

mineItem::mineItem()
{
    {
        this->setFlag(QGraphicsItem::ItemIsSelectable);
        this->setAcceptedMouseButtons(Qt::AllButtons);
        updateItem();
    }
}

void mineItem::leftClick(){
    if(!opened&&!flaged){
       //内联函数包含updateItem;
        setOpened(true);
        if(isMine){
            bomb=true;
            updateItem();
            emit stepMinesSignals(row,col);
        }
        else if(roundMines==0)emit stepNoneSignals(row,col);
    }
}

void mineItem::mousePressEvent(QGraphicsSceneMouseEvent *event){


    if(event->buttons()==Qt::LeftButton)
    {
        emit firstSignal(row,col);
    }

    if(event->buttons()==(Qt::LeftButton|Qt::RightButton)){

        if(opened&&roundMines!=0){//已被挖掘且有数字
            emit doubleClickSignals(row,col);
        }

    }else if(event->button()==Qt::LeftButton){//左键点击 
        leftClick();
    }else if(event->button()==Qt::RightButton){

        if(!opened){

            if(flaged)
            {
                emit markChangeSignals(1);
                setFlaged(false);
                setQuestioned(true);
            }
            else if(questioned)
            {
                setQuestioned(false);
                setFlaged(false);
                setSweeped(true);
            }
            else
            {
                emit markChangeSignals(0);
                setFlaged(true);
                setSweeped(false);
                setQuestioned(false);
            }
        }
    }
    emit checkVictorySignals();
}

void mineItem::updateItem(){
    if(bomb)this->setPixmap(QPixmap(":/mine/pic/mine_step.jpg"));
    //如果踩雷，显示红色地雷
    else if(!opened)
    //未被打开，显示标记或空白 或者问号
    {
        if(flaged) this->setPixmap(QPixmap(":/mine/pic/flag.jpg"));
        else if(questioned) this->setPixmap(QPixmap(":/mine/pic/question.jpg"));
        else this->setPixmap(QPixmap(":/mine/pic/notSweep.jpg"));
    }
    else if(isMine){
        this->setPixmap(QPixmap(":/mine/pic/mine.jpg"));
    }else{
        QString path(":/mine/pic/mine");
        path += QString::number(roundMines);
        path += ".jpg";
        QPixmap pix(path);
        this->setPixmap(pix);
    }
}
