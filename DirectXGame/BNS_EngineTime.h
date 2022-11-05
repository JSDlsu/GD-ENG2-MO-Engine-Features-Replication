#pragma once
// Class for storing of frame ticks
#include <iostream>
#include <chrono>
#include <ctime>

class BNS_Window;

/*
 * a singleton class that gives the deltaTime from the current
 * time instance.
 */
class BNS_EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();
private:
	BNS_EngineTime();
	~BNS_EngineTime();
	BNS_EngineTime(BNS_EngineTime const&) {}; // copy constructor is private
	BNS_EngineTime& operator=(BNS_EngineTime const&) {}; // assignment operator is private

	static BNS_EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class BNS_Window;
};