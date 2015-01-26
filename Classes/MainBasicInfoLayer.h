#ifndef __MAIN_BASIC_INFO_LAYER_H__
#define __MAIN_BASIC_INFO_LAYER_H__

#include "cocos2d.h"
#include <Component\slot.h>

class MainBasicInfoLayer : public cocos2d::Layer
{
private:
	kxlol::component::slot slot;
public:
    virtual bool init();

    CREATE_FUNC(MainBasicInfoLayer);
};

#endif // __MAIN_BASIC_INFO_LAYER_H__
