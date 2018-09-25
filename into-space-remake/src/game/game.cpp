#include "game.h"

namespace game {
	Game::Game() :
		m_world{m_entities} {}

	bool Game::process(std::shared_ptr<app::event::Event> eventHandler) {
		return m_entities.rocket->process(eventHandler);
	}
	void Game::update() {
		float deltaTime = m_deltaClock.restart();

		m_entities.rocket->pickUpIntersecting(m_entities.items);
		m_world.update();

		m_entities.rocket->updatePosition(deltaTime);
	}
	void Game::render() {
		m_itemsRenderer.draw(m_entities.items);
		m_movablesRenderer.reserve(1 + m_entities.items.size());
		m_movablesRenderer.addMovable(m_entities.rocket);
		m_movablesRenderer.draw();
	}
}