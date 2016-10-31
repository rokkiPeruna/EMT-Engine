//Copyrights
//Link to repo's wikipage containing this classes long description

#ifndef JEJ_BASECLASS_HPP
#define JEJ_BASECLASS_HPP

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

//Forward declarations if class is outside namespace
class ExampleOne;
/////////////////////////////////

namespace jej //NAMESPACE jej STARTS
{

	//Forward declarations inside namespace
	class ExampleTwo;

	//Description of the class
	//Short desc: Baseclass for all subclasses, all functions are pure virtual
	class BaseClass
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

		//Describe constructor(s)
		//Default constructor
		BaseClass();

        BaseClass(const BaseClass&);

		//Describe destructor
		virtual ~BaseClass();


		//Method description, this is described as final so deriving classes can't override this
		virtual void PublicFunction(int p_Number) final;

        virtual void AnotherFunction();

		//Public variable, describing name
		int myNumberForSomething;

        //Public pointer FOR TESTING PURPOSES ONLY!!!!!!!!!
        int* myIntPtr;


	//Virtual methods and variables
	protected:

		//Method description
		virtual void _protectedFunctionOne() = 0;

		//Method description
		virtual int _protectedFunctionTwo() = 0;

		//Protected variable, describing name
		float m_speedOfShip;


	//Private methods and variables
	private:

		int m_numberOfInstances;

	};

}//NAMESPACE jej ENDS

#endif