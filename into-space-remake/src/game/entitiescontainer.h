#ifndef _INTO_SPACE_REMAKE_GAME_ENTITIESCONTAINER_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITIESCONTAINER_H_

#include <vector>
#include <memory>

#include "ent/item.h"
#include "ent/mov/rocket.h"
#include "ent/cloud.h"

namespace game {
	struct EntitiesContainer {
		std::unique_ptr<ent::mov::Rocket> rocket;
		std::vector<std::unique_ptr<ent::Item>> items;
		std::vector<std::unique_ptr<ent::Cloud>> clouds;

		inline EntitiesContainer() :
			rocket{std::make_unique<ent::mov::Rocket>()} {}
	};
}

#endif