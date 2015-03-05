#include "MagiciteGameContainerView.h"
#include "MagiciteItem.h"
#include "MagiciteEffectItem.h"

USING_NS_CC;

MagiciteGameContainerView::MagiciteGameContainerView()
{
}

MagiciteGameContainerView::~MagiciteGameContainerView()
{
    CC_SAFE_DELETE(_list);
}

bool MagiciteGameContainerView::init(int max_size)
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }

    _max_size = max_size;
    _list = new std::vector<std::pair<int, MagiciteItem*>>(max_size);

    return true;
}

MagiciteItem* MagiciteGameContainerView::getItem(int num)
{
    return _list->at(num).second;
}

void MagiciteGameContainerView::setViewInvisible(bool is_visible)
{
    this->setVisible(is_visible);
}

bool MagiciteGameContainerView::getViewInvisible() const
{
    return this->isVisible();
}