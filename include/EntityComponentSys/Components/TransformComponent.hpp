#ifndef JEJ_TRANSFROM_COMPONENT_HPP
#define JEJ_TRANSFROM_COMPONENT_HPP

//
#include <EntityComponentSys/Components/Component.hpp>
//

#include <Core/BaseStructs.hpp>

namespace jej
{

    class Entity;

    class TransformComponent : public Component
    {

    public:

        //Default constructor
        TransformComponent(Entity* entity, const Vector2f& p_position = Vector2f(), const Vector2f& p_scale = Vector2f(), const Vector4f& p_rotation = Vector4f());

        //Disabled copy-constructors
        NOCOPY(TransformComponent);

        //Destructor
        virtual ~TransformComponent();

        //Variables
        Vector2f position;
        Vector2f scale;
        Vector4f rotation;

        //For handling collision etc.
        Vector2f previousPosition;
        Vector2f previousScale;
        Vector4f previousRotation;

		//
		Vector2f velocity;
		Vector2f previousVelocity;

        //For checking if any transform quality has changed
        bool hasChanged;

    };
}



#endif