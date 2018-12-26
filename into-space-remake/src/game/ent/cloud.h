#ifndef _INTO_SPACE_REMAKE_GAME_ENT_CLOUD_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_CLOUD_H_

#include "entity.h"
#include "../../rend/rectangles.h"

namespace game::ent {
	namespace mov { class Rocket; }
	
	class Cloud : public Entity, public rend::RectangleRender {
		friend class mov::Rocket;

		static constexpr float widthHeightRatio = 1.5f;

		float m_lastTimeRanInto;
	public:
		Cloud(float x, float y);

		GLfloat x() const override { return m_renderData->x; }
		GLfloat y() const override { return m_renderData->y; }
		GLfloat w() const override { return m_renderData->w; }
		GLfloat h() const override { return m_renderData->h; }
		GLfloat rotation() const override { return m_renderData->rotation; };
	};
}

#endif