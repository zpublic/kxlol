#include "MagiciteGameBagView.h"

USING_NS_CC;

MagiciteGameBagView::MagiciteGameBagView()
:MagiciteGameContainerView(_max_size)
{

}

MagiciteGameBagView::~MagiciteGameBagView()
{

}

bool MagiciteGameBagView::init()
{
    if (!MagiciteGameContainerView::init())
    {
        return false;
    }

    _size = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    _block_size = _size.width / (_max_size + 3);
    _offset = _size.height / 2 - _block_size * 0.5f;

    this->setContentSize(Size(_size.width, _block_size));
    this->setAnchorPoint(Vec2(0.5f, 0.5f));

    for (int i = 1; i <= _max_size; ++i)
    {
        auto node = Node::create();
        node->setPosition(Vec2(_origin.x + Id2Pos(i), _origin.y - _offset));
        node->setContentSize(Size(_block_size, _block_size));
        auto color = LayerColor::create(Color4B(0xee, 0xee, 0xee, 0x80));
        color->setContentSize(Size(_block_size, _block_size));
        node->addChild(color);
        this->addChild(node);
    }

    return true;
}


void MagiciteGameBagView::addItem(MagiciteGameObject* item)
{
    if (item != nullptr)
    {
        this->addChild(item);

        auto iter = std::find(_list.begin(), _list.end(), nullptr);
        if (iter != _list.end())
        {
            *iter = item;
        }

        item->setPosition(Vec2(_origin.x + Id2Pos(iter - _list.begin() + 1) + _block_size / 2, _origin.y - _offset + _block_size / 2));
    }
}

void MagiciteGameBagView::eraseItem(int num)
{
    auto remove_tmp = _list[num];
    remove_tmp->removeFromParentAndCleanup(true);
    _list[num] = nullptr;
}

float MagiciteGameBagView::Id2Pos(int n)
{
    return (_block_size + _bag_blank) * n;
}