#include "BNS_Log.h"

BNS_Log* BNS_Log::m_instance = nullptr;

BNS_Log::BNS_Log()
{
	
}

BNS_Log::~BNS_Log()
{
}

BNS_Log* BNS_Log::GetInstance()
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

std::string BNS_Log::enum_to_string(LogVerbosity verbosity)
{
	switch (verbosity)
	{
	case Display:
		return "Display";
		break;

	case Warning:
		return "Warning";
		break;

	case Error:
		return "Error";
		break;
	}
}

std::vector<BNS_Log::LogMessage> BNS_Log::GetLogList()
{
	return LogList;
}

void BNS_Log::setShowDisplay(bool value)
{
	ShowDisplay = value;
}

void BNS_Log::setShowWarning(bool value)
{
	ShowWarning = value;
}

void BNS_Log::setShowError(bool value)
{
	ShowError = value;
}

