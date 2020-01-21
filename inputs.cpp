#include "Inputs.h"

//Inputs
int  Inputs::unichar = 0;
bool Inputs::_typing = false;
int  Inputs::_Event = 0;
bool Inputs::close_win = false;


Inputs::Inputs()
{
	for (int i = 0; i < 32; i++)
	{
		_Keys[i][Last] = false;
		_Keys[i][Actual] = false;
	}
}

void Inputs::UpdateKeyboardInputs(bool mode)
{
	for (int i = 0; i < 64; i++)
		_Keys[i][Last] = _Keys[i][Actual];

	_Keys[WheelDown][Actual] = _Keys[WheelUp][Actual] = false;

	while (SDL_PollEvent(&_event))
	{
		switch (_event.type)
		{
		case SDL_QUIT:
			close_win = true;
			break;
		case SDL_KEYDOWN:
			_Keys[Up][Actual] |= (_event.key.keysym.sym == SDLK_UP);
			_Keys[Down][Actual] |= (_event.key.keysym.sym == SDLK_DOWN);
			_Keys[Right][Actual] |= (_event.key.keysym.sym == SDLK_RIGHT);
			_Keys[Left][Actual] |= (_event.key.keysym.sym == SDLK_LEFT);
			_Keys[A][Actual] |= (_event.key.keysym.sym == SDLK_a);
			_Keys[Q][Actual] |= (_event.key.keysym.sym == SDLK_q);
			_Keys[Z][Actual] |= (_event.key.keysym.sym == SDLK_z);
			_Keys[E][Actual] |= (_event.key.keysym.sym == SDLK_e);
			_Keys[D][Actual] |= (_event.key.keysym.sym == SDLK_d);
			_Keys[R][Actual] |= (_event.key.keysym.sym == SDLK_r);
			_Keys[F][Actual] |= (_event.key.keysym.sym == SDLK_f);
			_Keys[P][Actual] |= (_event.key.keysym.sym == SDLK_p);
			_Keys[S][Actual] |= (_event.key.keysym.sym == SDLK_s);
			_Keys[W][Actual] |= (_event.key.keysym.sym == SDLK_w);
			_Keys[L][Actual] |= (_event.key.keysym.sym == SDLK_l);
			_Keys[T][Actual] |= (_event.key.keysym.sym == SDLK_t);
			_Keys[ONE][Actual] |= (_event.key.keysym.sym == SDLK_1);
			_Keys[TWO][Actual] |= (_event.key.keysym.sym == SDLK_2);
			_Keys[THREE][Actual] |= (_event.key.keysym.sym == SDLK_3);
			_Keys[FOUR][Actual] |= (_event.key.keysym.sym == SDLK_4);
			_Keys[FIVE][Actual] |= (_event.key.keysym.sym == SDLK_5);
			_Keys[SIX][Actual] |= (_event.key.keysym.sym == SDLK_6);
			_Keys[SEVEN][Actual] |= (_event.key.keysym.sym == SDLK_7);
			_Keys[EIGHT][Actual] |= (_event.key.keysym.sym == SDLK_8);
			_Keys[NINE][Actual] |= (_event.key.keysym.sym == SDLK_9);
			_Keys[ZERO][Actual] |= (_event.key.keysym.sym == SDLK_0);
			_Keys[ESCAPE][Actual] |= (_event.key.keysym.sym == SDLK_ESCAPE);
			_Keys[Space][Actual] |= (_event.key.keysym.sym == SDLK_SPACE);
			_Keys[L_SHIFT][Actual] |= (_event.key.keysym.sym == SDLK_LSHIFT);
			_Keys[Ctrl][Actual] |= (_event.key.keysym.sym == SDLK_LCTRL);
			_Keys[Delete][Actual] |= (_event.key.keysym.sym == SDLK_DELETE);
			_Keys[Return][Actual] |= (_event.key.keysym.sym == SDLK_RETURN);
			_Keys[F1][Actual] |= (_event.key.keysym.sym == SDLK_F1);
			_Keys[F2][Actual] |= (_event.key.keysym.sym == SDLK_F2);
			_Keys[F3][Actual] |= (_event.key.keysym.sym == SDLK_F3);
			_Keys[F4][Actual] |= (_event.key.keysym.sym == SDLK_F4);
			_Keys[F5][Actual] |= (_event.key.keysym.sym == SDLK_F5);
			break;
		case SDL_KEYUP:
			_Keys[Up][Actual] &= (_event.key.keysym.sym != SDLK_UP);
			_Keys[Down][Actual] &= (_event.key.keysym.sym != SDLK_DOWN);
			_Keys[Right][Actual] &= (_event.key.keysym.sym != SDLK_RIGHT);
			_Keys[Left][Actual] &= (_event.key.keysym.sym != SDLK_LEFT);
			_Keys[A][Actual] &= (_event.key.keysym.sym != SDLK_a);
			_Keys[Q][Actual] &= (_event.key.keysym.sym != SDLK_q);
			_Keys[Z][Actual] &= (_event.key.keysym.sym != SDLK_z);
			_Keys[E][Actual] &= (_event.key.keysym.sym != SDLK_e);
			_Keys[D][Actual] &= (_event.key.keysym.sym != SDLK_d);
			_Keys[R][Actual] &= (_event.key.keysym.sym != SDLK_r);
			_Keys[F][Actual] &= (_event.key.keysym.sym != SDLK_f);
			_Keys[P][Actual] &= (_event.key.keysym.sym != SDLK_p);
			_Keys[S][Actual] &= (_event.key.keysym.sym != SDLK_s);
			_Keys[W][Actual] &= (_event.key.keysym.sym != SDLK_w);
			_Keys[L][Actual] &= (_event.key.keysym.sym != SDLK_l);
			_Keys[T][Actual] &= (_event.key.keysym.sym != SDLK_t);
			_Keys[ONE][Actual] &= (_event.key.keysym.sym != SDLK_1);
			_Keys[TWO][Actual] &= (_event.key.keysym.sym != SDLK_2);
			_Keys[THREE][Actual] &= (_event.key.keysym.sym != SDLK_3);
			_Keys[FOUR][Actual] &= (_event.key.keysym.sym != SDLK_4);
			_Keys[FIVE][Actual] &= (_event.key.keysym.sym != SDLK_5);
			_Keys[SIX][Actual] &= (_event.key.keysym.sym != SDLK_6);
			_Keys[SEVEN][Actual] &= (_event.key.keysym.sym != SDLK_7);
			_Keys[EIGHT][Actual] &= (_event.key.keysym.sym != SDLK_8);
			_Keys[NINE][Actual] &= (_event.key.keysym.sym != SDLK_9);
			_Keys[ZERO][Actual] &= (_event.key.keysym.sym != SDLK_0);
			_Keys[ESCAPE][Actual] &= (_event.key.keysym.sym != SDLK_ESCAPE);
			_Keys[Space][Actual] &= (_event.key.keysym.sym != SDLK_SPACE);
			_Keys[L_SHIFT][Actual] &= (_event.key.keysym.sym != SDLK_LSHIFT);
			_Keys[Ctrl][Actual] &= (_event.key.keysym.sym != SDLK_LCTRL);
			_Keys[Delete][Actual] &= (_event.key.keysym.sym != SDLK_DELETE);
			_Keys[Return][Actual] &= (_event.key.keysym.sym != SDLK_RETURN);
			_Keys[F1][Actual] &= (_event.key.keysym.sym != SDLK_F1);
			_Keys[F2][Actual] &= (_event.key.keysym.sym != SDLK_F2);
			_Keys[F3][Actual] &= (_event.key.keysym.sym != SDLK_F3);
			_Keys[F4][Actual] &= (_event.key.keysym.sym != SDLK_F4);
			_Keys[F5][Actual] &= (_event.key.keysym.sym != SDLK_F5);
			break;
		case SDL_MOUSEWHEEL:
			_Keys[WheelDown][Actual] = (_event.wheel.y < 0);
			_Keys[WheelUp][Actual] = (_event.wheel.y > 0);
			_z = _event.wheel.y;
			break;
		case SDL_MOUSEMOTION:
			_x = _event.motion.x;
			_y = _event.motion.y;
			_xRel = _event.motion.xrel;
			_yRel = _event.motion.yrel;
			break;
		case SDL_MOUSEBUTTONDOWN:
			_Keys[R_Clic][Actual] |= (_event.button.button == SDL_BUTTON_RIGHT);
			_Keys[L_Clic][Actual] |= (_event.button.button == SDL_BUTTON_LEFT);
			break;
		case SDL_MOUSEBUTTONUP:
			_Keys[R_Clic][Actual] &= (_event.button.button != SDL_BUTTON_RIGHT);
			_Keys[L_Clic][Actual] &= (_event.button.button != SDL_BUTTON_LEFT);
			break;
		}
	}


}


bool Inputs::GetInput(int k) { return _Keys[k][Actual]; }

bool Inputs::isHoldingInput(int k)
{
	return (_Keys[k][Last] == _Keys[k][Actual] && _Keys[k][Last]);
}

bool Inputs::hasReleasedInput(int k)
{
	return (_Keys[k][Last] != _Keys[k][Actual] && !_Keys[k][Actual]);
}

bool Inputs::pushedInput(int k)
{
	return (_Keys[k][Last] != _Keys[k][Actual] && _Keys[k][Last] == false);
}

int Inputs::GetXRel()
{
	return _xRel;
}

int Inputs::GetYRel()
{
	return _yRel;
}

int Inputs::GetX()
{
	return _x;
}

int Inputs::GetY()
{
	return _y;
}

int Inputs::GetZRel()
{
	return _zRel;
}

int Inputs::GetZ()
{
	return _z;
}
