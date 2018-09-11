#include "mousemove.h"

#include "../event/mousemove.h"

namespace app::input {
	MouseMove::MouseMove(GLFWwindow*& window, event::Handler& eventHandler) :
		MouseMove{window, eventHandler, 0, 0} {}
	MouseMove::MouseMove(GLFWwindow*& window, event::Handler& eventHandler, sp::Tint8 nrEventsX, sp::Tint8 nrEventsY) :
		m_window{window}, m_eventHandler{eventHandler},
		m_nrEventsX{nrEventsX}, m_nrEventsY{nrEventsY} {}

	void MouseMove::update() {
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		double xOffset = x - m_lastX,
			   yOffset = y - m_lastY;

		if (xOffset != 0.0) {
			for (sp::Tint8 xEvents = 0; xEvents != m_nrEventsX; ++xEvents)
				m_eventHandler.push(new event::MouseMove{event::MouseMove::xAxis, xOffset, x});
			m_lastX = x;
		}
		
		if (yOffset != 0.0) {
			for (sp::Tint8 yEvents = 0; yEvents != m_nrEventsY; ++yEvents)
				m_eventHandler.push(new event::MouseMove{event::MouseMove::yAxis, yOffset, y});
			m_lastY = y;
		}
	}
}