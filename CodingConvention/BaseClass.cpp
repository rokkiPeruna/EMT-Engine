//This header
#include "BaseClass.hpp"
/////////////////////////////////

//Includes for forward declarations
//#include <ExampleTwo.hpp>
/////////////////////////////////

//Include engine's headers
//#include <jej/...>
/////////////////////////////////

//Include third party headers
//#include <gl/Audio/...>
/////////////////////////////////

//Includes for standard headers
#include <string>
#include <vector>
/////////////////////////////////

namespace jej //NAMESPACE jej STARTS
{
    //Default constructor
    BaseClass::BaseClass() :
        myNumberForSomething(0),
        myIntPtr(nullptr),
        m_speedOfShip(0),
        m_numberOfInstances(0)
    {

    }
    /////////////////////////////////

    BaseClass::BaseClass(const BaseClass& p_copy) :
        myNumberForSomething(p_copy.myNumberForSomething),
        myIntPtr(new int(*p_copy.myIntPtr)),
        m_speedOfShip(p_copy.m_speedOfShip),
        m_numberOfInstances(p_copy.m_numberOfInstances)
    {
        
    }
    /////////////////////////////////

    BaseClass::~BaseClass()
    {
    }
    /////////////////////////////////

    ////Public methods///////////////////////////////////////////////////////////////////////////////////////////////////

    void BaseClass::PublicFunction(int p_number)
    {
        p_number += m_speedOfShip;			//This adds m_speedOfShip
        p_number * m_numberOfInstances;		//Comment this way inside methods and functions
        p_number += m_speedOfShip
            * m_numberOfInstances
            * p_number;
    }
    /////////////////////////////////

    void BaseClass::AnotherFunction()
    {

    }
    /////////////////////////////////

    ////Private methods///////////////////////////////////////////////////////////////////////////////////////////////////

}//NAMESPACE jej ENDS
