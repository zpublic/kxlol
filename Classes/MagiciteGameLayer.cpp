#include "MagiciteGameLayer.h"
#include "MagiciteGameMap.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGamePause.h"
#include "MagiciteGameOver.h"
#include "MagiciteGameWin.h"
#include "MagiciteGamePlayer.h"
#include "MagiciteGameContact.h"
#include "MagiciteGameControlAble.h"
#include "MagiciteGaemFactoryMethod.h"
#include "MagiciteGameIncubator.h"
#include "MagiciteWeatherSnow.h"
#include "MagiciteWeatherEffect.h"
#include "MagiciteGamePitfall.h"
#include "MagiciteGameBagView.h"
#include "MagiciteItemCoin.h"
#include "MagiciteItemContainer.h"
#include "MagiciteSkillCardFireBall.h"

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
    
    _phyLayer = MagiciteGamePhyLayer::create(Size(_background->getBackSize().width, _visibleSize.height));
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
    //create_Particle();

    use_weather(new MagiciteWeatherSnow);

    init_contact();

    auto view =  MagiciteGameBagView::create();
    view->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
    view->runAction(Follow::create(this));
    this->addChild(view,999);
    _player->bindBagView(view);

    _player->getBag()->addItem(new MagiciteItemCoin());
    _player->getBag()->addItem(MagiciteSkillCardFireBall::create(_phyLayer, _player->getDire()));
    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE :
        MagiciteGamePause::Pause(this);
        break;
    
    default:
        MagiciteGameControlAble::dispatchKeyPress(keyCode, event, _player);
        break;
    }
    
}

void MagiciteGameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    MagiciteGameControlAble::dispatchKeyRelease(keyCode, event, _player);
}

void MagiciteGameLayer::update(float timeDelta)
{
    _player->Move();
}

bool MagiciteGameLayer::onOnJudgeContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    auto objectA = reinterpret_cast<MagiciteGameObject*>(bodyA->GetUserData());
    auto objectB = reinterpret_cast<MagiciteGameObject*>(bodyB->GetUserData());
    MagiciteGameContact::Contact_type objectTypeA = MagiciteGameContact::Contact_type::unknow_type;
    MagiciteGameContact::Contact_type objectTypeB = MagiciteGameContact::Contact_type::unknow_type;

    objectTypeA = MagiciteGameContact::trivial_contact_type(objectA);
    objectTypeB = MagiciteGameContact::trivial_contact_type(objectB);

    return MagiciteGameContact::judge_contact[objectTypeA][objectTypeB];
}

void MagiciteGameLayer::onOnBeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    auto objectA = reinterpret_cast<MagiciteGameObject*>(bodyA->GetUserData());
    auto objectB = reinterpret_cast<MagiciteGameObject*>(bodyB->GetUserData());
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
    MagiciteGameContact::_onJudgeContact = std::bind(&MagiciteGameLayer::onOnJudgeContact, this, std::placeholders::_1);
    MagiciteGameContact::_onBeginContact = std::bind(&MagiciteGameLayer::onOnBeginContact, this, std::placeholders::_1);;

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
    _phyLayer->createPhyBody(endCube, true);
    _phyLayer->addChild(endCube);
}

void MagiciteGameLayer::create_player(TMXObjectGroup* game)
{
    _player = MagiciteGamePlayer::create(MagiciteGamePlayer::Chicken_Type, _phyLayer);
    this->runAction(Follow::create(_player->getSprite(), Rect(0, 0, _background->getBackSize().width, _visibleSize.height)));
    ValueMap playerMap = game->getObject("player");
    Vec2 playerPos = Vec2(playerMap.at("x").asFloat(), playerMap.at("y").asFloat());
    _player->setPosition(playerPos);
    _phyLayer->createPhyBody(_player->getSprite(), false);
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
            _phyLayer->createPhyBody(enemy, false);
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
            _phyLayer->createPhyBody(pit, true);
            _phyLayer->addChild(pit);
        }
        else if (vm.at("type").asString() == "hole")
        {
            auto pit = MagiciteGaemFactoryMethod::createPitfall(MagiciteGaemFactoryMethod::Pitfall);
            pit->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            pit->setContentSize(Size(vm.at("width").asFloat(), vm.at("height").asFloat()));
            _phyLayer->createPhyBody(pit, true);
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

void MagiciteGameLayer::use_weather(MagiciteWeather* weather)
{
    auto weatherEffect = weather->getWeatherEffect(Vec2(_background->getBackSize().width, _visibleSize.height));
    weatherEffect->positive(this);
}