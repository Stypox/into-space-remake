#include "../rend/items.h"
#include "../rend/rectangles.h"
#include "game.h"

#include <iostream>

#include "../rend/renderer.h"
#include "../app/event/key.h"
#include "../app/debug.h"

namespace game {
	void Game::update(float deltaTime, float timeNow) {
		m_entities.rocket->pickUpIntersecting(m_entities.items);
		m_entities.rocket->runIntoIntersecting(m_entities.clouds, timeNow);
		m_world.update();

		m_entities.rocket->updatePosition(deltaTime);
	}

	Game::Game() :
		m_entities{}, m_world{m_entities},
		m_deltaClock{}, m_paused{false} {}

	bool Game::process(std::shared_ptr<app::event::Event> event) {
		if (event->type == app::event::Event::key) {
			switch (app::event::Key* keyEvent = static_cast<app::event::Key*>(event.get()); keyEvent->key) {
			case GLFW_KEY_ESCAPE: {
				togglePause();
				return true;
			}
			}
		}
		return m_entities.rocket->process(event);
	}
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
	void Game::render() {
		rend::Renderer::moveCameraToRocket(m_entities.rocket);

		rend::Items::draw();
		rend::Rectangles::draw();
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