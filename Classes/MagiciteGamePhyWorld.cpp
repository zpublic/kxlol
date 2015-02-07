#include "MagiciteGamePhyWorld.h"

USING_NS_CC;

MagiciteGamePhyWorld::MagiciteGamePhyWorld(b2Vec2 gravity)
:b2World(gravity), _contactListener(nullptr)
{

}

MagiciteGamePhyWorld::~MagiciteGamePhyWorld()
{

}

bool MagiciteGamePhyWorld::init(Size size, const std::function<void(b2Contact*)> &contactFunc)
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
    body->CreateFixture(&groundBox, 0);
    groundBox.Set(b2Vec2(0, boxSize.height / PTM_RATIO), b2Vec2(boxSize.width / PTM_RATIO, boxSize.height / PTM_RATIO));
    body->CreateFixture(&groundBox, 0);
    groundBox.Set(b2Vec2(0, boxSize.height / PTM_RATIO), b2Vec2(0, 0));
    body->CreateFixture(&groundBox, 0);
    groundBox.Set(b2Vec2(boxSize.width / PTM_RATIO, boxSize.height / PTM_RATIO), b2Vec2(boxSize.width / PTM_RATIO, 0));
    body->CreateFixture(&groundBox, 0);

    _contactListener = MagiciteGameContactListener::create(contactFunc);
    this->SetContactListener(_contactListener);

    return true;
}

void MagiciteGamePhyWorld::createPhyBody(MagiciteGameObject* ptr, bool is_static, uint16 Category, uint16 mask)
{
    b2BodyDef bodyDef;
    bodyDef.type = is_static ? b2_staticBody : b2_dynamicBody;
    bodyDef.position.Set(
        (ptr->getPositionX() + ptr->getContentSize().width / 2) / PTM_RATIO,
        (ptr->getPositionY() + ptr->getContentSize().height / 2) / PTM_RATIO);
    bodyDef.userData = ptr;
    b2Body* body = this->CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(ptr->getContentSize().width / 2 / PTM_RATIO, ptr->getContentSize().height / 2 / PTM_RATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.filter.categoryBits = Category;
    fixtureDef.filter.maskBits = mask;
    fixtureDef.friction = 0.0f;
    fixtureDef.shape = &dynamicBox;
    body->CreateFixture(&fixtureDef);
    ptr->setBody(body);
}

void MagiciteGamePhyWorld::updateBody()
{
    int velocityIterations = 8;
    int positionIterations = 1;
    this->Step(0.03f, velocityIterations, positionIterations);

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
                sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(it->GetAngle()));
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

MagiciteGamePhyWorld* MagiciteGamePhyWorld::create(b2Vec2 gravity, cocos2d::Size size, const std::function<void(b2Contact*)> &contactFunc)
{
    auto ptr = new MagiciteGamePhyWorld(gravity);
    if (ptr && ptr->init(size,contactFunc))
    {
        return ptr;
    }
    return nullptr;
}