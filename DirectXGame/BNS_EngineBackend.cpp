#include "BNS_EngineBackend.h"

BNS_EngineBackend* BNS_EngineBackend::sharedInstance = nullptr;

BNS_EngineBackend* BNS_EngineBackend::getInstance()
{
	return sharedInstance;
}

void BNS_EngineBackend::initialize()
{
	sharedInstance = new BNS_EngineBackend();
}

void BNS_EngineBackend::destroy()
{
	delete sharedInstance;
}

void BNS_EngineBackend::setMode(EditorMode mode)
{
	this->editorMode = mode;
	if (this->editorMode == EditorMode::PLAY) {

	}
	else if (this->editorMode == EditorMode::EDITOR) {

	}
}

void BNS_EngineBackend::startFrameStep()
{
	this->frameStepping = true;
}

void BNS_EngineBackend::endFrameStep()
{
	this->frameStepping = false;
}

bool BNS_EngineBackend::insideFrameStep()
{
	return this->frameStepping;
}

BNS_EngineBackend::EditorMode BNS_EngineBackend::getMode()
{
	return this->editorMode;
}

BNS_EngineBackend::BNS_EngineBackend()
{
}

BNS_EngineBackend::~BNS_EngineBackend()
{
}
