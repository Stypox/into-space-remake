#ifndef _INTO_SPACE_REMAKE_GAME_ENT_MOV_ROCKET_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_MOV_ROCKET_H_

#include <vector>
#include <memory>
#include <math.h>

#include "movable.h"
#include "../item.h"
#include "../cloud.h"
#include "../../../misc/acceleration.h"
#include "../../../app/event/event.h"

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

		bool process(std::shared_ptr<app::event::Event> event);
		void updatePosition(float deltaTime) override;

		void pickUpIntersecting(std::vector<std::unique_ptr<Item>>& items);
		void runIntoIntersecting(const std::vector<std::unique_ptr<Cloud>>& clouds, float timeNow);
	};
}

#endif