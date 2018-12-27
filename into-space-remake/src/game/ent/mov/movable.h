#ifndef _INTO_SPACE_REMAKE_GAME_ENT_MOV_MOVABLE_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_MOV_MOVABLE_H_

#include "../entity.h"

namespace game::ent::mov {
	class Movable : public Entity {
	public:
		virtual void updatePosition(float deltaTime) = 0;
	};
}

#endif