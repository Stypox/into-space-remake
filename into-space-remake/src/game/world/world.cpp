#include "world.h"

#include <range.h>
#include <algorithm>
#include <math.h>

namespace game::world {	
	void World::removeFarEntities() {
		std::set<std::pair<int, int>> maybeEmptyChunks;

		for (auto item = m_entities.items.rbegin(); item != m_entities.items.rend(); ++item) {
			if (distance(m_entities.rocket.get(), item->get()) > m_minRemovalDistance) {
				maybeEmptyChunks.emplace(floor((*item)->x()), floor((*item)->y()));
				m_entities.items.erase(std::next(item).base());
			}
		}

		removeEmptyChunks(maybeEmptyChunks);
	}
	void World::removeEmptyChunks(std::set<std::pair<int, int>> maybeEmptyChunks) {
		for (auto chunk = m_chunks.rbegin(); chunk != m_chunks.rend(); ++chunk) {
			for (auto maybeEmptyChunk = maybeEmptyChunks.rbegin(); maybeEmptyChunk != maybeEmptyChunks.rend(); ++maybeEmptyChunk) {
				if (chunk->isAt(maybeEmptyChunk->first, maybeEmptyChunk->second)) {
					maybeEmptyChunks.erase(--maybeEmptyChunk.base());
					if (chunk->isEmpty(m_entities))
						m_chunks.erase(std::next(chunk).base());
				}
			}
		}
	}
	void World::genNearChunks() {
		for (int x : sp::range(-m_maxGenDistance, m_maxGenDistance + 1)) {
			for (int y : sp::range(-m_maxGenDistance, m_maxGenDistance + 1)) {
				if (std::find_if(m_chunks.begin(), m_chunks.end(), [x, y](const Chunk& chunk){ return chunk.isAt(x, y); }) == m_chunks.end()) {
					m_chunks.emplace_back(x, y);
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