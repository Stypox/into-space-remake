#include "game.h"

namespace game {
	Game::Game() {}

	void Game::update() {
		m_entities.rocket->pickUpIntersecting(m_entities.items);
		// TODO update world
	}
	void Game::rend() {
		m_itemsRenderer.draw(m_entities.items);
		m_movablesRenderer.reserve(1 + m_entities.items.size());
		m_movablesRenderer.addMovable(m_entities.rocket);
		m_movablesRenderer.draw();
	}
}