#ifndef _INTO_SPACE_REMAKE_GAME_ENTITIESCONTAINER_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITIESCONTAINER_H_

#include <vector>
#include <memory>

#include "entity/item.h"
#include "entity/movable/rocket.h"

namespace game {
	struct EntitiesContainer {
		entity::movable::Rocket rocket;
		std::vector<std::unique_ptr<entity::Item>> items;
	};
}

#endif