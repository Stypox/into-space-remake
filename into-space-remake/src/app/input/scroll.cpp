#include "scroll.h"

#include <vector>
#include <algorithm>

#include "../event/scroll.h"

namespace app::input {
	void Scroll::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
		if (void* userPointer = glfwGetWindowUserPointer(window); userPointer) {
			std::vector<Scroll*>* scrollsToUpdate = static_cast<std::vector<Scroll*>*>(userPointer);
			for (auto&& scroll : *scrollsToUpdate)
				scroll->updateOffset(xOffset, yOffset);
		}
	}

	void Scroll::updateOffset(double xOffset, double yOffset) {
		m_xOffset += xOffset;
		m_yOffset += yOffset;
	}
	
	Scroll::Scroll(GLFWwindow*& window, event::Handler& eventHandler) :
		Scroll{window, eventHandler, 0, 0} {}
	Scroll::Scroll(GLFWwindow*& window, event::Handler& eventHandler, int8_t nrEventsX, int8_t nrEventsY) :
		m_window{window}, m_eventHandler{eventHandler},
		m_nrEventsX{nrEventsX}, m_nrEventsY{nrEventsY},
		m_xOffset{0.0}, m_yOffset{0.0} {
		activateWindowCallback();
	}
	Scroll::~Scroll() {
		removeWindowCallback();
	}

	void Scroll::activateWindowCallback() {
		if (m_window != nullptr) {
			if (void* userPointer = glfwGetWindowUserPointer(m_window); userPointer) {
				std::vector<Scroll*>* scrollsToUpdate = static_cast<std::vector<Scroll*>*>(userPointer);
				if (std::find(scrollsToUpdate->begin(), scrollsToUpdate->end(), this) == scrollsToUpdate->end()) {
					scrollsToUpdate->push_back(this);
				}
			}
			else {
				glfwSetWindowUserPointer(m_window, new std::vector<Scroll*> {this});
				glfwSetScrollCallback(m_window, scrollCallback);
			}
		}
	}
	void Scroll::removeWindowCallback() {
		if (m_window != nullptr) {
			if (void* userPointer = glfwGetWindowUserPointer(m_window); userPointer) {
				std::vector<Scroll*>* scrollsToUpdate = static_cast<std::vector<Scroll*>*>(userPointer);
				if (auto thisScroll = std::find(scrollsToUpdate->begin(), scrollsToUpdate->end(), this); thisScroll != scrollsToUpdate->end()) {
					scrollsToUpdate->erase(thisScroll, thisScroll + 1);
				}
				if (scrollsToUpdate->size() == 0) {
					glfwSetScrollCallback(m_window, nullptr);
					glfwSetWindowUserPointer(m_window, nullptr);
					delete scrollsToUpdate;
				}
			}
		}
	}

	void Scroll::update() {
		double xCursor, yCursor;
		glfwGetCursorPos(m_window, &xCursor, &yCursor);

		if (m_xOffset != 0.0) {
			for (int8_t xEvents = 0; xEvents != m_nrEventsX; ++xEvents)
				m_eventHandler.push(new event::Scroll{event::Scroll::xAxis, m_xOffset, xCursor, yCursor});
			m_xOffset = 0.0;
		}

		if (m_yOffset != 0.0) {
			for (int8_t yEvents = 0; yEvents != m_nrEventsY; ++yEvents)
				m_eventHandler.push(new event::Scroll{event::Scroll::yAxis, m_yOffset, xCursor, yCursor});
			m_yOffset = 0.0;
		}
	}
}