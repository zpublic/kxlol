#ifndef _KXLOL_COMPONENT_SLOT_H
#define _KXLOL_COMPONENT_SLOT_H

#include <vector>
#include <string>
#include <MsgCenter.h>

namespace kxlol{
namespace component{
	class slot{
	public:
		typedef std::vector<std::pair<std::string, long>> CONTAINTYPE;
		long addSlot(const std::string& strMsgName, const MsgCenter::MSG_CALLBACK& callback);
		void rmSlot(const std::string& strMsgName);
		void rmSlot(long handle);
		~slot();

	private:
		CONTAINTYPE contain;
	};
}}

#endif