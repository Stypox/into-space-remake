#include <glad/glad.h>
#include "chunk.h"

#include "../../misc/random.h"
#include "../../app/arguments.h"

using namespace misc;

namespace game::world {
	Chunk::Chunk(int x, int y) :
		m_x{x}, m_y{y} {}
	
	void Chunk::generate(EntitiesContainer& entities) const {
		static const int percItemsClouds = app::Arguments::percItems + app::Arguments::percClouds;
		const int nrEntities = Random::range(0, app::Arguments::entitiesPerChunk);
		
		for (int entity = 0; entity != nrEntities; ++entity) {
			float type = Random::range(0, percItemsClouds);
			if (type < app::Arguments::percItems)
				entities.items.emplace_back(new ent::Item{
					static_cast<ent::Item::Type>(Random::range(ent::Item::Type::max)),
					Random::range(static_cast<float>(m_x), m_x + 1.0f),
					Random::range(static_cast<float>(m_y), m_y + 1.0f)});
			else if (type < percItemsClouds)
				entities.clouds.emplace_back(new ent::Cloud{
					Random::range(static_cast<float>(m_x), m_x + 1.0f),
					Random::range(static_cast<float>(m_y), m_y + 1.0f)});
		}
	}

	bool Chunk::isAt(int x, int y) const {
		return m_x == x && m_y == y;
	}
	bool Chunk::isEmpty(EntitiesContainer& entities) const {
		for (auto item = entities.items.rbegin(); item != entities.items.rend(); ++item) {
			if ((*item)->x() >= m_x && (*item)->x() < m_x + 1.0f && (*item)->y() >= m_y && (*item)->y() < m_y + 1.0f)
				return false;
		}
		return true;
	}
}