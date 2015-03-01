#include "MagiciteGamePhyLayer.h"
#include "MagiciteGameObject.h"
#include "MagiciteGamePhyWorld.h"

USING_NS_CC;

MagiciteGamePhyLayer::MagiciteGamePhyLayer()
    :_world(nullptr)
{

}

MagiciteGamePhyLayer::~MagiciteGamePhyLayer()
{
    CC_SAFE_DELETE(_world);
    CC_SAFE_DELETE(_debugDraw);
}

bool MagiciteGamePhyLayer::initPhysics(Size size)
{
    if (!Layer::init())
    {
        return false;
    }

    _visibleSize = Director::getInstance()->getVisibleSize();
    this->schedule(schedule_selector(MagiciteGamePhyLayer::update));

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    _world = MagiciteGamePhyWorld::create(gravity, size);
    
    _debugDraw = new GLESDebugDraw(PTM_RATIO);
    _world->SetDebugDraw(_debugDraw);
    uint32 flags = 0;

#ifdef MAGICITE_DEBUG_ON
    flags += b2Draw::e_shapeBit;
#endif

    _debugDraw->SetFlags(flags);

    return true;
}

void MagiciteGamePhyLayer::createPhyBody(
    MagiciteGameObject* ptr, 
    bool is_static)
{
    _world->createPhyBody(ptr, is_static);
}

void MagiciteGamePhyLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
    _world->DrawDebugData();
    CHECK_GL_ERROR_DEBUG();
}

void MagiciteGamePhyLayer::update(float timeDelta)
{
    _world->updateBody();
}

MagiciteGamePhyLayer* MagiciteGamePhyLayer::create(Size size)
{
    auto ptr = new MagiciteGamePhyLayer();
    if (ptr && ptr->initPhysics(size))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGamePhyLayer::Ray_Cast(MagiciteGameMoveAbleLiving* sprite, float length, b2Fixture*& outFix, float& output)
{
    int dire = (sprite->getDire() == MagiciteGameMoveAbleLiving::Direction::right ? 1 : -1);
    b2Body* body = sprite->getBody();
    b2RayCastInput hin;
    hin.p1 = body->GetPosition();
    hin.p2 = b2Vec2(
        body->GetPosition().x + length / PTM_RATIO * dire,
        (sprite->getPosition().y + sprite->getContentSize().width / 2) / PTM_RATIO);
    hin.maxFraction = 1;
    b2RayCastInput fin;
    fin.p1 = body->GetPosition();
    fin.p2 = b2Vec2(
        body->GetPosition().x + length / PTM_RATIO * dire,
        (sprite->getPosition().y - sprite->getContentSize().width / 2) / PTM_RATIO + 1);
    fin.maxFraction = 1;

    b2RayCastOutput out;
    b2Fixture* fixture = nullptr;
    bool flagHead = false;
    bool flagFoot = false;

    for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
    {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
        {
            if (f->RayCast(&out, hin, 0))
            {
                flagHead = true;
                fixture = f;
                break;
            }
            if (f->RayCast(&out, fin, 0))
            {
                flagFoot = true;
                fixture = f;
                break;
            }
        }
        if (flagFoot || flagHead) break;
    }

    output = out.fraction;
    outFix = fixture;
    return flagFoot || flagHead;
}