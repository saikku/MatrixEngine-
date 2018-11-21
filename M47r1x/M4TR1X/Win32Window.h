#ifndef WIN32WINDOW_H
#define WIN32WINDOW_H
#include <tchar.h>
#include "Window.h"
#include "windows.h"
#include <string>
#include "Input.h"


namespace Engine{
	class Input;

	class Win32Window : public Window
	{
	public:
		Win32Window(int width, int height, const std::wstring& title);
		~Win32Window();

		bool updateMsg();
		virtual EGLNativeWindowType getNativeWindow() const;

	private:
		HWND hwnd;
		// Jos on aktiivinen, palauttaa TRUE jos on
		bool isActive;
	};
}
#endif
/*
TODO:
- move "Engine::Input inpt" from Win32Window.cpp (line 38 and 45) to Win32Window.h
*/