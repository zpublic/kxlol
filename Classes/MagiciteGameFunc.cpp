#include "MagiciteGameFunc.h"

USING_NS_CC;

bool MagiciteGameFunc::is_player_to_end(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB)
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
            return true;
        }
    }
    return false;
}

bool MagiciteGameFunc::is_sprite_type_same(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB)
{
    if (spriteA->_SpriteType == spriteB->_SpriteType) return true;
    return false;
}

bool MagiciteGameFunc::is_has_living(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB)
{
    if (spriteA->_SpriteType == MagiciteGamePhySprite::T_Living
        || spriteB->_SpriteType == MagiciteGamePhySprite::T_Living)
    {
        return true;
    }
    return false;
}

bool MagiciteGameFunc::is_living_type_same(MagiciteGameLiving *livingA, MagiciteGameLiving* livingB)
{
    if (livingA->_LivingType == livingB->_LivingType) return true;
    return false;
}

void MagiciteGameFunc::changeEnemyDirection(MagiciteGameEnemy* enemy)
{
    enemy->setMoveDire(enemy->getMoveDire() == MagiciteGameLiving::Direction::left ?
        MagiciteGameLiving::Direction::right :
        MagiciteGameLiving::Direction::left);
}

bool MagiciteGameFunc::is_player_and_enemy(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB)
{
    if ((livingA->_LivingType == MagiciteGameLiving::T_Player
        &&livingB->_LivingType == MagiciteGameLiving::T_Enemy)
        || (livingA->_LivingType == MagiciteGameLiving::T_Enemy
        &&livingB->_LivingType == MagiciteGameLiving::T_Player))
    {
        return true;
    }
    return false;
}

MagiciteGamePlayer* MagiciteGameFunc::trivialPlayer(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB)
{
    if (livingA->_LivingType == MagiciteGameLiving::LivingType::T_Player)
    {
        return reinterpret_cast<MagiciteGamePlayer*>(livingA);
    }
    return reinterpret_cast<MagiciteGamePlayer*>(livingB);
}

MagiciteGameEnemy* MagiciteGameFunc::trivialEnemy(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB)
{
    if (livingA->_LivingType == MagiciteGameLiving::LivingType::T_Enemy)
    {
        return reinterpret_cast<MagiciteGameEnemy*>(livingA);
    }
    return reinterpret_cast<MagiciteGameEnemy*>(livingB);
}

bool MagiciteGameFunc::is_player_above_enemy(MagiciteGamePlayer* player, MagiciteGameEnemy* enemy)
{
    Vec2 playerPos = player->getPosition();
    Vec2 enemyPos = enemy->getPosition();
    Size playerSize = player->getContentSize();
    Size enemySize = enemy->getContentSize();

    if (playerPos.x + playerSize.width / 2 > enemyPos.x - enemySize.width / 2
        && playerPos.x - playerSize.width / 2 < enemyPos.x + enemySize.width / 2
        && playerPos.y > enemyPos.y + enemySize.height / 2)
    {
        return true;
    }
    return false;
}

MagiciteGameLiving* MagiciteGameFunc::trivialLiving(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB)
{
    if (spriteA->_SpriteType == MagiciteGamePhySprite::SpriteType::T_Living)
    {
        return reinterpret_cast<MagiciteGameLiving*>(spriteA);
    }
    return reinterpret_cast<MagiciteGameLiving*>(spriteB);
}

MagiciteGamePhySprite* MagiciteGameFunc::trivialGround(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB)
{
    if (spriteA->_SpriteType == MagiciteGamePhySprite::T_Ground)
    {
        return spriteA;
    }
    return spriteB;
}

bool MagiciteGameFunc::is_living_above_ground(MagiciteGameLiving* living, MagiciteGamePhySprite* ground)
{
    Vec2 livingPos = living->getPosition();
    Vec2 groundPos = ground->getPosition();
    Size livingSize = living->getContentSize();
    Size groundSize = ground->getContentSize();

    if (livingPos.x + livingSize.width / 2 > groundPos.x - groundSize.width / 2
        && livingPos.x - livingSize.width / 2 < groundPos.x + groundSize.width / 2
        && livingPos.y > groundPos.y + groundSize.height / 2)
    {
        return true;
    }
    return false;
}

bool MagiciteGameFunc::is_enemy_on_ground(MagiciteGameEnemy* enemy, MagiciteGamePhySprite* ground)
{
    Vec2 enemyPos = enemy->getPosition();
    Vec2 groundPos = ground->getPosition();
    Size enemySize = enemy->getContentSize();
    Size groundSize = ground->getContentSize();

    if (enemyPos.x + enemySize.width / 2 > groundPos.x - groundSize.width / 2
        && enemyPos.x - enemySize.width / 2 < groundPos.x + groundSize.width / 2)
    {
            return true;
    }
    return false;
}

bool MagiciteGameFunc::is_enemy_above_ground(MagiciteGameEnemy* enemy, MagiciteGamePhySprite* ground)
{
    if (enemy->getPositionY()> ground->getPositionY() + ground->getContentSize().height / 2)
    {
        return true;
    }
    return false;
}