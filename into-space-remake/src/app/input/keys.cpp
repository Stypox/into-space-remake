#include "keys.h"

namespace app::input {
	using std::initializer_list;
	using std::pair;
	using std::tuple;
	using std::get;


	void Keys::updatePress() {
		//keyboard
		for (auto&& key : m_pressData) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::Key{event::Key::press, key.key});
				key.lastState = keyState;
			}
		}

		//mouse
		for (auto&& key : m_mousePressData) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::Key{event::Key::press, key.key});
				key.lastState = keyState;
			}
		}
	}
	void Keys::updateDoublePress() {
		//keyboard
		for (auto&& key : m_doublePressData) {
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
		for (auto&& key : m_mouseDoublePressData) {
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
		for (auto&& key : m_releaseData) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::Key{event::Key::release, key.key});
				key.lastState = keyState;
			}
		}

		//mouse
		for (auto&& key : m_mouseReleaseData) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::Key{event::Key::release, key.key});
				key.lastState = keyState;
			}
		}
	}
	void Keys::updateLongPress() {
		//keyboard
		for (auto&& key : m_longPressData) {
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
		for (auto&& key : m_mouseLongPressData) {
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
		for (auto&& key : m_longReleaseData) {
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
		for (auto&& key : m_mouseLongReleaseData) {
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
		//mouse
		if (key >= 0 && key <= GLFW_MOUSE_BUTTON_LAST) {
			switch (type) {
				case event::Key::press:
					m_mousePressData.emplace_back(key);
					break;
				case event::Key::doublePress:
					m_mouseDoublePressData.emplace_back(key, m_doublePressDelay);
					break;
				case event::Key::release:
					m_mouseReleaseData.emplace_back(key);
					break;
			}
		}
		//keyboard
		else {
			switch (type) {
				case event::Key::press:
					m_pressData.emplace_back(key);
					break;
				case event::Key::doublePress:
					m_doublePressData.emplace_back(key, m_doublePressDelay);
					break;
				case event::Key::release:
					m_releaseData.emplace_back(key);
					break;
			}
		}
	}
	void Keys::addListener(event::KeyLong::Type type, int key, float delayAfterAction, float delayInBetween) {
		//mouse
		if (key > 0 && key < GLFW_MOUSE_BUTTON_LAST) {
			switch (type) {
				case event::KeyLong::press:
					m_mouseLongPressData.emplace_back(key, delayAfterAction, delayInBetween);
					break;
				case event::KeyLong::release:
					m_mouseLongReleaseData.emplace_back(key, delayAfterAction, delayInBetween);
					break;
			}
		}
		//keyboard
		else {
			switch (type) {
				case event::KeyLong::press:
					m_longPressData.emplace_back(key, delayAfterAction, delayInBetween);
					break;
				case event::KeyLong::release:
					m_longReleaseData.emplace_back(key, delayAfterAction, delayInBetween);
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