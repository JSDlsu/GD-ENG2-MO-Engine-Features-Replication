#pragma once
#include <Windows.h>

// this window class can handle events in a customized way (creation/opening, release/closing)
class BNS_Window
{
public:
	//Initialize the window
	BNS_Window();
	//Release the window
	~BNS_Window();

	bool isRun();
	RECT getClientWindowRect();

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();
public:
	static int HEIGHT;
	static int WIDTH;
private:
	bool broadcast();
protected:
	HWND m_hwnd;
	bool m_is_run;
	bool m_is_init = false;
};


