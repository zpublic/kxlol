#include "slot.h"

namespace kxlol{
namespace component{
	long slot::addSlot(const std::string& strMsgName, const MsgCenter::MSG_CALLBACK& callback)
	{
		long handle = MsgCenter::getInstance()->RegisterMsg(strMsgName, callback);
		contain.push_back(std::make_pair(strMsgName, handle));
		return handle;
	}

	void slot::rmSlot(const std::string& strMsgName)
	{
		for(auto it = contain.begin(); contain.end() != it;)
		{
			if(it->first == strMsgName)
				it = contain.erase(it);
			else
				++it;
		}
	}

	void slot::rmSlot(long handle)
	{
		for(auto it = contain.begin(); contain.end() != it;)
		{
			if(it->second == handle)
			{
				it = contain.erase(it);
				break;
			}
			else
				++it;
		}
	}

	slot::~slot()
	{
		MsgCenter* msgcenter = MsgCenter::getInstance();
		for(auto it = contain.begin(); contain.end() != it; ++it)
		{
			msgcenter->UnregisterMsg(it->first, it->second);
		}
	}
}
}