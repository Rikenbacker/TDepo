#pragma once

//#include <SDL2\SDL.h>

namespace TDC
{
	class MouseButtons
	{
		public:
			bool ButtonLeft;
			bool ButtonMiddle;
			bool ButtonRight;
			bool ButtonX1;
			bool ButtonX2;

//			MouseButtons(Uint32 btn) { ButtonLeft = btn & SDL_BUTTON_LMASK; ButtonMiddle = btn & SDL_BUTTON_MMASK; ButtonRight = btn & SDL_BUTTON_RMASK; ButtonX1 = btn & SDL_BUTTON_X1MASK; ButtonX2 = btn & SDL_BUTTON_X2MASK; }
	};
}
