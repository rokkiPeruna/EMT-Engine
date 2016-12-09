#ifndef JEJ_MATH_HPP
#define JEJ_MATH_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>


namespace jej
{
	// Little bit misguiding name, so far calculates the AABB box.
	class Math
	{
	public:

		Math();
		~Math();
		
		// Calculates AABB box over all shapes of Entity.
		static const std::pair<const Vector2f, const Vector2f> ConvexCollisionBox(const ShapeComponent& p_shapes, const Vector2f p_centerPoint = { 0, 0 });

	private:
		
	};

}

#endif