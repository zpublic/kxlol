#include "Player.h"

namespace kxlol
{
	Player* Player::_instance = nullptr;

	Player::Player():_godPower(0)
		, _name("zapline")
	{}

	Player::~Player()
	{
	}

	Player* Player::getInstance()
	{
		if(nullptr == _instance)
		{
			static Player instance;
			_instance = &instance;
		}

		return _instance;
	}

	const std::string& Player::getName()const
	{
		return _name;
	}

	void Player::setName(const std::string& name)
	{
		_name = name;
	}

	const int Player::getGodPower()const
	{
		return _godPower;
	}

	void Player::addGodPower(unsigned nNum /* =1*/)
	{
		_godPower += nNum;
	}

	bool Player::subGodPower(unsigned nNum /* =1*/)
	{
		if(_godPower < nNum) return false;
		_godPower -= nNum;
		return true;
	}
}