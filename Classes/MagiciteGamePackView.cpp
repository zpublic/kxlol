#include "MagiciteGamePackView.h"

bool MagiciteGamePackView::init()
{
    if(!Layer::init())
        return false;

    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    _table = cocos2d::extension::TableView::create(this, cocos2d::Size(600.0f, 400.0f));
    _table->setPosition(origin.x + visibleSize.width / 2 - 300.0f, 
        origin.y + visibleSize.height / 2 - 200.0f);
    this->addChild(_table);

    return true;
}

cocos2d::extension::TableViewCell* MagiciteGamePackView::tableCellAtIndex( cocos2d::extension::TableView *table, ssize_t idx )
{
    cocos2d::extension::TableViewCell* cell = table->dequeueCell();
    if(nullptr == cell)
    {
        cell = cocos2d::extension::TableViewCell::create();

        auto node = cocos2d::Node::create();
        node->setContentSize(cocos2d::Size(600.0f, 100.0f));
        cell->addChild(node);

        for(int i = 0; i < 6; ++i)
        {
            auto packCell = MagiciteGamePackCell::create();
            packCell->setPosition(i * 100.0f, 0.0f);
            node->addChild(packCell);
        }

    }

    return cell;
}

cocos2d::Size MagiciteGamePackView::cellSizeForTable( cocos2d::extension::TableView *table )
{
    return cocos2d::Size(600.0f, 100.0f);
}

ssize_t MagiciteGamePackView::numberOfCellsInTableView( cocos2d::extension::TableView* table )
{
    return 10;
}

void MagiciteGamePackView::tableCellTouched( cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell )
{

}

bool MagiciteGamePackCell::init()
{
    if(!Node::init())
        return false;

    auto bg = cocos2d::LayerColor::create(cocos2d::Color4B(0xee, 0xee, 0xee, 0x80), 96.0f, 96.0f);
    bg->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    bg->setPosition(2.0f, 2.0f);
    this->addChild(bg);

    return true;
}
