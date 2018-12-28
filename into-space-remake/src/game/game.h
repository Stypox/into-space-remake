#ifndef _INTO_SPACE_REMAKE_GAME_GAME_H_
#define _INTO_SPACE_REMAKE_GAME_GAME_H_

#include "world/world.h"
#include "../misc/clock.h"

namespace game {
	class Game {
		// when the framerate is lower than 60fps the game is updated more than once per frame
		static constexpr float maxDeltaTime = 1.0f/60.0f; // (s)

		world::World m_world;

		misc::Chronometer<> m_deltaClock;
		bool m_paused;

		void update(float deltaTime, float timeNow);

	public:
		Game();

		float rocketX() const { return m_world.rocketX(); }
		float rocketY() const { return m_world.rocketY(); }

		bool process(const std::shared_ptr<app::event::Event>& event);
		void update();

		void pause();
		void togglePause();
	};
}

#endif