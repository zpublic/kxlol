#ifndef _KXLOL_COMPONENT_SLOT_H
#define _KXLOL_COMPONENT_SLOT_H

#include <vector>
#include <string>
#include <MsgCenter.h>

namespace kxlol{
namespace component{
	/**
	 * @brief: a message slot component to manage the lifecycle
	 *         of the message callback
	 */
	class slot{
	public:
		typedef std::vector<std::pair<std::string, long>> CONTAINTYPE;

		/**
		 * @brief: add a message callback to slot component
		 * @param[in] strMsgName: the name of message
		 * @param[in] callback: a std::function<void(void*)> type callback,
		 *                  support lambda
		 * @return: handle which is used to unregister message
		 */
		long addSlot(const std::string& strMsgName, const MsgCenter::MSG_CALLBACK& callback);

		/**
		 * @brief: remove message callback by message name
		 */
		void rmSlot(const std::string& strMsgName);

		/**
		 * @brief: remove message callback by handle
		 */
		void rmSlot(long handle);

		~slot();

	private:
		CONTAINTYPE contain;
	};
}}

#endif