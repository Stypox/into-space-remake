#include "item.h"

namespace game::ent {
	Item::Item(Type type, float x, float y) :
		m_type{type}, m_x{x},
		m_y{y} {}

	GLfloat Item::x() const {
		return m_x;
	}
	GLfloat Item::y() const {
		return m_y;
	}
	GLfloat Item::textureIndex() const {
		return static_cast<GLfloat>(m_type);
	}
}