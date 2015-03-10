#include "MagiciteGameBagView.h"
#include "MagiciteItem.h"

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

    _size = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    _block_size = _size.width / (_max_size + 3);
    _offset = _size.height / 2 - _block_size * 0.5f;

    this->setContentSize(Size(_size.width, _block_size));
    this->setAnchorPoint(Vec2(0.5f, 0.5f));

    _cd_node = Node::create();
    _cd_node->setContentSize(Size(_size.width, _block_size));
    _cd_node->setAnchorPoint(Point::ZERO);
    _cd_node->setPosition(Point::ZERO);
    this->addChild(_cd_node, 1);

    auto menu = Menu::create();
    menu->setPosition(Point::ZERO);

    for (int i = 1; i <= _max_size; ++i)
    {
        auto node = MenuItem::create();
        node->setCallback([this,i](Ref*){
           this->onItemUse(i - 1);
        });

        node->setPosition(Vec2(_origin.x + Id2Pos(i), _origin.y - _offset));
        node->setContentSize(Size(_block_size, _block_size));
        node->setAnchorPoint(Point::ZERO);
        auto color = LayerColor::create(Color4B(0xee, 0xee, 0xee, 0x80));
        color->setContentSize(Size(_block_size, _block_size));
        node->addChild(color);

        char c[10];
        std::sprintf(c, "%d", i - 1);
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
            item->setPosition(Vec2(_origin.x + Id2Pos(iter - _list->begin() + 1) + _block_size / 2, _origin.y - _offset + _block_size / 2));
            this->addChild(item);
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

    MagiciteGameContainerView::onItemUse(id);

    auto cd_sprite = Sprite::create("img\\Magicite\\Item\\cd.png");
    auto pt = ProgressTimer::create(cd_sprite);
    pt->setReverseProgress(true);
    pt->setType(kCCProgressTimerTypeRadial);
    pt->setAnchorPoint(Point::ZERO);
    pt->setPosition(_origin.x + Id2Pos(id + 1), _origin.y - _offset);
    pt->setScale(_block_size / cd_sprite->getContentSize().width, _block_size / cd_sprite->getContentSize().width);
    pt->setOpacity(80);
    _cd_node->addChild(pt);

    auto progressAction = ProgressFromTo::create(3.0f, 0.0f, 100.0f);
    auto progressCallback = CallFuncN::create(this, callfuncN_selector(MagiciteGameBagView::progressCallback));
    pt->runAction(Sequence::create(progressAction, progressCallback, nullptr));
}

void MagiciteGameBagView::progressCallback(cocos2d::Node* node)
{
    node->removeFromParentAndCleanup(true);
}