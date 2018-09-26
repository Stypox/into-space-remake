#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_MOVABLE_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_MOVABLE_H_

#include <GLFW/glfw3.h>

#include "../entity.h"

namespace game::ent::mov {
	class Movable : public Entity {
	protected:
		GLfloat m_x, m_y;
	public:
		Movable(GLfloat x, GLfloat y);

		GLfloat x() const override;
		GLfloat y() const override;
		virtual GLfloat w() const = 0;
		virtual GLfloat h() const = 0;
		virtual GLfloat rotation() const = 0;
		virtual GLfloat textureOffset() const = 0;
		virtual GLfloat textureWidth() const = 0;

		virtual void updatePosition(float deltaTime) = 0;
	};
}

#endif