#ifndef _INTO_SPACE_REMAKE_APP_INPUT_MOUSE_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_MOUSE_H_

#include <GLFW/glfw3.h>
#include "../event/handler.h"

namespace app::input {
	class Scroll {
		static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

		GLFWwindow*& m_window;
		event::Handler& m_eventHandler;
		int8_t m_nrEventsX, m_nrEventsY;

		double m_xOffset, m_yOffset;
	
		void updateOffset(double xOffset, double yOffset);
	public:
		Scroll(GLFWwindow*& window, event::Handler& eventHandler);
		Scroll(GLFWwindow*& window, event::Handler& eventHandler, int8_t nrEventsX, int8_t nrEventsY);
		~Scroll();

		inline void setNrEventsX(int8_t nrEventsX) { m_nrEventsX = nrEventsX; }
		inline void setNrEventsY(int8_t nrEventsY) { m_nrEventsY = nrEventsY; }

		void activateWindowCallback();
		void removeWindowCallback();

		void update();
	};
}

#endif