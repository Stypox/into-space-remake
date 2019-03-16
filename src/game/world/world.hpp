#ifndef _INTO_SPACE_REMAKE_GAME_WORLD_WORLD_HPP_
#define _INTO_SPACE_REMAKE_GAME_WORLD_WORLD_HPP_

#include <vector>

#include "chunk.hpp"
#include "../ent/mov/rocket.hpp"

namespace game::world {
	class World {
		static constexpr float m_minRemovalDistance = 20.0f;
		static constexpr int m_maxGenDistance = 5;

		ent::mov::Rocket m_rocket;
		std::vector<Chunk> m_chunks;

		void removeFarChunks();
		void genNearChunks();

		std::vector<Chunk*> positionsToChunks(const std::vector<std::pair<int, int>>& positions);

	public:
		float rocketX() const { return m_rocket.x(); }
		float rocketY() const { return m_rocket.y(); }

		void update(float deltaTime, float timeNow);
	};
}

#endif