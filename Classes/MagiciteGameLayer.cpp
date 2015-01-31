#include "MagiciteGameLayer.h"

USING_NS_CC;

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

    TMXTiledMap* tiled = TMXTiledMap::create("test.tmx");
    _background = MagiciteGameMap::create(tiled);
    this->addChild(_background, -1);
   
    auto player = MagiciteGamePlayerManager::getInstance()->getPlayer();
    player->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    
    _phyLayer = MagiciteGamePhyLayer::create(Size(_background->getBackSize().width, _visibleSize.height));
    _phyLayer->addPhysicSprite(player, false);
    this->addChild(_phyLayer);

    this->runAction(Follow::create(player, Rect(0, 0, _background->getBackSize().width, _visibleSize.height)));

    _move_left = false;
    _move_right = false;

    /*----------------------------------init finish---------------------------------------------------*/

    auto enemyA = MagiciteGameEnemyManager::getInstance()->createEnemy(
        Vec2(_visibleSize.width / 3, _visibleSize.height / 3), true);
    auto enemyB = MagiciteGameEnemyManager::getInstance()->createEnemy(
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
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        MagiciteGamePlayerManager::getInstance()->getPlayer()->Jump();
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
    auto player = MagiciteGamePlayerManager::getInstance()->getPlayer();
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        _move_left = false;
        player->getBody()->SetLinearVelocity(b2Vec2(0, player->getBody()->GetLinearVelocity().y));
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        _move_right = false;
        player->getBody()->SetLinearVelocity(b2Vec2(0, player->getBody()->GetLinearVelocity().y));
        break;
    default:
        break;
    }
}

void MagiciteGameLayer::update(float timeDelta)
{
    if (_move_left && !_move_right)
    {
        MagiciteGamePlayerManager::getInstance()->getPlayer()->Move(MagiciteGameLiving::Direction::left);
    }
    else if (!_move_left && _move_right)
    {
        MagiciteGamePlayerManager::getInstance()->getPlayer()->Move(MagiciteGameLiving::Direction::right);
    }
    MagiciteGameEnemyManager::getInstance()->updateEnemyPosition();
}
