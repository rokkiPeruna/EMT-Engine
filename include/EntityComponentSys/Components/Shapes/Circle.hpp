#ifndef JEJ_CIRCLE_HPP
#define JEJ_CIRCLE_HPP

#include <EntityComponentSys/Components/Shapes/Shape.hpp>

namespace jej
{
    class Circle : public Shape
    {

    public:

        //Default constructor
        Circle();

        //Constructor
        Circle(const float radius, const unsigned int accuracy);

        //Destructor
        virtual ~Circle();

		//bool Transform(const std::vector<float>& p_newPoints) override;

	private:
		
        void _load(const float radius, const unsigned int accuracy);
    };


}

#endif