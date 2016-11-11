#ifndef JEJ_TRANSFROM_COMPONENT_HPP
#define JEJ_TRANSFROM_COMPONENT_HPP

//
#include <EntityComponentSys/Components/Component.hpp>
//

namespace jej
{
        //These are positions for entity's pivot point
        struct Vector2f
        {
            float x = 0.0f;
            float y = 0.0f;

            Vector2f(){};
            Vector2f(const float p_x, const float p_y)
            {
                x = p_x;
                y = p_y;
            };
        };

        //These are entity's rotation angles in object coordinate system
        struct Vector4f
        {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
            float w = 0.0f;

            Vector4f(){};
            Vector4f(const float p_x, const float p_y, const float p_z, const float p_w)
            {
                x = p_x;
                y = p_y;
                z = p_z;
                w = p_w;
            };
        };

    class TransformComponent
        :public Component
    {

    public:
        //
        TransformComponent();

        //
        virtual ~TransformComponent();

        Vector2f position;
        Vector2f scale;
        Vector4f rotation;

    };
}



#endif