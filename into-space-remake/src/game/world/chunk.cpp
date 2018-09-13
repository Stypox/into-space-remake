#include "chunk.h"

#include <memory>

#include "../../misc/random.h"
#include "../entity/item.h"
#include "../../app/arguments.h"

using namespace misc;

namespace game::world {
	Chunk::Chunk(int x, int y) :
		m_x{x}, m_y{y} {}
	
	std::vector<std::unique_ptr<entity::Entity>> Chunk::generate() {
		std::vector<std::unique_ptr<entity::Entity>> entities;

		const int nrEntities = Random::range(1, app::Arguments::entitiesPerChunk + 1);
		entities.reserve(nrEntities);
		
		for (int item = 0; item != nrEntities; ++item) {
			int type = Random::range(1, app::Arguments::percItems + 1);
			if (type < app::Arguments::percItems)
				entities.emplace_back(new entity::Item{
					static_cast<entity::Item::Type>(Random::range(entity::Item::Type::max)),
					Random::range(static_cast<float>(m_x), m_x + 1.0f),
					Random::range(static_cast<float>(m_y), m_y + 1.0f)});			
		}

		return entities;
	}
	void Chunk::remove(std::vector<std::unique_ptr<entity::Entity>> entities) {
		for (auto entity = entities.end(); entity != entities.begin(); ++entity) {
			if ((*entity)->x() >= m_x && (*entity)->x() < m_x + 1.0f && (*entity)->y() >= m_y && (*entity)->y() < m_y + 1.0f) {
				entities.erase(entity, entity + 1);
			}
		}
	}
}