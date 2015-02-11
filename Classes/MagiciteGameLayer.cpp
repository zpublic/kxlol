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
    TMXObjectGroup* game = tiled->getObjectGroup("game");
    TMXObjectGroup* ground = tiled->getObjectGroup("physics");

    _background = MagiciteGameMap::create(tiled);
    this->addChild(_background);
    
    _phyLayer = MagiciteGamePhyLayer::create(
        Size(_background->getBackSize().width, _visibleSize.height),
        [&](b2Contact* contact){MagiciteGameLayer::onOnBeginContact(contact); });
    this->addChild(_phyLayer,1);

    create_end_cube(game);
    create_player(game);
    create_enemy(game);
    create_pitfall(game);
    create_ground(ground);

    init_contact();

    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    MagiciteGameMoveAbleLiving* friends = nullptr;
    MagiciteGameFireball*   fireball = nullptr;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_C:
        friends = _friendManager->createFriend(
            MagiciteGameFriendManager::Slime, 
            (_player->getDire() == MagiciteGameMoveAbleLiving::Direction::left ? true : false));
        friends->setPosition(Vec2(_player->getPosition().x, _player->getPosition().y));

        _phyLayer->createPhyBody(
            friends,
            false,
            Category::DEFAULT_FRIEND,
            Category::DEFAULT_GROUND | Category::DEFAULT_ENEMY | Category::DEFAULT_PITFALL);
        _phyLayer->addChild(friends);
        break;
    case EventKeyboard::KeyCode::KEY_F:
        fireball = MagiciteGameFireball::create();
        fireball->setPosition(_player->getPosition().x, _player->getPosition().y - _player->getContentSize().height / 2 + fireball->getContentSize().height / 2 + 1);
        _phyLayer->createPhyBody(fireball, false, Category::DEFAULT_AMMO, Category::DEFAULT_ENEMY | Category::DEFAULT_GROUND);
        _phyLayer->addChild(fireball);
        fireball->getBody()->SetGravityScale(0.0f);
        fireball->Move(_player->getDire());

        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE :
        MagiciteGamePause::Pause(this);
        break;
    default:
        break;
    }
    MagiciteGameControlAble::dispatchKeyPress(keyCode, event, static_cast<MagiciteGameControlAble*>(_player));
}

void MagiciteGameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    MagiciteGameControlAble::dispatchKeyRelease(keyCode, event, static_cast<MagiciteGameControlAble*>(_player));
}

void MagiciteGameLayer::update(float timeDelta)
{
    _enemyManager->updateEnemyPos();
    _pitfallManager->updatePitfallAvtive();
    _friendManager->updateFriendPos();
    _player->Move();
}

void MagiciteGameLayer::onOnBeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    auto objectA = reinterpret_cast<MagiciteGameObject*>(bodyA->GetUserData());
    auto objectB = reinterpret_cast<MagiciteGameObject*>(bodyB->GetUserData());
    /*if (objectA != nullptr && objectB != nullptr) return;*/
    MagiciteGameContact::Contact_type objectTypeA = MagiciteGameContact::Contact_type::unknow_type;
    MagiciteGameContact::Contact_type objectTypeB = MagiciteGameContact::Contact_type::unknow_type;

    objectTypeA = MagiciteGameContact::trivial_contact_type(objectA);
    objectTypeB = MagiciteGameContact::trivial_contact_type(objectB);
    if (MagiciteGameContact::is_in_types(objectTypeA) == false || MagiciteGameContact::is_in_types(objectTypeB) == false) return;

    MagiciteGameContact::on_contact[objectTypeA][objectTypeB](objectA, objectB);

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

void MagiciteGameLayer::try_ammo_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto ammo = reinterpret_cast<MagiciteGameAmmo*>(objectA);
    auto enemy = reinterpret_cast<MagiciteGameLiving*>(objectB);
    ammo->Dead();
    enemy->attact();
    if (enemy->getHP() <= 0)
    {
        _enemyManager->destroyEnemy(enemy);
    }
}

void MagiciteGameLayer::try_ammo_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto ammo = reinterpret_cast<MagiciteGameAmmo*>(objectA);
    ammo->Dead();
}

void MagiciteGameLayer::try_ammo_contact_with_edge(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    objectA->Dead();
}

void MagiciteGameLayer::try_living_contact_with_edge(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto moveLiving = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    if (!moveLiving->_is_contraled)
    {
        MagiciteGameContact::try_to_change_living_direction(moveLiving);
    }
}

void MagiciteGameLayer::init_contact()
{
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
    MagiciteGameContact::try_ammo_contact_with_enemy = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_ammo_contact_with_enemy(objA, objB);
    };
    MagiciteGameContact::try_ammo_contact_with_ground = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_ammo_contact_with_ground(objA, objB);
    };
    MagiciteGameContact::try_ammo_contact_with_edge = [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_ammo_contact_with_edge(objA, objB);
    };
    MagiciteGameContact::try_living_contact_with_edge= [&](MagiciteGameObject* objA, MagiciteGameObject* objB)
    {
        MagiciteGameLayer::try_living_contact_with_edge(objA, objB);
    };
    MagiciteGameContact::resiger_contact();
}


void MagiciteGameLayer::create_end_cube(TMXObjectGroup* game)
{
    ValueMap endMap = game->getObject("finish");
    Size endSize = Size(endMap.at("width").asFloat(), endMap.at("height").asFloat());
    Vec2 endPos = Vec2(endMap.at("x").asFloat() + endSize.width / 2, endMap.at("y").asFloat() + endSize.height / 2);
    auto endCube = MagiciteGameObject::create(MagiciteGameObject::Type::T_End);
    endCube->setContentSize(endSize);
    endCube->setPosition(endPos);
    _phyLayer->createPhyBody(endCube, true, Category::DEFAULT_END, Category::DEFAULT_LIVING);
    _phyLayer->addChild(endCube);
}

void MagiciteGameLayer::create_player(TMXObjectGroup* game)
{
    _player = MagiciteGamePlayer::create(MagiciteGamePlayer::Chicken_Type);
    this->runAction(Follow::create(_player->getSprite(), Rect(0, 0, _background->getBackSize().width, _visibleSize.height)));
    ValueMap playerMap = game->getObject("player");
    Vec2 playerPos = Vec2(playerMap.at("x").asFloat(), playerMap.at("y").asFloat());
    _player->setPosition(playerPos);
    _phyLayer->createPhyBody(_player->getSprite(), false, Category::DEFAULT_LIVING, Category::DEFAULT_ENEMY | Category::DEFAULT_PITFALL | Category::DEFAULT_GROUND | Category::DEFAULT_END);
    _phyLayer->addChild(_player->getSprite());
}

void MagiciteGameLayer::create_enemy(TMXObjectGroup* game)
{
    ValueVector enemyVec = game->getObjects();
    for (auto it = enemyVec.begin(); it != enemyVec.end(); ++it)
    {
        Value obj = *it;
        ValueMap vm = obj.asValueMap();
        if (vm.at("type").asString() == "enemy")
        {
            auto enemy = _enemyManager->createEnemy(MagiciteGameEnemyManager::Sheep);
            enemy->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(enemy, false, Category::DEFAULT_ENEMY, Category::DEFAULT_GROUND | Category::DEFAULT_ENEMY | Category::DEFAULT_LIVING | Category::DEFAULT_FRIEND | Category::DEFAULT_AMMO);
            _phyLayer->addChild(enemy);
        }
    }
}

void MagiciteGameLayer::create_pitfall(TMXObjectGroup* game)
{
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
}

void MagiciteGameLayer::create_ground(TMXObjectGroup* ground)
{

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
            _phyLayer->createPhyBody(node, true);
            _phyLayer->addChild(node);
        }
    }
}