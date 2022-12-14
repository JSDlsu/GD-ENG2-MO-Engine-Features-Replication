#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <list>

class BNS_EditorAction;
class BNS_AGameObject;

class BNS_ActionHistory
{
public:
	typedef std::stack<BNS_EditorAction*> ActionStack;

	static BNS_ActionHistory* GetInstance();
	static void Initialize();
	static void Destroy();
	
	void recordAction(std::string name);
	BNS_EditorAction* recordUndo(BNS_EditorAction* action);
	BNS_EditorAction* recordRedo(BNS_EditorAction* action);
	bool undoCheck(std::string name);
	bool redoCheck(std::string name);
	BNS_EditorAction* replaceUndo(BNS_EditorAction* action);
	BNS_EditorAction* replaceRedo(BNS_EditorAction* action);
	BNS_EditorAction* tempToRedo();
	BNS_EditorAction* tempToUndo();
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
	std::list<BNS_EditorAction*> undoTemp;
	std::list<BNS_EditorAction*> redoTemp;
};

