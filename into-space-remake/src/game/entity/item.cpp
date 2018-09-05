#include "item.h"

namespace game::entity {
	Item::Item(Type type, float x, float y) :
		m_type{type}, m_x{x},
		m_y{y} {}

	std::array<float, nrVerticesItem * render::vertexSize> Item::vertices() const {
		float texturePos = 1.0f * static_cast<float>(m_type),
			  texturePosShifted = texturePos + 1.0f;
		return {
			m_x - 0.5f, m_y - 0.5f, texturePos,		   texturePos,
			m_x + 0.5f, m_y - 0.5f, texturePosShifted, texturePos,
			m_x + 0.5f, m_y + 0.5f, texturePosShifted, texturePosShifted,
			m_x - 0.5f, m_y + 0.5f, texturePos,		   texturePosShifted,
		};
	}
}