#include "MagiciteGamePhyWorld.h"
#include "MagiciteGameObject.h"
#include "MagiciteGameContactListener.h"
#include "MagiciteGamePhysics.h"

USING_NS_CC;

MagiciteGamePhyWorld::MagiciteGamePhyWorld(b2Vec2 gravity)
:b2World(gravity), _contactListener(nullptr)
{

}

MagiciteGamePhyWorld::~MagiciteGamePhyWorld()
{

}

bool MagiciteGamePhyWorld::init(Size size)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    this->SetAllowSleeping(true);
    this->SetContinuousPhysics(true);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);

    b2Body* body = this->CreateBody(&groundBodyDef);
    if (body == nullptr)
    {
        return false;
    }
    Size boxSize = Size(size.width, visibleSize.height);

    b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0, 0), b2Vec2(boxSize.width / PTM_RATIO, 0));
    auto fix = body->CreateFixture(&groundBox, 0);
    fix->SetUserData(reinterpret_cast<void*>(Magicite::FIXTRUE_TYPE_EDGE));
    groundBox.Set(b2Vec2(0, boxSize.height / PTM_RATIO), b2Vec2(boxSize.width / PTM_RATIO, boxSize.height / PTM_RATIO));
    fix = body->CreateFixture(&groundBox, 0);
    fix->SetUserData(reinterpret_cast<void*>(Magicite::FIXTRUE_TYPE_EDGE));

    groundBox.Set(b2Vec2(0, boxSize.height / PTM_RATIO), b2Vec2(0, 0));
    fix = body->CreateFixture(&groundBox, 0);
    fix->SetUserData(reinterpret_cast<void*>(Magicite::FIXTRUE_TYPE_EDGE));

    groundBox.Set(b2Vec2(boxSize.width / PTM_RATIO, boxSize.height / PTM_RATIO), b2Vec2(boxSize.width / PTM_RATIO, 0));
    fix = body->CreateFixture(&groundBox, 0);
    fix->SetUserData(reinterpret_cast<void*>(Magicite::FIXTRUE_TYPE_EDGE));


    _contactListener = MagiciteGameContactListener::create();
    this->SetContactListener(_contactListener);

    return true;
}

void MagiciteGamePhyWorld::createPhyBody(MagiciteGameObject* ptr, bool is_static, Magicite::FIXTURE_TYPE type)
{
    b2BodyDef bodyDef;
    bodyDef.type = is_static ? b2_staticBody : b2_dynamicBody;
    bodyDef.position.Set(
        (ptr->getPositionX() + ptr->getContentSize().width / 2) / PTM_RATIO,
        (ptr->getPositionY() + ptr->getContentSize().height / 2) / PTM_RATIO);
    bodyDef.userData = ptr;
    b2Body* body = this->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(ptr->getContentSize().width / 2 / PTM_RATIO, ptr->getContentSize().height / 2 / PTM_RATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.friction = 0.0f;
    fixtureDef.shape = &dynamicBox;
    auto bodyfix = body->CreateFixture(&fixtureDef);
    bodyfix->SetUserData(reinterpret_cast<void*>(type));

    if (type == Magicite::FIXTURE_TYPE_PLAYER || type == Magicite::FIXTURE_TYPE_ENEMY || type == Magicite::FIXTURE_TYPE_FRIEND)
    {
        b2PolygonShape polygonShape;
        polygonShape.SetAsBox(0.3f, 0.3f, b2Vec2(0.03f, ptr->getContentSize().height / 2.0f / -PTM_RATIO), 0);

        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygonShape;
        myFixtureDef.density = 1;

        body->CreateFixture(&myFixtureDef);
        b2Fixture* footSensorFixture = body->CreateFixture(&myFixtureDef);
        footSensorFixture->SetUserData(reinterpret_cast<void*>(Magicite::FIXTURE_TYPE_JUMP_POINT));
    }
    ptr->setBody(body);
}

void MagiciteGamePhyWorld::updateBody(float timeDelta)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    this->Step(timeDelta * 2.0f, velocityIterations, positionIterations);

    std::vector<b2Body*> deadlist;
    for (auto it = this->GetBodyList(); it; it = it->GetNext())
    {
        if (it->GetUserData() != nullptr)
        {
            MagiciteGamePhySprite* sprite = reinterpret_cast<MagiciteGamePhySprite*>(it->GetUserData());
            if (sprite->isDead())
            {
                deadlist.push_back(it);
            }
            else
            {
                sprite->setPosition(Vec2(it->GetPosition().x * PTM_RATIO, it->GetPosition().y * PTM_RATIO));
                sprite->setRotation(0.0f);
            }
        }
    }
    for (auto ptr : deadlist)
    {
        auto spriteDead = reinterpret_cast<MagiciteGamePhySprite*>(ptr->GetUserData());
        this->DestroyBody(ptr);
        spriteDead->removeFromParentAndCleanup(true);
    }
}

MagiciteGamePhyWorld* MagiciteGamePhyWorld::create(b2Vec2 gravity, Size size)
{
    auto ptr = new MagiciteGamePhyWorld(gravity);
    if (ptr && ptr->init(size))
    {
        return ptr;
    }
    return nullptr;
}

b2Body* MagiciteGamePhyWorld::createBody(b2BodyDef* bd)
{
    return this->CreateBody(bd);
}