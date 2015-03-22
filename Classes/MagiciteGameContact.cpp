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
std::function<MagiciteGameContact::ContactType(b2Contact* contact)> MagiciteGameContact::_onJudgeContact;
std::function<void(b2Contact* contact)> MagiciteGameContact::_onBeginContact;

std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, std::function<void(MagiciteGameObject*, MagiciteGameObject*)>>> MagiciteGameContact::on_contact;
std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, MagiciteGameContact::ContactType>> MagiciteGameContact::judge_contact;
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

void MagiciteGameContact::try_to_change_living_direction(MagiciteGameLiving* living)
{
    if (living->LivingMoveType == MagiciteGameLiving::MoveAbleLiving)
    {
        change_moveable_direction(reinterpret_cast<MagiciteGameMoveAbleLiving*>(living));
    }
}

void MagiciteGameContact::resiger_contact()
{
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_player_contact_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_player_contact_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_ammo_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Contact;
    judge_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Calcture;


    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_pitfall, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_END][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_end, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_ITEM][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_item, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PORTAL][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_protal, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Contact;
    judge_contact[Magicite::FIXTURE_TYPE_END][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_ITEM][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PORTAL][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;


    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_friend_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_friend_contact_with_pitfall, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_player_contact_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_FRIEND] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_FRIEND] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_FRIEND] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_FRIEND] = MagiciteGameContact::Calcture;


    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_friend_contact_with_pitfall, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_player_contact_with_pitfall, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_enemy_contact_with_hole, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_PITFALL] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PITFALL] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PITFALL] = MagiciteGameContact::Calcture;


    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_friend_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_player_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_player_contact_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_enemy_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_ammo_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_enemy_contact_with_hole, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;


    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_END] = std::bind(try_player_contact_with_end, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_END] = MagiciteGameContact::Calcture;

    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_AMMO] = std::bind(try_ammo_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_AMMO] = std::bind(try_ammo_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_AMMO] = std::bind(try_ammo_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_AMMO] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_AMMO] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_AMMO] = MagiciteGameContact::Calcture;

    on_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTRUE_TYPE_EDGE] = std::bind(try_ammo_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTRUE_TYPE_EDGE] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTRUE_TYPE_EDGE] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTRUE_TYPE_EDGE] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTRUE_TYPE_EDGE] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTRUE_TYPE_EDGE] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTRUE_TYPE_EDGE] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTRUE_TYPE_EDGE] = MagiciteGameContact::Calcture;

    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ITEM] = std::bind(try_player_contact_with_item, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ITEM] = MagiciteGameContact::Calcture;

    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PORTAL] = std::bind(try_player_contact_with_protal, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PORTAL] = MagiciteGameContact::Calcture;

    on_contact[Magicite::FIXTURE_TYPE_JUMP_POINT][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_player_contact_ground, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_JUMP_POINT][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Calture_Cancle;

    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_JUMP_POINT] = std::bind(try_player_contact_ground, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_JUMP_POINT] = MagiciteGameContact::Calture_Cancle;

    on_contact[Magicite::FIXTURE_TYPE_JUMP_POINT][Magicite::FIXTURE_TYPE_PLATFORM] = std::bind(try_player_contact_ground, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_JUMP_POINT][Magicite::FIXTURE_TYPE_PLATFORM] = MagiciteGameContact::Calture_Cancle;

    on_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_JUMP_POINT] = std::bind(try_player_contact_ground, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_JUMP_POINT] = MagiciteGameContact::Calture_Cancle;

    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PLATFORM] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PLATFORM] = MagiciteGameContact::Calcture;

}

void MagiciteGameContact::try_living_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameGround* ground = reinterpret_cast<MagiciteGameGround*>(objectB);
    if (living->_is_contraled == false)
    {
        MagiciteGameContact::change_moveable_direction(living);
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

void MagiciteGameContact::try_player_contact_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto player = static_cast<MagiciteGameMoveAbleLiving*>(objectA);
    player->JumpOver();
}
