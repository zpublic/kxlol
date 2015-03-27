#include "MagiciteGameLayer.h"
#include "MagiciteGameMap.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGamePause.h"
#include "MagiciteGameOver.h"
#include "MagiciteGameWin.h"
#include "MagiciteScene.h"
#include "MagiciteGamePlayer.h"
#include "MagiciteGameContact.h"
#include "MagiciteGameControlAble.h"
#include "MagiciteGameFactoryMethod.h"
#include "MagiciteGameIncubator.h"
#include "MagiciteWeatherSnow.h"
#include "MagiciteWeatherEffect.h"
#include "MagiciteGamePitfall.h"
#include "MagiciteGameBagView.h"
#include "MagiciteItemCoin.h"
#include "MagiciteSkillCardFriend.h"
#include "MagiciteSkillCardFireBall.h"
#include "MagiciteSkillCardFlash.h"
#include "MagiciteSkillCardSpeedUp.h"
#include "MagiciteSkillCardSprint.h"
#include "MagiciteSkillCardAcid.h"
#include "MagiciteGamePackView.h"
#include "MagiciteGameNPC.h"
#include "MagiciteGameEquipment.h"
#include "MagiciteGamePortal.h"
#include "MagiciteGameShowLayer.h"
#include "MagiciteGamePhysics.h"
#include "PhysicsLoader.h"
#include "MagiciteGameMoveAbleGround.h"
#include "MagiciteGameMoveAbleManager.h"

USING_NS_CC;

/*add*/
static bool solve_one_side_platform(b2Body* player, b2Body* platform)
{
    const auto one_sided_redundance = 2.0f * b2_linearSlop;

    CCASSERT(player->GetFixtureList()->GetShape()->m_type == b2Shape::e_polygon, "bad shape");
    CCASSERT(platform->GetFixtureList()->GetShape()->m_type == b2Shape::e_polygon, "bad shape");
    b2PolygonShape* player_shape = nullptr;
    for (auto iter = player->GetFixtureList(); iter; iter = iter->GetNext())
    {
        if (static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(iter->GetUserData())) == Magicite::FIXTURE_TYPE_PLAYER)
        {
            player_shape = reinterpret_cast<b2PolygonShape*>(iter->GetShape());
        }
    }
        
    auto player_min_y = player_shape->m_vertices[0].y;
    for (auto i = 1; i < player_shape->m_count; i++) {
        if (player_shape->m_vertices[i].y < player_min_y) {
            player_min_y = player_shape->m_vertices[i].y;
        }
    }
    player_min_y += player->GetPosition().y;
    auto platform_shape = reinterpret_cast<b2PolygonShape*>(platform->GetFixtureList()->GetShape());
    auto platform_max_y = platform_shape->m_vertices[0].y;
    for (auto i = 1; i < platform_shape->m_count; i++) {
        if (platform_shape->m_vertices[i].y > platform_max_y) {
            platform_max_y = platform_shape->m_vertices[i].y;
        }
    }
    platform_max_y += platform->GetPosition().y;
    return player_min_y + one_sided_redundance <= platform_max_y;
}
/*~*/

MagiciteGameLayer::MagiciteGameLayer()
{

}

MagiciteGameLayer::~MagiciteGameLayer()
{
    CC_SAFE_DELETE(_moveableManager);
}

bool MagiciteGameLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MagiciteGameLayer::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(MagiciteGameLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    _moveableManager = new MagiciteGameMoveAbleManager();

    this->schedule(schedule_selector(MagiciteGameLayer::update));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    char tiledPath[] = "img\\Magicite\\map\\level5.tmx";
    //std::sprintf(tiledPath, "img\\Magicite\\map\\level%d.tmx", MagiciteScene::getLevel() % 6);
    TMXTiledMap* tiled = TMXTiledMap::create(tiledPath);

    _background = MagiciteGameMap::create(tiled);
    this->addChild(_background);

    _phyLayer = MagiciteGamePhyLayer::create(Size(_background->getBackSize().width, visibleSize.height));
    this->addChild(_phyLayer, 1);

    init_map_data(tiled);
    init_contact();

    //Pet
    /*auto pet = MagiciteGameIncubator::create();
    pet->setPosition(Vec2(_player->getContentSize().width / -2.0f, _player->getContentSize().height * 1.2f));
    pet->setFloat();
    _player->setPetFollow(pet);*/

    //Weather
    //use_weather(MagiciteWeatherSnow::create());

    //EarthQuake
    /*auto earthquake = Repeat::create(Sequence::create(RotateTo::create(0.1f, 1.5f), RotateTo::create(0.1f, -1.5f), nullptr), 5);
    auto earthquakeReset = RotateTo::create(0.0f, 0.0f);
    this->runAction(Sequence::create(earthquake, earthquakeReset, nullptr));*/

    //Meteorite
    /*auto stone = reinterpret_cast<MagiciteGameMoveAbleGround*>(
        MagiciteGameFactoryMethod::createPitfall(MagiciteGameFactoryMethod::Meteorite));
    stone->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height);
    _phyLayer->createPhyBody(stone, false, Magicite::FIXTURE_TYPE_PITFALL);
    stone->Move(MagiciteGameMoveAble::left);
    _phyLayer->addChild(stone);*/

    //FragileGround
    /*auto ground_f = MagiciteGameFragileGround::create();
    ground_f->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    _phyLayer->createPhyBody(ground_f, true, Magicite::FIXTURE_TYPE_PLATFORM);
    _phyLayer->addChild(ground_f);*/

    ////Portal
    //auto portal = MagiciteGameDefaultPortalPair::create();
    //auto sub_portalA = portal->PortalA();
    //auto sub_portalB = portal->PortalB();
    //sub_portalA->setPosition(Vec2(_visibleSize.width * 0.4, _visibleSize.height * 0.4));
    //sub_portalB->setPosition(Vec2(_visibleSize.width * 0.7, _visibleSize.height * 0.4));
    //_phyLayer->createPhyBody(sub_portalA, true);
    //_phyLayer->createPhyBody(sub_portalB, true);

    //_phyLayer->addChild(sub_portalA);
    //_phyLayer->addChild(sub_portalB);

    auto valueMap = FileUtils::getInstance()->getValueMapFromFile("text/story.plist");
    auto str = valueMap.find("story_3")->second.asString();
    showText(str);

    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {

    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
        MagiciteGamePause::Pause(this);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_TAB:
        //_player->switchBagInvisible();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_P:
        {
            if(this->getChildByTag(PACK) == nullptr)
            {
                auto pack = MagiciteGamePackView::create();
                this->addChild(pack, 1000, PACK);
                pack->runAction(Follow::create(this));
            }
            else
                this->getChildByTag(PACK)->setVisible(!this->getChildByTag(PACK)->isVisible());
        }
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_E:
        {
            if(this->getChildByTag(EQUIP) == nullptr)
            {
                auto equip = MagiciteGameEquipment::create();
                this->addChild(equip, 1000, EQUIP);
                equip->runAction(Follow::create(this));
            }
            else
                this->getChildByTag(EQUIP)->setVisible(!this->getChildByTag(EQUIP)->isVisible());
        }
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
    _moveableManager->UpdateMoveAble();
}

MagiciteGameContact::ContactType MagiciteGameLayer::onOnJudgeContact(b2Contact* contact)
{
    auto fixA = contact->GetFixtureA();
    auto fixB = contact->GetFixtureB();
    auto typeA = static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(fixA->GetUserData()));
    auto typeB = static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(fixB->GetUserData()));
    
    /*add*/
    if ((typeA == Magicite::FIXTURE_TYPE_PLAYER &&
        typeB == Magicite::FIXTURE_TYPE_PLATFORM)
        ||
        (typeB == Magicite::FIXTURE_TYPE_PLAYER &&
        typeA == Magicite::FIXTURE_TYPE_PLATFORM)
        ) {
            if (solve_one_side_platform(reinterpret_cast<b2Body*>(fixA->GetBody()), reinterpret_cast<b2Body*>(fixB->GetBody()))) 
            {
                return MagiciteGameContact::Cancle;
            }
        }
    /*~*/

    return MagiciteGameContact::judge_contact[typeA][typeB];
}

void MagiciteGameLayer::onOnBeginContact(b2Contact* contact)
{
    auto fixA = contact->GetFixtureA();
    auto fixB = contact->GetFixtureB();
    auto typeA = static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(fixA->GetUserData()));
    auto typeB = static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(fixB->GetUserData()));

    MagiciteGameContact::on_contact[typeA][typeB](
        reinterpret_cast<MagiciteGameObject*>(fixA->GetBody()->GetUserData()), 
        reinterpret_cast<MagiciteGameObject*>(fixB->GetBody()->GetUserData()));
}

void MagiciteGameLayer::init_contact()
{
    MagiciteGameContact::_onWin = [&](){
        MagiciteGameWin::Win(this);
    };
    MagiciteGameContact::_onOver = [&](){
        MagiciteGameOver::Over(this);
    };
    MagiciteGameContact::_onPick = [&](MagiciteItem* item){
        auto item_clone = item->clone();
        item->Dead();
        item->removeFromParent();
        _player->getBag()->addItem(item_clone);
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
    _phyLayer->createPhyBody(endCube, true, Magicite::FIXTURE_TYPE_END);
    _phyLayer->addChild(endCube);
}

void MagiciteGameLayer::create_player(TMXObjectGroup* game)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(
        MagiciteGameFactoryMethod::createLiving(MagiciteGameFactoryMethod::Chicken));
    living->setDire(MagiciteGameMoveAbleLiving::right);

    this->runAction(Follow::create(living, Rect(0, 0, _background->getBackSize().width, visibleSize.height)));
    ValueMap playerMap = game->getObject("player");
    Vec2 playerPos = Vec2(playerMap.at("x").asFloat(), playerMap.at("y").asFloat());
    living->setPosition(playerPos);
    _phyLayer->createPhyBody(living, false, Magicite::FIXTURE_TYPE_PLAYER);
    _phyLayer->addChild(living);

    _player = MagiciteGamePlayer::create(living);
    auto bag_view = _player->getBag();
    bag_view->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    bag_view->runAction(Follow::create(this));
    this->addChild(bag_view, 999);

    _player->switchBagInvisible();

    _player->getBag()->addItem(MagiciteSkillCardFireBall::create(_phyLayer));
    _player->getBag()->addItem(MagiciteSkillCardAcid::create(_phyLayer));
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
            auto enemy = MagiciteGameFactoryMethod::createEnemy(MagiciteGameFactoryMethod::Dirt);
            enemy->setDire(MagiciteGameMoveAbleLiving::left);
            enemy->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(enemy, false, Magicite::FIXTURE_TYPE_ENEMY);
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
            auto pit = MagiciteGameFactoryMethod::createPitfall(MagiciteGameFactoryMethod::Piranha);
            pit->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(pit, true, Magicite::FIXTURE_TYPE_PITFALL);
            _phyLayer->addChild(pit);
        }
        else if (vm.at("type").asString() == "hole")
        {
            auto pit = MagiciteGameFactoryMethod::createPitfall(MagiciteGameFactoryMethod::Pitfall);
            pit->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            pit->setContentSize(Size(vm.at("width").asFloat(), vm.at("height").asFloat()));
            _phyLayer->createPhyBody(pit, true, Magicite::FIXTURE_TYPE_PITFALL);
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
        if ( vm.at("type").asString() == "platform"/*~*/)
        {
            float x = vm.at("x").asFloat();
            float w = vm.at("width").asFloat();
            float h = vm.at("height").asFloat();
            float y = vm.at("y").asFloat();
            auto node = MagiciteGameGround::create();
            node->setPosition(Vec2(x, y));
            node->setContentSize(Size(w, h));
            node->setAnchorPoint(Point::ZERO);
            _phyLayer->createPhyBody(node, true, vm.at("type").asString() == "cube" ? Magicite::FIXTURE_TYPE_LAND: Magicite::FIXTURE_TYPE_PLATFORM);
            _phyLayer->addChild(node);
            ///*add*/node->setUserData(reinterpret_cast<void*>(vm.at("type").asString() == "platform"));/*~*/
        }
    }
    //
    b2BodyDef  body_def;
    body_def.type = b2_staticBody;
    auto body = _phyLayer->createBody(&body_def);

    PhysicsLoader loader;
    loader.addShapesWithFile("point.plist");
    loader.addFixturesToBody(body, "level5");

}

void MagiciteGameLayer::create_NPC( TMXObjectGroup* game)
{
    ValueVector npcVector = game->getObjects();

    for(auto it = npcVector.begin(); it != npcVector.end(); ++it)
    {
        Value obj = *it;
        ValueMap vm = obj.asValueMap();
        auto str = vm.at("type").asString();
        if(str == "NPC")
        {
            auto npc = MagiciteGameFactoryMethod::createFriend(MagiciteGameFactoryMethod::NPC);
            npc->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            npc->setContentSize(Size(vm.at("width").asFloat(), vm.at("height").asFloat()));
            _phyLayer->createPhyBody(npc, true, Magicite::FIXTURE_TYPE_FRIEND);
            _phyLayer->addChild(npc);
            auto strName = vm.at("name").asString();
            auto npcptr = dynamic_cast<MagiciteGameNPC*>(npc);
            if(npcptr != nullptr && strName != "")
            {
                npcptr->setNpcName(strName);
            }
        }
    }
}


void MagiciteGameLayer::use_weather(MagiciteWeather* weather)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto weatherEffect = weather->getWeatherEffect(Vec2(_background->getBackSize().width, visibleSize.height));
    weatherEffect->positive(this);
}

void MagiciteGameLayer::create_item(cocos2d::TMXObjectGroup* game)
{
    ValueVector enemyVec = game->getObjects();
    for (auto it = enemyVec.begin(); it != enemyVec.end(); ++it)
    {
        Value obj = *it;
        ValueMap vm = obj.asValueMap();
        if (vm.at("type").asString() == "item")
        {
            auto item = MagiciteSkillCardFriend::create(MagiciteSkillCardFriend::LivingType::Sheep, _phyLayer);
            item->setPosition(vm.at("x").asFloat(), vm.at("y").asFloat());
            _phyLayer->createPhyBody(item, true, Magicite::FIXTURE_TYPE_ITEM);
            _phyLayer->addChild(item);
        }
    }
}

void MagiciteGameLayer::init_map_data(cocos2d::TMXTiledMap* tiledMap)
{
    TMXObjectGroup* game = tiledMap->getObjectGroup("game");
    TMXObjectGroup* ground = tiledMap->getObjectGroup("physics");

    create_end_cube(game);
    create_player(game);

    create_enemy(game);
    create_pitfall(game);
    create_ground(ground);
    create_NPC(game);
    create_moveground();
    //create_item(game);
}

void MagiciteGameLayer::showText(const std::string& str)
{
    auto show = MagiciteGameShowLayer::create(2.0f, str);
    this->addChild(show, 1);
    show->start();
}

void MagiciteGameLayer::create_moveground()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto mg = MagiciteGameMoveAbleGround::create();
    mg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    mg->_pointA = Vec2(visibleSize.width * 0.4f, visibleSize.height / 2);
    mg->_pointB = Vec2(visibleSize.width * 0.6f, visibleSize.height / 2);
    _phyLayer->createPhyBody(mg, false, Magicite::FIXTURE_TYPE_LAND);
    _phyLayer->addChild(mg);

    auto fix = MagiciteGameObject::create();
    fix->setContentSize(Size(mg->_pointB.x - mg->_pointA.x + 2, mg->_pointB.y - mg->_pointA.y + 2));
    fix->setPosition(mg->_pointA);
    _phyLayer->createPhyBody(fix, true, Magicite::FIXTURE_TYPE_NONE);
    _phyLayer->addChild(fix);

    b2PrismaticJointDef prismaticJointDef;
    prismaticJointDef.bodyA = fix->getBody();
    prismaticJointDef.bodyB = mg->getBody();
    prismaticJointDef.collideConnected = false;
    prismaticJointDef.localAxisA.Set(1.0f, 0.0f);
    prismaticJointDef.enableLimit = true;
    prismaticJointDef.lowerTranslation = -fix->getContentSize().width / PTM_RATIO;
    prismaticJointDef.upperTranslation = fix->getContentSize().width / PTM_RATIO;
    _phyLayer->createJoint(&prismaticJointDef);

    _moveableManager->addMoveAble(static_cast<MagiciteGameAutoMoveAble*>(mg));
}
