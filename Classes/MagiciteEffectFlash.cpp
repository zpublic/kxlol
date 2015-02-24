#include "MagiciteEffectFlash.h"

USING_NS_CC;

MagiciteEffectFlash::MagiciteEffectFlash(MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAbleLiving* player, float length)
:_phyLayer(phyLayer), _player(player), _length(length)
{

}


void MagiciteEffectFlash::positive()
{
    int PTM_RATIO = MagiciteGamePhyLayer::PTM_RATIO;

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

    delete this;
}

void MagiciteEffectFlash::negative()
{

}