#ifndef _INTO_SPACE_REMAKE_GAME_GAME_H_
#define _INTO_SPACE_REMAKE_GAME_GAME_H_

#include "../render/items.h"
#include "../render/movables.h"
#include "entitiescontainer.h"

namespace game {
	class Game {
		EntitiesContainer m_entities;
		render::Items m_itemsRenderer;
		render::Movables m_movablesRenderer;
	public:
		Game();

		void update();
		void render();
	};
}

#endif