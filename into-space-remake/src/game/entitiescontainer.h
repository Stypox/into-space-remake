#ifndef _INTO_SPACE_REMAKE_GAME_ENTITIESCONTAINER_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITIESCONTAINER_H_

#include <vector>
#include <memory>

#include "entity/item.h"
#include "entity/movable/rocket.h"

namespace game {
	struct EntitiesContainer {
		std::unique_ptr<entity::movable::Rocket> rocket;
		std::vector<std::unique_ptr<entity::Item>> items;

		inline EntitiesContainer() :
			rocket{std::make_unique<entity::movable::Rocket>()} {}
	};
}

#endif