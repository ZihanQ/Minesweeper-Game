#include "mineshow_scene.h"

mineShowScene::mineShowScene()
{

}

void mineShowScene::initMineScene(int mineNum)
{
    rest_mine=mineNum;
    this->setNumer(rest_mine);
}

void mineShowScene::updateMineScene(int change)
{
    //1增多,0减少
    if(change==1) rest_mine++;
    else if(change==0) rest_mine--;
    this->setNumer(rest_mine);
}
