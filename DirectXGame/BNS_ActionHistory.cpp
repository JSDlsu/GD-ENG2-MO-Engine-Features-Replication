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

void BNS_ActionHistory::recordAction(std::string name)
{
	if (BNS_EngineBackend::getInstance()->getMode() == BNS_EngineBackend::EDITOR)
	{
		BNS_EditorAction* editorAction = new BNS_EditorAction(BNS_GameObjectManager::get()->FindObjectByName(name));
		if (undoCheck(name))
		{
			BNS_EditorAction* tempAct = replaceUndo(editorAction);
			this->actionsPerformed.push(tempAct);
		}
		else
		{
			undoTemp.emplace_back(editorAction);
		}

	}
}

BNS_EditorAction* BNS_ActionHistory::recordUndo(BNS_EditorAction* action)
{
	if (BNS_EngineBackend::getInstance()->getMode() == BNS_EngineBackend::EDITOR)
	{
		if (redoCheck(action->GetOwnerName()))
		{
			action = replaceRedo(action);
			this->actionsCancelled.push(action);
		}
		else
		{
			redoTemp.emplace_back(action);
			this->actionsPerformed.pop();
			this->actionsCancelled.push(action);
		}

		return action;

	}

	return NULL;
}

BNS_EditorAction* BNS_ActionHistory::recordRedo(BNS_EditorAction* action)
{
	if (BNS_EngineBackend::getInstance()->getMode() == BNS_EngineBackend::EDITOR)
	{
		if (undoCheck(action->GetOwnerName()))
		{
			action = replaceUndo(action);
			this->actionsCancelled.push(action);
		}
		else
		{
			undoTemp.emplace_back(action);
			this->actionsPerformed.pop();
			this->actionsCancelled.push(action);
		}

		return action;

	}

	return NULL;
}

bool BNS_ActionHistory::undoCheck(std::string name)
{
	for (auto action : undoTemp)
	{
		if (action->GetOwnerName() == name)
			return true;
	}
	
	return false;
}

bool BNS_ActionHistory::redoCheck(std::string name)
{
	for (auto action : redoTemp)
	{
		if (action->GetOwnerName() == name)
			return true;
	}

	return false;
}

BNS_EditorAction* BNS_ActionHistory::replaceUndo(BNS_EditorAction* action)
{
	for (auto act : undoTemp)
	{
		if (act->GetOwnerName() == action->GetOwnerName())
		{
			BNS_EditorAction* tempAction = act;
			undoTemp.remove(act);
			undoTemp.emplace_back(action);
			return act;
		}
	}

	return NULL;
}

BNS_EditorAction* BNS_ActionHistory::replaceRedo(BNS_EditorAction* action)
{
	for (auto act : redoTemp)
	{
		if (act->GetOwnerName() == action->GetOwnerName())
		{
			BNS_EditorAction* tempAction = act;
			redoTemp.remove(act);
			redoTemp.emplace_back(action);
			return act;
		}
	}

	return NULL;
}

BNS_EditorAction* BNS_ActionHistory::tempToRedo()
{
	return nullptr;
}

BNS_EditorAction* BNS_ActionHistory::tempToUndo()
{
	return nullptr;
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

		action = recordUndo(action);
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
