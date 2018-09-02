#ifndef _INTO_SPACE_REMAKE_APP_INPUT_MOUSEMOVE_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_MOUSEMOVE_H_

#include <GLFW/glfw3.h>
#include <stypox/basicTypes.h>

#include "../event/mousemove.h"
#include "../event/handler.h"

namespace app::input {
	class MouseMove {
		GLFWwindow*& m_window;
		event::Handler& m_eventHandler;
		sp::Tint8 m_nrEventsX, m_nrEventsY;

		double m_lastX, m_lastY;
	public:
		MouseMove(GLFWwindow*& window, event::Handler& eventHandler);
		MouseMove(GLFWwindow*& window, event::Handler& eventHandler, sp::Tint8 nrEventsX, sp::Tint8 nrEventsY);

		inline void setNrEventsX(sp::Tint8 nrEventsX) { m_nrEventsX = nrEventsX; }
		inline void setNrEventsY(sp::Tint8 nrEventsY) { m_nrEventsY = nrEventsY; }

		void update();
	};
}

#endif