#include <memory>


#include <Core/EngineObject.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>

#include <EntityComponentSys/Systems/System.hpp>
#include <Core/Scene.hpp>

#include <Utility/Random.hpp>

//#include <Utility/FileHandler.hpp>

#include <EntityComponentSys/Components/ShaderComponent.hpp>

#include <IO_Manager/Win32/Mouse.hpp>
#include <IO_Manager/Win32/Keyboard.hpp>
#include <IO_Manager/Win32/InputManager.hpp>

int main(int argc, char* argv[])
{

    //Create new EngineObject, initialize it and get alias handle to it
    if (!jej::EngineObject::Initialize(argv[0]))
        return 1;
    auto& game = jej::EngineObject::GetInstance();


    //Create scene in which you can put entities.
    //Scene can be start menu, game level, credits ec.
    jej::Scene myScene;

    //Add new entity to the newly created scene
    myScene.AddEntity("Character");

    auto& player = myScene.AddEntity("Player");
    player.AddComponent<jej::TransformComponent>();
    player.AddComponent<jej::ShapeComponent>();
    player.AddComponent<jej::ShaderComponent>();
    
    auto* PlayerShapeComponent = player.GetComponentPtr<jej::ShapeComponent>();
    std::vector<jej::Vector2f> kolmionPisteet = {
        jej::Vector2f(0.f, 0.f),
        jej::Vector2f(0.f, 0.5f),
        jej::Vector2f(-0.75f, 0.f)
    };
    
    if (PlayerShapeComponent != nullptr)
        PlayerShapeComponent->AddShape(kolmionPisteet);
    
    //player.AddComponent<jej::RenderComponent>();

    const char enemyNumber = 20;

    //Creates as many enemies as enemyNumber is
    for (signed char i = 0; i < enemyNumber; ++i)
    {
        //Adds a single enemy to the scene
        auto& enemy = myScene.AddEntity("Enemy " + std::to_string(i));
        
        //Adds a growing position for current enemy
        enemy.AddComponent<jej::TransformComponent>(jej::Vector2f(i,7));

        //Adds a downwards pointing triangle shape for current enemy
        enemy.AddComponent<jej::ShapeComponent>().AddShape(std::vector<jej::Vector2f>
        {
            jej::Vector2f(0.f, -1.f),
            jej::Vector2f(-0.5f, 0.5f),
            jej::Vector2f(0.5f, 0.5f) 
        });

        //Adds shader for the current enemy
        enemy.AddComponent<jej::ShaderComponent>();

        //Adds the possibility to draw current enemy
        //enemy.AddComponent<jej::RenderComponent>();
    }

    //Get vector of all entities (std::vector<shared_ptr<Entity>>)
    auto* allEntities = myScene.GetEntities();
    
    //Iterates through all the entities
    for (const auto& itr : *allEntities)
    {
        if (itr->RemoveAllComponents())
            jej::Messenger::Add(jej::Messenger::MessageType::Info, "Removed all components from Entity. Entity ID: ", itr->GetID(), "Entity name: ", itr->m_name);
        else
            jej::Messenger::Add(jej::Messenger::MessageType::Warning, "Could not remove all components from Entity. Entity ID: ", itr->GetID(), "Entity name: ", itr->m_name);
    }

    std::string *entityNames = new std::string[allEntities->size()];

    for (signed char i = 0; i < allEntities->size(); ++i)
        entityNames[i] = allEntities->at(i)->m_name;

    for (signed char i = 0; i < entityNames->size(); ++i)
    {
        if (myScene.RemoveEntity(entityNames[i]))
            jej::Messenger::Add(jej::Messenger::MessageType::Info, "Removed entity: " + entityNames[i]);
        else
            jej::Messenger::Add(jej::Messenger::MessageType::Warning, "Could not remove entity: " + entityNames[i]);
        
    }

    ////Make alias of added entity for ease of use
    //auto& myCharacter = *myScene.GetEntityPtr("Character");


    ////Start adding components to our entity
    ////Entity has template method AddComponent which allows you to add all kinds of components
    ////AddComponent takes as typename a component name that is available with jej::SomeComponent - style syntax
    ////Every different component has a different parameter list so be sure what you're giving to your component
    ////In this example, TransformComponent is created as parameter of Entity's AddComponent - method and is then added 
    ////to myCharacter:

    ////Creating:
    //myCharacter.AddComponent<jej::TransformComponent>(
    //    //&myCharacter,					//Tell component that this is its owner
    //    jej::Vector2f(0.f, 0.f),		//Position, we start at center of the screen
    //    jej::Vector2f(1.f, 1.f),		//Scale in x, y - axises
    //    jej::Vector4f(0.f, 0.f, 0.f, 0.f)//Rotation x, y, z, w
    //    );


    ////Next we create ShaderComponent and add it to our entity so it can be drawn
    //myCharacter.AddComponent<jej::ShaderComponent>(
    //    //&myCharacter					//Tell component that this is its owner
    //    //"PixelShader.frag",			//First we must give vertex shader name and file extension
    //    //"VertexShader.vert"			//Second we guve fragment shader name and file extencion
    //    );



    ////Then we create and add ShapeComponent to give our entity some form and color
    ////NOTICE that we don't give any coordinates yet or what type of shape this component holds
    ////This is because our ShapeComponent might consist of several different shapes
    ////etc. we make a pyramid that has four triangles as sides and rectangle as bottom.
    ////As we add ShapeComponent, we take an alias at the sametime for ease of use.

    //auto& myShapeComp = myCharacter.AddComponent<jej::ShapeComponent>(
    //    //&myCharacter,					//Tell component that this is its owner
    //    jej::Vector4i(0, 255, 0, 150)	//This our shape's color in RGBA, so this is fully green and somewhat opaque
    //    );



    ////Now we can add shape to our ShapeComponent. AddShape - method works intuitively. As we now
    ////add three points, AddShape knows we are making a triangle.
    //myShapeComp.AddShape(std::vector<jej::Vector2f>
    //{
    //        //jej::Vector2f(1.f, -1.f),       //Third point, lower-right corner
    //        //jej::Vector2f(0.f, 0.f),		//First point, middle of screen
    //        //jej::Vector2f(0.5f, 0.2f),		//Second point, upper-right corner
    //        //jej::Vector2f(0.7f, -0.2f)
    //   
    //        jej::Vector2f(-1.f, 1.f),
    //        jej::Vector2f(-1.f, -1.f),		//Second point, upper-right corner
    //        jej::Vector2f(1.f, -1.f),		//First point, middle of screen
    //        //jej::Vector2f(1.f, 1.f)       //Third point, lower-right corner

    //}
    //);


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
    //myCharacter.AddComponent<jej::RenderComponent>(
    //    //&myCharacter
    //    );

    ////Don't try setting components to other entities other than the one calling the function

    auto& mouse = jej::Mouse::GetInstance();
    auto& keyboard = jej::Keyboard::GetInstance();

    //Finalize EngineObject
    game.Finalize();
    while (1)
    {
        game.EngineUpdate();
        //break;
        //std::cout << mouse.GetMousePosition().x << "   " << mouse.GetMousePosition().y << std::endl;

    }

    return 0;
}