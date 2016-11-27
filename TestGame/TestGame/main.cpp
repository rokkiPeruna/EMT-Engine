
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
    jej::EngineObject::Initialize(argv[0]);
    auto& game = jej::EngineObject::GetInstance();

    jej::Scene gameLevel;

    gameLevel.AddEntity("player1");


    auto* playeri = gameLevel.GetEntityPtr("player1");

    playeri->AddComponent<jej::TransformComponent>(
        jej::Vector2f(3.f, 5.f),
        jej::Vector2f(1, 1),
        jej::Vector4f(9, 2, 50, 1));

    auto& shaderRef = playeri->AddComponent<jej::ShaderComponent>("FragmentShaderTexture.frag");
    auto* shaderPtr = playeri->GetComponentPtr<jej::ShaderComponent>();

    auto& renderRef = playeri->AddComponent<jej::RenderComponent>();

    //auto* transvormi = playeri->GetComponentPtr<jej::TransformComponent>();
    //
    //bool on = playeri->HasComponent<jej::TransformComponent>();
    //
    //transvormi->position.x += transvormi->position.x;

	auto& mouse = jej::Mouse::GetInstance();
	auto& keyboard = jej::Keyboard::GetInstance();

    for (;;)
    {
        game.EngineUpdate();
        break;
		//std::cout << mouse.GetMousePosition().x << "   " << mouse.GetMousePosition().y << std::endl;
		
    }

    return 0;
}