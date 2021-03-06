#ifndef _INTO_SPACE_REMAKE_GAME_WORLD_CHUNK_HPP_
#define _INTO_SPACE_REMAKE_GAME_WORLD_CHUNK_HPP_

#include "../ent/item.hpp"
#include "../ent/cloud.hpp"

namespace game::world {
	class Chunk {
		friend class World;

		static constexpr float size = 1.0f;

		int m_x, m_y;
		std::vector<ent::Item> m_items;
		std::vector<ent::Cloud> m_clouds;

		void generate();

	public:
		Chunk(int x, int y);

		bool isAt(int x, int y) const;
		// Manhattan distance (Taxicab geometry)
		float manhattanDistance(const ent::Entity* entity) const;
	};
}

#endif