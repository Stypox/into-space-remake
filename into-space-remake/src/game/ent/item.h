#ifndef _INTO_SPACE_REMAKE_GAME_ENT_ITEM_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_ITEM_H_

#include <GLFW/glfw3.h>
#include <stypox/stock_container.h>

#include "entity.h"

namespace game::ent {
	class Item : public Entity {
	public:
		// the enum values represent the index in the packed texture file 
		enum Type : GLbyte {
			fuel0  = 0,
			fuel1  = 1,
			fuel2  = 2,
			money0 = 3,
			money1 = 4,
			money2 = 5,
			repair = 6,
			max = repair,
		};

		struct RenderData {
			GLfloat x, y, textureIndex;
		};
		
	private:
		const Type m_type;
		stypox::StockContainer<RenderData>::handler m_renderData;

	public:
		Item(Type type, float x, float y);

		GLfloat x() const override { return m_renderData->x; }
		GLfloat y() const override { return m_renderData->y; }
		GLfloat w() const override { return 0.2f; }
		GLfloat h() const override { return 0.2f; }
		GLfloat textureIndex() const { return m_renderData->textureIndex; }

		Type type() const { return m_type; }
	};
}

#endif