//Copyrights
//Link to repo's wikipage containing this classes long description

#ifndef JEJ_SUBCLASS_HPP
#define JEJ_SUBCLASS_HPP

//Include engine's headers
#include "BaseClass.hpp" //Include base class first
//#include <jej/...>
/////////////////////////////////

//Include third party headers
//#include <gl/Audio/...>
/////////////////////////////////

//Includes for standard headers
#include <string>
#include <vector>
/////////////////////////////////

//Forward declarations if class is outside namespace
class ExampleOne;
/////////////////////////////////

namespace jej //NAMESPACE jej STARTS
{
	//Forward declarations inside namespace
	class ExampleTwo;

	//Description of the class
	//Short desc: Subclass, extends BaseClass
	class SubClass :
		public BaseClass
	{

		//Friend classes or functors
		friend class ExampleThree;

	//Public enums and structs
	public:

		//Public enum classes
		enum class EXAMPLE_ENUM : int
		{
			ZERO,
			ONE,
			TWO,
			FIVE = 5
		};

		//Public structs
		struct ExampleStruct
		{
			std::string name = "defaultName";
			unsigned int ID = 0u;
			void* pointer = nullptr;
			std::vector<std::pair<int, char>> vectorOfPairs;

			//This is required for Android, use also in _WIN32
			ExampleStruct(){};
		};


	//Public methods and variables	
	public:

		//Default constructor
		SubClass();

		//Copy constructor if needed
		SubClass(const SubClass& p_copy);

		//Override =operator if needed
		SubClass operator=(const SubClass&) = delete;

		//Destructor
		~SubClass();

		inline int GetVariable() const;

	//Protected methods and variables if further inheriting takes place
	protected:

		//Some methods and variables...

	//Private methods and variables
	private:

		//Method description
		virtual void _protectedFunctionOne() override;

		//Method description
		virtual int _protectedFunctionTwo() override;

        float m_myOwmMember;
	};

}//NAMESPACE jej ENDS
#endif