#ifndef JEJ_RECTANGLE_HPP
#define JEJ_RECTANGLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    class Rectangle : public ShapeComponent
    {
    private:
		void _load(const float x, const float y);

    public:

        //Default constructor
        Rectangle(Entity& entity);

        //Constructor
		Rectangle(Entity& entity, const float x, const float y);

        //Destructor
        virtual ~Rectangle();

		bool Transform(const std::vector<float>& p_newPoints) override;
    };

}

#endif