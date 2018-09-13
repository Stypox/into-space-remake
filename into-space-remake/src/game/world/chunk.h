#ifndef _INTO_SPACE_REMAKE_GAME_WORLD_CHUNK_H_
#define _INTO_SPACE_REMAKE_GAME_WORLD_CHUNK_H_

#include <vector>

#include "../entity/entity.h"

namespace game::world {
	class Chunk {
		static constexpr float size = 1.0f;

		int m_x, m_y;
	public:
		Chunk(int x, int y);

		std::vector<std::unique_ptr<entity::Entity>> generate();
		void remove(std::vector<std::unique_ptr<entity::Entity>> entities);
	};
}

#endif