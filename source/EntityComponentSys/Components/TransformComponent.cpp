#include <EntityComponentSys/Components/TransformComponent.hpp>



namespace jej
{
    TransformComponent::TransformComponent():
        Component()
    {
        
        
        //Give component it's right enum type, see Component.hpp for types
        _MyComponentType = static_cast<unsigned short int>(ComponentType::Transform);
    }
    //

    TransformComponent::~TransformComponent()
    {

    }
    //
}