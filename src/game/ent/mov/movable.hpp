#ifndef _INTO_SPACE_REMAKE_GAME_ENT_MOV_MOVABLE_HPP_
#define _INTO_SPACE_REMAKE_GAME_ENT_MOV_MOVABLE_HPP_

#include "../entity.hpp"

namespace game::ent::mov {
	class Movable : public Entity {
	public:
		virtual void updatePosition(float deltaTime) = 0;
	};
}

#endif