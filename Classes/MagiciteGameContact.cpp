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
std::function<void(b2Contact* contace)> MagiciteGameContact::_onEndContact;

std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, std::function<void(MagiciteGameObject*, MagiciteGameObject*)>>> MagiciteGameContact::on_contact;
std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, std::function<void(MagiciteGameObject*, MagiciteGameObject*)>>> MagiciteGameContact::on_contact_end;

std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, MagiciteGameContact::ContactType>> MagiciteGameContact::judge_contact;
std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, bool>> MagiciteGameContact::judge_contact_end;

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
    on_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_ammo_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_player_contact_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact_end[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_player_leave_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_JUMP_POINT][Magicite::FIXTURE_TYPE_LAND] = std::bind(try_jump_point_contact_ground, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_JUMP_POINT][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Calture_Cancle;
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Contact;
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Contact;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_LAND] = MagiciteGameContact::Calcture;
    judge_contact_end[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_LAND] = true;


    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_pitfall, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_END][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_end, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_ITEM][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_item, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PORTAL][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_with_protal, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_contact_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact_end[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_PLAYER] = std::bind(try_player_leave_ground, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_END][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_ITEM][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PORTAL][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_PLAYER] = MagiciteGameContact::Calcture;
    judge_contact_end[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_PLAYER] = true;

    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_friend_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_friend_contact_with_pitfall, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_FRIEND] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_FRIEND] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_FRIEND] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_FRIEND] = MagiciteGameContact::Contact;
    judge_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_FRIEND] = MagiciteGameContact::Calcture;

    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_friend_contact_with_pitfall, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_player_contact_with_pitfall, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PITFALL] = std::bind(try_enemy_contact_with_hole, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_PITFALL] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PITFALL] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_PITFALL] = MagiciteGameContact::Calcture;

    on_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_friend_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_player_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_ENEMY][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_enemy_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_AMMO][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_ammo_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTRUE_TYPE_EDGE][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PITFALL][Magicite::FIXTURE_TYPE_ENEMY] = std::bind(try_enemy_contact_with_hole, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_FRIEND][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Calcture;
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_ENEMY] = MagiciteGameContact::Contact;
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

    on_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_JUMP_POINT] = std::bind(try_jump_point_contact_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_JUMP_POINT] = std::bind(try_jump_point_contact_ground, std::placeholders::_2, std::placeholders::_1);
    judge_contact[Magicite::FIXTURE_TYPE_LAND][Magicite::FIXTURE_TYPE_JUMP_POINT] = MagiciteGameContact::Calture_Cancle;
    judge_contact[Magicite::FIXTURE_TYPE_PLATFORM][Magicite::FIXTURE_TYPE_JUMP_POINT] = MagiciteGameContact::Calture_Cancle;

    on_contact[Magicite::FIXTURE_TYPE_JUMP_POINT][Magicite::FIXTURE_TYPE_PLATFORM] = std::bind(try_jump_point_contact_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Magicite::FIXTURE_TYPE_PLAYER][Magicite::FIXTURE_TYPE_PLATFORM] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    judge_contact[Magicite::FIXTURE_TYPE_JUMP_POINT][Magicite::FIXTURE_TYPE_PLATFORM] = MagiciteGameContact::Calture_Cancle;
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
    player->getBody()->SetGravityScale(0.0f);
}

void MagiciteGameContact::try_jump_point_contact_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto player = static_cast<MagiciteGameMoveAbleLiving*>(objectA);
    player->JumpOver();
}

void MagiciteGameContact::try_player_leave_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto player = static_cast<MagiciteGameMoveAbleLiving*>(objectA);
    player->getBody()->SetGravityScale(1.0f);
}

bool MagiciteGameContact::solve_one_side_platform(b2Body* player, b2Body* platform)
{
    const auto one_sided_redundance = 2.0f * b2_linearSlop;

    CCASSERT(player->GetFixtureList()->GetShape()->m_type == b2Shape::e_polygon, "bad shape");
    CCASSERT(platform->GetFixtureList()->GetShape()->m_type == b2Shape::e_polygon, "bad shape");
    b2PolygonShape* player_shape = nullptr;
    for (auto iter = player->GetFixtureList(); iter; iter = iter->GetNext())
    {
        if (static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(iter->GetUserData())) == Magicite::FIXTURE_TYPE_PLAYER)
        {
            player_shape = reinterpret_cast<b2PolygonShape*>(iter->GetShape());
        }
    }

    auto player_min_y = player_shape->m_vertices[0].y;
    for (auto i = 1; i < player_shape->m_count; i++) {
        if (player_shape->m_vertices[i].y < player_min_y) {
            player_min_y = player_shape->m_vertices[i].y;
        }
    }
    player_min_y += player->GetPosition().y;
    auto platform_shape = reinterpret_cast<b2PolygonShape*>(platform->GetFixtureList()->GetShape());
    auto platform_max_y = platform_shape->m_vertices[0].y;
    for (auto i = 1; i < platform_shape->m_count; i++) {
        if (platform_shape->m_vertices[i].y > platform_max_y) {
            platform_max_y = platform_shape->m_vertices[i].y;
        }
    }
    platform_max_y += platform->GetPosition().y;
    return player_min_y + one_sided_redundance <= platform_max_y;
}