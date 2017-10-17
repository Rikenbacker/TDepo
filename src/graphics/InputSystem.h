#pragma once

#include <irrlicht.h>

class InputSystem : public irr::IEventReceiver
{
	public:
		InputSystem();
		~InputSystem();

		void update();

		bool OnEvent(const irr::SEvent& event);
		bool IsKeyDown(irr::EKEY_CODE keyCode) const;
//		bool isQuit() { return m_quit; }

//		void removeListener(event, listener);

//		void addListener(InputEventsType type, SDLEventCallback funct);
//		void addListener(InputEventsType type, MouseMoveEventCallback funct);

	private:
//		bool m_quit = false;
//		void handleWindowEvent(const SDL_Event& evt);

		// We use this array to store the current state of each key
		bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

