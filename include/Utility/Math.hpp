#ifndef JEJ_MATH_HPP
#define JEJ_MATH_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>


namespace jej
{

	class Math
	{
	public:

		Math();
		~Math();

		static const std::pair<const Vector2f, const Vector2f> ConvexCollisionBox(const Shape* p_shape, const Vector2f p_centralPoint = { 0, 0 });

	private:
		
	};

}

#endif