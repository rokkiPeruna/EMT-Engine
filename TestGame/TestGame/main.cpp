
#include <Core/EngineObject.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>

#include <EntityComponentSys/Systems/System.hpp>
#include <Core/Scene.hpp>

#include <Utility/Random.hpp>

#include <Utility/FileHandler.hpp>

#include <EntityComponentSys/Components/ShaderComponent.hpp>

int main(int argc, char* argv[])
{
    jej::EngineObject::Initialize(argv[0]);
    auto& game = jej::EngineObject::GetInstance();

    jej::Scene gameLevel;

    game.SetCurrentScene(gameLevel);

    gameLevel.AddEntity("player1");



    {

        auto& box = gameLevel.AddEntity("boxToCopy");
        auto& transform = box.AddComponent<jej::TransformComponent>(
            jej::Vector2f(1.f, 2.f),
            jej::Vector2f(3.f, 4.f),
            jej::Vector4f(5.f, 6.f, 7.f, 8.f)
            );

        std::vector<jej::Entity*> myTower;

        for (unsigned int i = 0u; i < 10u; ++i)
        {
            myTower.emplace_back(&gameLevel.AddEntity());
            myTower.back()->AddComponent<jej::RenderComponent>(*box.GetComponentPtr<jej::TransformComponent>());
            myTower.back()->GetComponentPtr<jej::TransformComponent>()->position.x += i + 1u;
        }






    }




    auto* playeri = gameLevel.GetEntityPtr("player1");

    playeri->AddComponent<jej::TransformComponent>(
        jej::Vector2f(3.f, 5.f),
        jej::Vector2f(1.f, 1.f),
        jej::Vector4f(9.f, 2.f, 50.f, 1.f));

    auto& shaderRef = playeri->AddComponent<jej::ShaderComponent>("FragmentShaderTexture.frag");
    auto* shaderPtr = playeri->GetComponentPtr<jej::ShaderComponent>();

    auto& renderRef = playeri->AddComponent<jej::RenderComponent>();

    //auto* transvormi = playeri->GetComponentPtr<jej::TransformComponent>();
    //
    //bool on = playeri->HasComponent<jej::TransformComponent>();
    //
    //transvormi->position.x += transvormi->position.x;


    for (;;)
    {
        game.EngineUpdate();
        break;
    }

    return 0;
}