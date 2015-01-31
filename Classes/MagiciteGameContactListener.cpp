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
        if (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living
            || spriteB->_SpriteType == MagiciteGamePhySprite::T_Living)
        {
            if (spriteA->_SpriteType == spriteB->_SpriteType)
            {
                MagiciteGameLiving* livingA = reinterpret_cast<MagiciteGameLiving*>(spriteA);
                MagiciteGameLiving* livingB = reinterpret_cast<MagiciteGameLiving*>(spriteB);
                MagiciteGamePlayer* player = nullptr;
                MagiciteGameEnemy* enemy = nullptr;
                if (livingA->_LivingType == MagiciteGameLiving::T_Player)
                {
                    player = reinterpret_cast<MagiciteGamePlayer*>(livingA);
                    enemy = reinterpret_cast<MagiciteGameEnemy*>(livingB);
                }
                else
                {
                    player = reinterpret_cast<MagiciteGamePlayer*>(livingB);
                    enemy = reinterpret_cast<MagiciteGameEnemy*>(livingA);
                }

                Vec2 playerPos = player->getPosition();
                Vec2 enemyPos = enemy->getPosition();
                Size playerSize = player->getContentSize();
                Size enemySize = enemy->getContentSize();
                if (playerPos.x + playerSize.width / 2 > enemyPos.x - enemySize.width / 2
                    && playerPos.x - playerSize.width / 2 < enemyPos.x + enemySize.width / 2
                    && playerPos.y > enemyPos.y + enemySize.height / 2)
                {
                    player->setState(MagiciteGameLiving::State::S_Jump, false);
                    player->Jump();
                    MagiciteGameEnemyManager::getInstance()->destroyEnemy(enemy);
                }
                else
                {
                    log("dead");
                }
            }
            else
            {
                MagiciteGameLiving*         player = nullptr;
                MagiciteGamePhySprite*      ground = nullptr;
                if (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living)
                {
                    player = reinterpret_cast<MagiciteGameLiving*>(spriteA);
                    ground = spriteB;
                }
                else
                {
                    player = reinterpret_cast<MagiciteGameLiving*>(spriteB);
                    ground = spriteA;
                }

                Vec2 playerPos = player->getPosition();
                Vec2 groundPos = ground->getPosition();
                Size playerSize = player->getContentSize();
                Size groundSize = ground->getContentSize();

                if (playerPos.x + playerSize.width / 2 > groundPos.x - groundSize.width / 2
                    && playerPos.x - playerSize.width / 2 < groundPos.x + groundSize.width / 2
                    && playerPos.y > groundPos.y)
                {
                    player->setState(MagiciteGameLiving::State::S_Jump, false);
                }
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

MagiciteGameContactListener* MagiciteGameContactListener::create()
{
    auto ptr = new MagiciteGameContactListener();
    if (ptr && ptr->init())
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGameContactListener::init()
{
    return true;
}