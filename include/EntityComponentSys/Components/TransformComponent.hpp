#ifndef JEJ_TRANSFROM_COMPONENT_HPP
#define JEJ_TRANSFROM_COMPONENT_HPP

//
#include <EntityComponentSys/Components/Component.hpp>
//

#include <Core/BaseStructs.hpp>

namespace jej
{


    class TransformComponent : public Component
    {

    public:
        
        //Default constructor
        TransformComponent(Entity* entity, const Vector2f& p_position = Vector2f(), const Vector2f& p_scale = Vector2f(), const Vector4f& p_rotation = Vector4f());

        //Copy-constructor //TODO: This is not a copy constructor!!
        //TransformComponent(Entity& entity, const Vector2f& p_position, const Vector2f& p_scale, const Vector4f& p_rotation);

		//Copy constructor for TransformComponent. This keeps owner Entity as same as from which it is copied.
		//User must handle entity owner swap if needed.
		TransformComponent(Entity* entity, const TransformComponent& p_toCopy);

        //Destructor
        virtual ~TransformComponent();

        //Variables
        Vector2f position;
        Vector2f scale;
        Vector4f rotation;

    };
}



#endif