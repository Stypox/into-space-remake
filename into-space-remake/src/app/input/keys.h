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

	class KeysInput {
		std::vector<KeyData> m_keys;
		GLFWwindow* m_window;
		event::EventHandler& m_handler;

	public:
		KeysInput(event::EventHandler& handler);
		KeysInput(GLFWwindow* window, event::EventHandler& handler);

		inline void setWindow(GLFWwindow* window) { m_window = window; }
		inline void removeWindow() { m_window = nullptr; }

		void addListener(int key, event::KeyboardEvent::Type type);
		void update();
	};
}

#endif