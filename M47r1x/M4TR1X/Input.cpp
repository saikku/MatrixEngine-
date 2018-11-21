#include "Input.h"

namespace Engine{

	void Input::keyUpdate()
	{
		for (int i = 0; i < sizeof(keys); ++i)
		{
			prevKeys[i] = keys[i];
		}

		for (int i = 0; i < 0xff; ++i)
		{
			keys[i] = (GetAsyncKeyState(i) & 0x8000) ? 1 : 0;
		}
	}

	void Input::MouseMove(int x, int y)
	{
		xPos = x;
		yPos = y;
		std::cout << xPos << " " << yPos << "\n";
		return;
	}

	void Input::mouseWheel(WPARAM wP)
	{
		wheel += GET_WHEEL_DELTA_WPARAM(wP) / WHEEL_DELTA;
		std::cout << wheel << "\n";
	}

	int Input::getKeyState(int key)
	{
		return keys[key];
	}

	int Input::isKeyPressed(int key )
	{
		return keys[key] && !prevKeys[key];
	}

	int Input::isKeyReleased(int key)
	{
		return !keys[key] && prevKeys[key];
	}

	int Input::getMouseWheel()
	{
		return wheel;
	}

	int Input::getMouseXPos()
	{
		return xPos;
	}

	int Input::getMouseYPos()
	{
		return yPos;
	}
}
