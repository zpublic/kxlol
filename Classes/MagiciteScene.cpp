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

    this->addChild(LayerColor::create(Color4B(0xDE, 0xDF, 0xDE, 0x7F)));
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
