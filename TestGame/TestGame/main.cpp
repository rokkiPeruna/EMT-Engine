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


    auto& bg = myScene.AddEntity("bg");
    bg.AddComponent<jej::TextureComponent>(bg.AddComponent<jej::ShapeComponent>().AddShape(jej::Vector2f(-1, 1)).GetID()).AddImage("JEJDemoBackG.png");
    bg.AddComponent<jej::RenderComponent>();




    ////Then we create and add ShapeComponent to give our entity some form and color
    ////NOTICE that we don't give any coordinates yet or what type of shape this component holds
    ////This is because our ShapeComponent might consist of several different shapes
    ////etc. we make a pyramid that has four triangles as sides and rectangle as bottom.
    ////As we add ShapeComponent, we take an alias at the sametime for ease of use.



    ////Now we can add shape to our ShapeComponent. AddShape - method works intuitively. As we now
    ////add three points, AddShape knows we are making a triangle.



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



    //Bullets:

#if 1

    auto& bullet = myScene.AddEntity("Bullet");

    auto& bulletToShoot = bullet.AddComponent<jej::TransformComponent>(
        jej::Vector2f(0.f, -0.75f),		//Position, we start at center of the screen
        jej::Vector2f(1.f, 1.f),		//Scale in x, y - axises
        jej::Vector4f(0.f, 0.f, 0.f, 0.f)//Rotation x, y, z, w
        );

    bullet.AddComponent<jej::ShaderComponent>(
        "PixelShader.frag",			//First we must give vertex shader name and file extension
        "VertexShader.vert"			//Second we give fragment shader name and file extension
        );


    auto& bulletTex = bullet.AddComponent<jej::TextureComponent>(
        bullet.AddComponent<jej::ShapeComponent>
        (
        jej::Vector4i(0, 255, 0, 150)
        ).AddShape(
        jej::Vector2f(0.025f, 0.02f)
        ).GetID()
        );

    bulletTex.AddImage("JEJDemoSheet.png", jej::Vector2i(2, 2));
    bulletTex.UseImage(2);


    bullet.AddComponent<jej::RenderComponent>();
    bullet.AddComponent<jej::CollisionComponent>();

#endif



    //Player
#if 1
    auto& player = myScene.AddEntity("Player");


    ////Start adding components to our entity
    ////Entity has template method AddComponent which allows you to add all kinds of components
    ////AddComponent takes as typename a component name that is available with jej::SomeComponent - style syntax
    ////Every different component has a different parameter list so be sure what you're giving to your component
    ////In this example, TransformComponent is created as parameter of Entity's AddComponent - method and is then added 
    ////to myCharacter:



    auto& PlayerShapeComponent = player.AddComponent<jej::ShapeComponent>(
        jej::Vector4i(0, 255, 0, 150)	//This our shape's color in RGBA, so this is fully green and somewhat opaque
        );

    ////Creating:
    player.AddComponent<jej::TransformComponent>(
        jej::Vector2f(0.25f, -0.75f),		//Position, we start at center of the screen
        jej::Vector2f(1.f, 1.f),		//Scale in x, y - axises
        jej::Vector4f(0.f, 0.f, 0.f, 0.f)//Rotation x, y, z, w
        );

    ;

    auto& playerTex = player.AddComponent<jej::TextureComponent>(
        PlayerShapeComponent.AddShape(
        jej::Vector2f(0.05f, 0.05f)		//Second point, upper-right corner
        ).GetID()
        );

    playerTex.AddImage("JEJDemoSheet.png", jej::Vector2i(2, 2));
    playerTex.UseImage(1);


    ////Next we create ShaderComponent and add it to our entity so it can be drawn
    player.AddComponent<jej::ShaderComponent>(
        "PixelShader.frag",			//First we must give vertex shader name and file extension
        "VertexShader.vert"			//Second we guve fragment shader name and file extencion
        );

    ////Creating
    player.AddComponent<jej::RenderComponent>();

    ////Don't try setting components to other entities other than the one calling the function

    //player.AddComponent<jej::CollisionComponent>();

#endif



    //Enemies:
    //Creates as many enemies as enemyNumber is

    //ENEMIES
#if 1

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
                jej::Vector2f(-0.5f + (float)i / 9.5f, 0.45f + (float)j / 5)
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
            auto& tex = enemy.AddComponent<jej::TextureComponent>(enemyShapeComp.AddShape(
                jej::Vector2f(-0.04f, 0.04f)
                ).GetID());
            tex.AddImage("JEJDemoSheet.png", jej::Vector2i(2, 2));
            tex.UseImage(0);


            //Adds the possibility to draw current enemy
            enemy.AddComponent<jej::RenderComponent>();
            enemy.AddComponent<jej::CollisionComponent>();
        }
    }

#endif


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
    bool bt = true;
    game.Finalize();
    bool loop = true;
    float deltaTime;
    while (loop)
    {
        deltaTime = myTimer.GetTime();

        game.EngineUpdate();



        bulletTex.UseImage(static_cast<unsigned char>(bt) );
        bt = !bt;


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
            bulletToShoot.position = player.GetComponentPtr<jej::TransformComponent>()->position;
            bulletToShoot.velocity.y = 0.02f;
        }

        auto kek = myScene.GetEntities("Enemy");

        for (const auto& itr : kek)
        {
            auto& enemyPosition = itr->GetComponentPtr<jej::TransformComponent>()->position;

            //end game if enemy through
            if (enemyPosition.y < -0.8f)
            {
                loop = false;
            }



            if (!itr->userData)
            {
                enemyPosition.x += -0.5f * deltaTime;

                if (enemyPosition.x < -1)
                {
                    for (unsigned char i = 0u; i < kek.size(); ++i)
                    {
                        //EnemyMove = true;
                        enemyPosition.x = -1.f;
                        kek[i]->userData = (void*)true;
                    }

                    for (unsigned char i = 0u; i < kek.size(); ++i)
                    {
                        kek[i]->GetComponentPtr<jej::TransformComponent>()->position.y -= 0.15f;
                    }
                }

            }

            else if (itr->userData)
            {
                enemyPosition.x += 0.5f * deltaTime;

                if (enemyPosition.x > 1)
                {

                    for (unsigned char i = 0u; i < kek.size(); ++i)
                    {
                        //EnemyMove = false;
                        enemyPosition.x = 1.f;
                        kek[i]->userData = (void*)false;
                    }

                    for (unsigned char i = 0u; i < kek.size(); ++i)
                    {
                        kek[i]->GetComponentPtr<jej::TransformComponent>()->position.y -= 0.15f;
                    }
                }
            }


            if (itr->GetComponentPtr<jej::CollisionComponent>()->IsColliding)
            {
                myScene.RemoveEntity(itr->GetID());
            }

        }

        if (keyboard.IsKeyPressed(jej::Keyboard::Key::Escape))
            loop = false;

        //break;
        //std::cout << mouse.GetMousePosition().x << "   " << mouse.GetMousePosition().y << std::endl;

    }

    return 0;
}