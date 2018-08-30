#include "keys.h"

namespace app::input {
	Keys::Keys(event::Handler& handler, int doublePressDelay) :
		m_doublePressDelay{doublePressDelay}, m_window{nullptr},
		m_handler{handler} {}
	Keys::Keys(GLFWwindow* window, event::Handler& handler, int doublePressDelay) :
		m_doublePressDelay{doublePressDelay}, m_window{window},
		m_handler{handler} {}

	void Keys::addListener(int key, event::Key::Type type) {
		m_keys.emplace_back(key, type, m_doublePressDelay);
	}
	
	void Keys::update() {
		for (auto&& key : m_keys) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState) {
					if (key.type == event::Key::press)
						m_handler.push(static_cast<event::Event*>(new event::Key{event::Key::press, key.key}));
					else if (key.type == event::Key::doublePress && key.lastPressed + m_doublePressDelay > 0.0f)
						m_handler.push(static_cast<event::Event*>(new event::Key{event::Key::doublePress, key.key}));
					key.lastPressed = glfwGetTime();
				}
				else {
					if (key.type == event::Key::release)
						m_handler.push(static_cast<event::Event*>(new event::Key{event::Key::release, key.key}));
				}
				key.lastState = keyState;
			}
		}
	}
}