#ifndef JEJ_CIRCLE_HPP
#define JEJ_CIRCLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{
	class Circle:ShapeComponent
	{
	private:
		float m_radius;

	public:

		Circle();

		//Constructor
		Circle(const float radius);

		//Destructor
		virtual ~Circle();
	};


}

#endif