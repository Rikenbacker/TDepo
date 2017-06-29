#pragma once

#include "OgrePlatform.h"
#include <functional>
#include <vector>

#include "..\common\Vector2D.h"
#include "..\common\MouseButtons.h"

#define SDL_EVENT_CALLBACK(method) (SDLEventCallback)std::bind(&method, this, std::placeholders::_1)
#define MOUSE_MOVE_CALLBACK(method) (MouseMoveEventCallback)std::bind(&method, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

union SDL_Event;
struct SDL_MouseButtonEvent;

struct SDL_TextInputEvent;
struct SDL_KeyboardEvent;

struct SDL_JoyButtonEvent;
struct SDL_JoyAxisEvent;
struct SDL_JoyHatEvent;

class LSDLEvent;

typedef std::function<void(LSDLEvent*)> SDLEventCallback;
typedef std::function<void(TDC::Vector2D<unsigned int>*, TDC::Vector2D<unsigned int>*, TDC::MouseButtons *)> MouseMoveEventCallback;

enum class InputEventsType {MouseWheelScroll, MouseMove, KeyPressed};


class LSDLEvent
{
	public:
		LSDLEvent() {};
		~LSDLEvent() {};
		virtual void callNext() final;
		virtual void callFirst(const SDL_Event& _env) final;
		virtual void addListener(SDLEventCallback _listener) final;
		const SDL_Event *getSDL_Event() { return env; };

	protected:
		std::vector<SDLEventCallback> m_listeners;
		std::vector<SDLEventCallback>::iterator m_it;
		const SDL_Event *env = nullptr;
		virtual void call();
};

class MouseMoveEvent
{
	public:
		MouseMoveEvent() {};
		~MouseMoveEvent() {};
		void callFirst(TDC::Vector2D<unsigned int>*, TDC::Vector2D<unsigned int>*, TDC::MouseButtons*);
		virtual void callNext();
		virtual void addListener(MouseMoveEventCallback _listener) ;

	private:
		std::vector<MouseMoveEventCallback> m_listeners;
		std::vector<MouseMoveEventCallback>::iterator m_it;
		TDC::Vector2D<unsigned int> *m_position = nullptr;
		TDC::Vector2D<unsigned int> *m_relation = nullptr;
		TDC::MouseButtons *m_btns = nullptr;
		void call();
};
