#ifndef _KXLOL_PLAYER_H
#define _KXLOL_PLAYER_H

#include <string>

namespace kxlol
{
	class Player
	{
	private:
		std::string _name;
		int _godPower;
		static Player* _instance;
		Player();
		~Player(){}
	public:
		static Player* getInstance();
		const std::string& getName()const;
		void setName(const std::string& name);
		const int getGodPower()const;
		void addGodPower(unsigned nNum = 1);
		bool subGodPower(unsigned nNum = 1);
	};
}

#endif