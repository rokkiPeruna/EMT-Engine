
#include <Core/EngineObject.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <EntityComponentSys/Components/TransformComponent.hpp>

#include <EntityComponentSys/Systems/System.hpp>
#include <Core/Scene.hpp>

#include <Utility/Random.hpp>

int main(int argc, char* argv[])
{
    jej::EngineObject::Initialize(argv[0]);
    auto& game = jej::EngineObject::GetInstance();

    jej::Scene gameLevel;

    gameLevel.AddEntity("player1");


    auto* playeri = gameLevel.GetEntityPtr("player1");

    playeri->AddComponent(jej::ComponentType::Transform,
        jej::Vector2f(3.f, 5.f),
        jej::Vector2f(1, 1),
        jej::Vector4f(9, 2, 50, 1));


    auto* transvormi = playeri->GetComponentPtr<jej::TransformComponent>(jej::ComponentType::Transform);




   // editor.AddComponent<jej::TransformComponent>(player, jej::ComponentType::Transform,
   //     jej::Vector2f(3.f, 5.f),
   //     jej::Vector2f(1, 1),
   //     jej::Vector4f(9, 2, 50, 1));


    

    //bool on = editor.HasComponent(player, jej::ComponentType::Transform);

    //auto transvormi = editor.GetComponentPtr<jej::TransformComponent>(player, jej::ComponentType::Transform);

    //transvormi->position.x += transvormi->position.x;

    return 0;
}