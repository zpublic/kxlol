#ifndef __MAIN_OPERATE_LAYER_H__
#define __MAIN_OPERATE_LAYER_H__

#include "cocos2d.h"
#include "ui\UIWidget.h"

class MainOperatePanel : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(MainOperatePanel);

    void TabBtnCallback(Ref* pSender);
	void LinkVoidCallBack(Ref* pSender, cocos2d::ui::Widget::TouchEventType _event);
};

#endif // __MAIN_OPERATE_LAYER_H__
