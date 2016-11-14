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
        TransformComponent(const JEJ_COUNT p_parentID);

        //Copy-constructor
        TransformComponent(const JEJ_COUNT p_parentID, const Vector2f& p_position, const Vector2f& p_scale, const Vector4f& p_rotation);

        //Destructor
        virtual ~TransformComponent();

        //Variables
        Vector2f position;
        Vector2f scale;
        Vector4f rotation;

    };
}



#endif