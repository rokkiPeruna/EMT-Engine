#ifndef JEJ_CONVEX_HPP
#define JEJ_CONVEX_HPP

#include <EntityComponentSys/Components/ShapeComponent.hpp>

namespace jej
{
    class Convex : public ShapeComponent
    {
    private:
		void _load(const std::vector<float>& p_points);

    public:

        //Default constructor
        Convex(Entity& entity);

        //Constructor
		Convex(Entity& entity, const std::vector<float>& p_points);

        //Destructor
        virtual ~Convex();

		bool Transform(const std::vector<float>& p_newPoints) override;
    };


}

#endif