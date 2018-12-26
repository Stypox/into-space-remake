#ifndef _INTO_SPACE_REMAKE_GAME_ENT_MOV_CLOUD_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_MOV_CLOUD_H_

#include "movable.h"

namespace game::ent::mov {
	class Cloud : public Movable {
		friend class Rocket;

		static constexpr float widthHeightRatio = 1.5f;

		float lastTimeRanInto;
	public:
		Cloud(float x, float y);

		void updatePosition(float deltaTime) override {};
	};
}

#endif