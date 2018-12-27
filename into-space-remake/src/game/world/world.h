#ifndef _INTO_SPACE_REMAKE_GAME_WORLD_WORLD_H_
#define _INTO_SPACE_REMAKE_GAME_WORLD_WORLD_H_

#include <vector>

#include "chunk.h"
#include "../ent/mov/rocket.h"

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

		bool process(std::shared_ptr<app::event::Event> event);
		void update(float deltaTime, float timeNow);
	};
}

#endif