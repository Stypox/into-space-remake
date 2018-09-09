#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_ITEM_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_ITEM_H_

#include "entity.h"
#include "GLFW/glfw3.h"

namespace game::entity {
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
		
	private:
		const Type m_type;
		const GLfloat m_x, m_y;

	public:
		Item(Type type, float x, float y);

		GLfloat x() const override;
		GLfloat y() const override;
		GLfloat textureIndex() const;
	};
}

#endif