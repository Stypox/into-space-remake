#include <glad/glad.h>
#include "world.h"

#include <algorithm>
#include <math.h>

namespace game::world {	
	void World::removeFarChunks() {
		for (auto chunk = m_chunks.rbegin(); chunk != m_chunks.rend(); ++chunk) {
			if (chunk->distance(&m_rocket) > m_minRemovalDistance)
				m_chunks.erase(std::next(chunk).base());
		}
	}
	void World::genNearChunks() {
		int rocketPosX = floor(m_rocket.x()),
			rocketPosY = floor(m_rocket.y());

		for (int x = rocketPosX - m_maxGenDistance; x <= rocketPosX + m_maxGenDistance; ++x) {
			for (int y = rocketPosY - m_maxGenDistance; y <= rocketPosY + m_maxGenDistance; ++y) {
				if (y < 0) // not generating chunks under ground level
					continue;
				if (std::find_if(m_chunks.begin(), m_chunks.end(), [x, y](const Chunk& chunk){
						return chunk.isAt(x, y);
					}) == m_chunks.end()) {
					m_chunks.push_back(Chunk{x, y});
				}
			}
		}
	}

	std::vector<Chunk*> World::positionsToChunks(const std::vector<std::pair<int, int>>& positions) {
		std::vector<Chunk*> chunks;
		chunks.reserve(positions.size());

		for (auto&& position : positions) {
			auto found = std::find_if(m_chunks.begin(), m_chunks.end(), [position](const Chunk& chunk){
				return chunk.isAt(position.first, position.second);
			});
			if (found != m_chunks.end())
				chunks.push_back(&*found);
		}

		return chunks;
	}

	bool World::process(std::shared_ptr<app::event::Event> event) {
		return m_rocket.process(event);
	}
	void World::update(float deltaTime, float timeNow) {
		removeFarChunks();
		genNearChunks();

		auto overlappingChunks = positionsToChunks(m_rocket.overlappingChunks());
		for (auto&& chunk : overlappingChunks) {
			m_rocket.pickUpIntersecting(chunk->m_items);
			m_rocket.runIntoIntersecting(chunk->m_clouds, timeNow);
		}
		m_rocket.updatePosition(deltaTime);
	}
}