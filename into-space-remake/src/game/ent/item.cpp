#include "../../rend/items.h"
#include "item.h"

namespace game::ent {
	Item::Item(Type type, float x, float y) :
		m_type{type}, m_renderData{rend::Items::renderData.emplace(x, y, static_cast<GLfloat>(m_type))} {}
}