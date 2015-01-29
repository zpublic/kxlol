#include "MagiciteGameContactListener.h"

USING_NS_CC;

void MagiciteGameContactListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    auto spriteA = reinterpret_cast<MagiciteGamePhySprite*>(bodyA->GetUserData());
    auto spriteB = reinterpret_cast<MagiciteGamePhySprite*>(bodyB->GetUserData());
    if (spriteA != nullptr && spriteB != nullptr)
    {
        if (spriteA == _player || spriteB == _player)
        {
            auto node = (spriteA != _player ? spriteA : spriteB);
            Vec2 playerPos = _player->getPosition();
            Vec2 nodePos = node->getPosition();
            Size playerSize = _player->getContentSize();
            Size nodeSize = node->getContentSize();
            if (playerPos.x + playerSize.width / 2 > nodePos.x - nodeSize.width / 2
                && playerPos.x - playerSize.width / 2 < nodePos.x + nodeSize.width / 2
                && playerPos.y > nodePos.y)
            {
                _player->setState(MagiciteGameLivine::State::S_Jump, false);
            }
        }
    }
}

void MagiciteGameContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void MagiciteGameContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

void MagiciteGameContactListener::EndContact(b2Contact* contact)
{

}

MagiciteGameContactListener* MagiciteGameContactListener::create(MagiciteGameLivine* player)
{
    auto ptr = new MagiciteGameContactListener();
    if (ptr && ptr->init(player))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGameContactListener::init(MagiciteGameLivine* player)
{
    _player = player;
    return true;
}