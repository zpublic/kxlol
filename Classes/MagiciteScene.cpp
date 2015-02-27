#include "MagiciteScene.h"
#include "MagiciteGameLayer.h"
int MagiciteScene::LevelNumber = 0;

USING_NS_CC;

bool MagiciteScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    this->addChild(MagiciteGameLayer::create());

    return true;    
}

void MagiciteScene::setLevel(int level)
{
    LevelNumber = level;
}

int MagiciteScene::getLevel()
{
    return LevelNumber;
}
