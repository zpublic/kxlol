#include "MagiciteGameContactListener.h"
#include "MagiciteGameContact.h"
#include "MagiciteGamePhysics.h"

USING_NS_CC;

void MagiciteGameContactListener::BeginContact(b2Contact* contact)
{
    

}

void MagiciteGameContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    auto tag = MagiciteGameContact::_onJudgeContact(contact);
    if (tag == MagiciteGameContact::Calcture)
    {
        MagiciteGameContact::_onBeginContact(contact);
    }
    else if (tag == MagiciteGameContact::Cancle)
    {
        contact->SetEnabled(false);
    }
    else if (tag == MagiciteGameContact::Calture_Cancle)
    {
        MagiciteGameContact::_onBeginContact(contact);
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
