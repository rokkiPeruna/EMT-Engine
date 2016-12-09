#include <Utility/Math.hpp>
#include <Utility/Messenger.hpp>

#include <assert.h>

namespace jej
{
	const std::pair<const Vector2f, const Vector2f> Math::ConvexCollisionBox(const ShapeComponent& p_shapes, const Vector2f p_centerPoint)
	{
		// Initialize min and max values to points held by this entity
		Vector2f min = p_shapes.m_shapes.at(0)->GetPoints().at(0);
		Vector2f max = p_shapes.m_shapes.at(0)->GetPoints().at(0);
		
		
		
		

		// In order to get 1 single vertex point we have to got through all shapes of the entity (Shape.hpp)
		// TEMP comment
		// and compare its content with itself..? since its a vector of shapes.. which are a vector of vertecies...
		for (const auto& all_shapes : p_shapes.m_shapes)
		{
			/*
			if (all_shapes->GetType == ShapeType::Circle)
			{
				min = { p_centerPoint.x - p_shape->GetRadius(), p_centerPoint.y - p_shape->GetRadius() };
				max = { p_centerPoint.x + p_shape->GetRadius(), p_centerPoint.y + p_shape->GetRadius() };

				return std::make_pair(min, max);
			}
			*/

			for (const auto& single_shape : all_shapes->GetPoints())
			{
				if (single_shape.x < min.x)
					min.x = single_shape.x;

				if (single_shape.y < min.y)
					min.y = single_shape.y;

				if (single_shape.x > max.x)
					max.x = single_shape.x;

				if (single_shape.y > max.y)
					max.y = single_shape.y;
			}
		}

		min.x += p_centerPoint.x;
		min.y += p_centerPoint.y;

		max.x += p_centerPoint.x;
		max.y += p_centerPoint.y;

		return std::make_pair(min, max);
	}
}


