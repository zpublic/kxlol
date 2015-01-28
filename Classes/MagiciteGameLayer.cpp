#include "MagiciteGameLayer.h"

USING_NS_CC;

MagiciteGameLayer::MagiciteGameLayer()
    :_world(nullptr)
{

}

MagiciteGameLayer::~MagiciteGameLayer()
{
    delete _world;
    _world = nullptr;
}

bool MagiciteGameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    this->setKeyboardEnabled(true);
    this->schedule(schedule_selector(MagiciteGameLayer::update));
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    initPhysics();

    _background = MagiciteGameMap::create();
    this->addChild(_background, 0);

    _player = MagiciteGamePhySprite::create("img\\avatar\\1.png");
    _player->setPosition(Vec2(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    this->addChild(_player, 1);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(_player->getPositionX() / PTM_RATIO, _player->getPositionY() / PTM_RATIO);
    bodyDef.userData = _player;
    b2Body* body = _world->CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(_player->getContentSize().width / 2 / PTM_RATIO, _player->getContentSize().height / 2 / PTM_RATIO);
    b2FixtureDef fixtureDef;                                                
    fixtureDef.shape = &dynamicBox;
    body->CreateFixture(&fixtureDef);
    _player->setBody(body);

    _move_left = false;
    _move_right = false;

    return true;
}

void MagiciteGameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        _move_left = true;
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
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
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        _move_left = false;
        _player->getBody()->SetLinearVelocity(b2Vec2(0, _player->getBody()->GetLinearVelocity().y));
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        _move_right = false;
        _player->getBody()->SetLinearVelocity(b2Vec2(0, _player->getBody()->GetLinearVelocity().y));
        break;
    default:
        break;
    }
}

void MagiciteGameLayer::update(float timeDelta)
{
    b2Vec2 bodyVelocity = _player->getBody()->GetLinearVelocity();
    if (_move_left && !_move_right)
    {
        if (_player->getPositionX() > _visibleSize.width / 3 + _origin.x)
        {
            _player->getBody()->SetLinearVelocity(b2Vec2(-3, bodyVelocity.y));
        }
        else
        {
            if (_background->is_left_open())
            {
                _player->getBody()->SetLinearVelocity(b2Vec2(0, bodyVelocity.y));
                _background->MoveMap(-3);
            }
            else
            {
                if (_player->getPositionX() >= _origin.x + 3)
                {
                    _player->getBody()->SetLinearVelocity(b2Vec2(-3, bodyVelocity.y));
                }
            }
        }
    }
    else if (!_move_left && _move_right)
    {
        if (_player->getPositionX() < _visibleSize.width / 3 * 2 + _origin.x)
        {
            _player->getBody()->SetLinearVelocity(b2Vec2(3, bodyVelocity.y));
        }
        else
        {
            if (_background->is_right_open())
            {
                _player->getBody()->SetLinearVelocity(b2Vec2(0, bodyVelocity.y));
                _background->MoveMap(+3);
            }
            else
            {
                if (_player->getPositionX() <= _visibleSize.width + _origin.x - 3)
                {
                    _player->getBody()->SetLinearVelocity(b2Vec2(3, bodyVelocity.y));
                }
            }
        }
    }

    int velocityIterations = 8;
    int positionIterations = 1;
    _world->Step(0.03f, velocityIterations, positionIterations);
    for (auto it = _world->GetBodyList(); it; it = it->GetNext())
    {
        if (it->GetUserData() != nullptr)
        {
            Sprite* sprite = reinterpret_cast<Sprite*>(it->GetUserData());
            sprite->setPosition(ccp(it->GetPosition().x * PTM_RATIO, it->GetPosition().y * PTM_RATIO));
            sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(it->GetAngle()));
        }
    }
}

void MagiciteGameLayer::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    _world = new b2World(gravity);
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    b2Body* body = _world->CreateBody(&groundBodyDef);
    Size boxSize = _visibleSize;

    b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0, 0), b2Vec2(boxSize.width / PTM_RATIO, 0));
    body->CreateFixture(&groundBox, 0);
    groundBox.Set(b2Vec2(0, boxSize.height / PTM_RATIO), b2Vec2(boxSize.width / PTM_RATIO, boxSize.height / PTM_RATIO));
    body->CreateFixture(&groundBox, 0);
    groundBox.Set(b2Vec2(0, boxSize.height / PTM_RATIO), b2Vec2(0, 0));
    body->CreateFixture(&groundBox, 0);
    groundBox.Set(b2Vec2(boxSize.width / PTM_RATIO, boxSize.height / PTM_RATIO), b2Vec2(boxSize.width / PTM_RATIO, 0));
    body->CreateFixture(&groundBox, 0);
}