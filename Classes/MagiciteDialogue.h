#ifndef _MAGICITE_DIALOGUE_H_
#define _MAGICITE_DIALOGUE_H_

#include <cocos2d.h>

class MagiciteDialogue : public cocos2d::Layer
{
public:
    virtual bool init(unsigned long storyId);

    static MagiciteDialogue* create(unsigned long storyId);
};

#endif