#include "mousemove.h"

#include "../event/mousemove.h"

namespace app::input {
	MouseMove::MouseMove(GLFWwindow*& window, stypox::EventNotifier& eventNotifier) :
		MouseMove{window, eventNotifier, 0, 0} {}
	MouseMove::MouseMove(GLFWwindow*& window, stypox::EventNotifier& eventNotifier, int8_t nrEventsX, int8_t nrEventsY) :
		m_window{window}, m_eventNotifier{eventNotifier},
		m_nrEventsX{nrEventsX}, m_nrEventsY{nrEventsY} {}

	void MouseMove::update() {
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		double xOffset = x - m_lastX,
			   yOffset = y - m_lastY;

		if (xOffset != 0.0) {
			for (int8_t xEvents = 0; xEvents != m_nrEventsX; ++xEvents)
				m_eventNotifier.notify(event::MouseMove{event::MouseMove::xAxis, xOffset, x});
			m_lastX = x;
		}
		
		if (yOffset != 0.0) {
			for (int8_t yEvents = 0; yEvents != m_nrEventsY; ++yEvents)
				m_eventNotifier.notify(event::MouseMove{event::MouseMove::yAxis, yOffset, y});
			m_lastY = y;
		}
	}
}