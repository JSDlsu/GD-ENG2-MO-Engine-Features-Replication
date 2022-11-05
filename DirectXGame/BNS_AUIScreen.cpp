#include "BNS_AUIScreen.h"

BNS_AUIScreen::BNS_AUIScreen(std::string name) : name(name)
{

}

BNS_AUIScreen::~BNS_AUIScreen()
{
}

std::string BNS_AUIScreen::GetName()
{
	return name;
}
