#include "chunk.h"

#include "../../misc/random.h"
#include "../entity/item.h"
#include "../../app/arguments.h"

using namespace misc;

namespace game::world {
	Chunk::Chunk(int x, int y) :
		m_x{x}, m_y{y} {}
	
	void Chunk::generate(EntitiesContainer& entities) {
		const int nrEntities = Random::range(0, app::Arguments::entitiesPerChunk);
		
		for (int item = 0; item != nrEntities; ++item) {
			int type = Random::range(1, app::Arguments::percItems + 1);
			if (type < app::Arguments::percItems)
				entities.items.emplace_back(new entity::Item{
					static_cast<entity::Item::Type>(Random::range(entity::Item::Type::max)),
					Random::range(static_cast<float>(m_x), m_x + 1.0f),
					Random::range(static_cast<float>(m_y), m_y + 1.0f)});			
		}
	}
	void Chunk::remove(EntitiesContainer& entities) {
		for (auto item = entities.items.end(); item != entities.items.begin(); ++item) {
			if ((*item)->x() >= m_x && (*item)->x() < m_x + 1.0f && (*item)->y() >= m_y && (*item)->y() < m_y + 1.0f) {
				entities.items.erase(item, item + 1);
			}
		}
	}
}