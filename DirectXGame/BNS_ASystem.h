#pragma once
#include <string>
#include <unordered_map>

template <class TList>
class BNS_ASystem
{
public:
	typedef std::string String;
	typedef std::unordered_map<String, TList*> ComponentTable;
	typedef  std::vector<TList*> ComponentList;

	BNS_ASystem();
	~BNS_ASystem();

	void RegisterComponent(TList* component);
	void UnRegisterComponent(TList* component);
	void UnRegisterComponentByName(String name);
	TList* FindComponentByName(String name);
	ComponentList GetAllComponents();

	virtual void UpdateAllComponents();

protected:
	ComponentTable componentTable;
	ComponentList componentList;
};



