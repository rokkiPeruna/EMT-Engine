#include <Utility/Math.hpp>
#include <Utility/Messenger.hpp>

namespace jej
{
	void Math::Finalize(Shape p_shape)
	{
		switch (p_shape.m_shapeType)
		{
		case ShapeType::Triangle:
		{

			break;
		}
		case ShapeType::Rectangle:
		{

			break;
		}
		case ShapeType::Convex:
		{

		}
		case ShapeType::Circle:
		{

		}
		default:
		{
			Messenger::Add()

		}

		}


	}


}