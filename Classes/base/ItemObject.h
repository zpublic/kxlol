#ifndef _KXLOL_BASE_ITEMOBJECT_H
#define _KXLOL_BASE_ITEMOBJECT_H

namespace kxlol
{
	class ItemObject
	{
	public:
		virtual bool isStackable()
		{
			return true;
		}

		virtual const long getId()const
		{
			return _id;
		}

		virtual void setId(long id)
		{
			_id = id;
		}

		virtual unsigned getCount()
		{
			return 1;
		}

		virtual void setCount(unsigned nNum)
		{
		}

		virtual bool addCount(unsigned nNum = 1)
		{
			return true;
		}

		virtual bool subCount(unsigned nNum = 1)
		{
			return true;
		}

		virtual void setMax(unsigned nMax)
		{
		}

	private:
		long _id;
	};
}

#endif