#include "chunk.h"

#include "../../misc/random.h"
#include "../../app/arguments.h"

using namespace misc;

namespace game::world {
	Chunk::Chunk(int x, int y) :
		m_x{x}, m_y{y} {}
	
	void Chunk::generate(EntitiesContainer& entities) const {
		const int nrEntities = Random::range(0, app::Arguments::entitiesPerChunk);
		
		for (int item = 0; item != nrEntities; ++item) {
			int type = Random::range(1, app::Arguments::percItems + 1);
			if (type < app::Arguments::percItems)
				entities.items.emplace_back(new ent::Item{
					static_cast<ent::Item::Type>(Random::range(ent::Item::Type::max)),
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