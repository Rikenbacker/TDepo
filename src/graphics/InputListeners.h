#pragma once

#include "OgrePlatform.h"
#include <functional>
#include <vector>

union SDL_Event;
struct SDL_MouseButtonEvent;

struct SDL_TextInputEvent;
struct SDL_KeyboardEvent;

struct SDL_JoyButtonEvent;
struct SDL_JoyAxisEvent;
struct SDL_JoyHatEvent;

class LSDLEvent;

typedef std::function<void(LSDLEvent*)> SDLEventCallback;

enum class InputEventsType {MouseWheelScroll, KeyPressed};

class LSDLEvent
{
	public:
		LSDLEvent() {};
		~LSDLEvent() {};
		void callNext();
		void callFirst(const SDL_Event& _env);
		void addListener(SDLEventCallback _listener);
		const SDL_Event *getSDL_Event() { return env; };

	private:
		std::vector<SDLEventCallback> m_listeners;
		std::vector<SDLEventCallback>::iterator m_it;
		const SDL_Event *env = nullptr;
		void call();
};
