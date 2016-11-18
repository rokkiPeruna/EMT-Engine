#ifndef JEJ_SHAPE_COMPONENT_HPP
#define JEJ_SHAPE_COMPONENT_HPP

#include <EntityComponentSys\Components\Component.hpp>
#include <Core\BaseStructs.hpp>

namespace jej
{

	class ShapeComponent
	{
	protected:
		ShapeType m_shapeType;

	public:
		//Constructor
		ShapeComponent();

		//Destructor
		virtual ~ShapeComponent();

	};

}

#endif