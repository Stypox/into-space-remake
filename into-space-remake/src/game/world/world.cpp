#include "world.h"

#include <algorithm>
#include <math.h>

namespace game::world {	
	void World::removeFarEntities() {
		std::map<int, int> maybeEmptyChunks;

		for (auto item = m_entities.items.rbegin(); item != m_entities.items.rend(); ++item) {
			if (distance(m_entities.rocket.get(), item->get()) > m_minRemovalDistance) {
				maybeEmptyChunks.insert({floor((*item)->x()), floor((*item)->y())});
				m_entities.items.erase(std::next(item).base());
			}
		}

		removeEmptyChunks(maybeEmptyChunks);
	}
	void World::removeEmptyChunks(std::map<int, int>& maybeEmptyChunks) {
		for (auto chunk = m_chunks.rbegin(); chunk != m_chunks.rend(); ++chunk) {
			for (auto maybeEmptyChunk = maybeEmptyChunks.begin(); maybeEmptyChunk != maybeEmptyChunks.end(); ++maybeEmptyChunk) {
				if (chunk->isAt(maybeEmptyChunk->first, maybeEmptyChunk->second)) {
					maybeEmptyChunks.erase(maybeEmptyChunk);
					if (chunk->isEmpty(m_entities))
						m_chunks.erase(std::next(chunk).base());
					break;
				}
			}
		}
	}
	void World::genNearChunks() {
		for (int x = -m_maxGenDistance; x <= m_maxGenDistance; ++x) {
			for (int y = abs(x) - m_maxGenDistance; y <= -abs(x) + m_maxGenDistance; ++y) {
				int posX = x + floor(m_entities.rocket->x()),
					posY = y + floor(m_entities.rocket->y());
				if (posY < 0) // not generating chunks under ground level
					continue;
				if (std::find_if(m_chunks.begin(), m_chunks.end(), [posX, posY](const Chunk& chunk){
						return chunk.isAt(posX, posY);
					}) == m_chunks.end()) {
					m_chunks.emplace_back(posX, posY);
					m_chunks.back().generate(m_entities);
				}
			}
		}
	}

	World::World(EntitiesContainer& entities) :
		m_entities{entities} {}

	void World::update() {
		removeFarEntities();
		genNearChunks();
	}
}