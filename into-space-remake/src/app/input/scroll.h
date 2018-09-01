#ifndef _INTO_SPACE_REMAKE_APP_INPUT_MOUSE_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_MOUSE_H_

#include <vector>
#include <algorithm>
#include <GLFW/glfw3.h>
#include <stypox/basicTypes.h>

#include "../event/scroll.h"
#include "../event/handler.h"

namespace app::input {
	class Scroll {
		static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

		GLFWwindow*& m_window;
		event::Handler& m_eventHandler;
		sp::Tint8 m_nrEventsX, m_nrEventsY;

		double m_xOffset, m_yOffset;
	
		void updateOffset(double xOffset, double yOffset);
	public:
		Scroll(GLFWwindow*& window, event::Handler& eventHandler);
		Scroll(GLFWwindow*& window, event::Handler& eventHandler, sp::Tint8 nrEventsX, sp::Tint8 nrEventsY);
		~Scroll();

		inline void setNrEventsX(sp::Tint8 nrEventsX) { m_nrEventsX = nrEventsX; }
		inline void setNrEventsY(sp::Tint8 nrEventsY) { m_nrEventsY = nrEventsY; }

		void activateWindowCallback();
		void removeWindowCallback();

		void update();
	};
}

#endif