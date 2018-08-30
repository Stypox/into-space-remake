#include "keys.h"

namespace app::input {
	Keys::Keys(event::Handler& handler) :
		m_window{nullptr}, m_handler{handler} {}
	Keys::Keys(GLFWwindow* window, event::Handler& handler) :
		m_window{window}, m_handler{handler} {}

	void Keys::addListener(int key, event::KeyboardEvent::Type type) {
		m_keys.emplace_back(key, type);
	}
	void Keys::update() {
		for (auto&& key : m_keys) {

		}
	}
}