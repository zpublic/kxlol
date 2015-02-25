#include "MagiciteGameLayer.h"
#include "MagiciteEffectFlash.h"
#include "MagiciteEffectFireBall.h"
#include "MagiciteEffectCreateFriend.h"

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

    auto pet = MagiciteGameIncubator::create();
    pet->setPosition(Vec2(_player->getContentSize().width / -2.0f, _player->getContentSize().height * 1.2f));
    pet->setFloat();
    _player->setPetFollow(pet);

    create_enemy(game);
    create_pitfall(game);
    create_ground(ground);
    create_Particle();

    init_contact();

    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    MagiciteGameMoveAbleLiving* friends = nullptr;
    MagiciteGameAmmo*   ammo = nullptr;
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_C:
        _player->useSkill(MagiciteEffectCreateFriend::create(
            Vec2(_player->getPosition()),
            _phyLayer,
            _player->getDire(), MagiciteEffectCreateFriend::LivingType::Slime));
        break;
    case EventKeyboard::KeyCode::KEY_F:
        _player->useSkill(MagiciteEffectFireBall::create(
            Vec2(_player->getPosition()),
            _phyLayer,
            _player->getDire()));
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE :
        MagiciteGamePause::Pause(this);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        _player->useSkill(MagiciteEffectFlash::create(_phyLayer, _player->getSprite(), 200));
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

void MagiciteGameLayer::init_contact()
{
    MagiciteGameContact::_onWin = [&](){
        MagiciteGameWin::Win(this);
    };
    MagiciteGameContact::_onOver = [&](){
        MagiciteGameOver::Over(this);
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
    _phyLayer->createPhyBody(_player->getSprite(), false, Category::DEFAULT_LIVING, Category::DEFAULT_ENEMY | Category::DEFAULT_PITFALL | Category::DEFAULT_GROUND | Category::DEFAULT_END | Category::DEFAULT_HOLE);
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
            auto enemy = MagiciteGaemFactoryMethod::createEnemy(MagiciteGaemFactoryMethod::Dirt);
            enemy->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(enemy, false, Category::DEFAULT_ENEMY, Category::DEFAULT_GROUND | Category::DEFAULT_ENEMY | Category::DEFAULT_LIVING | Category::DEFAULT_FRIEND | Category::DEFAULT_AMMO | Category::DEFAULT_HOLE);
            _phyLayer->addChild(enemy);
            if (enemy->LivingMoveType == MagiciteGameLiving::MoveAbleLiving)
            {
                auto moveEnemy = reinterpret_cast<MagiciteGameMoveAbleLiving*>(enemy);
                moveEnemy->Move(moveEnemy->getDire());
            }
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
            auto pit = MagiciteGaemFactoryMethod::createPitfall(MagiciteGaemFactoryMethod::Spine_Type);
            pit->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(pit, true, Category::DEFAULT_PITFALL, Category::DEFAULT_GROUND | Category::DEFAULT_LIVING | Category::DEFAULT_FRIEND);
            _phyLayer->addChild(pit);
        }
        else if (vm.at("type").asString() == "hole")
        {
            auto pit = MagiciteGaemFactoryMethod::createPitfall(MagiciteGaemFactoryMethod::Pitfall);
            pit->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            pit->setContentSize(Size(vm.at("width").asFloat(), vm.at("height").asFloat()));
            _phyLayer->createPhyBody(pit, true, Category::DEFAULT_HOLE, Category::DEFAULT_GROUND | Category::DEFAULT_LIVING | Category::DEFAULT_FRIEND | Category::DEFAULT_ENEMY);
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

void MagiciteGameLayer::create_Particle()
{
    auto snow = ParticleSnow::create();
    snow->setTexture(Director::getInstance()->getTextureCache()->addImage("img\\Magicite\\Particle\\snow.png"));

    snow->setDuration(-1);
    snow->setGravity(Vec2(0.0f, -80.0f));

    snow->setAngle(90.0f);
    snow->setAngleVar(360.0f);

    snow->setPosition(_background->getBackSize().width / 2, _visibleSize.height);
    snow->setPosVar(Vec2(_background->getBackSize().width / 2, 0));

    snow->setStartSpin(30);
    snow->setStartSpinVar(60);
    snow->setEndSpin(60);
    snow->setEndSpinVar(60);

    snow->setEmissionRate(6);
    this->addChild(snow);
}
