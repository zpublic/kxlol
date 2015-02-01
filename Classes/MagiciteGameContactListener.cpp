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
        if ((spriteA->_SpriteType == MagiciteGamePhySprite::T_End
                || spriteB->_SpriteType == MagiciteGamePhySprite::T_End)
            && (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living 
                || spriteB->_SpriteType == MagiciteGamePhySprite::T_End))
        {
            MagiciteGameLiving* livingA = reinterpret_cast<MagiciteGameLiving*>(spriteA);
            MagiciteGameLiving* livingB = reinterpret_cast<MagiciteGameLiving*>(spriteB);
            if (livingA->_LivingType == MagiciteGameLiving::T_Player
                || livingB->_LivingType == MagiciteGameLiving::T_Player)
            {
                _win();
            }
        }

        if (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living
            || spriteB->_SpriteType == MagiciteGamePhySprite::T_Living)
        {
            if (spriteA->_SpriteType == spriteB->_SpriteType)
            {
                MagiciteGameLiving* livingA = reinterpret_cast<MagiciteGameLiving*>(spriteA);
                MagiciteGameLiving* livingB = reinterpret_cast<MagiciteGameLiving*>(spriteB);
                if (livingA->_LivingType == livingB->_LivingType)
                {
                    MagiciteGameEnemy* enemyA = reinterpret_cast<MagiciteGameEnemy*>(livingA);
                    MagiciteGameEnemy* enemyB = reinterpret_cast<MagiciteGameEnemy*>(livingB);
                    if (!enemyA->getPass())
                    {
                       enemyA->setMoveDire(enemyA->getMoveDire() == MagiciteGameLiving::Direction::left ?
                            MagiciteGameLiving::Direction::right:
                            MagiciteGameLiving::Direction::left);
                       enemyB->setMoveDire(enemyB->getMoveDire() == MagiciteGameLiving::Direction::left ?
                           MagiciteGameLiving::Direction::right :
                           MagiciteGameLiving::Direction::left);
                    }
                }
                else
                {
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
                        _manager->destroyEnemy(enemy);
                    }
                    else
                    {
                        _failed();
                    }
                }
            }
            else
            {
                MagiciteGameLiving*         living = nullptr;
                MagiciteGamePhySprite*      ground = nullptr;
                if (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living)
                {
                    living = reinterpret_cast<MagiciteGameLiving*>(spriteA);
                    ground = spriteB;
                }
                else
                {
                    living = reinterpret_cast<MagiciteGameLiving*>(spriteB);
                    ground = spriteA;
                }

                if (living->_LivingType == MagiciteGameLiving::T_Player)
                {
                    Vec2 playerPos = living->getPosition();
                    Vec2 groundPos = ground->getPosition();
                    Size playerSize = living->getContentSize();
                    Size groundSize = ground->getContentSize();

                    if (playerPos.x + playerSize.width / 2 > groundPos.x - groundSize.width / 2
                        && playerPos.x - playerSize.width / 2 < groundPos.x + groundSize.width / 2
                        && playerPos.y > groundPos.y + groundSize.height / 2)
                    {
                        living->setState(MagiciteGameLiving::State::S_Jump, false);
                    }
                }
                else
                {
                    MagiciteGameEnemy* enemy = reinterpret_cast<MagiciteGameEnemy*>(living);
                    Vec2 enemyPos = enemy->getPosition();
                    Vec2 groundPos = ground->getPosition();
                    Size enemySize = enemy->getContentSize();
                    Size groundSize = ground->getContentSize();

                    if (enemyPos.x + enemySize.width / 2 > groundPos.x - groundSize.width / 2
                        && enemyPos.x - enemySize.width / 2 < groundPos.x + groundSize.width / 2)
                    {
                        if (enemyPos.y > groundPos.y + groundSize.height / 2)
                        {
                            enemy->setState(MagiciteGameLiving::State::S_Jump, false);
                        }
                    }
                    else
                    {
                        enemy->setMoveDire(enemy->getMoveDire() == MagiciteGameLiving::Direction::left ?
                            MagiciteGameLiving::Direction::right :
                            MagiciteGameLiving::Direction::left);
                    }
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

MagiciteGameContactListener* MagiciteGameContactListener::create(
    MagiciteGameEnemyManager* manager, 
    const std::function<void(void)> &failed, 
    const std::function<void(void)> &win)
{
    auto ptr = new MagiciteGameContactListener();
    if (ptr && ptr->init(manager, failed, win))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteGameContactListener::init(
    MagiciteGameEnemyManager* manager, 
    const std::function<void(void)> &failed, 
    const std::function<void(void)> &win)
{
    _failed = failed;
    _win = win;
    _manager = manager;
    return true;
}