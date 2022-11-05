#include "BNS_EngineTime.h"

BNS_EngineTime* BNS_EngineTime::sharedInstance = nullptr;

void BNS_EngineTime::initialize()
{
	sharedInstance = new BNS_EngineTime();
}

double BNS_EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

BNS_EngineTime::BNS_EngineTime()
{

}

BNS_EngineTime::~BNS_EngineTime()
{
	delete sharedInstance;
}

void BNS_EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void BNS_EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsed_seconds.count();

	//std::cout << "Frame update finished in " << sharedInstance->deltaTime << "\n";
}