#include "MagiciteEffectFlash.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteEffectFlash::MagiciteEffectFlash()
{

}


void MagiciteEffectFlash::positive(MagiciteGameObject* obj)
{
    int PTM_RATIO = MagiciteGamePhyLayer::PTM_RATIO;
    auto _player = static_cast<MagiciteGameMoveAbleLiving*>(obj);

    b2Fixture* fixture = nullptr;
    float fraction = 0.0f;
    bool flag = _phyLayer->Ray_Cast(_player, _length, fixture, fraction);
    int dire = (_player->getDire() == MagiciteGameMoveAbleLiving::Direction::right ? 1 : -1);
    b2Vec2 distance(_length / PTM_RATIO * fraction, 0);

    b2Body* body = _player->getBody();

    if (!flag)
    {
        b2Vec2 pos(body->GetPosition().x + _length / PTM_RATIO * dire, body->GetPosition().y);
        body->SetTransform(pos, 0);
    }
    else
    {
        MagiciteGameObject* obj = reinterpret_cast<MagiciteGameObject*>(fixture->GetBody()->GetUserData());
        if (obj == nullptr)
        {
            b2Vec2 pos(
                body->GetPosition().x + (distance.x - _player->getContentSize().width / 2 / PTM_RATIO) * dire,
                body->GetPosition().y);
            body->SetTransform(pos, 0);
        }
        else
        {
            if ((obj->getContentSize().width + _length * fraction + _player->getContentSize().width / 2 < _length))
            {
                b2Vec2 pos(body->GetPosition().x + _length / PTM_RATIO * dire, body->GetPosition().y);
                body->SetTransform(pos, 0);
            }
            else
            {
                b2Vec2 pos(body->GetPosition().x + (distance.x - _player->getContentSize().width / 2 / PTM_RATIO) * dire,
                    body->GetPosition().y);
                body->SetTransform(pos, 0);
            }
        }
    }
    body->SetAwake(true);

}

void MagiciteEffectFlash::negative()
{

}

MagiciteEffectFlash* MagiciteEffectFlash::create(MagiciteGamePhyLayer* phyLayer, float length)
{
    auto ptr = new MagiciteEffectFlash();
    if (ptr && ptr->init(phyLayer, length))
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

bool MagiciteEffectFlash::init(MagiciteGamePhyLayer* phyLayer, float length)
{
    _phyLayer = phyLayer;
    _length = length;

    setCd(cool_down);

    return true;
}