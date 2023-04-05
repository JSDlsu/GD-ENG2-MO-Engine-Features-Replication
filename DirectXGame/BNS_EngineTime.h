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
 // Define a high-resolution clock
using high_resolution_clock = std::chrono::high_resolution_clock;
class BNS_EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();
	static double getFPS();
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
	static void CalculateFPS();

	// Record the start time at the beginning of the program
	static std::chrono::time_point<std::chrono::steady_clock> startTime;
	// Record the time at the beginning of each frame
	static std::chrono::time_point<std::chrono::steady_clock> prevTime;
	static std::chrono::time_point<std::chrono::steady_clock> fpsTime;
	static double fps;
	static int frameCount;
	static std::chrono::duration<double> targetFrameTime;

	friend class BNS_Window;
};