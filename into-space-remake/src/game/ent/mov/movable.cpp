#include "../../../rend/movables.h"

#include "movable.h"

namespace game::ent::mov {
	Movable::Movable(const RenderData& renderData) :
		m_renderData{rend::Movables::renderData.emplace(renderData)} {}
}