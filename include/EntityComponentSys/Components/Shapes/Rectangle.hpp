#ifndef JEJ_RECTANGLE_HPP
#define JEJ_RECTANGLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

	class Rectangle :ShapeComponent
	{
	private:
		Vector2f m_extents;

	public:

		Rectangle();

		//Constructor
		Rectangle(const Vector2f extents);

		//Destructor
		virtual ~Rectangle();
	};

}

#endif