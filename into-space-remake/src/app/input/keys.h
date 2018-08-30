#ifndef _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_
#define _INTO_SPACE_REMAKE_APP_INPUT_KEYS_H_

#include <vector>

#include "../event/keyboard.h"
#include "../event/handler.h"
#include "GLFW/glfw3.h"

namespace app::input {
	constexpr bool pressed = true, notPressed = false;

	struct KeyData {
		int key;
		event::KeyboardEvent::Type type;
		bool lastState = notPressed;
		float lastPressed = 0.0f;
	};

	class Keys {
		std::vector<KeyData> m_keys;
		GLFWwindow* m_window;
		event::Handler& m_handler;

	public:
		Keys(event::Handler& handler);
		Keys(GLFWwindow* window, event::Handler& handler);

		inline void setWindow(GLFWwindow* window) { m_window = window; }
		inline void removeWindow() { m_window = nullptr; }

		void addListener(int key, event::KeyboardEvent::Type type);
		void update();
	};
}

#endif