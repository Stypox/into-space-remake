#ifndef _INTO_SPACE_REMAKE_GAME_GAME_H_
#define _INTO_SPACE_REMAKE_GAME_GAME_H_

#include "../rend/items.h"
#include "../rend/movables.h"
#include "entitiescontainer.h"
#include "world/world.h"
#include "../misc/clock.h"

namespace game {
	class Game {
		// when the framerate is lower than 60fps the game is updated more than once per frame
		static constexpr float maxDeltaTime = 1.0f/60.0f; // (s)

		EntitiesContainer m_entities;
		world::World m_world;

		misc::Chronometer<> m_deltaClock;
		bool m_paused;

		void update(float deltaTime);

	public:
		Game();

		bool process(std::shared_ptr<app::event::Event> eventHandler);
		void update();
		void render();

		void pause();
	};
}

#endif