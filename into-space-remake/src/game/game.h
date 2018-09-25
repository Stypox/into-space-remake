#ifndef _INTO_SPACE_REMAKE_GAME_GAME_H_
#define _INTO_SPACE_REMAKE_GAME_GAME_H_

#include "../rend/items.h"
#include "../rend/movables.h"
#include "entitiescontainer.h"
#include "world/world.h"

namespace game {
	class Game {
		EntitiesContainer m_entities;
		world::World m_world;
		rend::Items m_itemsRenderer;
		rend::Movables m_movablesRenderer;
	public:
		Game();

		bool process(std::shared_ptr<app::event::Event> eventHandler);
		void update();
		void render();
	};
}

#endif