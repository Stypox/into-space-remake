#ifndef _INTO_SPACE_REMAKE_APP_INPUT_MOUSEMOVE_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_MOUSEMOVE_H_

#include <GLFW/glfw3.h>

#include "../event/handler.h"

namespace app::input {
	class MouseMove {
		GLFWwindow*& m_window;
		event::Handler& m_eventHandler;
		int8_t m_nrEventsX, m_nrEventsY;

		double m_lastX, m_lastY;
	public:
		MouseMove(GLFWwindow*& window, event::Handler& eventHandler);
		MouseMove(GLFWwindow*& window, event::Handler& eventHandler, int8_t nrEventsX, int8_t nrEventsY);

		inline void setNrEventsX(int8_t nrEventsX) { m_nrEventsX = nrEventsX; }
		inline void setNrEventsY(int8_t nrEventsY) { m_nrEventsY = nrEventsY; }

		void update();
	};
}

#endif