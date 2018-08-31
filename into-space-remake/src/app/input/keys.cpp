#include "keys.h"

namespace app::input {
	using std::initializer_list;
	using std::pair;
	using std::tuple;
	using std::get;

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
	void Keys::addListener(event::KeyLong::Type type, int key, float delayAfterAction, float delayInBetween) {
		switch (type) {
			case event::KeyLong::press:
				m_keysLongPressListener.emplace_back(key, delayAfterAction, delayInBetween);
				break;
			case event::KeyLong::release:
				m_keysLongReleaseListener.emplace_back(key, delayAfterAction, delayInBetween);
				break;
		}
	}

	void Keys::update() {
		for (auto&& key : m_keysPressListener) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::Key{event::Key::press, key.key});
				key.lastState = keyState;
			}
		}
		for (auto&& key : m_keysDoublePressListener) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState) {
					if (float time = static_cast<float>(glfwGetTime()); key.lastPressed + m_doublePressDelay > time) {
						m_eventHandler.push(new event::Key{event::Key::doublePress, key.key});
						key.lastPressed = -3 * m_doublePressDelay;
					}
					else {
						key.lastPressed = time;
					}
				}
				key.lastState = keyState;
			}
		}
		for (auto&& key : m_keysReleaseListener) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::Key{event::Key::release, key.key});
				key.lastState = keyState;
			}
		}
		for (auto&& key : m_keysLongPressListener) {
			float time = static_cast<float>(glfwGetTime());
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (keyState)
					key.lastAction = glfwGetTime();
			}
			if (key.lastState && key.lastAction + key.delayAfterAction < time) {
				m_eventHandler.push(new event::KeyLong{event::KeyLong::press, key.key, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}
		for (auto&& key : m_keysLongReleaseListener) {
			float time = static_cast<float>(glfwGetTime());
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (!keyState)
					key.lastAction = glfwGetTime();
			}
			if (!key.lastState && key.lastAction + key.delayAfterAction < time) {
				m_eventHandler.push(new event::KeyLong{event::KeyLong::release, key.key, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}
	}
}