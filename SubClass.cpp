#include "SubClass.hpp"

namespace jej //NAMESPACE jej STARTS
{

	SubClass::SubClass():
        BaseClass(),
        m_myOwmMember(0)
	{

	}
    /////////////////////////////////

    //This needs refining
    SubClass::SubClass(const SubClass& p_copy) :
        BaseClass(p_copy),
        m_myOwmMember(p_copy.m_myOwmMember)
    {

    }

	SubClass::~SubClass()
	{
	}
    /////////////////////////////////

    ////Public methods///////////////////////////////////////////////////////////////////////////////////////////////////
	
    inline int SubClass::GetVariable() const
	{
		return (int)m_speedOfShip;
	}
    /////////////////////////////////

    ////Private methods///////////////////////////////////////////////////////////////////////////////////////////////////

    void SubClass::_protectedFunctionOne()
    {

    }
    /////////////////////////////////

    int SubClass::_protectedFunctionTwo()
    {
        return 0;
    }
    /////////////////////////////////

}//NAMESPACE jej ENDS
