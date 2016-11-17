#ifndef JEJ_BASESTRUCTS_HPP
#define JEJ_BASESTRUCTS_HPP

namespace jej
{
    enum  ComponentType
    {
        //This is TransformComponent, it takes daadiidaa...
        Transform,
		Shader
    };

    //Vector of two floats
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

    //Vector of three floats
    struct Vector3f
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Vector3f(){};
        Vector3f(const float p_x, const float p_y, const float p_z)
        {
            x = p_x;
            y = p_y;
            z = p_z;
        };
    };

    //Vector of four floats
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
}

#endif