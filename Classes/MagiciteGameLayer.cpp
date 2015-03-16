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
#include "MagiciteGameMeteorite.h"
#include "MagiciteGameGround.h"
#include "MagiciteGameFragileGround.h"
#include "MagiciteGameDefaultPortalPair.h"
#include "MagiciteGamePortal.h"
#include "MagiciteGameShowLayer.h"

USING_NS_CC;

/*add*/
static bool solve_one_side_platform(b2Body* player, b2Body* platform)
{
    const auto one_sided_redundance = 2.0f * b2_linearSlop;

    CCASSERT(player->GetFixtureList()->GetShape()->m_type == b2Shape::e_polygon, "bad shape");
    CCASSERT(platform->GetFixtureList()->GetShape()->m_type == b2Shape::e_polygon, "bad shape");
    auto player_shape = reinterpret_cast<b2PolygonShape*>(player->GetFixtureList()->GetShape());
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

    this->schedule(schedule_selector(MagiciteGameLayer::update));

    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    char tiledPath[200];
    std::sprintf(tiledPath, "img\\Magicite\\map\\level%d.tmx", MagiciteScene::getLevel() % 5);
    TMXTiledMap* tiled = TMXTiledMap::create(tiledPath);

    _background = MagiciteGameMap::create(tiled);
    this->addChild(_background);

    _phyLayer = MagiciteGamePhyLayer::create(Size(_background->getBackSize().width, _visibleSize.height));
    this->addChild(_phyLayer, 1);

    init_map_data(tiled);
    init_contact();

    auto pet = MagiciteGameIncubator::create();
    pet->setPosition(Vec2(_player->getContentSize().width / -2.0f, _player->getContentSize().height * 1.2f));
    pet->setFloat();
    _player->setPetFollow(pet);

    use_weather(MagiciteWeatherSnow::create());

    //EarthQuake

    auto earthquake = Repeat::create(Sequence::create(RotateTo::create(0.1f, 1.5f), RotateTo::create(0.1f, -1.5f), nullptr), 5);
    auto earthquakeReset = RotateTo::create(0.0f, 0.0f);
    this->runAction(Sequence::create(earthquake, earthquakeReset, nullptr));

    //Meteorite
    auto stone = MagiciteGameMeteorite::create();
    stone->setPosition(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height);
    _phyLayer->createPhyBody(stone, false); 
    stone->Move(MagiciteGameMoveAble::left);
    _phyLayer->addChild(stone);

    //FragileGround
    auto ground_f = MagiciteGameFragileGround::create();
    ground_f->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
    _phyLayer->createPhyBody(ground_f, true);
    _phyLayer->addChild(ground_f);

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

    /*add*/
    if (objectTypeA == MagiciteGameContact::Contact_type::player_type &&
        objectTypeB == MagiciteGameContact::Contact_type::ground_type &&
        objectB->getUserData() != nullptr) {
        if (solve_one_side_platform(bodyA, bodyB)) {
            return false;
        }
    }
    /*~*/

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

    auto bag_view = _player->getBag();
    bag_view->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
    bag_view->runAction(Follow::create(this));
    this->addChild(bag_view, 999);

    _player->switchBagInvisible();

    //_player->getBag()->addItem(MagiciteSkillCardFireBall::create(_phyLayer));
    //_player->getBag()->addItem(MagiciteSkillCardAcid::create(_phyLayer));
    //_player->getBag()->addItem(MagiciteSkillCardFlash::create(_phyLayer, 200));
    //_player->getBag()->addItem(MagiciteSkillCardSpeedUp::create());
    //_player->getBag()->addItem(MagiciteSkillCardSprint::create());
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
            auto enemy = MagiciteGameFactoryMethod::createEnemy(MagiciteGameFactoryMethod::Dirt, true);
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
            auto pit = MagiciteGameFactoryMethod::createPitfall(MagiciteGameFactoryMethod::Spine_Type);
            pit->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            _phyLayer->createPhyBody(pit, true);
            _phyLayer->addChild(pit);
        }
        else if (vm.at("type").asString() == "hole")
        {
            auto pit = MagiciteGameFactoryMethod::createPitfall(MagiciteGameFactoryMethod::Pitfall);
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
        if (vm.at("type").asString() == "cube" /*add*/ || vm.at("type").asString() == "platform"/*~*/)
        {
            float x = vm.at("x").asFloat();
            float w = vm.at("width").asFloat();
            float h = vm.at("height").asFloat();
            float y = vm.at("y").asFloat();
            auto node = MagiciteGameGround::create();
            node->setPosition(Vec2(x, y));
            node->setContentSize(Size(w, h));
            node->setAnchorPoint(Point::ZERO);
            _phyLayer->createPhyBody(node, true);
            _phyLayer->addChild(node);
            /*add*/node->setUserData(reinterpret_cast<void*>(vm.at("type").asString() == "platform"));/*~*/
        }
    }
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
            auto npc = MagiciteGameFactoryMethod::createFriend(MagiciteGameFactoryMethod::NPC, true);
            npc->setPosition(Vec2(vm.at("x").asFloat(), vm.at("y").asFloat()));
            npc->setContentSize(Size(vm.at("width").asFloat(), vm.at("height").asFloat()));
            _phyLayer->createPhyBody(npc, true);
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
    auto weatherEffect = weather->getWeatherEffect(Vec2(_background->getBackSize().width, _visibleSize.height));
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
            _phyLayer->createPhyBody(item, true);
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
    //create_item(game);
}

void MagiciteGameLayer::showText(const std::string& str)
{
    auto show = MagiciteGameShowLayer::create(2.0f, str);
    this->addChild(show, 1);
    show->start();
}