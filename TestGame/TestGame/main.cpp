
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

    gameLevel.AddEntity("player1");


    auto* playeri = gameLevel.GetEntityPtr("player1");

    playeri->AddComponent<jej::TransformComponent>(
        jej::Vector2f(3.f, 5.f),
        jej::Vector2f(1, 1),
        jej::Vector4f(9, 2, 50, 1));


    //	playeri->AddComponent<jej::ShaderComponent>();

    //auto* transvormi = playeri->GetComponentPtr<jej::TransformComponent>();
    //
    //bool on = playeri->HasComponent<jej::TransformComponent>();
    //
    //transvormi->position.x += transvormi->position.x;

    for (;;)
    {
        //game.EngineUpdate();
        break;
    }

    return 0;
}