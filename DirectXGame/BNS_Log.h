#pragma once
#include <string>
#include <iostream>
#include <vector>

#include "BNS_EnumHandler.h"

class BNS_Log
{
public:
	BNS_Log();
	~BNS_Log();

public:
	static BNS_Log* get();
	static void create();
	static void release();

	void DisplayLog(LogType logType, std::string logMessage);
	std::vector<std::string> getLogList();

private:
	static BNS_Log* m_instance;
	friend class BNS_AppWindow;
	std::vector<std::string> logList;


};