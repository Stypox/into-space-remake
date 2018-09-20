#ifndef _INTO_SPACE_REMAKE_GAME_WORLD_WORLD_H_
#define _INTO_SPACE_REMAKE_GAME_WORLD_WORLD_H_

#include <vector>
#include <set>

#include "chunk.h"
#include "../entitiescontainer.h"

namespace game::world {
	class World {
		static constexpr float m_minRemovalDistance = 20.0f;
		static constexpr int m_maxGenDistance = 5;

		EntitiesContainer& m_entities;
		std::vector<Chunk> m_chunks;

		void removeFarEntities();
		void removeEmptyChunks(std::set<std::pair<int, int>> maybeEmptyChunks);
		void genNearChunks();

	public:
		World(EntitiesContainer& entities);

		void update();
	};
}

#endif