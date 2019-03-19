#include "rocket.hpp"

#include <GLFW/glfw3.h>
#include <math.h>
#include <imgui.h>
#include <stypox/key_event.hpp>

#include "../../../app/application.hpp"

namespace game::ent::mov {

	void Rocket::pickUp(const Item& item) {
		switch (item.type()) {
		case Item::fuel0:
			m_fuel += 1.0f;
			break;
		case Item::fuel1:
			m_fuel += 3.0f;
			break;
		case Item::fuel2:
			m_fuel += 10.0f;
			break;
		case Item::money0:
			m_collectedMoney += 5;
			break;
		case Item::money1:
			m_collectedMoney += 20;
			break;
		case Item::money2:
			m_collectedMoney += 100;
			break;
		case Item::repair:
			m_integrity += 1.0f;
			break;
		}
	}
	void Rocket::updateRotation(float deltaTime) {
		if (m_gravity.active()) {
			m_renderData->rotation += m_rotationVelocity * deltaTime;
		}
		else {
			//normalize rotation
			m_renderData->rotation -= std::floor(m_renderData->rotation / (2.0f * M_PI)) * 2.0f * M_PI;

			// the inclination at which the Rocket laying direction changes
			// (when the Rocket is / it falls right; \ -> left)
			constexpr float barycenterOnYAxis = 0.463647609f; // = std::atan(width / height)
			if	   ((m_renderData->rotation > 0.0f								&& m_renderData->rotation <					barycenterOnYAxis	) ||
					(m_renderData->rotation > 0.5f * M_PI						&& m_renderData->rotation < M_PI		  - barycenterOnYAxis	) ||
					(m_renderData->rotation > M_PI								&& m_renderData->rotation < M_PI		  + barycenterOnYAxis	) ||
					(m_renderData->rotation > 1.5f * M_PI						&& m_renderData->rotation < 2.0f * M_PI	  - barycenterOnYAxis	)) {
				// the rocket should fall anticlockwise
				m_renderData->rotation -= 10.0f * M_PI * deltaTime;
			}
			else if((m_renderData->rotation > 				barycenterOnYAxis	&& m_renderData->rotation < 0.5f * M_PI							) ||
					(m_renderData->rotation > M_PI		  - barycenterOnYAxis	&& m_renderData->rotation < M_PI								) ||
					(m_renderData->rotation > M_PI		  + barycenterOnYAxis	&& m_renderData->rotation < 1.5f * M_PI							) ||
					(m_renderData->rotation > 2.0f * M_PI -	barycenterOnYAxis	&& m_renderData->rotation < 2.0f * M_PI							)) {
				// the rocket should fall clockwise
				m_renderData->rotation += 10.0f * M_PI * deltaTime;
			}

			// round rotation if near axes
			constexpr float roundingValue = 0.1f; // (rad)
			if ((m_renderData->rotation > 2.0f * M_PI - roundingValue && m_renderData->rotation < 0.0f) || (m_renderData->rotation > 0.0f && m_renderData->rotation < roundingValue))
				m_renderData->rotation = 0.0f;
			else if (m_renderData->rotation > 0.5f * M_PI - roundingValue && m_renderData->rotation < 0.5f * M_PI + roundingValue)
				m_renderData->rotation = 0.5f * M_PI;
			else if (m_renderData->rotation > 1.0f * M_PI - roundingValue && m_renderData->rotation < 1.0f * M_PI + roundingValue)
				m_renderData->rotation = 1.0f * M_PI;
			else if (m_renderData->rotation > 1.5f * M_PI - roundingValue && m_renderData->rotation < 1.5f * M_PI + roundingValue)
				m_renderData->rotation = 1.5f * M_PI;
		}
		// the rocket rotation is 0 when it is vertical, not horizontal (along x axis), so summing 90°
		m_engine.setRotation(m_renderData->rotation + 0.5f * M_PI);
	}
	void Rocket::damage(float velocity) {
		m_integrity -= velocity * velocity * 0.1f;
	}

	using namespace app;
	using stypox::KeyEvent, stypox::Key;
	Rocket::Rocket() :
		RectangleRender{rend::RectangleRenderData{0.0f, groundLevel, width, height, 0.0f, 0.0f, 0.2f}}, m_vx{0.0f},
		m_vy{0.0f}, m_engine{/*TODO*/10.2f, 0.5f * M_PI},
		m_gravity{g, 1.5 * M_PI}, m_rotationVelocity{0.0f},
		m_fuel{/*TODO*/10.0f}, m_collectedMoney{/*TODO*/0},
		m_integrity{/*TODO*/0.0f}, m_keyboardFunctionHandlers{
			Application::eventNotifier.connect_member(m_engine, &misc::Acceleration::activate,
				KeyEvent{KeyEvent::press,   Key::kb_w}, KeyEvent{KeyEvent::press,   Key::kb_up}),
			Application::eventNotifier.connect_member(m_engine, &misc::Acceleration::deactivate,
				KeyEvent{KeyEvent::release, Key::kb_w}, KeyEvent{KeyEvent::release, Key::kb_up},
				KeyEvent{KeyEvent::press,   Key::kb_s}, KeyEvent{KeyEvent::press,   Key::kb_down}),
			Application::eventNotifier.connect([this](){ m_rotationVelocity += defaultRotationVelocity; },
				KeyEvent{KeyEvent::press,   Key::kb_a}, KeyEvent{KeyEvent::press,   Key::kb_left},
				KeyEvent{KeyEvent::release, Key::kb_d}, KeyEvent{KeyEvent::release, Key::kb_right}),
			Application::eventNotifier.connect([this](){ m_rotationVelocity -= defaultRotationVelocity; },
				KeyEvent{KeyEvent::release, Key::kb_a}, KeyEvent{KeyEvent::release, Key::kb_left},
				KeyEvent{KeyEvent::press,   Key::kb_d}, KeyEvent{KeyEvent::press,   Key::kb_right}),
		} {
		m_engine.deactivate();
		m_gravity.deactivate();
	}

	void Rocket::updatePosition(float deltaTime) {
		updateRotation(deltaTime);

		// calculate acceleration sum
		auto accelSum = m_engine + m_gravity;

		// update velocity
		m_vx += accelSum.deltavx(deltaTime);
		m_vy += accelSum.deltavy(deltaTime);
		if (m_vx > maxHorizontalSpeed)
			m_vx = maxHorizontalSpeed;
		else if (m_vx < -maxHorizontalSpeed)
			m_vx = -maxHorizontalSpeed;
		if (m_vy > maxSpeedUp)
			m_vy = maxSpeedUp;
		else if (m_vy < -maxSpeedDown)
			m_vy = -maxSpeedDown;

		// update position and check if rocket is below ground
		m_renderData->y += m_vy * deltaTime;
		if (m_renderData->y > groundLevel) {
			m_renderData->x += m_vx * deltaTime;
			m_gravity.activate();
		}
		else {
			m_renderData->y = groundLevel;
			if (m_vy < accelSum.deltavy(deltaTime))
				damage(m_vy);

			m_vy = 0.0f;
			m_vx = 0.0f;
			m_gravity.deactivate();
		}

#ifdef DEBUG
		{
			ImGui::Begin("Rocket debug");
			ImGui::Text("x=%.2f " "y=%.2f\n" "rotation=%.3f\n" "v=%.2f " "(vx=%.2f " "vy=%.2f)\n",
						m_renderData->x, m_renderData->y, m_renderData->rotation, std::sqrt(m_vx*m_vx + m_vy*m_vy), m_vx, m_vy);
			ImGui::Text("fuel=%.2f\n" "collected money=%i\n" "integrity=%.2f\n",
						m_fuel,		  m_collectedMoney,		 m_integrity);
			ImGui::End();
		}
#endif
	}

	std::vector<std::pair<int, int>> Rocket::chunksToCheck() const {
		int x1 = std::floor(m_renderData->x),
		    y1 = std::floor(m_renderData->y),
			x2 = std::round(m_renderData->x),
		    y2 = std::round(m_renderData->y);
		if (x1 == x2)
			--x2;
		if (y1 == y2)
			--y2;

		// 2x2 area of chunks around the rocket. The center is the closest vertex of the chunk it is in.
		return {
			{x1, y1},
			{x1, y2},
			{x2, y1},
			{x2, y2},
		};
	}

	void Rocket::pickUpIntersecting(std::vector<ent::Item>& items) {
		for (auto item = items.rbegin(); item != items.rend(); ++item) {
			if (intersects(this, &*item)) {
				pickUp(*item);
				items.erase(std::next(item).base());
			}
		}
	}
	void Rocket::runIntoIntersecting(std::vector<Cloud>& clouds, float timeNow) {
		float timeCanRunInto = timeNow - 0.7f; // Run into clouds only if 0.7 seconds have passed since the last time the rocket run into them
		for (auto&& cloud : clouds) {
			if (intersects(this, &cloud) && cloud.m_lastTimeRanInto < timeCanRunInto) {
				m_vy -= 0.6f; /* TODO */
				m_integrity -= 0.05f; /* TODO */
				cloud.m_lastTimeRanInto = timeNow;
			}
		}
	}
}