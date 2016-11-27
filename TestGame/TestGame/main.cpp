#include <memory>


#include <Core/EngineObject.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>

#include <EntityComponentSys/Systems/System.hpp>
#include <Core/Scene.hpp>

#include <Utility/Random.hpp>

#include <Utility/FileHandler.hpp>

#include <EntityComponentSys/Components/ShaderComponent.hpp>

#include <IO_Manager/Win32/Mouse.hpp>
#include <IO_Manager/Win32/Keyboard.hpp>
#include <IO_Manager/Win32/InputManager.hpp>

int main(int argc, char* argv[])
{

	//Create new EngineObject, initialize it and get alias handle to it
    jej::EngineObject::Initialize(argv[0]);
    auto& game = jej::EngineObject::GetInstance();


	//Create scene in which you can put entities.
	//Scene can be start menu, game level, credits ec.
    jej::Scene myScene;

	//Add new entity to the newly created scene
	myScene.AddEntity("Character");

	//Make alias of added entity for ease of use
	auto* myCharacter = myScene.GetEntityPtr("Character");

	
	//Start adding components to our entity
	//Entity has template method AddComponent which allows you to add all kinds of components
	//AddComponent takes as typename a component name that is available with jej::SomeComponent - style syntax
	//Every different component has a different parameter list so be sure what you're giving to your component
	//In this example, TransformComponent is created as a shared pointer and then added 
	//to myCharacter:

	////Creating:
	//jej::TransformComponent myTransformComp = std::make_shared<jej::TransformComponent>(
	//	myCharacter,					//Tell component that this is its owner
 //       jej::Vector2f(0.f, 0.f),		//Position, we start at center of the screen
 //       jej::Vector2f(1, 1),			//Scale in x, y - axises
 //       jej::Vector4f(0, 0, 0, 0)		//Rotation x, y, z, w
	//	);		
	////Adding
	//myCharacter->AddComponent<jej::TransformComponent>(myTransformComp);
	//	

	////Next we create ShaderComponent and add it to our entity so it can be drawn
	//std::shared_ptr<jej::ShaderComponent> myShaderComp = std::make_shared<jej::ShaderComponent>(
	//	myCharacter,					//Tell component that this is its owner
	//	"VertexShader.vert"	,			//First we must give vertex shader name and file extension
	//	"FragmentShader.frag"			//Second we guve fragment shader name and file extencion
	//	);
	//myCharacter->AddComponent<jej::ShaderComponent>(myShaderComp);



	////Then we create and add ShapeComponent to give our entity some form and color
	////NOTICE that we don't give any coordinates yet or what type of shape this component holds
	////This is because our ShapeComponent might consist of several different shapes
	////etc. we make a pyramid that has four triangles as sides and rectangle as bottom

	//std::shared_ptr<jej::ShapeComponent> myShapeComp = std::make_shared<jej::ShapeComponent>(
	//	myCharacter,					//Tell component that this is its owner
	//	jej::Vector4i(0, 255, 0, 150)	//This our shape's color in RGBA, so this is fully green and somewhat opaque
	//	);
	//myCharacter->AddComponent<jej::ShapeComponent>(myShapeComp);

	////Now that our ShapeComponent is added to our character, let's add some shape to the ShapeComponent.
	////First we make alias of our character's ShapeComponent for ease of use
	//auto myShapeComp = myCharacter->GetComponentPtr<jej::ShapeComponent>();

	////Now we can add shape to our ShapeComponent, multiple if we want
	////First parameter of ShapeComponent's AddShape template method is the type of shape we
	////want to add, in this case triangle. ShapeTypes are found at jej::ShapeType::
	////Following parameters are the actual points (vertices) we want our shape has.
	//myShapeComp->AddShape(
	//	jej::ShapeType::Triangle,		//Type of shape to add
	//	jej::Vector2f(0.f, 0.f),		//First point, middle of screen
	//	jej::Vector2f(1.f, 1.f),		//Second point, upper-right corner
	//	jej::Vector2f(1.f, -1.f)		//Third point, lower-right corner
	//	);


	////Now we have our character with transform, shader and shape component. At this point it exist
	////in our scene and has data in it with witch we can make it react to other entities and
	////vice versa. At this point, our "myCharacter" - entity could act as invisible trigger box, or 
	////trigger triangle if you will.
	////However, we want our character to be visible protagonist that moves and shows. So, in addition to all above
	////components, we must tell our rendering system that we want to draw this entity. We do it by
	////creating and adding one more component, RenderComponent. RenderComponent is a container component that takes in
	////all the above created components and uses their data in rendering system.
	////NOTICE that we have in scope all those aliases we created, so let's use them instead of
	////fetching component with entity's GetComponentPtr<> template function

	////Creating
	//std::shared_ptr<jej::RenderComponent> myRenderComp = std::make_shared<jej::RenderComponent>(
	//	myTransformComp,
	//	myShaderComp,
	//	myShapeComp
	//	);

	////Adding
	//myCharacter->AddComponent<jej::RenderComponent>(myRenderComp);
		
	

    

	auto& mouse = jej::Mouse::GetInstance();
	auto& keyboard = jej::Keyboard::GetInstance();

    for (;;)
    {
        game.EngineUpdate();
		//std::cout << mouse.GetMousePosition().x << "   " << mouse.GetMousePosition().y << std::endl;
		
    }

    return 0;
}