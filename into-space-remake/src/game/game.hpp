#ifndef _INTO_SPACE_REMAKE_GAME_GAME_HPP_
#define _INTO_SPACE_REMAKE_GAME_GAME_HPP_

#include <stypox/event_notifier.hpp>

#include "world/world.hpp"
#include "stypox/clock.hpp"

namespace game {
	class Game {
		// when the framerate is lower than 60fps the game is updated more than once per frame
		static constexpr float maxDeltaTime = 1.0f/60.0f; // (s)

		world::World m_world;

		stypox::Chronometer<> m_deltaClock;
		bool m_paused;

		stypox::EventNotifier::Handler m_pauseFunctionHandler;

		void update(float deltaTime, float timeNow);

	public:
		Game();

		float rocketX() const { return m_world.rocketX(); }
		float rocketY() const { return m_world.rocketY(); }

		void update();

		void pause();
		void togglePause();
	};
}

#endif