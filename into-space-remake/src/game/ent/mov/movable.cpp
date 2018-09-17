#include "movable.h"

namespace game::ent::mov {
	Movable::Movable(GLfloat x, GLfloat y) :
		m_x{x}, m_y{y} {}
	
	GLfloat Movable::x() const {
		return m_x;
	}
	GLfloat Movable::y() const {
		return m_y;
	}
}