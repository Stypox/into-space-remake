#include "keys.h"

namespace app::input {
	Keys::Keys(GLFWwindow* window, event::Handler& eventHandler, int doublePressDelay) :
		m_doublePressDelay{doublePressDelay}, m_window{window},
		m_eventHandler{eventHandler} {}
	Keys::Keys(GLFWwindow* window, event::Handler& eventHandler, int doublePressDelay, std::initializer_list<std::pair<int, event::Key::Type>> listeners) :
		m_doublePressDelay{doublePressDelay}, m_window{window},
		m_eventHandler{eventHandler} {
		for (auto&& listener : listeners)
			addListener(std::get<int>(listener), std::get<event::Key::Type>(listener));
	}

	void Keys::update() {
		for (auto&& key : m_keys) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState) {
					if (key.type == event::Key::press)
						m_eventHandler.push(static_cast<event::Event*>(new event::Key{event::Key::press, key.key}));
					else if (key.type == event::Key::doublePress && key.lastPressed + m_doublePressDelay > 0.0f)
						m_eventHandler.push(static_cast<event::Event*>(new event::Key{event::Key::doublePress, key.key}));
					key.lastPressed = glfwGetTime();
				}
				else {
					if (key.type == event::Key::release)
						m_eventHandler.push(static_cast<event::Event*>(new event::Key{event::Key::release, key.key}));
				}
				key.lastState = keyState;
			}
		}
	}
}