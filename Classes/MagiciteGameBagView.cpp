#include "MagiciteGameBagView.h"
#include "MagiciteItem.h"
#include "MagiciteGameCDItem.h"
#include "MagiciteEffectItem.h"

USING_NS_CC;

MagiciteGameBagView::MagiciteGameBagView()
:_bag_blank(5)
{

}

MagiciteGameBagView::~MagiciteGameBagView()
{

}

bool MagiciteGameBagView::init(int max_size)
{
    if (!MagiciteGameContainerView::init(max_size))
    {
        return false;
    }

    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    _block_size = size.width / (_max_size + 3);
    _offset = size.height / 2 - _block_size * 0.5f;

    this->setContentSize(Size(size.width, _block_size));
    this->setAnchorPoint(Vec2(0.5f, 0.5f));

    _cd_node = Node::create();
    _cd_node->setContentSize(Size(size.width, _block_size));
    _cd_node->setAnchorPoint(Point::ZERO);
    _cd_node->setPosition(Point::ZERO);
    this->addChild(_cd_node, 1);

    auto menu = Menu::create();
    menu->setPosition(Point::ZERO);

    for (int i = 1; i <= _max_size; ++i)
    {
        auto node = MagiciteGameCDItem::create();
        node->setCallback([this, i, node](Ref*){
           this->onItemUse(i - 1);
        });

        node->setPosition(Vec2(origin.x + Id2Pos(i), origin.y - _offset));
        node->setContentSize(Size(_block_size, _block_size));
        node->setAnchorPoint(Point::ZERO);
        auto color = LayerColor::create(Color4B(0xee, 0xee, 0xee, 0x80));
        color->setContentSize(Size(_block_size, _block_size));
        node->addChild(color);
        _itemArray.push_back(node);

        char c[10];
        std::sprintf(c, "%d", i);
        auto font = Label::createWithSystemFont(c, "Arial", 40);
        font->setPosition(Vec2(node->getContentSize().width / 2, node->getContentSize().height / 2));
        node->addChild(font);
        menu->addChild(node);
    }

    this->addChild(menu);

    return true;
}


void MagiciteGameBagView::addItem(MagiciteItem* item)
{
    if (item != nullptr)
    {
        auto iter = std::find_if(_list->begin(), _list->end(), [](const std::pair<int, MagiciteItem*> &p)->bool{
            return p.second == nullptr;
        });
        if (iter != _list->end())
        {
            MagiciteGameContainerView::addItem(item, iter);
            _itemArray[iter - _list->begin()]->setItemView(item);
            if (item->_itemType == MagiciteItem::EffectItem)
            {
                _itemArray[iter - _list->begin()]->setCDEnable(true);
                _itemArray[iter - _list->begin()]->setCD(reinterpret_cast<MagiciteEffectItem*>(item)->getCd());
            }
        }
    }
}

void MagiciteGameBagView::eraseItem(int num)
{
    auto remove_tmp = _list->begin() + num;
    if (remove_tmp->second != nullptr)
    {
        remove_tmp->second->removeFromParentAndCleanup(true);
        MagiciteGameContainerView::eraseItem(remove_tmp);
        _itemArray[num]->eraseItemView();
    }
}

float MagiciteGameBagView::Id2Pos(int n)
{
    return (_block_size + _bag_blank) * n;
}

MagiciteGameBagView* MagiciteGameBagView::create(int max_size/* = DEFAULT_MAX_SIZE*/)
{
    auto ptr = new MagiciteGameBagView();
    if (ptr && ptr->init(max_size))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

void MagiciteGameBagView::onItemUse(int id)
{
    if (_itemArray[id]->isEnabled())
    {
        MagiciteGameContainerView::onItemUse(id);
        _itemArray[id]->startCd(_itemArray[id]->getCD());
    }
}
