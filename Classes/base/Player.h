#ifndef _KXLOL_PLAYER_H
#define _KXLOL_PLAYER_H

#include <string>

namespace kxlol
{
	/**
	 * @brief: player type
	 */
	class Player
	{
	private:
		std::string _name;
		int _godPower;
		static Player* _instance;
		Player();
		~Player();
	public:

		/**
		 * @brief: singleton method of Player
		 */
		static Player* getInstance();

		/**
		 * @brief: get player name
		 * @return: player name in std::string type
		 */
		const std::string& getName()const;

		/**
		 * @brief: set player name
		 */
		void setName(const std::string& name);

		/**
		 * @brief: get current god power value
		 */
		const int getGodPower()const;

		/**
		 * @brief: add god power
		 * @param[in] nNum: the god power value to add
		 */
		void addGodPower(unsigned nNum = 1);

		/**
		 * @brief: decrease god power
		 * @return: if current god power value is little
		 *          than nNum then return false
		 */
		bool subGodPower(unsigned nNum = 1);
	};
}

#endif