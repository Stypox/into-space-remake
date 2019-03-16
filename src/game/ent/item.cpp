#include "item.hpp"

namespace game::ent {
	Item::Item(Type type, float x, float y) :
		ItemRender{rend::ItemRenderData{x, y, static_cast<GLfloat>(type)}} {}
}