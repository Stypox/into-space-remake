#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_MOVABLE_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_MOVABLE_H_

#include <GLFW/glfw3.h>
#include <stypox/stock_container.h>

#include "../entity.h"

namespace game::ent::mov {
	class Movable : public Entity {
	public:
		struct RenderData {
			GLfloat x, y, w, h,
				rotation, textureOffset, textureWidth;
		};
	protected:
		stypox::StockContainer<RenderData>::handler m_renderData;
	public:
		Movable(const RenderData& renderData);

		GLfloat x() const override { return m_renderData->x; }
		GLfloat y() const override { return m_renderData->y; }
		GLfloat w() const override { return m_renderData->w; }
		GLfloat h() const override { return m_renderData->h; }
		GLfloat rotation() const { return m_renderData->rotation; };
		GLfloat textureOffset() const { return m_renderData->textureOffset; }
		GLfloat textureWidth() const { return m_renderData->textureWidth; }

		virtual void updatePosition(float deltaTime) = 0;
	};
}

#endif