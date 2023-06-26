#include "mine_scene.h"

mineScene::mineScene(QObject *parent) : QGraphicsScene(parent)
{

    //initMineScene();

    //initSignals();
}
void mineScene::initSignals()
{

    for(int i=1;i<=MAX_WIDTH;i++)
        for(int j=1;j<=MAX_HEIGHT;j++)
        {
            connect(this->mines[i][j],&mineItem::stepMinesSignals,this,&mineScene::gameOver);
            connect(this->mines[i][j],&mineItem::stepNoneSignals,this,&mineScene::recursionOpen);
            connect(this->mines[i][j],&mineItem::doubleClickSignals,this,&mineScene::doubleClick);
            connect(this->mines[i][j],&mineItem::firstSignal,this,&mineScene::getRandomMines);
            connect(this->mines[i][j],&mineItem::checkVictorySignals,this,&mineScene::checkVictory);
            connect(this->mines[i][j],&mineItem::markChangeSignals,this,&mineScene::markChange);

}

}

void mineScene::initMineScene()
{

    this->clear();

    for(int i=1;i<=MAX_WIDTH;i++)
        for(int j=1;j<=MAX_HEIGHT;j++)
        {
            mines[i][j] = new mineItem;
            mines[i][j] ->setPos(i*20,j*20);
            mines[i][j] ->setColAndRow(i,j);
        }

    for(int i=1;i<=width;i++)
        for(int j=1;j<=height;j++)
        {
            this->addItem(mines[i][j]);
            mines[i][j]->updateItem();
        }
    emit AllInitialSignals(0);
}

void mineScene::getRandomMines(int row,int col)
{
    if(!isFirst)return;
    this -> setFirst(false);

    int mineNumTemp=0;
    while(mineNumTemp<this->minesNum){ //随机数生成地雷位置

        int x=QRandomGenerator::global()->bounded(width)+1;
        int y=QRandomGenerator::global()->bounded(height)+1;
        //利用QRandomGenerator类的bounded()函数
        //生成两个范围在0到宽度（width）和高度（height）之间的随机整数x和y作为地雷的位置。

        if(!this->mines[x][y]->getIsMine() && !(row==x && col==y))//第一个点击的位置不能是地雷
        {
            this->mines[x][y]->setMine(true);
            mineNumTemp++;
        }
    }
    int xx,yy,roundMinesTemp;
    //临时变量便于临时计算
    int dx[8]={1,1,1,0,0,-1,-1,-1};
    int dy[8]={-1,0,1,-1,1,-1,0,1};

    for(int i=1;i<=width;++i){//设置周围雷数
        for(int j=1;j<=height;++j){

            roundMinesTemp=0;
            for(int k=0;k<8;++k){
                xx=i+dx[k];
                yy=j+dy[k];
                if(1<=xx&&xx<=width&&1<=yy&&yy<=height){
                    if(this->mines[xx][yy]->getIsMine())roundMinesTemp++;//这里的numOfMines是临时变量

                }
            }

            mines[i][j]->setRoundMines(roundMinesTemp);

        }
    }

    emit firstTimeSignals();
}

void mineScene::gameOver(int row,int col)
{
    emit gameVictorySignals(1);
    for(int i=1;i<=width;++i){//显示其余的地雷
        for(int j=1;j<=height;++j){
            if(mines[i][j]->getIsMine()&&!(i==row&&j==col)){
                mines[i][j]->setOpened(true);
            }
        }
    }

    QMessageBox msg;
    msg.setWindowTitle("扫雷");
    msg.setWindowIcon(QIcon(":/icon/img/icon.ico"));
    msg.setIcon(QMessageBox::Critical);
    msg.setText("游戏结束！");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.exec();
    emit restartGame();
}

void mineScene::recursionOpen(int row,int col){
    mines[row][col]->setOpened(true);//模拟点击

    if(mines[row][col]->getRoundMines()!=0)return;//有数字的方块就不展开了

    int xx,yy;
    int dx[8]={1,1,1,0,0,-1,-1,-1};
    int dy[8]={-1,0,1,-1,1,-1,0,1};
    for(int i=0;i<8;++i){
        xx=row+dx[i];
        yy=col+dy[i];
        if(1<=xx&&xx<=width&&1<=yy&&yy<=height && !mines[xx][yy]->isOpened()){
            recursionOpen(xx,yy);
        }
    }
}

void mineScene::doubleClick(int row,int col){
    int flags = 0, rightFlags = 0, temps = 0, state = 0; // state表示是否标错,1为标错
    int xx, yy;
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; ++i)
    {
        xx = row + dx[i];
        yy = col + dy[i];
        if (1 <= xx && xx <= width && 1 <= yy && yy <= height && !mines[xx][yy]->isSweeped())
        {
            if (mines[xx][yy]->getIsMine())
                temps++;
            if (mines[xx][yy]->isFlaged())
                flags++;
            if (mines[xx][yy]->isFlaged() && mines[xx][yy]->getIsMine())
                rightFlags++;
        }
    }

    if (flags == temps)
    {
        if (rightFlags < flags)
            state = 1;
        for (int i = 0; i < 8; ++i)
        {
            xx = row + dx[i];
            yy = col + dy[i];
            if (1 <= xx && xx <= width && 1 <= yy && yy <= height && !mines[xx][yy]->isSweeped() && !mines[xx][yy]->isFlaged())
            {
                if (state == 0)
                    mines[xx][yy]->leftClick();
                else if (state == 1 && mines[xx][yy]->getIsMine())
                    mines[xx][yy]->leftClick();
            }
        }
    }
}

void mineScene::checkVictory(){
    int block=0;
    for(int i=1;i<=width;++i){
        for(int j=1;j<=height;++j){
            if(mines[i][j]->isOpened()&&!mines[i][j]->getIsMine()){
                block++;
            }
        }
    }
    if(block==(height*width - minesNum)){
        emit gameVictorySignals(2);

        QMessageBox msg;
        msg.setWindowTitle("扫雷");
        msg.setWindowIcon(QIcon(":/icon/img/icon.ico"));
        msg.setIcon(QMessageBox::Information);
        msg.setText("恭喜你成功了！");
        msg.setStandardButtons(QMessageBox::Yes);
        msg.exec();
        emit restartGame();
    }
}

void mineScene::markChange(int x)
{
    emit ChangeMarkSignals(x);
}




