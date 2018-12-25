#ifndef _INTO_SPACE_REMAKE_GAME_ENT_MOV_CLOUD_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_MOV_CLOUD_H_

#include <glad/glad.h>

#include "movable.h"

namespace game::ent::mov {
	class Cloud : public Movable {
		static constexpr GLfloat widthHeightRatio = 1.5f;
	public:
		Cloud(GLfloat x, GLfloat y);

		void updatePosition(float deltaTime) override {};
	};
}

#endif