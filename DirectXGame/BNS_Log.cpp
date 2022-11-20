#include "BNS_Log.h"

BNS_Log* BNS_Log::m_instance = nullptr;

BNS_Log::BNS_Log()
{
}

BNS_Log::~BNS_Log()
{
}

BNS_Log* BNS_Log::get()
{
	return m_instance;
}

void BNS_Log::create()
{
	if (BNS_Log::m_instance)
		throw std::exception("BNS_Log already created");
	BNS_Log::m_instance = new BNS_Log();
}

void BNS_Log::release()
{
	if (!BNS_Log::m_instance)
		return;
	delete BNS_Log::m_instance;
}

void BNS_Log::DisplayLog(LogType logType, std::string logMessage)
{
	logMessage = std::to_string(static_cast<int>(logType)) + ": " + logMessage;
	logList.push_back(logMessage);
}

std::vector<std::string> BNS_Log::getLogList()
{
	return logList;
}
