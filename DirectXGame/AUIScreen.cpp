#include "AUIScreen.h"

AUIScreen::AUIScreen(std::string name) : name(name)
{

}

AUIScreen::~AUIScreen()
{
}

std::string AUIScreen::GetName()
{
	return name;
}
