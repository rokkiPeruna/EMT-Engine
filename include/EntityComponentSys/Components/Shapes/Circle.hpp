#ifndef JEJ_CIRCLE_HPP
#define JEJ_CIRCLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{
    class Circle : public ShapeComponent
    {

    public:

        //Default constructor
        Circle(Entity& entity);

        //Constructor
        Circle(Entity& entity, const float radius, const unsigned int accuracy);

        //Destructor
        virtual ~Circle();

		bool Transform(const std::vector<float>& p_newPoints) override;

	private:
		void _load(const float radius, const unsigned int accuracy);
    };


}

#endif