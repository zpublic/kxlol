#ifndef _KXLOL_BASE_BAG_H
#define _KXLOL_BASE_BAG_H

#include <map>

namespace kxlol
{
	class ItemObject;
	class bag
	{
	public:
		typedef std::map<long, ItemObject*> CONTAINTYPE;

		/**
		 * @brief: add something to bag
		 * @param[in] item: item object
		 * @param[in] item: add count, if object is not stackable,
		 *                  then this param will not be use
		 * @return: if bag full, return false, else return true
		 */
		bool addItem(ItemObject* item, unsigned nNum = 1);

		/**
		 * @brief: remove something from bag
		 * @param[in] item: item object
		 * @param[in] item: add count, if object is not stackable,
		 *                  then this param will not be use
		 * @return: if their is no such object or have no such count, 
		 *          return false, else return true
		 */
		bool rmItem(ItemObject* item, unsigned nNum = 1);

		/**
		 * @brief: remove something from bag by id
		 * @param[in] item: item id
		 * @param[in] item: add count, if object is not stackable,
		 *                  then this param will not be use
		 * @return: if their is no such object or have no such count, 
		 *          return false, else return true
		 */
		bool rmItem(long id, unsigned nNum = 1);
		
		/**
		 * @brief: get the bag's size
		 */
		const unsigned getSize()const;

		/**
		 * @breif: get the bag's being used size
		 */
		const unsigned getUsedSize()const;

		/**
		 * @brief: set the bag's size
		 */
		void setSize(unsigned nSize);

		/**
		 * @brief: get item object by id
		 */
		ItemObject* getItem(long id);

		~bag();
	private:
		unsigned _size;
		CONTAINTYPE _bagContain;
	};
}

#endif