#include "movable.h"

namespace game::entity::movable {
	Movable::Movable(GLfloat x, GLfloat y) :
		m_x{x}, m_y{y} {}
	
	GLfloat Movable::x() const {
		return m_x;
	}
	GLfloat Movable::y() const {
		return m_y;
	}
}