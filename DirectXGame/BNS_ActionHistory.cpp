#include "BNS_ActionHistory.h"
#include "BNS_EditorAction.h"
#include "BNS_EngineBackend.h"
#include "BNS_GameObjectManager.h"

BNS_ActionHistory* BNS_ActionHistory::sharedInstance = nullptr;

BNS_ActionHistory* BNS_ActionHistory::GetInstance()
{
	return sharedInstance;
}

void BNS_ActionHistory::Initialize()
{
	sharedInstance = new BNS_ActionHistory();
}

void BNS_ActionHistory::Destroy()
{
	delete sharedInstance;
}

void BNS_ActionHistory::recordAction(BNS_AGameObject* gameObject)
{
	if (BNS_EngineBackend::getInstance()->getMode() == BNS_EngineBackend::EDITOR)
	{
		BNS_EditorAction* editorAction = new BNS_EditorAction(gameObject);
		this->actionsPerformed.push(editorAction);
	}
}

void BNS_ActionHistory::recordAction(std::string name)
{
	if (BNS_EngineBackend::getInstance()->getMode() == BNS_EngineBackend::EDITOR)
	{
		BNS_EditorAction* editorAction = new BNS_EditorAction(BNS_GameObjectManager::get()->FindObjectByName(name));
		this->actionsPerformed.push(editorAction);
	}
}

bool BNS_ActionHistory::hasRemainingUndoActions()
{
	return !this->actionsPerformed.empty();
}

bool BNS_ActionHistory::hasRemainingRedoActions()
{
	return !this->actionsCancelled.empty();
}

BNS_EditorAction* BNS_ActionHistory::undoAction()
{
	if (BNS_EngineBackend::getInstance()->getMode() != BNS_EngineBackend::EDITOR)
		return NULL;

	if (this->hasRemainingUndoActions())
	{
		BNS_EditorAction* action = this->actionsPerformed.top();
		this->actionsPerformed.pop();
		this->actionsCancelled.push(action);
		return action;
	}

	else
		return NULL;
}

BNS_EditorAction* BNS_ActionHistory::redoAction()
{
	if (BNS_EngineBackend::getInstance()->getMode() != BNS_EngineBackend::EDITOR)
		return NULL;

	if (this->hasRemainingRedoActions())
	{
		BNS_EditorAction* action = this->actionsCancelled.top();
		this->actionsCancelled.pop();
		this->actionsPerformed.push(action);
		return action;
	}

	else
		return NULL;
}

void BNS_ActionHistory::clear()
{
	while (this->hasRemainingUndoActions()) {
		BNS_EditorAction* action = this->actionsPerformed.top();
		delete action;
		this->actionsPerformed.pop();
	}

	while (this->hasRemainingRedoActions()) {
		BNS_EditorAction* action = this->actionsCancelled.top();
		delete action;
		this->actionsCancelled.pop();
	}
}

BNS_ActionHistory::BNS_ActionHistory()
{
}

BNS_ActionHistory::~BNS_ActionHistory()
{
	this->clear();
}
