#ifndef _KXLOL_MSGCENTER_H
#define _KXLOL_MSGCENTER_H

#include <map>
#include <string>
#include <functional>

namespace kxlol
{
	/**
	 * @brief: a message center to retransmit message
	 */
	class MsgCenter
	{
	public:
		typedef std::function<void(void*)> MSG_CALLBACK;
		typedef std::map<long, MSG_CALLBACK> MSG_SLOT;
		typedef std::map<std::string, MSG_SLOT> MSG_CENTER;

		/**
		 * @brief: singleton method of MsgCenter
		 */
		static MsgCenter* getInstance();

		/**
		 * @brief: register a message callback to message center
		 * @param[in] strMsgName: the name of message
		 * @param[in] callback: a std::function<void(void*)> type callback,
		 *                  support lambda
		 * @return: handle which is used to unregister message
		 */
		long RegisterMsg(const std::string& strMsgName,const MSG_CALLBACK& callback);

		/**
		 * @brief: send a message to message center and run the 
		 *            callbacks sync
		 * @param[in] strMsgName: then name of message
		 * @param[in] param: void* type parameter used in callbacks
		 */
		void SendMsg(const std::string& strMsgName, void* param);

		/**
		 *!warn : this function is not implement yet
		 * @brief: post a message to message center and run the
		 *            callbacks async
		 * @param[in] strMsgName: then name of message
		 * @param[in] param: void* type parameter used in callbacks
		 */
		void PostMsg(const std::string& strMsgName, void* param);

		/**
		 * @brief: unregister a message call back from message center
		 * @param[in] strMsgName: the name of message
		 * @param[in] handle: the handle return in register this message
		 */
		void UnregisterMsg(const std::string& strMsgName, long handle);

	private:
		MSG_CENTER _msgcenter;
		static MsgCenter* _instance;
		MsgCenter(){}
		~MsgCenter(){}
	};
}

#endif