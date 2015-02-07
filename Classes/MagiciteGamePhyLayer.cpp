#include "MagiciteGamePhyLayer.h"

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

bool MagiciteGamePhyLayer::initPhysics(Size size, const std::function<void(b2Contact*)> &contactFunc)
{
    if (!Layer::init())
    {
        return false;
    }

    _visibleSize = Director::getInstance()->getVisibleSize();
    this->schedule(schedule_selector(MagiciteGamePhyLayer::update));

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    _world = MagiciteGamePhyWorld::create(gravity, size, contactFunc);
    
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
    bool is_static,
    uint16 Category /*= MagiciteGameObject::DEFAULT_GROUND*/,
    uint16 mask /*= MagiciteGameObject::DEFAULT_ALL*/)
{
    _world->createPhyBody(ptr, is_static, Category, mask);
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

MagiciteGamePhyLayer* MagiciteGamePhyLayer::create(Size size, const std::function<void(b2Contact*)> &contactFunc)
{
    auto ptr = new MagiciteGamePhyLayer();
    if (ptr && ptr->initPhysics(size,contactFunc))
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
