#include "MagiciteGameBagView.h"
#include "MagiciteItemContainer.h"
#include "MagiciteItem.h"

USING_NS_CC;

MagiciteGameBagView::MagiciteGameBagView()
:_bag_blank(5)
{

}

MagiciteGameBagView::~MagiciteGameBagView()
{

}

bool MagiciteGameBagView::init(MagiciteGameObject* obj, int max_size)
{
    if (!MagiciteGameContainerView::init(obj, max_size))
    {
        return false;
    }

    _size = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    _block_size = _size.width / (_max_size + 3);
    _offset = _size.height / 2 - _block_size * 0.5f;

    this->setContentSize(Size(_size.width, _block_size));
    this->setAnchorPoint(Vec2(0.5f, 0.5f));

    auto menu = Menu::create();
    menu->setPosition(Point::ZERO);

    for (int i = 1; i <= _max_size; ++i)
    {
        auto node = MenuItem::create();
        node->setCallback([this,i](Ref*){
            this->ItemEvent(i - 1);
        });
        node->setPosition(Vec2(_origin.x + Id2Pos(i), _origin.y - _offset));
        node->setContentSize(Size(_block_size, _block_size));
        node->setAnchorPoint(Point::ZERO);
        auto color = LayerColor::create(Color4B(0xee, 0xee, 0xee, 0x80));
        color->setContentSize(Size(_block_size, _block_size));
        node->addChild(color);
        menu->addChild(node);
    }

    this->addChild(menu);

    return true;
}


void MagiciteGameBagView::addItem(MagiciteItem* item)
{
    if (item != nullptr)
    {
        _container->addItem(item);
        auto itemObj = item->getItemObject();

        auto iter = std::find(_list->begin(), _list->end(), nullptr);
        if (iter != _list->end())
        {
            *iter = itemObj;
        }

        itemObj->setPosition(Vec2(_origin.x + Id2Pos(iter - _list->begin() + 1) + _block_size / 2, _origin.y - _offset + _block_size / 2));
        this->addChild(itemObj);
    }
}

void MagiciteGameBagView::eraseItem(int num)
{
    auto remove_tmp = *(_list->begin() + num);
    remove_tmp->removeFromParentAndCleanup(true);
    *(_list->begin() + num) = nullptr;

    _container->eraseItem(num);
}

float MagiciteGameBagView::Id2Pos(int n)
{
    return (_block_size + _bag_blank) * n;
}

MagiciteGameBagView* MagiciteGameBagView::create(MagiciteGameObject* obj, int max_size/* = DEFAULT_MAX_SIZE*/)
{
    auto ptr = new MagiciteGameBagView();
    if (ptr && ptr->init(obj, max_size))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}