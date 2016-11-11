
#include <Core/EngineObject.hpp>
#include <EntityComponentSys/Entity.hpp>
#include <TransformComponent.hpp>

#include <Systems/System.hpp>

int main(int argc, char* argv[])
{
    jej::System::_transformCont.reserve(1000);

    jej::Entity player;

    player.AddComponent(jej::ComponentType::Transform,
     jej::Vector2f(0.f,0.f),
     jej::Vector2f(1, 1),
     jej::Vector4f(0, 0, 50, 0));

     
        
    jej::EngineObject::Initialize(argv[0]);

    return 0;
}