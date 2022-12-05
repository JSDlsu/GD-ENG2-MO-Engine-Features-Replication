#include "BNS_AUIScreen.h"

bool& BNS_AUIScreen::GetShow()
{
	return toShow;
}

BNS_AUIScreen::BNS_AUIScreen(std::string name, int ID)
{
	this->name = name;
	this->ID = ID;
	//std::cout << name << "\n";
}

BNS_AUIScreen::~BNS_AUIScreen()
{
}

std::string BNS_AUIScreen::GetName()
{
	return name;
}

int BNS_AUIScreen::GetID()
{
	return ID;
}
