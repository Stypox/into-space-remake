#ifndef _INTO_SPACE_REMAKE_GAME_ENT_ITEM_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_ITEM_H_

#include "entity.h"
#include "../../rend/items.h"

namespace game::ent {
	class Item : public Entity, public rend::ItemRender {
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

		Item(Type type, float x, float y);

		GLfloat x() const override { return m_renderData->x; }
		GLfloat y() const override { return m_renderData->y; }
		GLfloat w() const override { return 0.2f; }
		GLfloat h() const override { return 0.2f; }
		GLfloat rotation() const override { return 0.0f; }

		Type type() const { return static_cast<Type>(static_cast<int>(m_renderData->textureIndex)); }
	};
}

#endif