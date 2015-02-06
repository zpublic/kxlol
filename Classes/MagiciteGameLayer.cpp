#include "MagiciteGameLayer.h"

USING_NS_CC;

MagiciteGameLayer::MagiciteGameLayer()
{
    _enemyManager = new MagiciteGameEnemyManager();
    _pitfallManager = new MagiciteGamePitfallManager();
}

MagiciteGameLayer::~MagiciteGameLayer()
{
    delete _enemyManager;
    delete _pitfallManager;
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
    
    ValueMap endMap = game->getObject("finish");
    Size endSize = Size(endMap.at("width").asFloat(), endMap.at("height").asFloat());
    Vec2 endPos = Vec2(endMap.at("x").asFloat() + endSize.width / 2, endMap.at("y").asFloat() + endSize.height / 2);
    auto endCube = MagiciteGameObject::create(MagiciteGameObject::Type::T_End);
    endCube->setContentSize(endSize);
    endCube->setPosition(endPos);
    
    _phyLayer = MagiciteGamePhyLayer::create(
        Size(_background->getBackSize().width, _visibleSize.height),
        [&](b2Contact* contact){MagiciteGameLayer::onOnBeginContact(contact); });
    _phyLayer->createPhyBody(endCube, true);
    _phyLayer->addChild(endCube);
    this->addChild(_phyLayer,1);

    _player = MagiciteGamePlayer::create(MagiciteGamePlayer::Human_Type);
    this->runAction(Follow::create(_player->getSprite(), Rect(0, 0, _background->getBackSize().width, _visibleSize.height)));
    ValueMap playerMap = game->getObject("player");
    Vec2 playerPos = Vec2(playerMap.at("x").asFloat(), playerMap.at("y").asFloat());
    _player->setPosition(playerPos);
    _phyLayer->createPhyBody(_player->getSprite(), false, Category::DEFAULT_LIVING, Category::DEFAULT_ENEMY | Category::DEFAULT_PITFALL | Category::DEFAULT_GROUND);
    _phyLayer->addChild(_player->getSprite());

    _move_left = false;
    _move_right = false;

    /*----------------------------------init finish---------------------------------------------------*/

    auto enemyA = _enemyManager->createEnemy(MagiciteGameEnemyManager::Chicken);
    enemyA->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
    _phyLayer->createPhyBody(enemyA, false, Category::DEFAULT_ENEMY, Category::DEFAULT_GROUND | Category::DEFAULT_ENEMY | Category::DEFAULT_LIVING);
    _phyLayer->addChild(enemyA);
    auto enemyB = _enemyManager->createEnemy(MagiciteGameEnemyManager::Chicken);
    enemyB->setPosition(Vec2(_visibleSize.width / 2 + 150, _visibleSize.height / 2));
    _phyLayer->createPhyBody(enemyB, false, Category::DEFAULT_ENEMY, Category::DEFAULT_GROUND | Category::DEFAULT_ENEMY | Category::DEFAULT_LIVING);
    _phyLayer->addChild(enemyB);

    ValueVector pitVec = game->getObjects();
    for (auto it = pitVec.begin(); it != pitVec.end(); ++it)
    {
        Value obj = *it;
        ValueMap vm = obj.asValueMap();
        if (vm.at("type").asString() == "pitfall")
        {
            auto pit = _pitfallManager->createPitfall(MagiciteGamePitfallManager::Spine_Type);
            pit->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(pit, true, Category::DEFAULT_PITFALL, Category::DEFAULT_GROUND | Category::DEFAULT_LIVING);
            _phyLayer->addChild(pit);
        }
    }

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
            auto node = MagiciteGameObject::create();
            node->setPosition(Vec2(x, y));
            node->setContentSize(Size(w, h));
            node->setAnchorPoint(Point::ZERO);
            _phyLayer->createPhyBody(node,true);
            _phyLayer->addChild(node);
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
    case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
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
        _player->Move(MagiciteGamePlayer::Direction::left);
    }
    else if (!_move_left && _move_right)
    {
        _player->Move(MagiciteGamePlayer::Direction::right);
    }
    _enemyManager->updateEnemyPos();
    _pitfallManager->updatePitfallAvtive();
}

void MagiciteGameLayer::onOnBeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    auto objectA = reinterpret_cast<MagiciteGameObject*>(bodyA->GetUserData());
    auto objectB = reinterpret_cast<MagiciteGameObject*>(bodyB->GetUserData());

    if (objectA != nullptr && objectB != nullptr)
    {
        
        if (dynamic_cast<MagiciteGameObject*>(_player->getSprite()) == objectA || dynamic_cast<MagiciteGameObject*>(_player->getSprite()) == objectB)
        {
            if (dynamic_cast<MagiciteGameObject*>(_player->getSprite()) == objectA)
            {
                reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA)->JumpOver();
            }
            else
            {
                reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectB)->JumpOver();
            }
        }
    }
}
