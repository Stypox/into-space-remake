#ifndef _INTO_SPACE_REMAKE_APP_INPUT_MOUSEMOVE_HPP_
#define _INTO_SPACE_REMAKE_APP_INPUT_MOUSEMOVE_HPP_

#include <GLFW/glfw3.h>
#include <stypox/event_notifier.hpp>

namespace app::input {
	class MouseMove {
		GLFWwindow*& m_window;
		stypox::EventNotifier& m_eventNotifier;
		int8_t m_nrEventsX, m_nrEventsY;

		double m_lastX, m_lastY;
	public:
		MouseMove(GLFWwindow*& window, stypox::EventNotifier& eventNotifier);
		MouseMove(GLFWwindow*& window, stypox::EventNotifier& eventNotifier, int8_t nrEventsX, int8_t nrEventsY);

		inline void setNrEventsX(int8_t nrEventsX) { m_nrEventsX = nrEventsX; }
		inline void setNrEventsY(int8_t nrEventsY) { m_nrEventsY = nrEventsY; }

		void update();
	};
}

#endif