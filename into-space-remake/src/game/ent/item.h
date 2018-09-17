#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_ITEM_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_ITEM_H_

#include <GLFW/glfw3.h>

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
		
	private:
		const Type m_type;
		const GLfloat m_x, m_y;

	public:
		Item(Type type, float x, float y);

		GLfloat x() const override;
		GLfloat y() const override;
		GLfloat sizeX() const override { return 0.1f; }
		GLfloat sizeY() const override { return 0.1f; }
		GLfloat textureIndex() const;

		Type type() const { return m_type; }
	};
}

#endif