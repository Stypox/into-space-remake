#include "movable.h"

namespace game::entity::movable {
	GLfloat Movable::x() const {
		return m_x;
	}
	GLfloat Movable::y() const {
		return m_y;
	}
}