#include "BNS_AUIScreen.h"

bool& BNS_AUIScreen::GetShow()
{
	return toShow;
}

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
