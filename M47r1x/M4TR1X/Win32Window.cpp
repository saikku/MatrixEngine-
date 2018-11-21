#include "Win32Window.h"
#include "Ref.h"
#include "Application.h"

namespace Engine{

	LRESULT WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT  lRet = 1;
		switch (uMsg)
		{
		case WM_CREATE:
			break;

		case WM_PAINT:
		{
						 Win32Window *window = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
						 // Call application render and pass pointer to Graphics-object.
						 window->getApplication()->Render(window, window->getGraphics());
						 ValidateRect(window->getNativeWindow(), NULL);
		}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CHAR:
		{
						POINT      point;
						Win32Window *esContext = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
						GetCursorPos(&point);
		}
			break;
	
		case WM_KEYDOWN:
		{
		}
			break;
		
		case WM_MOUSEMOVE:
		{
		}
		break;
		default:
			lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}
		
		return lRet;
	}



	Win32Window::Win32Window(int width, int height, const std::wstring& title)
		: Window()
		, hwnd(NULL)
		, isActive(false) // Assume not yet active
	{
		setSize(width, height); // Set size to base class

		WNDCLASS wndclass = { 0 };
		DWORD    wStyle = 0;
		RECT     windowRect;
		HINSTANCE hInstance = GetModuleHandle(NULL);

		wndclass.style = CS_OWNDC;
		wndclass.lpfnWndProc = (WNDPROC)WindowProc;
		wndclass.hInstance = hInstance;
		wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszClassName = "opengles2.0";

		if (!RegisterClass(&wndclass))
			return; // fail!

		wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

		// Adjust the window rectangle so that the client area has
		// the correct number of pixels
		windowRect.left = 0;
		windowRect.top = 0;
		windowRect.right = width - windowRect.left;
		windowRect.bottom = height - windowRect.top;

		AdjustWindowRect(&windowRect, wStyle, FALSE);
		hwnd = CreateWindow(
			"opengles2.0",
			"Makkaratehdas",
			wStyle,
			0,
			0,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			NULL,
			NULL,
			hInstance,
			NULL);

		// Set the ESContext* to the GWL_USERDATA so that it is available to the 
		// ESWindowProc
		SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG)(LONG_PTR)this);

		if (hwnd == NULL)
		{
			// TODO: Unregister window class if fail
			return; // fail!
		}

		ShowWindow(hwnd, TRUE);

		// success!
		isActive = true;
	}


	Win32Window::~Win32Window()
	{
	}


	// Returns native window handle
	EGLNativeWindowType Win32Window::getNativeWindow() const
	{
		return hwnd;
	}


	bool Win32Window::updateMsg()
	{
		MSG msg = { 0 };
		int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
		if (gotMsg)
		{
			if (msg.message == WM_QUIT)
			{
				isActive = false;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			SendMessage(getNativeWindow(), WM_PAINT, 0, 0);
		}
		return isActive;
	}
}

