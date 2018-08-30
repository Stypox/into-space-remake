#ifndef _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_

#include <vector>

#include "../event/key.h"
#include "../event/handler.h"
#include "GLFW/glfw3.h"

namespace app::input {
	constexpr bool pressed = true, notPressed = false;

	struct KeyData {
		int key;
		event::Key::Type type;
		bool lastState = notPressed;
		float lastPressed;

		constexpr KeyData(int key, event::Key::Type type, float doubleClickTime) :
			key{key}, type{type},
			lastPressed{-3 * doubleClickTime} {}
	};

	class Keys {
		int m_doublePressDelay;

		std::vector<KeyData> m_keys;
		GLFWwindow* m_window;
		event::Handler& m_handler;

	public:
		Keys(event::Handler& handler, int doublePressDelay);
		Keys(GLFWwindow* window, event::Handler& handler, int doublePressDelay);

		inline void setWindow(GLFWwindow* window) { m_window = window; }
		inline void removeWindow() { m_window = nullptr; }

		void addListener(int key, event::Key::Type type);

		void update();

		inline bool isPressed(int key) { return glfwGetKey(m_window, key); }
	};
}

#endif