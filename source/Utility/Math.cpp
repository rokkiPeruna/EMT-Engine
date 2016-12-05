#include <Utility/Math.hpp>
#include <Utility/Messenger.hpp>

#include <assert.h>

namespace jej
{
	const std::pair<const Vector2f, const Vector2f> Math::ConvexCollisionBox(const Shape* p_shape, const Vector2f p_centralPoint)
	{
			Vector2f min, max = p_shape->GetPoints().at(0);


			//if (p_shape->m_shapeType == ShapeType::Circle)
			//{
			//	float radius = abs(sqrt((min.x - p_centralPoint.x) * (min.x - p_centralPoint.x) + (min.y - p_centralPoint.y) * (min.y - p_centralPoint.y)));
			//	
			//	min = { p_centralPoint.x - radius, p_centralPoint.y - radius };
			//	max = { p_centralPoint.x + radius, p_centralPoint.y + radius };
            //
            //
			//	return std::make_pair(min, max);
			//}
            //
			//for (const auto& itr : p_shape->GetPoints())
			//{
			//	if (min.x > itr.x)
			//		min.x = itr.x;
            //
			//	if (min.y > itr.y)
			//		min.y = itr.y;
			//}
            //
			//for (const auto& itr : p_shape->GetPoints())
			//{
			//	if (max.x < itr.x)
			//		max.x = itr.x;
            //
			//	if (max.y < itr.y)
			//		max.y = itr.y;
			//}
            //
			return std::make_pair(min, max);
	}




}


