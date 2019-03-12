#include "game.hpp"

#include <GLFW/glfw3.h>

#include "../app/event/key.hpp"
#include "../app/debug.hpp"
#include "../app/application.hpp"

namespace game {
	void Game::update(float deltaTime, float timeNow) {
		m_world.update(deltaTime, timeNow);
	}

	Game::Game() :
		m_world{}, m_deltaClock{},
		m_paused{false}, m_pauseFunctionHandler{
			app::Application::eventNotifier.connect_member(*this, &Game::togglePause,
				app::event::Key{app::event::Key::press, app::input::kb_escape})
		} {}

	void Game::update() {
		static float totalTime = 0.0f;

		float deltaTime = m_deltaClock.restart();
		if (!m_paused) {
			float timeConsumed = maxDeltaTime;
			for (; timeConsumed < deltaTime; timeConsumed += maxDeltaTime)
				update(maxDeltaTime, totalTime += maxDeltaTime);
			deltaTime = deltaTime - timeConsumed + maxDeltaTime;
			update(deltaTime, totalTime += deltaTime);
		}
	}

	void Game::pause() {
		m_paused = true;
		app::debug(app::Gravity::info, "Game", "Paused");
	}
	void Game::togglePause() {
		m_paused = !m_paused;
		app::debug(app::Gravity::info, "Game", m_paused ? "Paused" : "Unpaused");
	}
}