#ifndef __MAIN_TAB_BTN_LAYER_H__
#define __MAIN_TAB_BTN_LAYER_H__

#include "cocos2d.h"

class MainTabBtnLayer : public cocos2d::Layer
{
private:
	cocos2d::Ref* pCurSelBtn;
	cocos2d::Node* pOpre;
	cocos2d::Node* pOpreInfo;
public:
    virtual bool init();
	static MainTabBtnLayer* create(Node* pOpre, Node* pOpreInfo)
	{
		MainTabBtnLayer *pRet = new MainTabBtnLayer(); 
		if (pRet && pRet->init()) 
		{ 
			pRet->setOperatorLayer(pOpre, pOpreInfo);
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = NULL; 
			return NULL; 
		} 
	}

    void TabChange(Ref* pSender);
	void MainGodSpaceCallBack(Ref* pSender);
	void PlanesMgrCenter(Ref* pSender);
	void OriginUniverse(Ref* pSender);
	void PowerCapsule(Ref* pSender);

	void setOperatorLayer(Node* pOpre, Node* pOpreInfo);
};

#endif // __MAIN_TAB_BTN_LAYER_H__
