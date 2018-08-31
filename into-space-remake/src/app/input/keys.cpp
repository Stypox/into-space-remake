#include "keys.h"

namespace app::input {
	using std::initializer_list;
	using std::pair;
	using std::tuple;
	using std::get;


	void Keys::updatePress() {
		//keyboard
		for (auto&& key : m_keysPressListener) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::Key{event::Key::press, key.key});
				key.lastState = keyState;
			}
		}

		//mouse
		for (auto&& key : m_mouseKeysPressListener) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::Key{event::Key::press, key.key});
				key.lastState = keyState;
			}
		}
	}
	void Keys::updateDoublePress() {
		//keyboard
		for (auto&& key : m_keysDoublePressListener) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState) {
					if (key.lastPressed + m_doublePressDelay > m_time) {
						m_eventHandler.push(new event::Key{event::Key::doublePress, key.key});
						key.lastPressed = -3 * m_doublePressDelay;
					}
					else
						key.lastPressed = m_time;
				}
				key.lastState = keyState;
			}
		}

		//mouse
		for (auto&& key : m_mouseKeysDoublePressListener) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (keyState) {
					if (key.lastPressed + m_doublePressDelay > m_time) {
						m_eventHandler.push(new event::Key{event::Key::doublePress, key.key});
						key.lastPressed = -3 * m_doublePressDelay;
					}
					else
						key.lastPressed = m_time;
				}
				key.lastState = keyState;
			}
		}
	}
	void Keys::updateRelease() {
		//keyboard
		for (auto&& key : m_keysReleaseListener) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::Key{event::Key::release, key.key});
				key.lastState = keyState;
			}
		}

		//mouse
		for (auto&& key : m_mouseKeysReleaseListener) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::Key{event::Key::release, key.key});
				key.lastState = keyState;
			}
		}
	}
	void Keys::updateLongPress() {
		//keyboard
		for (auto&& key : m_keysLongPressListener) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (keyState)
					key.lastAction = m_time;
			}

			if (key.lastState && key.lastAction + key.delayAfterAction < m_time) {
				m_eventHandler.push(new event::KeyLong{event::KeyLong::press, key.key, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}

		//mouse
		for (auto&& key : m_mouseKeysLongPressListener) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (keyState)
					key.lastAction = m_time;
			}

			if (key.lastState && key.lastAction + key.delayAfterAction < m_time) {
				m_eventHandler.push(new event::KeyLong{event::KeyLong::press, key.key, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}
	}
	void Keys::updateLongRelease() {
		//keyboard
		for (auto&& key : m_keysLongReleaseListener) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (!keyState)
					key.lastAction = m_time;
			}

			if (!key.lastState && key.lastAction + key.delayAfterAction < m_time) {
				m_eventHandler.push(new event::KeyLong{event::KeyLong::release, key.key, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}

		//mouse
		for (auto&& key : m_mouseKeysLongReleaseListener) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (!keyState)
					key.lastAction = m_time;
			}

			if (!key.lastState && key.lastAction + key.delayAfterAction < m_time) {
				m_eventHandler.push(new event::KeyLong{event::KeyLong::release, key.key, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}
	}


	Keys::Keys(GLFWwindow*& window, event::Handler& eventHandler, float doublePressDelay) :
		m_window{window}, m_eventHandler{eventHandler},
		m_doublePressDelay{doublePressDelay} {}
	Keys::Keys(GLFWwindow*& window, event::Handler& eventHandler, float doublePressDelay,
		initializer_list<pair<event::Key::Type, int>> listeners,
		initializer_list<tuple<event::KeyLong::Type, int, float, float>> longListeners) :
		m_window{window}, m_eventHandler{eventHandler},
		m_doublePressDelay{doublePressDelay} {
		for (auto&& listener : listeners)
			addListener(get<event::Key::Type>(listener), get<int>(listener));
		for (auto&& listener : longListeners)
			addListener(get<0>(listener), get<1>(listener), get<2>(listener), get<3>(listener));
	}

	void Keys::addListener(event::Key::Type type, int key) {
		if (key >= 0 && key <= GLFW_MOUSE_BUTTON_LAST) {
			switch (type) {
				case event::Key::press:
					m_mouseKeysPressListener.emplace_back(key);
					break;
				case event::Key::doublePress:
					m_mouseKeysDoublePressListener.emplace_back(key, m_doublePressDelay);
					break;
				case event::Key::release:
					m_mouseKeysReleaseListener.emplace_back(key);
					break;
			}
		}
		else {
			switch (type) {
				case event::Key::press:
					m_keysPressListener.emplace_back(key);
					break;
				case event::Key::doublePress:
					m_keysDoublePressListener.emplace_back(key, m_doublePressDelay);
					break;
				case event::Key::release:
					m_keysReleaseListener.emplace_back(key);
					break;
			}
		}
	}
	void Keys::addListener(event::KeyLong::Type type, int key, float delayAfterAction, float delayInBetween) {
		if (key > 0 && key < GLFW_MOUSE_BUTTON_LAST) {
			switch (type) {
				case event::KeyLong::press:
					m_mouseKeysLongPressListener.emplace_back(key, delayAfterAction, delayInBetween);
					break;
				case event::KeyLong::release:
					m_mouseKeysLongReleaseListener.emplace_back(key, delayAfterAction, delayInBetween);
					break;
			}
		}
		else {
			switch (type) {
				case event::KeyLong::press:
					m_keysLongPressListener.emplace_back(key, delayAfterAction, delayInBetween);
					break;
				case event::KeyLong::release:
					m_keysLongReleaseListener.emplace_back(key, delayAfterAction, delayInBetween);
					break;
			}
		}
	}

	void Keys::update() {
		m_time = static_cast<float>(glfwGetTime());
		updatePress();
		updateDoublePress();
		updateRelease();
		updateLongPress();
		updateLongRelease();
	}
}