#ifndef __MAGICITE_GAME_LAYER_H__
#define __MAGICITE_GAME_LAYER_H__

#include "cocos2d.h"
#include "MagiciteGameMap.h"
class MagiciteGameLayer : public cocos2d::Layer
{
public:
    virtual bool init();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    CREATE_FUNC(MagiciteGameLayer);

	void update(float timeDelta);

private:
	cocos2d::Sprite *_player;
	MagiciteGameMap *_background;
	bool _is_move;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	enum _direction : int
	{
		left = 0,
		right = 1
	};
	_direction _left_or_right;
	const int seed = 3;
};

#endif // __MAGICITE_GAME_LAYER_H__
