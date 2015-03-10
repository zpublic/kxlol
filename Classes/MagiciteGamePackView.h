#ifndef _MAGICITE_GAME_PACK_VIEW_H
#define _MAGICITE_GAME_PACK_VIEW_H

#include <cocos2d.h>
#include <cocos-ext.h>

class MagiciteGamePackCell : public cocos2d::Node
{
public:
    virtual bool init();
    CREATE_FUNC(MagiciteGamePackCell);
};

class MagiciteGamePackView : public cocos2d::Layer
    , public cocos2d::extension::TableViewDataSource
    , public cocos2d::extension::TableViewDelegate
{
public:
    virtual bool init();
    
    CREATE_FUNC(MagiciteGamePackView);

    // virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) ;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, 
        ssize_t idx);
    virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView* table);

    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);

private:
    MagiciteGamePackView(){}
    cocos2d::extension::TableView* _table;
};

#endif // !_MAGICITE_GAME_PACK_VIEW_H
