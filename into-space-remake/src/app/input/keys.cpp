#include "keys.h"

namespace app::input {
	KeysInput::KeysInput(event::EventHandler& handler) :
		m_window{nullptr}, m_handler{handler} {}
	KeysInput::KeysInput(GLFWwindow* window, event::EventHandler& handler) :
		m_window{window}, m_handler{handler} {}

	void KeysInput::addListener(int key, event::KeyboardEvent::Type type) {
		m_keys.emplace_back(key, type);
	}
	void KeysInput::update() {
		for (auto&& key : m_keys) {
			
		}
	}
}