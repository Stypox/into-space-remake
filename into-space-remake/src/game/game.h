#ifndef _INTO_SPACE_REMAKE_GAME_GAME_H_
#define _INTO_SPACE_REMAKE_GAME_GAME_H_

#include "../rend/items.h"
#include "../rend/movables.h"
#include "entitiescontainer.h"

namespace game {
	class Game {
		EntitiesContainer m_entities;
		rend::Items m_itemsRenderer;
		rend::Movables m_movablesRenderer;
	public:
		Game();

		void update();
		void render();
	};
}

#endif