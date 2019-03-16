#ifndef _INTO_SPACE_REMAKE_APP_INPUT_MOUSE_HPP_
#define _INTO_SPACE_REMAKE_APP_INPUT_MOUSE_HPP_

#include <GLFW/glfw3.h>
#include <stypox/event_notifier.hpp>

namespace app::input {
	class Scroll {
		static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

		GLFWwindow*& m_window;
		stypox::EventNotifier& m_eventNotifier;
		int8_t m_nrEventsX, m_nrEventsY;

		double m_xOffset, m_yOffset;
	
		void updateOffset(double xOffset, double yOffset);
	public:
		Scroll(GLFWwindow*& window, stypox::EventNotifier& eventNotifier);
		Scroll(GLFWwindow*& window, stypox::EventNotifier& eventNotifier, int8_t nrEventsX, int8_t nrEventsY);
		~Scroll();

		inline void setNrEventsX(int8_t nrEventsX) { m_nrEventsX = nrEventsX; }
		inline void setNrEventsY(int8_t nrEventsY) { m_nrEventsY = nrEventsY; }

		void activateWindowCallback();
		void removeWindowCallback();

		void update();
	};
}

#endif