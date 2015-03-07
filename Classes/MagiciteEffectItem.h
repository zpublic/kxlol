#ifndef __MAGICITE_EFFECT_ITEM__
#define __MAGICITE_EFFECT_ITEM__

#include "MagiciteItem.h"
#include <chrono>

class MagiciteEffect;

class MagiciteEffectItem : public MagiciteItem
{
public:
    MagiciteEffectItem();
    ~MagiciteEffectItem();

    //MagiciteItem
    virtual bool init();
    virtual bool initWithFile(const char* filename);

    virtual void positive(MagiciteGameObject* obj);

    long long getCd() const;

protected:
    void setEffect(MagiciteEffect* effect);
    void setCd(long long cd);

    MagiciteEffect*                         _effect;
    long long                               _cool_down; //milliseconds
    std::chrono::system_clock::time_point   _last_time;
};

#endif //__MAGICITE_EFFECT_ITEM__