#include "chunk.h"

#include "../../misc/random.h"
#include "../../app/arguments.h"

using namespace misc;

namespace game::world {
	void Chunk::generate() {
		static const int percItemsClouds = app::Arguments::percItems + app::Arguments::percClouds;
		const int nrEntities = Random::range(0, app::Arguments::entitiesPerChunk);
		
		for (int entity = 0; entity != nrEntities; ++entity) {
			float type = Random::range(0, percItemsClouds);
			if (type < app::Arguments::percItems)
				m_items.emplace_back(
					static_cast<ent::Item::Type>(Random::range(ent::Item::Type::max)),
					Random::range(static_cast<float>(m_x), m_x + 1.0f),
					Random::range(static_cast<float>(m_y), m_y + 1.0f));
			else if (type < percItemsClouds)
				m_clouds.emplace_back(
					Random::range(static_cast<float>(m_x), m_x + 1.0f),
					Random::range(static_cast<float>(m_y), m_y + 1.0f));
		}
	}

	bool Chunk::isAt(int x, int y) const {
		return m_x == x && m_y == y;
	}
	float Chunk::manhattanDistance(const ent::Entity* entity) const {
		// Manhattan distance (Taxicab geometry)
		return std::abs(m_x - entity->x()) + std::abs(m_y - entity->y());
	}

	Chunk::Chunk(int x, int y) :
		m_x{x}, m_y{y} {
		generate();
	}
}