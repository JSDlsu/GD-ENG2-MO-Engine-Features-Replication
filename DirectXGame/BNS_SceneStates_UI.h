#pragma once
#include "BNS_AUIScreen.h"
#include "BNS_EngineBackend.h"

class BNS_SceneStates_UI : public BNS_AUIScreen
{
public:
	BNS_SceneStates_UI(std::string name, int ID);
	~BNS_SceneStates_UI();
	void DrawUI() override;

private:
	BNS_EngineBackend* m_state = BNS_EngineBackend::getInstance();
};
