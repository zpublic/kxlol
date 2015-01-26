#include "MsgCenter.h"
#include <random>

namespace kxlol
{
	MsgCenter* MsgCenter::_instance = nullptr;

	MsgCenter* MsgCenter::getInstance()
	{
		if(nullptr == _instance)
		{
			static MsgCenter instance;
			_instance = &instance;
		}

		return _instance;
	}

	long MsgCenter::RegisterMsg(const std::string& strMsgName, const MsgCenter::MSG_CALLBACK& callback)
	{
		auto it = _msgcenter.find(strMsgName);
		if(_msgcenter.end() == it)
		{
			_msgcenter[strMsgName];
			it = _msgcenter.find(strMsgName);
		}

		auto& slots = it->second;
		
		// make rand key for slot
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<long> dist(0, LONG_MAX);
		long handle = dist(mt);

		// keep the key unique
		do
		{
			auto itCallBack = slots.find(handle);
			if(slots.end() == itCallBack)
			{
				slots[handle] = callback;
				break;
			}
			handle = dist(mt);
		}while(true);

		return handle;
	}

	void MsgCenter::UnregisterMsg(const std::string& strMsgName, long handle)
	{
		auto it = _msgcenter.find(strMsgName);
		if(_msgcenter.end() == it)
			return;

		auto& slots = it->second;
		auto itCallBack = slots.find(handle);
		if(slots.end() != itCallBack)
		{
			slots.erase(itCallBack);
		}
	}

	void MsgCenter::SendMsg(const std::string& strMsgName, void* param)
	{
		auto it = _msgcenter.find(strMsgName);
		if(_msgcenter.end() == it)
			return;

		auto& slots = it->second;
		for(auto itCallBack = slots.begin(); itCallBack != slots.end(); ++itCallBack)
		{
			itCallBack->second(param);
		}
	}
}