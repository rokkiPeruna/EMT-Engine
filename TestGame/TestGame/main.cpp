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

	//Tämän tästä muutimme
	//int 2 = 5;

    //Create new EngineObject, initialize it and get alias handle to it
    jej::Window::WindowBaseInitData data;
    data.nameWindow = L"Jejuna Engine demo";
    data.sizeX = 1700;
    data.sizeY = 800;

    jej::Window::WindowOSInitData osdata;
    osdata.offsetX = 80;
    osdata.offsetY = 80;

    if (!jej::EngineObject::Initialize(argv[0], &data, &osdata))
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

    const unsigned char bulletCount = 5u;

    for (signed char i = 0; i < bulletCount; ++i)
    {
        auto& bullet = myScene.AddEntity("Bullet " + std::to_string(i));

        bullet.AddComponent<jej::TransformComponent>(
            jej::Vector2f(static_cast<float>(i), 1.75f),		//Position
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

        bulletTex.AddImage("bullets.png", jej::Vector2i(3, 4));
        bulletTex.UseImage(2);


        bullet.AddComponent<jej::RenderComponent>();
        bullet.AddComponent<jej::CollisionComponent>();
    }

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

#endif


    //ENEMIES
#if 1

    const char enemyNumber = 10;
    const char rows = 3;

    for (signed char j = 0; j < rows; ++j)
    {

        for (signed char i = 0; i < enemyNumber; ++i)
        {
            //Adds single enemy to the scene
            myScene.AddEntity("Enemy " + std::to_string(j) + " " + std::to_string(i));

            auto& enemy = *myScene.GetEntityPtr("Enemy " + std::to_string(j) + " " + std::to_string(i));


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

    //Prepare for gameloop
#if 1 
    
    game.Finalize();
    
    const auto& keyboard = jej::Keyboard::GetInstance();

    std::vector<jej::TextureComponent*> bulletTextures;
    std::vector<jej::CollisionComponent*> bulletCollisions;
    std::vector<jej::TransformComponent*> bulletTransforms;

    for (const auto& itr : myScene.GetEntities("Bullet"))
    {
        bulletCollisions.emplace_back(itr->GetComponentPtr<jej::CollisionComponent>());
        bulletTextures.emplace_back(itr->GetComponentPtr<jej::TextureComponent>());
        bulletTransforms.emplace_back(itr->GetComponentPtr<jej::TransformComponent>());
    }

    std::vector<jej::Entity*> enemies = myScene.GetEntities("Enemy");

    static const float enemyVel = 0.008f;
    for (const auto& itr : enemies)
    {
        itr->GetComponentPtr<jej::TransformComponent>()->velocity.x = enemyVel;
    }

    static const float bulletCD = 0.75f;
    unsigned char shootThisBullet = 0u;
    unsigned char bulletTexIndex = 0u;
    const float deltaTime = 1.f / 60.f;
    bool loop = true;

    while (true)
    {
        if (keyboard.IsKeyPressed(jej::Keyboard::Key::Return))
        {
            break;
        }
    }


    jej::Timer myTimer(true);
    jej::Timer bulletTimer(true);

#endif


    //Gameloop
#if 1

    while (loop)
    {

        game.EngineUpdate();

        if (myTimer.GetTime() > deltaTime)
        {
            bulletTexIndex == 11u ? bulletTexIndex = 0u : ++bulletTexIndex;
            for (const auto& itr : bulletTextures)
            {
                itr->UseImage(bulletTexIndex);
            }

            auto& playerPos = player.GetComponentPtr<jej::TransformComponent>()->position.x;

            if (keyboard.IsKeyPressed(jej::Keyboard::Key::A))
            {
                playerPos -= 0.02f;
            }
            else if (keyboard.IsKeyPressed(jej::Keyboard::Key::D))
            {
                playerPos += 0.02f;
            }
            if (keyboard.IsKeyPressed(jej::Keyboard::Key::Space))
            {
                if (bulletCD < bulletTimer.GetTime())
                {
                    bulletTransforms[shootThisBullet]->position = player.GetComponentPtr<jej::TransformComponent>()->position;
                    bulletTransforms[shootThisBullet]->velocity.y = 0.02f;
                    shootThisBullet == 4u ? shootThisBullet = 0u : ++shootThisBullet;
                    bulletTimer.Reset();
                }
            }
            if (keyboard.IsKeyPressed(jej::Keyboard::Key::Escape))
            {
                loop = false;
            }

            playerPos < -1.f ? playerPos = -1.f : playerPos > 1.f ? playerPos = 1.f : NULL;

            
            enemies = myScene.GetEntities("Enemy");

            for (const auto& itr : enemies)
            {
                auto& enemyPosition = itr->GetComponentPtr<jej::TransformComponent>()->position.x;

                if (enemyPosition < -1)
                {
                    for (const auto& itr2 : enemies)
                    {
                        auto* tra = itr2->GetComponentPtr<jej::TransformComponent>();
                        tra->velocity.x = enemyVel;
                        tra->position.y < -0.5f ? loop = false : tra->position.y -= 0.15f;

                    }
                    break;
                }
                else if (enemyPosition > 1)
                {
                    for (const auto& itr2 : enemies)
                    {
                        auto* tra = itr2->GetComponentPtr<jej::TransformComponent>();
                        tra->velocity.x = -enemyVel;
                        tra->position.y < -0.5f ? loop = false : tra->position.y -= 0.15f;
                    }
                    break;
                }
            }


            for (const auto& itrRemove : enemies)
            {
                if (itrRemove->GetComponentPtr<jej::CollisionComponent>()->IsColliding)
                {
                    myScene.RemoveEntity(itrRemove->GetID());
                }
            }

            myTimer.Reset();
        }
    }
#endif

    return 0;
}