#ifndef _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_

#include <vector>
#include <utility>

#include "../event/key.h"
#include "../event/handler.h"
#include "GLFW/glfw3.h"

namespace app::input {
	constexpr bool pressed = true, notPressed = false;

	class Keys {
		struct KeyData {
			int key;
			event::Key::Type type;
			bool lastState = notPressed;
			float lastPressed;

			constexpr KeyData(int key, event::Key::Type type, float doubleClickTime) :
				key{key}, type{type},
				lastPressed{-3 * doubleClickTime} {}
		};

		float m_doublePressDelay;

		std::vector<KeyData> m_keys;
		GLFWwindow* m_window;
		event::Handler& m_eventHandler;

	public:
		Keys(GLFWwindow* window, event::Handler& eventHandler, float doublePressDelay);
		Keys(GLFWwindow* window, event::Handler& eventHandler, float doublePressDelay, std::initializer_list<std::pair<event::Key::Type, int>> listeners);

		inline void setWindow(GLFWwindow* window) { m_window = window; }
		inline void setDoublePressDelay(float doublePressDelay) { m_doublePressDelay = doublePressDelay; }

		inline void addListener(event::Key::Type type, int key) { m_keys.emplace_back(key, type, m_doublePressDelay); }

		void update();

		inline bool isPressed(int key) { return glfwGetKey(m_window, key); }
	};
}

#endif