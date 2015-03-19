#include "MagiciteGameContactListener.h"
#include "MagiciteGameContact.h"
#include "MagiciteGamePhysics.h"

USING_NS_CC;

void MagiciteGameContactListener::BeginContact(b2Contact* contact)
{
    auto fixA = contact->GetFixtureA();
    auto fixB = contact->GetFixtureB();
    MagiciteGameObject* player = nullptr;
    MagiciteGameObject* ground = nullptr;
    if (static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(fixA->GetUserData())) == Magicite::FIXTURE_TYPE_JUMP_POINT &&
        static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(fixB->GetUserData())) == Magicite::FIXTURE_TYPE_LAND)
    {
        player = reinterpret_cast<MagiciteGameObject*>(fixA->GetBody()->GetUserData());
        ground = reinterpret_cast<MagiciteGameObject*>(fixB->GetBody()->GetUserData());
    }
    else if (static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(fixB->GetUserData())) == Magicite::FIXTURE_TYPE_LAND &&
        static_cast<Magicite::FIXTURE_TYPE>(reinterpret_cast<int>(fixA->GetUserData())) == Magicite::FIXTURE_TYPE_JUMP_POINT)
    {
        player = reinterpret_cast<MagiciteGameObject*>(fixB->GetBody()->GetUserData());
        ground = reinterpret_cast<MagiciteGameObject*>(fixA->GetBody()->GetUserData());
    }
    else
    {
        return;
    }
    MagiciteGameContact::try_player_contact_ground(player, ground);
    contact->SetEnabled(false);

}

void MagiciteGameContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    if (MagiciteGameContact::_onJudgeContact(contact))
    {
        MagiciteGameContact::_onBeginContact(contact);
    }
    else
    {
        contact->SetEnabled(false);
    }
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
