#ifndef  __MAGICITE_CAPTION_SCENE__
#define  __MAGICITE_CAPTION_SCENE__

#include "cocos2d.h"

class MagiciteCaptionScene : public cocos2d::Scene
{
public:
    MagiciteCaptionScene();

    virtual bool init();
    CREATE_FUNC(MagiciteCaptionScene);

private:
    bool                                    _is_ready;
};

#endif //__MAGICITE_CAPTION_SCENE__