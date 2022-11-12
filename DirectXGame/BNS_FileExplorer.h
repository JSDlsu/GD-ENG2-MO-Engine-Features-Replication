#pragma once
#include <unordered_map>
#include "BNS_AUIScreen.h"
#include "BNS_Prerequisites.h"

class BNS_FileExplorer
{
public:
	typedef std::unordered_map<std::string, TexturePtr> uiImageHashTable;
public:
	static BNS_FileExplorer* GetInstance();
	static void Initialize();
	static void Release();
	uiImageHashTable GetImageHashTable();
private:
	BNS_FileExplorer();
	~BNS_FileExplorer();
	BNS_FileExplorer(BNS_FileExplorer const&) {};
	BNS_FileExplorer& operator=(BNS_FileExplorer const&) {};
	static BNS_FileExplorer* sharedInstance;
private:
	void InitializeFiles();
private:
	uiImageHashTable imageTable;

};


