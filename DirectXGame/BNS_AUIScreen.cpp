#include "BNS_AUIScreen.h"

bool& BNS_AUIScreen::GetShow()
{
	return toShow;
}

BNS_AUIScreen::BNS_AUIScreen(std::string name, int ID)
{
	name.append(std::to_string(ID));
}

BNS_AUIScreen::~BNS_AUIScreen()
{
}

std::string BNS_AUIScreen::GetName()
{
	return name;
}
