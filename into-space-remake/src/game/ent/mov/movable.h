#ifndef _INTO_SPACE_REMAKE_GAME_ENT_MOV_MOVABLE_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_MOV_MOVABLE_H_

#include <GLFW/glfw3.h>
#include <stypox/stock_container.h>

#include "../entity.h"

namespace game::ent::mov {
	class Movable : public Entity {
	public:
		virtual void updatePosition(float deltaTime) = 0;
	};
}

#endif