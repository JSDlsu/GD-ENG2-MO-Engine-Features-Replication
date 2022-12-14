#include "BNS_Window.h"
#include "BNS_EngineTime.h"
#include <exception>

#include "BNS_UIManager.h"
#include "IMGUI/imgui.h"

static BNS_Window* windowInstance = nullptr;

//declare for handling mouse and key events in IMGUI.
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Calls the events of our window (creation and destroy events)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//Used for processing input events for IMGUI
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	switch (msg)
	{
	case WM_CREATE:
	{
		// Event fired when the window is created
		// collected here..

		break;
	}

	case WM_SIZE:
	{
		// Event fired when the window is resized
		windowInstance->onSize();

		break;
	}

	case WM_SETFOCUS:
	{
		// Event fired when the window get focus
		windowInstance->onFocus();
		break;
	}

	case WM_KILLFOCUS:
	{
		// Event fired when the window lost focus
		windowInstance->onKillFocus();
		break;
	}

	case WM_DESTROY:
	{
		// Event fired when the window is destroyed
		windowInstance->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	// recall this function to get another response (recursive)
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

BNS_Window::BNS_Window()
{
	windowInstance = this;
	// Set appearance for our windows; Setting up WNDCLASSEX object
	// WNDCLASSEX contains the properties of the window
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	// L == (wchar_t*); an optimize typecasting/conversion
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;
	// registers the customized properties we've set on our window
	// If the registration of class will fail, the function will return false
	if (!::RegisterClassEx(&wc))
		throw std::exception("BNS_Window not created successfully");

	/*if (!window)
		window = this;*/

		/* 12 Parameters
		 * 1 - WS_EX_OVERLAPPEDWINDOW
		 * 2 - Our lpszClassName we've set
		 * 3 - Title of our window
		 * 4 - Style flags (dw style)
		 * 5 - Position(X) of our window (default)
		 * 6 - Position(Y) of our window (default)
		 * 7 - Width of our window
		 * 8 - Height of our window
		 * 9 - hWndParent reference
		 * 10 - hMenu reference
		 * 11 - hInstance reference
		 * 12 - lpParam reference
		 */
		 //Creation of the window; HWND - "Handle to a BNS_Window"
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, BNS_UIManager::WINDOW_WIDTH, BNS_UIManager::WINDOW_HEIGHT,
		NULL, NULL, NULL, NULL);

	// if the creation fail return false
	if (!m_hwnd)
		throw std::exception("BNS_Window not created successfully");

	// show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	// Allow us to redraw the content of our window
	::UpdateWindow(m_hwnd);

	// set this flag to true to indicate that the window is initialized and running
	m_is_run = true;
	

}

BNS_Window::~BNS_Window()
{

}


bool BNS_Window::broadcast()
{
	MSG msg;

	// first time to initialize
	if (!m_is_init)
	{
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		BNS_EngineTime::initialize();
		this->onCreate();
		m_is_init = true;
	}

	BNS_EngineTime::LogFrameStart();
	// renders all the frames of the graphic 'C'
	this->onUpdate();

	// creates message based on the actions done on the windows that will be pass then to the 'WNDPROC'
	// message was received from the queue of the operating system
	while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		// translate msg into string / character messages / value of the window messages macro
		TranslateMessage(&msg);
		// gives the returned translated message to the WNDPROC
		DispatchMessage(&msg);
	}

	// doesn't allow the CPU to throttle due to chunk of processes;
	// allows a minimal pause of '1' Msec so that the CPU can handle the loop
	Sleep(1);
	BNS_EngineTime::LogFrameEnd();

	return true;
}

bool BNS_Window::isRun()
{
	if (m_is_run)
		broadcast();
	return m_is_run;
}

RECT BNS_Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

RECT BNS_Window::getSizeScreen()
{
	RECT rc;

	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = ::GetSystemMetrics(SM_CYSCREEN);

	return rc;
}

void BNS_Window::onCreate()
{
	
}

void BNS_Window::onUpdate()
{
	
}

void BNS_Window::onDestroy()
{
	m_is_run = false;
}

void BNS_Window::onFocus()
{
}

void BNS_Window::onKillFocus()
{
}

void BNS_Window::onSize()
{
}
