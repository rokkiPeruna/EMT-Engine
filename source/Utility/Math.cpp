#include <Utility/Math.hpp>
#include <Utility/Messenger.hpp>

#include <assert.h>

namespace jej
{
	const std::pair<const Vector2f, const Vector2f> Math::ConvexCollisionBox(const Shape* p_shape, const Vector2f p_centerPoint)
	{
		Vector2f min = {0, 0};
		Vector2f max = {0, 0};
		
		if (p_shape->GetType() == ShapeType::Circle)
		{
			
			min = { p_centerPoint.x - p_shape->GetRadius(), p_centerPoint.y - p_shape->GetRadius() };
			max = { p_centerPoint.x + p_shape->GetRadius(), p_centerPoint.y + p_shape->GetRadius() };

			return std::make_pair(min, max);
		}
	
		for (const auto& itr : p_shape->GetPoints())
		{
			if (itr.x < min.x)
				min.x = itr.x;
			if (itr.y < min.y)
				min.y = itr.y;

			if (itr.x > max.x)
				max.x = itr.x;
			if (itr.y > max.y)
				max.y = itr.y;
		}

		min.x += p_centerPoint.x;
		min.y += p_centerPoint.y;

		max.x += p_centerPoint.x;
		max.y += p_centerPoint.y;


		return std::make_pair(min, max);
	}
}


