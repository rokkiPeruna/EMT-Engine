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


    protected:

        void _update(const float p_deltaTime) override;

	private:
		
        void _load(const float radius, const unsigned int accuracy);
    };


}

#endif