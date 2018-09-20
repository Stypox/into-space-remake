#ifndef _INTO_SPACE_REMAKE_GAME_WORLD_CHUNK_H_
#define _INTO_SPACE_REMAKE_GAME_WORLD_CHUNK_H_

#include "../entitiescontainer.h"

namespace game::world {
	class Chunk {
		static constexpr float size = 1.0f;

		int m_x, m_y;
	public:
		Chunk(int x, int y);

		void generate(EntitiesContainer& entities) const;

		bool isAt(int x, int y) const;
		bool isEmpty(EntitiesContainer& entities) const;
	};
}

#endif