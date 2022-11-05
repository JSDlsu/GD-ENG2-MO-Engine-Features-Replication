#pragma once
#include <string>

class BNS_Resource
{
public:
	BNS_Resource(const wchar_t* full_path);
	~BNS_Resource();
protected:
	std::wstring m_full_path;
};

