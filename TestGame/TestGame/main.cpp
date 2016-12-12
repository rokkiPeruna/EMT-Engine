#include <memory>


#include <Core/EngineObject.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>

#include <EntityComponentSys/Systems/System.hpp>
#include <Core/Scene.hpp>

#include <Utility/Random.hpp>

#include <Utility/FileHandler.hpp>

#include <EntityComponentSys/Components/ShaderComponent.hpp>
#include <EntityComponentSys/Components/CollisionComponent.hpp>

#include <IO_Manager/Win32/Mouse.hpp>
#include <IO_Manager/Win32/Keyboard.hpp>
#include <IO_Manager/Win32/InputManager.hpp>

#include <Core/Timer.hpp>

int main(int argc, char* argv[])
{

	//Create new EngineObject, initialize it and get alias handle to it
	if (!jej::EngineObject::Initialize(argv[0]))
		return 1;
	auto& game = jej::EngineObject::GetInstance();


	//Create scene in which you can put entities.
	//Scene can be start menu, game level, credits ec.

	auto& myScene = *game.CreateScene(true, "My Scene Name");

	//Add new entity to the newly created scene and make alias of added entity for ease of use
	auto& player = myScene.AddEntity("Player");

	////Start adding components to our entity
	////Entity has template method AddComponent which allows you to add all kinds of components
	////AddComponent takes as typename a component name that is available with jej::SomeComponent - style syntax
	////Every different component has a different parameter list so be sure what you're giving to your component
	////In this example, TransformComponent is created as parameter of Entity's AddComponent - method and is then added 
	////to myCharacter:

	////Creating:
	player.AddComponent<jej::TransformComponent>(
		jej::Vector2f(0.25f, -0.5f),		//Position, we start at center of the screen
		jej::Vector2f(1.f, 1.f),		//Scale in x, y - axises
		jej::Vector4f(0.f, 0.f, 0.f, 0.f)//Rotation x, y, z, w
		);


	////Next we create ShaderComponent and add it to our entity so it can be drawn
	player.AddComponent<jej::ShaderComponent>(
		"PixelShader.frag",			//First we must give vertex shader name and file extension
		"VertexShader.vert"			//Second we guve fragment shader name and file extencion
		);



	////Then we create and add ShapeComponent to give our entity some form and color
	////NOTICE that we don't give any coordinates yet or what type of shape this component holds
	////This is because our ShapeComponent might consist of several different shapes
	////etc. we make a pyramid that has four triangles as sides and rectangle as bottom.
	////As we add ShapeComponent, we take an alias at the sametime for ease of use.

	auto& PlayerShapeComponent = player.AddComponent<jej::ShapeComponent>(
		jej::Vector4i(0, 255, 0, 150)	//This our shape's color in RGBA, so this is fully green and somewhat opaque
		);



	////Now we can add shape to our ShapeComponent. AddShape - method works intuitively. As we now
	////add three points, AddShape knows we are making a triangle.
	PlayerShapeComponent.AddShape(std::vector<jej::Vector2f>
	{
		jej::Vector2f(0.f, -0.1f),		//First point, middle of screen
			jej::Vector2f(-0.05f, -0.25f),		//Second point, upper-right corner
			jej::Vector2f(0.05f, -0.25f)        //Third point, lower-right corner
	}
	);


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
	player.AddComponent<jej::RenderComponent>();

	////Don't try setting components to other entities other than the one calling the function

	player.AddComponent<jej::CollisionComponent>();


	//Enemies:
	//Creates as many enemies as enemyNumber is


	const char enemyNumber = 10;
	const char rows = 3;
	bool EnemyMove = false;

	auto& myTimer = jej::Timer::GetInstance();

	for (signed char j = 0; j < rows; ++j)
	{

		for (signed char i = 0; i < enemyNumber; ++i)
		{
			//Adds single enemy to the scene
			myScene.AddEntity("Enemy " + std::to_string(j) + " " + std::to_string(i));

			auto& enemy = *myScene.GetEntityPtr("Enemy " + std::to_string(j) + " " + std::to_string(i));

			enemy.userData = &EnemyMove;

			//Adds growing position for current enemy
			enemy.AddComponent<jej::TransformComponent>(
				jej::Vector2f(-0.5f + (float)i / 10.f, 0.45f + (float)j / 5)
				);

			enemy.AddComponent<jej::ShaderComponent>(
				"PixelShader.frag",			//First we must give vertex shader name and file extension
				"VertexShader.vert"			//Second we give fragment shader name and file extension
				);


			auto& enemyShapeComp = enemy.AddComponent<jej::ShapeComponent>
				(
				jej::Vector4i(0, 255, 0, 150)	//This our shape's color in RGBA, so this is fully green and somewhat opaque
				);

			//Adds a downwards pointing triangle shape for current enemy
			auto& shape = enemyShapeComp.AddShape(std::vector<jej::Vector2f>
			{
				jej::Vector2f(0.f, -0.1f),
					jej::Vector2f(-0.04f, 0.04f),
					jej::Vector2f(0.04f, 0.04f)
			}
			);



			//Adds the possibility to draw current enemy
			enemy.AddComponent<jej::RenderComponent>();
			enemy.AddComponent<jej::CollisionComponent>();
		}
	}



	//#if 1
	//
	//    auto& tex = myCharacter.AddComponent<jej::TextureComponent>(s.GetID());
	//
	//#endif
	//
	//#if 1
	//
	//    if (tex.AddImage("Capture.png"))
	//        jej::Messenger::Add(jej::Messenger::MessageType::Info, "image loaded successfully");
	//    else
	//        jej::Messenger::Add(jej::Messenger::MessageType::Warning, "image loading unsuccessful");
	//#endif
	//
	//#if 0
	//
	//    if (tex.AddFont("Textures/Bungee_Regular.ttf"))
	//        jej::Messenger::Add(jej::Messenger::MessageType::Info, "font loaded successfully");
	//    else
	//        jej::Messenger::Add(jej::Messenger::MessageType::Warning, "font loading unsuccessful");
	//#endif


	auto& mouse = jej::Mouse::GetInstance();
	auto& keyboard = jej::Keyboard::GetInstance();

	//Finalize EngineObject
	game.Finalize();
	bool loop = true;
	float deltaTime;
	while (loop)
	{
		deltaTime = myTimer.GetTime();

		game.EngineUpdate();

		auto* charLocChange = player.GetComponentPtr<jej::TransformComponent>();

		if (keyboard.IsKeyPressed(jej::Keyboard::Key::A))
			charLocChange->position.x -= 0.05f;

		if (charLocChange->position.x < -1.f)
			charLocChange->position.x = -1.f;

		if (keyboard.IsKeyPressed(jej::Keyboard::Key::D))
			charLocChange->position.x += 0.05f;

		if (charLocChange->position.x > 1.f)
			charLocChange->position.x = 1.f;

		if (keyboard.IsKeyPressed(jej::Keyboard::Key::Space))
		{


		}

		auto kek = myScene.GetEntities("Enemy");

		for (const auto& itr : kek)
		{
			auto& enemyPosition = itr->GetComponentPtr<jej::TransformComponent>()->position;

			if (!itr->userData)
			{
				enemyPosition.x += -0.5f * deltaTime;

				if (enemyPosition.x < -1)
				{
					for (int i = 1; i <= myScene.GetEntityIDs().size(); ++i)
					{
						//EnemyMove = true;
						enemyPosition.x = -1.f;
						myScene.GetEntityPtr(i)->userData = (void*)true;
					}

					for (int i = 2; i <= myScene.GetEntityIDs().size(); ++i)
					{
						myScene.GetEntityPtr(i)->GetComponentPtr<jej::TransformComponent>()->position.y -= 3.0f *deltaTime;
					}
				}
			
			}

			if (itr->userData)
			{
				enemyPosition.x += 0.5f * deltaTime;

				if (enemyPosition.x > 1)
				{

					for (int i = 1; i <= myScene.GetEntityIDs().size(); ++i)
					{
						//EnemyMove = false;
						enemyPosition.x = 1.f;
						myScene.GetEntityPtr(i)->userData = (void*)false;
					}

					for (int i = 2; i <= myScene.GetEntityIDs().size(); ++i)
					{
						myScene.GetEntityPtr(i)->GetComponentPtr<jej::TransformComponent>()->position.y -= 3.0f *deltaTime;
					}
				}
			}

		}


		if (keyboard.IsKeyPressed(jej::Keyboard::Key::Escape))
			loop = false;

		//break;
		//std::cout << mouse.GetMousePosition().x << "   " << mouse.GetMousePosition().y << std::endl;

	}

	return 0;
}