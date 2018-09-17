#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_MOVABLE_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_MOVABLE_H_

#include <GLFW/glfw3.h>

#include "../entity.h"

namespace game::ent::mov {
	class Movable : public Entity {
		GLfloat m_x, m_y;
	public:
		Movable(GLfloat x, GLfloat y);

		GLfloat x() const override;
		GLfloat y() const override;
		virtual GLfloat sizeX() const = 0;
		virtual GLfloat sizeY() const = 0;
		virtual GLfloat textureOffset() const = 0;
		virtual GLfloat textureWidth() const = 0;
	};
}

#endif