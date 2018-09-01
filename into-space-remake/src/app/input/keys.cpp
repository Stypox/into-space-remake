#include "keys.h"

namespace app::input {
	using std::initializer_list;
	using std::pair;
	using std::tuple;
	using std::get;


	void Keys::updatePress() {
		// press type, no position tracking, keyboard key
		for (auto&& key : m_dataPress) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::Key{event::Key::press, key.key});
				key.lastState = keyState;
			}
		}

		// press type, no position tracking, mouse key
		for (auto&& key : m_dataPressM) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::Key{event::Key::press, key.key});
				key.lastState = keyState;
			}
		}

		// press type, position tracking, keyboard key
		for (auto&& key : m_dataPressP) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::KeyPos{event::Key::press, key.key, m_xCursor, m_yCursor});
				key.lastState = keyState;
			}
		}

		// press type, position tracking, mouse key
		for (auto&& key : m_dataPressPM) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (keyState)
					m_eventHandler.push(new event::KeyPos{event::Key::press, key.key, m_xCursor, m_yCursor});
				key.lastState = keyState;
			}
		}
	}
	void Keys::updateDoublePress() {
		// doublePress type, no position tracking, keyboard key
		for (auto&& key : m_dataDoublePress) {
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

		// doublePress type, no position tracking, mouse key
		for (auto&& key : m_dataDoublePressM) {
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

		// doublePress type, position tracking, keyboard key
		for (auto&& key : m_dataDoublePressP) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (keyState) {
					if (key.lastPressed + m_doublePressDelay > m_time) {
						m_eventHandler.push(new event::KeyPos{event::Key::doublePress, key.key, m_xCursor, m_yCursor});
						key.lastPressed = -3 * m_doublePressDelay;
					}
					else
						key.lastPressed = m_time;
				}
				key.lastState = keyState;
			}
		}

		// doublePress type, position tracking, mouse key
		for (auto&& key : m_dataDoublePressPM) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (keyState) {
					if (key.lastPressed + m_doublePressDelay > m_time) {
						m_eventHandler.push(new event::KeyPos{event::Key::doublePress, key.key, m_xCursor, m_yCursor});
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
		// release type, no position tracking, keyboard key
		for (auto&& key : m_dataRelease) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::Key{event::Key::release, key.key});
				key.lastState = keyState;
			}
		}

		// release type, no position tracking, mouse key
		for (auto&& key : m_dataReleaseM) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::Key{event::Key::release, key.key});
				key.lastState = keyState;
			}
		}

		// release type, position tracking, keyboard key
		for (auto&& key : m_dataReleaseP) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::KeyPos{event::Key::release, key.key, m_xCursor, m_yCursor});
				key.lastState = keyState;
			}
		}

		// release type, position tracking, mouse key
		for (auto&& key : m_dataReleasePM) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				if (!keyState)
					m_eventHandler.push(new event::KeyPos{event::Key::release, key.key, m_xCursor, m_yCursor});
				key.lastState = keyState;
			}
		}
	}
	void Keys::updateLongPress() {
		// longPress type, no position tracking, keyboard key
		for (auto&& key : m_dataLongPress) {
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

		// longPress type, no position tracking, mouse key
		for (auto&& key : m_dataLongPressM) {
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

		// longPress type, position tracking, keyboard key
		for (auto&& key : m_dataLongPressP) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (keyState)
					key.lastAction = m_time;
			}
			if (key.lastState && key.lastAction + key.delayAfterAction < m_time) {
				m_eventHandler.push(new event::KeyPosLong{event::KeyLong::press, key.key, m_xCursor, m_yCursor, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}

		// longPress type, position tracking, mouse key
		for (auto&& key : m_dataLongPressPM) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (keyState)
					key.lastAction = m_time;
			}
			if (key.lastState && key.lastAction + key.delayAfterAction < m_time) {
				m_eventHandler.push(new event::KeyPosLong{event::KeyLong::press, key.key, m_xCursor, m_yCursor, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}
	}
	void Keys::updateLongRelease() {
		// longRelease type, no position tracking, keyboard key
		for (auto&& key : m_dataLongRelease) {
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

		// longRelease type, no position tracking, mouse key
		for (auto&& key : m_dataLongReleaseM) {
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

		// longRelease type, position tracking, keyboard key
		for (auto&& key : m_dataLongReleaseP) {
			if (bool keyState = glfwGetKey(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (!keyState)
					key.lastAction = m_time;
			}
			if (!key.lastState && key.lastAction + key.delayAfterAction < m_time) {
				m_eventHandler.push(new event::KeyPosLong{event::KeyLong::release, key.key, m_xCursor, m_yCursor, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}

		// longRelease type, position tracking, mouse key
		for (auto&& key : m_dataLongReleasePM) {
			if (bool keyState = glfwGetMouseButton(m_window, key.key); keyState != key.lastState) {
				key.lastState = keyState;
				if (!keyState)
					key.lastAction = m_time;
			}
			if (!key.lastState && key.lastAction + key.delayAfterAction < m_time) {
				m_eventHandler.push(new event::KeyPosLong{event::KeyLong::release, key.key, m_xCursor, m_yCursor, key.delayAfterAction, key.delayInBetween});
				key.lastAction += key.delayInBetween;
			}
		}
	}


	Keys::Keys(GLFWwindow*& window, event::Handler& eventHandler, float doublePressDelay) :
		m_window{window}, m_eventHandler{eventHandler},
		m_doublePressDelay{doublePressDelay} {}
	Keys::Keys(GLFWwindow*& window, event::Handler& eventHandler, float doublePressDelay,
		initializer_list<tuple<event::Key::Type, int, bool>> listeners,
		initializer_list<tuple<event::KeyLong::Type, int, bool, float, float>> longListeners) :
		m_window{window}, m_eventHandler{eventHandler},
		m_doublePressDelay{doublePressDelay} {
		for (auto&& listener : listeners)
			addListener(get<0>(listener), get<1>(listener), get<2>(listener));
		for (auto&& listener : longListeners)
			addListener(get<0>(listener), get<1>(listener), get<2>(listener), get<3>(listener), get<4>(listener));
	}

	void Keys::addListener(event::Key::Type type, int key, bool trackPosition) {
		bool isMouseKey = (key >= 0 && key <= GLFW_MOUSE_BUTTON_LAST);
		int eventTypeId = (static_cast<int>(type) << 2) | (trackPosition << 1) | isMouseKey;
		// bits are laid down this way ...0000ABCD where AB are the first two "type" bits, C is "trackPosition" and D is "isMouseKey"

		switch (eventTypeId) {
			case 0:		// press type, no position tracking, keyboard key
				m_dataPress.emplace_back(key);
				break;
			case 1:		// press type, no position tracking, mouse key
				m_dataPressM.emplace_back(key);
				break;
			case 2:		// press type, position tracking, keyboard key
				m_dataPressP.emplace_back(key);
				break;
			case 3:		// press type, position tracking, mouse key
				m_dataPressPM.emplace_back(key);
				break;
			case 4:		// doublePress type, no position tracking, keyboard key
				m_dataDoublePress.emplace_back(key, m_doublePressDelay);
				break;
			case 5:		// doublePress type, no position tracking, mouse key
				m_dataDoublePressM.emplace_back(key, m_doublePressDelay);
				break;
			case 6:		// doublePress type, position tracking, keyboard key
				m_dataDoublePressP.emplace_back(key, m_doublePressDelay);
				break;
			case 7:		// doublePress type, position tracking, mouse key
				m_dataDoublePressPM.emplace_back(key, m_doublePressDelay);
				break;
			case 8:		// release type, no position tracking, keyboard key
				m_dataRelease.emplace_back(key);
				break;
			case 9:		// release type, no position tracking, mouse key
				m_dataReleaseM.emplace_back(key);
				break;
			case 10:	// release type, position tracking, keyboard key
				m_dataReleaseP.emplace_back(key);
				break;
			case 11:	// release type, position tracking, mouse key
				m_dataReleasePM.emplace_back(key);
				break;
		}
	}
	void Keys::addListener(event::KeyLong::Type type, int key, bool trackPosition, float delayAfterAction, float delayInBetween) {
		bool isMouseKey = (key >= 0 && key <= GLFW_MOUSE_BUTTON_LAST);
		int eventTypeId = (static_cast<int>(type) << 2) | (trackPosition << 1) | isMouseKey;
		// bits are laid down this way: ...0000ABC where A is the first "type" bit, B is "trackPosition" and D is "isMouseKey"

		switch (eventTypeId) {
			case 0:		// longPress type, no position tracking, keyboard key
				m_dataLongPress.emplace_back(key, delayAfterAction, delayInBetween);
				break;
			case 1:		// longPress type, no position tracking, mouse key
				m_dataLongPressM.emplace_back(key, delayAfterAction, delayInBetween);
				break;
			case 2:		// longPress type, position tracking, keyboard key
				m_dataLongPressP.emplace_back(key, delayAfterAction, delayInBetween);
				break;
			case 3:		// longPress type, position tracking, mouse key
				m_dataLongPressPM.emplace_back(key, delayAfterAction, delayInBetween);
				break;
			case 4:		// longRelease type, no position tracking, keyboard key
				m_dataLongRelease.emplace_back(key, delayAfterAction, delayInBetween);
				break;
			case 5:		// longRelease type, no position tracking, mouse key
				m_dataLongReleaseM.emplace_back(key, delayAfterAction, delayInBetween);
				break;
			case 6:		// longRelease type, position tracking, keyboard key
				m_dataLongReleaseP.emplace_back(key, delayAfterAction, delayInBetween);
				break;
			case 7:		// longRelease type, position tracking, mouse key
				m_dataLongReleasePM.emplace_back(key, delayAfterAction, delayInBetween);
				break;
		}
	}

	void Keys::update() {
		m_time = static_cast<float>(glfwGetTime());
		glfwGetCursorPos(m_window, &m_xCursor, &m_yCursor);
		updatePress();
		updateDoublePress();
		updateRelease();
		updateLongPress();
		updateLongRelease();
	}
}