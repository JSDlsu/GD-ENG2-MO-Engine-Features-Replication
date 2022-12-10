#pragma once
#include <iostream>
#include <vector>
#include <stack>

class BNS_EditorAction;
class BNS_AGameObject;

class BNS_ActionHistory
{
public:
	typedef std::stack<BNS_EditorAction*> ActionStack;

	static BNS_ActionHistory* GetInstance();
	static void Initialize();
	static void Destroy();

	void recordAction(BNS_AGameObject* gameObject);
	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();
	BNS_EditorAction* undoAction();
	BNS_EditorAction* redoAction();
	void clear();

private:
	BNS_ActionHistory();
	~BNS_ActionHistory();
	BNS_ActionHistory(BNS_ActionHistory const&) {};
	BNS_ActionHistory& operator=(BNS_ActionHistory const&) {};

	static BNS_ActionHistory* sharedInstance;

	ActionStack actionsPerformed;
	ActionStack actionsCancelled;
};

