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
        Size(_background->getBackSize().width, _visibleSize.height),
        [&](b2Contact* contact){MagiciteGameLayer::onOnBeginContact(contact); });
    _phyLayer->addPhysicSprite(_player, false);
    _player->setPosition(Vec2(_player->getBody()->GetPosition().x, _player->getBody()->GetPosition().y));
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

void MagiciteGameLayer::onOnBeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    auto spriteA = reinterpret_cast<MagiciteGamePhySprite*>(bodyA->GetUserData());
    auto spriteB = reinterpret_cast<MagiciteGamePhySprite*>(bodyB->GetUserData());
    if (spriteA != nullptr && spriteB != nullptr)
    {
        if ((spriteA->_SpriteType == MagiciteGamePhySprite::T_End
            || spriteB->_SpriteType == MagiciteGamePhySprite::T_End)
            && (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living
            || spriteB->_SpriteType == MagiciteGamePhySprite::T_End))
        {
            MagiciteGameLiving* livingA = reinterpret_cast<MagiciteGameLiving*>(spriteA);
            MagiciteGameLiving* livingB = reinterpret_cast<MagiciteGameLiving*>(spriteB);
            if (livingA->_LivingType == MagiciteGameLiving::T_Player
                || livingB->_LivingType == MagiciteGameLiving::T_Player)
            {
                MagiciteGameWin::Win(this);
            }
        }

        if (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living
            || spriteB->_SpriteType == MagiciteGamePhySprite::T_Living)
        {
            if (spriteA->_SpriteType == spriteB->_SpriteType)
            {
                MagiciteGameLiving* livingA = reinterpret_cast<MagiciteGameLiving*>(spriteA);
                MagiciteGameLiving* livingB = reinterpret_cast<MagiciteGameLiving*>(spriteB);
                if (livingA->_LivingType == livingB->_LivingType)
                {
                    MagiciteGameEnemy* enemyA = reinterpret_cast<MagiciteGameEnemy*>(livingA);
                    MagiciteGameEnemy* enemyB = reinterpret_cast<MagiciteGameEnemy*>(livingB);
                    if (!enemyA->getPass())
                    {
                        enemyA->setMoveDire(enemyA->getMoveDire() == MagiciteGameLiving::Direction::left ?
                            MagiciteGameLiving::Direction::right :
                            MagiciteGameLiving::Direction::left);
                        enemyB->setMoveDire(enemyB->getMoveDire() == MagiciteGameLiving::Direction::left ?
                            MagiciteGameLiving::Direction::right :
                            MagiciteGameLiving::Direction::left);
                    }
                }
                else
                {
                    MagiciteGamePlayer* player = nullptr;
                    MagiciteGameEnemy* enemy = nullptr;
                    if (livingA->_LivingType == MagiciteGameLiving::T_Player)
                    {
                        player = reinterpret_cast<MagiciteGamePlayer*>(livingA);
                        enemy = reinterpret_cast<MagiciteGameEnemy*>(livingB);
                    }
                    else
                    {
                        player = reinterpret_cast<MagiciteGamePlayer*>(livingB);
                        enemy = reinterpret_cast<MagiciteGameEnemy*>(livingA);
                    }

                    Vec2 playerPos = player->getPosition();
                    Vec2 enemyPos = enemy->getPosition();
                    Size playerSize = player->getContentSize();
                    Size enemySize = enemy->getContentSize();
                    if (playerPos.x + playerSize.width / 2 > enemyPos.x - enemySize.width / 2
                        && playerPos.x - playerSize.width / 2 < enemyPos.x + enemySize.width / 2
                        && playerPos.y > enemyPos.y + enemySize.height / 2)
                    {
                        player->setState(MagiciteGameLiving::State::S_Jump, false);
                        player->Jump();
                        _enemyManager.destroyEnemy(enemy);
                    }
                    else
                    {
                        MagiciteGameOver::Over(this);
                    }
                }
            }
            else
            {
                MagiciteGameLiving*         living = nullptr;
                MagiciteGamePhySprite*      ground = nullptr;
                if (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living)
                {
                    living = reinterpret_cast<MagiciteGameLiving*>(spriteA);
                    ground = spriteB;
                }
                else
                {
                    living = reinterpret_cast<MagiciteGameLiving*>(spriteB);
                    ground = spriteA;
                }

                if (living->_LivingType == MagiciteGameLiving::T_Player)
                {
                    Vec2 playerPos = living->getPosition();
                    Vec2 groundPos = ground->getPosition();
                    Size playerSize = living->getContentSize();
                    Size groundSize = ground->getContentSize();

                    if (playerPos.x + playerSize.width / 2 > groundPos.x - groundSize.width / 2
                        && playerPos.x - playerSize.width / 2 < groundPos.x + groundSize.width / 2
                        && playerPos.y > groundPos.y + groundSize.height / 2)
                    {
                        living->setState(MagiciteGameLiving::State::S_Jump, false);
                    }
                }
                else
                {
                    MagiciteGameEnemy* enemy = reinterpret_cast<MagiciteGameEnemy*>(living);
                    Vec2 enemyPos = enemy->getPosition();
                    Vec2 groundPos = ground->getPosition();
                    Size enemySize = enemy->getContentSize();
                    Size groundSize = ground->getContentSize();

                    if (enemyPos.x + enemySize.width / 2 > groundPos.x - groundSize.width / 2
                        && enemyPos.x - enemySize.width / 2 < groundPos.x + groundSize.width / 2)
                    {
                        if (enemyPos.y > groundPos.y + groundSize.height / 2)
                        {
                            enemy->setState(MagiciteGameLiving::State::S_Jump, false);
                        }
                    }
                    else
                    {
                        enemy->setMoveDire(enemy->getMoveDire() == MagiciteGameLiving::Direction::left ?
                            MagiciteGameLiving::Direction::right :
                            MagiciteGameLiving::Direction::left);
                    }
                }
            }
        }
    }
}