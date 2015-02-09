#include "MagiciteGameLayer.h"

USING_NS_CC;

MagiciteGameLayer::MagiciteGameLayer()
{
    _enemyManager = new MagiciteGameEnemyManager();
    _pitfallManager = new MagiciteGamePitfallManager();
    _friendManager = new MagiciteGameFriendManager();
}

MagiciteGameLayer::~MagiciteGameLayer()
{
    delete _enemyManager;
    delete _pitfallManager;
    delete _friendManager;
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
    
    _phyLayer = MagiciteGamePhyLayer::create(
        Size(_background->getBackSize().width, _visibleSize.height),
        [&](b2Contact* contact){MagiciteGameLayer::onOnBeginContact(contact); });
    this->addChild(_phyLayer,1);

    ValueMap endMap = game->getObject("finish");
    Size endSize = Size(endMap.at("width").asFloat(), endMap.at("height").asFloat());
    Vec2 endPos = Vec2(endMap.at("x").asFloat() + endSize.width / 2, endMap.at("y").asFloat() + endSize.height / 2);
    auto endCube = MagiciteGameObject::create(MagiciteGameObject::Type::T_End);
    endCube->setContentSize(endSize);
    endCube->setPosition(endPos);
    _phyLayer->createPhyBody(endCube, true, Category::DEFAULT_END, Category::DEFAULT_LIVING);
    _phyLayer->addChild(endCube);

    _player = MagiciteGamePlayer::create(MagiciteGamePlayer::Chicken_Type);
    this->runAction(Follow::create(_player->getSprite(), Rect(0, 0, _background->getBackSize().width, _visibleSize.height)));
    ValueMap playerMap = game->getObject("player");
    Vec2 playerPos = Vec2(playerMap.at("x").asFloat(), playerMap.at("y").asFloat());
    _player->setPosition(playerPos);
    _phyLayer->createPhyBody(_player->getSprite(), false, Category::DEFAULT_LIVING, Category::DEFAULT_ENEMY | Category::DEFAULT_PITFALL | Category::DEFAULT_GROUND | Category::DEFAULT_END);
    _phyLayer->addChild(_player->getSprite());

    _move_left = false;
    _move_right = false;

    /*----------------------------------init finish---------------------------------------------------*/

    ValueVector enemyVec = game->getObjects();
    for (auto it = enemyVec.begin(); it != enemyVec.end(); ++it)
    {
        Value obj = *it;
        ValueMap vm = obj.asValueMap();
        if (vm.at("type").asString() == "enemy")
        {
            auto enemy = _enemyManager->createEnemy(MagiciteGameEnemyManager::Human);
            enemy->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(enemy, false, Category::DEFAULT_ENEMY, Category::DEFAULT_GROUND | Category::DEFAULT_ENEMY | Category::DEFAULT_LIVING | Category::DEFAULT_FRIEND);
            _phyLayer->addChild(enemy);
        }
    }

    ValueVector pitVec = game->getObjects();
    for (auto it = pitVec.begin(); it != pitVec.end(); ++it)
    {
        Value obj = *it;
        ValueMap vm = obj.asValueMap();
        if (vm.at("type").asString() == "pitfall")
        {
            auto pit = _pitfallManager->createPitfall(MagiciteGamePitfallManager::Spine_Type);
            pit->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(pit, true, Category::DEFAULT_PITFALL, Category::DEFAULT_GROUND | Category::DEFAULT_LIVING | Category::DEFAULT_FRIEND);
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

    MagiciteGameContact::try_living_contact_with_ground = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_living_contact_with_ground(objA, objB);
    };
    MagiciteGameContact::try_player_contact_with_enemy = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_player_contact_with_enemy(objA, objB);
    };
    MagiciteGameContact::try_player_contact_with_pitfall = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_player_contact_with_pitfall(objA, objB);
    };
    MagiciteGameContact::try_friend_contact_with_pitfall = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_friend_contact_with_pitfall(objA, objB);
    };
    MagiciteGameContact::try_friend_contact_with_enemy = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_friend_contact_with_enemy(objA, objB);
    };
    MagiciteGameContact::try_enemy_contact_with_enemy = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_enemy_contact_with_enemy(objA, objB);
    };
    MagiciteGameContact::try_player_contact_with_end = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_player_contact_with_end(objA, objB);
    };
    MagiciteGameContact::resiger_contact();
    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    MagiciteGameMoveAbleLiving* friend_chicken = nullptr;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_C:
        friend_chicken = _friendManager->createFriend(
            MagiciteGameFriendManager::Chicken, 
            (_player->getDire() == MagiciteGameMoveAbleLiving::Direction::left ? true : false));
        friend_chicken->setPosition(Vec2(_player->getPosition().x , _player->getPosition().y));

        _phyLayer->createPhyBody(
            friend_chicken,
            false,
            Category::DEFAULT_FRIEND,
            Category::DEFAULT_GROUND | Category::DEFAULT_ENEMY | Category::DEFAULT_PITFALL);
        _phyLayer->addChild(friend_chicken);
        break;
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
    _friendManager->updateFriendPos();
}

void MagiciteGameLayer::onOnBeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    auto objectA = reinterpret_cast<MagiciteGameObject*>(bodyA->GetUserData());
    auto objectB = reinterpret_cast<MagiciteGameObject*>(bodyB->GetUserData());
    if (objectA == nullptr || objectB == nullptr) return;
    auto objectTypeA = MagiciteGameContact::trivial_contact_type(objectA);
    auto objectTypeB = MagiciteGameContact::trivial_contact_type(objectB);
    if (MagiciteGameContact::is_in_types(objectTypeA) == false || MagiciteGameContact::is_in_types(objectTypeB) == false) return;

    MagiciteGameContact::on_contact[objectTypeA][objectTypeB](objectA, objectB);
    /*if (objectA != nullptr && objectB != nullptr)
    {
        bool flag = MagiciteGameContact::try_player_to_end(objectA, objectB);
        if (flag)
        {
            MagiciteGameWin::Win(this);
        }
        flag = MagiciteGameContact::try_player_to_pitfall(objectA, objectB);
        if (flag)
        {
            auto player = MagiciteGameContact::trivialPlayer(objectA, objectB);
            player->attact();
            if (player->getHP() <= 0)
            {
                MagiciteGameOver::Over(this);
            }
        }
        if (MagiciteGameContact::is_all_living(objectA, objectB))
        {
            auto livingA = reinterpret_cast<MagiciteGameLiving*>(objectA);
            auto livingB = reinterpret_cast<MagiciteGameLiving*>(objectB);
            if (MagiciteGameContact::is_have_player(livingA, livingB))
            {
                MagiciteGameLiving* enemy = MagiciteGameContact::trivialEnemy(objectA, objectB);
                MagiciteGameMoveAbleLiving* player = MagiciteGameContact::trivialPlayer(objectA, objectB);
                if (MagiciteGameContact::try_player_contact_with_enemy(player, enemy))
                {
                    enemy->attact();
                    if (enemy->getHP() <= 0)
                    {
                        _enemyManager->destroyEnemy(enemy);
                    }
                    player->JumpOver();
                    player->Jump();
                }
                else
                {
                    player->attact();
                    if (player->getHP() <= 0)
                    {
                        MagiciteGameOver::Over(this);
                    }
                }
            }
            else
            {
                flag = MagiciteGameContact::try_friend_to_enemy(livingA, livingB);
                if (flag)
                {
                    auto friend_living = MagiciteGameContact::trivialFriend(livingA, livingB);
                    auto enemy = MagiciteGameContact::trivialEnemy(livingA, livingB);
                    if (friend_living != nullptr && enemy != nullptr)
                    {
                        MagiciteGameContact::try_to_change_living_direction(friend_living);
                        friend_living->attact();
                        if (friend_living->getHP() <= 0)
                        {
                            _friendManager->destroyFriend(friend_living);
                        }
                        MagiciteGameContact::try_to_change_living_direction(enemy);
                        enemy->attact();
                        if (enemy->getHP() <= 0)
                        {
                            _enemyManager->destroyEnemy(enemy);
                        }
                    }
                }
                else
                {
                    MagiciteGameContact::try_enemy_contact_with_enemy(livingA, livingB);
                }
            }
        }
        else
        {
            flag = MagiciteGameContact::try_moveable_contact_with_ground(objectA, objectB);
            if (!flag)
            {
                flag = MagiciteGameContact::try_friend_to_pitfall(objectA, objectB);
                if (flag)
                {
                    auto friend_living = MagiciteGameContact::trivialFriend(objectA, objectB);
                    auto pitfall = reinterpret_cast<MagiciteGamePitfall*>(friend_living == objectA ? objectB : objectA);
                    friend_living->attact();
                    if (friend_living->getHP() <= 0)
                    {
                        _friendManager->destroyFriend(friend_living);
                    }
                    _pitfallManager->destroyPitfall(pitfall);
                }
            }
        }
    }*/
}

void MagiciteGameLayer::try_living_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameObject* ground = objectB;
    if (MagiciteGameContact::is_moveable_on_ground(living, ground))
    {
        if (MagiciteGameContact::is_moveable_above_ground(living, ground))
        {
            living->JumpOver();
        }
    }
    else
    {
        if (!living->_is_contraled)
        {
            MagiciteGameContact::change_moveable_direction(living);
        }
    }
}

void MagiciteGameLayer::try_player_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* player = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameLiving* enemy = reinterpret_cast<MagiciteGameLiving*>(objectB);

    Vec2 playerPos = player->getPosition();
    Vec2 enemyPos = enemy->getPosition();
    Size playergSize = player->getContentSize();
    Size enemySize = enemy->getContentSize();

    if (playerPos.x + playergSize.width / 2 > enemyPos.x - enemySize.width / 2
        && playerPos.x - playergSize.width / 2 < enemyPos.x + enemySize.width / 2)
    {
        if (playerPos.y - playergSize.height / 2 + -1 * (player->getBody()->GetLinearVelocity().y) + 1
            >= enemyPos.y + enemySize.height / 2)
        {
            enemy->attact();
            if (enemy->getHP() <= 0)
            {
                _enemyManager->destroyEnemy(enemy);
            }
            player->JumpOver();
            player->Jump();
        }
        else
        {
            player->attact();
            if (player->getHP() <= 0)
            {
                MagiciteGameOver::Over(this);
            }
        }
    }
}

void MagiciteGameLayer::try_player_contact_with_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* player = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGamePitfall* pitfall = reinterpret_cast<MagiciteGamePitfall*>(objectB);
    if (pitfall->getPitFallAvtive())
    {
        player->attact();
        if (player->getHP() <= 0)
        {
            MagiciteGameOver::Over(this);
        }
    }
}

void MagiciteGameLayer::try_friend_contact_with_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGamePitfall* pitfall = reinterpret_cast<MagiciteGamePitfall*>(objectB);
    if (pitfall->getPitFallAvtive())
    {
        living->attact();
        if (living->getHP() <= 0)
        {
            _friendManager->destroyFriend(living);
        }
        _pitfallManager->destroyPitfall(pitfall);
    }
}

void MagiciteGameLayer::try_friend_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameMoveAbleLiving* enemy = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectB);
    
    MagiciteGameContact::change_moveable_direction(living);
    living->attact();
    if (living->getHP() <= 0)
    {
        _friendManager->destroyFriend(living);
    }
    MagiciteGameContact::change_moveable_direction(enemy);
    enemy->attact();
    if (enemy->getHP() <= 0)
    {
        _enemyManager->destroyEnemy(enemy);
    }
}

void MagiciteGameLayer::try_enemy_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto livingA = reinterpret_cast<MagiciteGameLiving*>(objectA);
    auto livingB = reinterpret_cast<MagiciteGameLiving*>(objectB);
    MagiciteGameContact::try_to_change_living_direction(livingA);
    MagiciteGameContact::try_to_change_living_direction(livingB);
}

void MagiciteGameLayer::try_player_contact_with_end(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameWin::Win(this);
}