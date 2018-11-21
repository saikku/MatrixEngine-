#ifndef Input_H
#define Input_H

#include <Windows.h>
#include <stdio.h>
#include <iostream>

namespace Engine{

#define GET_WHEEL_DELTA_WPARAM(wP)				((short)HIWORD(wP))

	struct keyCodes
	{
		int KC_Back = 0x08;
		int KC_Tab = 0x09;
		int KC_Clear = 0x0c;
		int KC_Return = 0x0D;
		int KC_Shift = 0x10;
		int KC_Control = 0x11;
		int KC_Menu = 0x12;
		int KC_Pause = 0x13;
		int KC_Capital = 0x14;
		int KC_ESC = 0x1B;
		int KC_Space = 0x20;
		int KC_Prior = 0x21;
		int KC_Next = 0x22;
		int KC_End = 0x23;
		int KC_Home = 0x24;
		int KC_Left = 0x25;
		int KC_Up = 0x26;
		int KC_Right = 0x27;
		int KC_Down = 0x28;
		int KC_Select = 0x29;
		int KC_Print = 0x2A;
		int KC_Execute = 0x2B;
		int KC_Snapshot = 0x2C;
		int KC_Insert = 0x2D;
		int KC_Delete = 0x2E;
		int KC_Help = 0x2F;
		int KC_0 = 0x30;
		int KC_1 = 0x31;
		int KC_2 = 0x32;
		int KC_3 = 0x33;
		int KC_4 = 0x34;
		int KC_5 = 0x35;
		int KC_6 = 0x36;
		int KC_7 = 0x37;
		int KC_8 = 0x38;
		int KC_9 = 0x39;
		int KC_A = 0x41;
		int KC_B = 0x42;
		int KC_C = 0x43;
		int KC_D = 0x44;
		int KC_E = 0x45;
		int KC_F = 0x46;
		int KC_G = 0x47;
		int KC_H = 0x48;
		int KC_I = 0x49;
		int KC_J = 0x4A;
		int KC_K = 0x4B;
		int KC_L = 0x4C;
		int KC_M = 0x4D;
		int KC_N = 0x4E;
		int KC_O = 0x4F;
		int KC_P = 0x50;
		int KC_Q = 0x51;
		int KC_R = 0x52;
		int KC_S = 0x53;
		int KC_T = 0x54;
		int KC_U = 0x55;
		int KC_V = 0x56;
		int KC_W = 0x57;
		int KC_X = 0x58;
		int KC_Y = 0x59;
		int KC_Z = 0x5A;
		int KC_NPad_0 = 0x60;
		int KC_NPad_1 = 0x61;
		int KC_NPad_2 = 0x62;
		int KC_NPad_3 = 0x63;
		int KC_NPad_4 = 0x64;
		int KC_NPad_5 = 0x65;
		int KC_NPad_6 = 0x66;
		int KC_NPad_7 = 0x67;
		int KC_NPad_8 = 0x68;
		int KC_NPad_9 = 0x69;
		int KC_Multiply = 0x6A;
		int KC_Add = 0x6B;
		int KC_Separator = 0x6C;
		int KC_Subtract = 0x6D;
		int KC_Decimal = 0x6E;
		int KC_Divide = 0x6F;
		int KC_F1 = 0x70;
		int KC_F2 = 0x71;
		int KC_F3 = 0x72;
		int KC_F4 = 0x73;
		int KC_F5 = 0x74;
		int KC_F6 = 0x75;
		int KC_F7 = 0x76;
		int KC_F8 = 0x77;
		int KC_F9 = 0x78;
		int KC_F10 = 0x79;
		int KC_F11 = 0x7A;
		int KC_F12 = 0x7B;
		int KC_Volume_Mute = 0xAD;
		int KC_Volume_Down = 0xAE;
		int KC_Volume_Up = 0xAF;
	};

	struct mouse
	{
		int LButton = 0x01;
		int RButton = 0x02;
		int MButton = 0x04;
		int XButton_1 = 0x05;		//which provide backward and 
		int XButton_2 = 0x06;		//forward navigation when using your browser
	};

	class Input
	{
	private:
		bool keys[0xff];
		bool prevKeys[0xff];
		int wheel = 0;
		int xPos;
		int yPos;
		int key;


	public:
		void keyUpdate();
		void MouseMove(int x, int y);
		void mouseWheel(WPARAM wP);

		int getKeyState(int key);		//returns 1 if selected key is pressed
		int isKeyPressed(int key);
		int isKeyReleased(int key);

		int getMouseWheel();			//returns 1 or -1(higher number if scrolling faster)

		int getMouseXPos();				//returns mouse position value
		int getMouseYPos();

	};

}
#endif
/*
TODO:
- add mouse xbutton's to win32window.cpp if those are needed

- add joystick input and necessary function to it if needed

- add to wm_mouse move check x and y locations for wm_buttondown's in win32window.cpp
*/
/*
Keyboard input: https://msdn.microsoft.com/en-us/library/windows/desktop/ms646268(v=vs.85).aspx

virtual-key codes: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

- Blockinput/enableWindow when application not in use
https://msdn.microsoft.com/en-us/library/windows/desktop/ms646290(v=vs.85).aspx
/https://msdn.microsoft.com/en-us/library/windows/desktop/ms646291(v=vs.85).aspxs

controller input:
https://msdn.microsoft.com/en-us/library/windows/desktop/ee417001(v=vs.85).aspx
https://msdn.microsoft.com/en-us/library/windows/desktop/dd743591(v=vs.85).aspx
*/
