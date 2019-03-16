#ifndef _INTO_SPACE_REMAKE_GAME_ENT_MOV_ROCKET_HPP_
#define _INTO_SPACE_REMAKE_GAME_ENT_MOV_ROCKET_HPP_

#include <vector>
#include <memory>
#include <math.h>
#include <stypox/event_notifier.hpp>

#include "movable.hpp"
#include "../item.hpp"
#include "../cloud.hpp"
#include "../../../misc/acceleration.hpp"

namespace game::ent::mov {
	class Rocket : public Movable, public rend::RectangleRender {
		// constants 
		static constexpr float g = 9.8f,							// gravity (m/s^2)
							   width = 0.2f,						// (hm)
							   height = 0.4f,						// (hm)
							   maxSpeedUp = 1.0f,					// (m/s)
							   maxSpeedDown = 8.0f,					// (m/s)
							   maxHorizontalSpeed = 1.0f,			// (m/s)
							   defaultRotationVelocity = M_PI / 12,	// (rad/s)
							   groundLevel = 0.0f;					// (hm)

		float m_vx, m_vy;
		misc::Acceleration m_engine, m_gravity;
		float m_rotationVelocity;

		float m_fuel;
		int m_collectedMoney;
		float m_integrity;

		std::array<stypox::EventNotifier::Handler, 4> m_keyboardFunctionHandlers;
		
		void pickUp(const Item& item);
		void updateRotation(float deltaTime);
		void damage(float velocity);

	public:
		Rocket();

		GLfloat x() const override { return m_renderData->x; }
		GLfloat y() const override { return m_renderData->y; }
		GLfloat w() const override { return m_renderData->w; }
		GLfloat h() const override { return m_renderData->h; }
		GLfloat rotation() const override { return m_renderData->rotation; };

		void updatePosition(float deltaTime) override;

		std::vector<std::pair<int, int>> chunksToCheck() const;

		void pickUpIntersecting(std::vector<Item>& items);
		void runIntoIntersecting(std::vector<Cloud>& clouds, float timeNow);
	};
}

#endif