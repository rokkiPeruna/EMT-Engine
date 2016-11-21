#ifndef JEJ_TRIANGLE_HPP
#define JEJ_TRIANGLE_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{

    class Triangle : public ShapeComponent
    {
    private:
		void _load(const float (&p_points)[6]);

    public:

        //Default constructor
        Triangle(Entity& entity);

        //Constructor
        Triangle(Entity& entity, const float (&p_points)[6]);

        //Destructor
        virtual ~Triangle();

		bool Transform(const std::vector<float>& p_newPoints) override;
    };

}

#endif