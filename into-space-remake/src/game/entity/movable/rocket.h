#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_ROCKET_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_ROCKET_H_

#include <GLFW/glfw3.h>

#include "movable.h"

namespace game::entity::movable {
	class Rocket : public Movable {
	public:
		Rocket();

		GLfloat sizeX() const override { return 0.1f; }
		GLfloat sizeY() const override { return 0.2f; }
		GLfloat textureOffset() const override { return 0.0f; }
		GLfloat textureWidth() const override { return 1.0f; }
	};
}

#endif