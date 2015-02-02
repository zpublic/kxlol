#include "MagiciteGameLayer.h"

USING_NS_CC;

MagiciteGameLayer::MagiciteGameLayer()
{

}

MagiciteGameLayer::~MagiciteGameLayer()
{

}

bool MagiciteGameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MagiciteGameLayer::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MagiciteGameLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->schedule(schedule_selector(MagiciteGameLayer::update));

    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    TMXTiledMap* tiled = TMXTiledMap::create("img\\Magicite\\map\\test.tmx");
    _background = MagiciteGameMap::create(tiled);
    TMXObjectGroup* game = tiled->getObjectGroup("game");
    this->addChild(_background);

    _player = MagiciteGamePlayer::create("img\\Magicite\\player\\player_stop.png");
    ValueMap playerMap = game->getObject("player");
    Vec2 playerPos = Vec2(playerMap.at("x").asFloat(), playerMap.at("y").asFloat());
    _player->setPosition(playerPos);
    
    ValueMap endMap = game->getObject("finish");
    Size endSize = Size(endMap.at("width").asFloat(), endMap.at("height").asFloat());
    Vec2 endPos = Vec2(endMap.at("x").asFloat() + endSize.width / 2, endMap.at("y").asFloat() + endSize.height / 2);
    auto endCube = MagiciteGamePhySprite::create();
    endCube->_SpriteType = MagiciteGamePhySprite::T_End;
    endCube->setContentSize(endSize);
    endCube->setPosition(endPos);

    _phyLayer = MagiciteGamePhyLayer::create(
        &_enemyManager,
        Size(_background->getBackSize().width, _visibleSize.height),
        [&](){MagiciteGameOver::Over(this); },
        [&](){MagiciteGameWin::Win(this); });
    _phyLayer->addPhysicSprite(_player, false);
    _phyLayer->addPhysicSprite(endCube, true);

    this->addChild(_phyLayer,1);

    this->runAction(Follow::create(_player, Rect(0, 0, _background->getBackSize().width, _visibleSize.height)));

    _move_left = false;
    _move_right = false;

    /*----------------------------------init finish---------------------------------------------------*/

    auto enemyA = _enemyManager.createEnemy(
        Vec2(_visibleSize.width / 3, _visibleSize.height / 3), true);
    auto enemyB = _enemyManager.createEnemy(
        Vec2(_visibleSize.width / 3 * 2, _visibleSize.height / 3), false);
    _phyLayer->addPhysicSprite(enemyA, false);
    _phyLayer->addPhysicSprite(enemyB, false);
    
    TMXObjectGroup* ground = tiled->getObjectGroup("physics");
    ValueVector VV = ground->getObjects();

    for (auto it = VV.begin(); it != VV.end(); ++it)
    {
        Value obj = *it;
        ValueMap vm = obj.asValueMap();
        if (vm.at("type").asString() == "cube")
        {
            float x = vm.at("x").asFloat();
            float w = vm.at("width").asFloat();
            float h = vm.at("height").asFloat();
            float y = vm.at("y").asFloat();
            auto node = MagiciteGamePhySprite::create();
            node->setPosition(Vec2(x, y));
            node->setContentSize(Size(w, h));
            node->setAnchorPoint(Point::ZERO);
            _phyLayer->addPhysicSprite(node,true);
        }
    }

    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE :
        MagiciteGamePause::Pause(this);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        _player->Jump();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _move_left = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _move_right = true;
        break;
    default:
        break;
    }
}

void MagiciteGameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _move_left = false;
        _player->Stop();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _move_right = false;
        _player->Stop();
        break;
    default:
        break;
    }
}

void MagiciteGameLayer::update(float timeDelta)
{
    if (_move_left && !_move_right)
    {
        _player->Move(MagiciteGameLiving::Direction::left);
    }
    else if (!_move_left && _move_right)
    {
        _player->Move(MagiciteGameLiving::Direction::right);
    }
    _enemyManager.updateEnemyPosition();
}
