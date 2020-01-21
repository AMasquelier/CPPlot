#pragma once
#ifndef INPUTS_H_INCLUDED
#define INPUTS_H_INCLUDED

#include <iostream>
#include <SDL2\SDL.h>
#include <thread>
#include "core.h"
#define WIN32
#ifdef WIN32
	#include <Windows.h>
#endif

using namespace std;

class Inputs
{
private:
	static int unichar;
	static bool _typing;
	static int _Event;
	bool _Keys[64][2];


public:
	static bool close_win;
	SDL_Event _event;
	int _xRel, _yRel, _zRel = 0;
	int _x, _y, _z = 0;
	int _AFK = 1;
	Inputs();
	//void Load();
	//static void UpdateEvents();
	void UpdateKeyboardInputs(bool mode);
	void UpdateMouseInputs(bool mode);
	//void SetInput(const int k, bool a);
	//void Entry(string *text, bool Num);
	//int GetEvent();
	bool GetInput(int k);
	bool isHoldingInput(int k);
	bool hasReleasedInput(int k);
	bool pushedInput(int k);
	int GetXRel();
	int GetX();
	int GetYRel();
	int GetY();
	int GetZRel();
	int GetZ();
	enum { Last, Actual };
	enum m_keys { F1, F2, F3, F4, F5, Return, Delete, WheelDown, WheelUp, Down, Up, Right, Left, Space, A, Q, Z, E, R, F, S, P, D, W, L, T, ESCAPE, L_SHIFT, Clic, L_Clic, R_Clic, Ctrl, Quit, Move, WhD, WhU, Input, Back, Next, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO };
};

#endif
