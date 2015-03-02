#include "MagiciteGameContainerView.h"

USING_NS_CC;

MagiciteGameContainerView::MagiciteGameContainerView(int n/* = _max_size*/)
:_list(n)
{

}

MagiciteGameContainerView::~MagiciteGameContainerView()
{

}

bool MagiciteGameContainerView::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }

    return true;
}
