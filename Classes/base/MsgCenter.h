#ifndef _KXLOL_MSGCENTER_H
#define _KXLOL_MSGCENTER_H

#include <map>
#include <string>
#include <functional>

namespace kxlol
{
	class MsgCenter
	{
	public:
		typedef std::function<void(void*)> MSG_CALLBACK;
		typedef std::map<long, MSG_CALLBACK> MSG_SLOT;
		typedef std::map<std::string, MSG_SLOT> MSG_CENTER;
		long RegisterMsg(const std::string& strMsgName,const MSG_CALLBACK& callback);
		void SendMsg(const std::string& strMsgName, void* param);
		void PostMsg(const std::string& strMsgName, void* param);
		void UnregisterMsg(const std::string& strMsgName, long handle);
		static MsgCenter* getInstance();

	private:
		MSG_CENTER _msgcenter;
		static MsgCenter* _instance;
		MsgCenter(){}
		~MsgCenter(){}
	};
}

#endif