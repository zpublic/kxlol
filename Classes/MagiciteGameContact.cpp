#include "MagiciteGameContact.h"
#include "MagiciteGameObject.h"
#include "MagiciteGameGround.h"
#include "MagiciteGameLiving.h"
#include "MagiciteGamePitfall.h"
#include "MagiciteGameFireball.h"
#include "MagiciteGameMoveAbleLiving.h"
#include "MagiciteGameFactoryMethod.h"
#include "MagiciteGamePortal.h"

std::function<void(void)> MagiciteGameContact::_onWin;
std::function<void(void)> MagiciteGameContact::_onOver;
std::function<void(MagiciteItem*)> MagiciteGameContact::_onPick;
std::function<bool(b2Contact* contact)> MagiciteGameContact::_onJudgeContact;
std::function<void(b2Contact* contact)> MagiciteGameContact::_onBeginContact;

std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, std::function<void(MagiciteGameObject*, MagiciteGameObject*)>>> MagiciteGameContact::on_contact;
std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, bool>> MagiciteGameContact::judge_contact;
USING_NS_CC;

void MagiciteGameContact::change_moveable_direction(MagiciteGameMoveAbleLiving* moveObj)
{
    if (moveObj->getDire() == MagiciteGameMoveAbleLiving::Direction::right)
    {
        moveObj->setDire(MagiciteGameMoveAbleLiving::Direction::left);
    }
    else
    {
        moveObj->setDire(MagiciteGameMoveAbleLiving::Direction::right);
    }
    moveObj->Move(moveObj->getDire());
}

bool MagiciteGameContact::is_moveable_on_ground(MagiciteGameMoveAbleLiving* moveObj, MagiciteGameObject* ground)
{
    Vec2 objPos = moveObj->getPosition();
    Vec2 groundPos = ground->getPosition();
    Size objSize = moveObj->getContentSize();
    Size groundSize = ground->getContentSize();

    if (objPos.x + objSize.width / 2 > groundPos.x - groundSize.width / 2
        && objPos.x - objSize.width / 2 < groundPos.x + groundSize.width / 2)
    {
        return true;
    }
    return false;
}

bool MagiciteGameContact::is_moveable_above_ground(MagiciteGameMoveAbleLiving* moveObj, MagiciteGameObject* ground)
{
    if (moveObj->getPositionY() - moveObj->getContentSize().height / 2 
        >= ground->getPositionY() + ground->getContentSize().height / 2)
    {
        return true;
    }
    return false;
}

void MagiciteGameContact::try_to_change_living_direction(MagiciteGameLiving* living)
{
    if (living->LivingMoveType == MagiciteGameLiving::MoveAbleLiving)
    {
        change_moveable_direction(reinterpret_cast<MagiciteGameMoveAbleLiving*>(living));
    }
}

void MagiciteGameContact::resiger_contact()
{
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_ammo_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_LAND] = true;
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_LAND] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_LAND] = true;
    judge_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_LAND] = true;


    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_pitfall, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_END][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_end, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_ITEM][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_item, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PORTAL][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_protal, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PLAYER] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_PLAYER] = true;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_PLAYER] = true;
    judge_contact[Magicite::FIXTURE_TYPE_END][Magicite::FIXTURE_TYPE_PLAYER] = true;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_PLAYER] = true;
    judge_contact[Magicite::FIXTURE_TYPE_ITEM][Magicite::FIXTURE_TYPE_PLAYER] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PORTAL][Magicite::FIXTURE_TYPE_PLAYER] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_PLAYER] = true;



    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_friend_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_friend_contact_with_pitfall, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_FRIEND] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_FRIEND] = true;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_FRIEND] = true;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_FRIEND] = true;


    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_friend_contact_with_pitfall, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_player_contact_with_pitfall, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_enemy_contact_with_hole, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_PITFALL] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PITFALL] = true;
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PITFALL] = true;


    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_friend_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_player_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_enemy_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_ammo_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_enemy_contact_with_hole, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_ENEMY] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ENEMY] = true;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_ENEMY] = true;
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_ENEMY] = true;
    judge_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_ENEMY] = true;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_ENEMY] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_ENEMY] = true;


    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_END] = std::bind(try_player_contact_with_end, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_END] = true;

    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_AMMO] = std::bind(try_ammo_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_AMMO] = std::bind(try_ammo_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_AMMO] = std::bind(try_ammo_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_AMMO] = true;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_AMMO] = true;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_AMMO] = true;

    on_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTRUE_TYPE_EDGE] = std::bind(try_ammo_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTRUE_TYPE_EDGE] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTRUE_TYPE_EDGE] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTRUE_TYPE_EDGE] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTRUE_TYPE_EDGE] = true;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTRUE_TYPE_EDGE] = true;
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTRUE_TYPE_EDGE] = true;
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTRUE_TYPE_EDGE] = true;

    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ITEM] = std::bind(try_player_contact_with_item, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ITEM] = true;

    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PORTAL] = std::bind(try_player_contact_with_protal, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PORTAL] = true;

    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PLATFORM] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);

}

void MagiciteGameContact::try_living_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameGround* ground = reinterpret_cast<MagiciteGameGround*>(objectB);

    if (MagiciteGameContact::is_moveable_on_ground(living, ground))
    {
        if (MagiciteGameContact::is_moveable_above_ground(living, ground))
        {
            living->JumpOver();
            if (living->_is_contraled)
            {
                ground->onStep();
            }
        }
    }
    else
    {
        if (living->_is_contraled == false && is_moveable_above_ground(living, ground) == false)
        {
            MagiciteGameContact::change_moveable_direction(living);
        }
    }
}

void MagiciteGameContact::try_player_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* player = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameLiving* enemy = reinterpret_cast<MagiciteGameLiving*>(objectB);

    Vec2 playerPos = player->getPosition();
    Vec2 enemyPos = enemy->getPosition();
    Size playergSize = player->getContentSize();
    Size enemySize = enemy->getContentSize();

    if (playerPos.x + playergSize.width / 2 > enemyPos.x - enemySize.width / 2
        && playerPos.x - playergSize.width / 2 < enemyPos.x + enemySize.width / 2)
    {
        if (playerPos.y - playergSize.height / 2 + -1 * (player->getBody()->GetLinearVelocity().y) + 1
            >= enemyPos.y + enemySize.height / 2)
        {
            enemy->attact();
            if (enemy->getHP() <= 0)
            {
                MagiciteGameFactoryMethod::destroyEnemy(enemy);
            }
            player->JumpOver();
            player->Jump();
        }
        else
        {
            player->attact();
            if (player->getHP() <= 0)
            {
                onOver();
            }
        }
    }
}

void MagiciteGameContact::try_player_contact_with_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* player = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGamePitfall* pitfall = reinterpret_cast<MagiciteGamePitfall*>(objectB);
    if (pitfall->getPitFallAvtive())
    {
        player->attact();
        if (player->getHP() <= 0)
        {
            onOver();
        }
    }
}

void MagiciteGameContact::try_friend_contact_with_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGamePitfall* pitfall = reinterpret_cast<MagiciteGamePitfall*>(objectB);
    if (pitfall->getPitFallAvtive())
    {
        living->attact();
        if (living->getHP() <= 0)
        {
            MagiciteGameFactoryMethod::destroyFriend(living);
        }
        if (pitfall->PiffallType == MagiciteGamePitfall::Spine)
        {
            MagiciteGameFactoryMethod::destroyPitfall(pitfall);
        }
    }
}

void MagiciteGameContact::try_friend_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameMoveAbleLiving* enemy = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectB);

    MagiciteGameContact::change_moveable_direction(living);
    living->attact();
    if (living->getHP() <= 0)
    {
        MagiciteGameFactoryMethod::destroyFriend(living);
    }
    MagiciteGameContact::change_moveable_direction(enemy);
    enemy->attact();
    if (enemy->getHP() <= 0)
    {
        MagiciteGameFactoryMethod::destroyEnemy(enemy);
    }
}

void MagiciteGameContact::try_enemy_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto livingA = reinterpret_cast<MagiciteGameLiving*>(objectA);
    auto livingB = reinterpret_cast<MagiciteGameLiving*>(objectB);
    MagiciteGameContact::try_to_change_living_direction(livingA);
    MagiciteGameContact::try_to_change_living_direction(livingB);
}

void MagiciteGameContact::try_player_contact_with_end(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    onWin();
}

void MagiciteGameContact::try_ammo_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto ammo = reinterpret_cast<MagiciteGameAmmo*>(objectA);
    auto enemy = reinterpret_cast<MagiciteGameLiving*>(objectB);
    ammo->Dead();
    enemy->attact();
    if (enemy->getHP() <= 0)
    {
        MagiciteGameFactoryMethod::destroyEnemy(enemy);
    }
}

void MagiciteGameContact::try_ammo_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    reinterpret_cast<MagiciteGameAmmo*>(objectA)->Dead();
}

void MagiciteGameContact::try_ammo_contact_with_edge(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    reinterpret_cast<MagiciteGameAmmo*>(objectA)->Dead();
}

void MagiciteGameContact::try_living_contact_with_edge(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto moveLiving = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    if (!moveLiving->_is_contraled)
    {
        MagiciteGameContact::try_to_change_living_direction(moveLiving);
    }
}

void MagiciteGameContact::onWin()
{
    _onWin();
}

void MagiciteGameContact::onOver()
{
    _onOver();
}

void MagiciteGameContact::try_enemy_contact_with_hole(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    reinterpret_cast<MagiciteGameLiving*>(objectA)->Dead();
}

void MagiciteGameContact::try_player_contact_with_item(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    _onPick(reinterpret_cast<MagiciteItem*>(objectB));
}

void MagiciteGameContact::try_player_contact_with_protal(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    /*auto portal = reinterpret_cast<MagiciteGamePortal*>(objectB);
    auto player = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);

    auto portal_pos = portal->getPair()->getBody()->GetPosition();
    player->getBody()->SetTransform(portal_pos, 0);*/

}