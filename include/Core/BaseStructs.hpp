#ifndef JEJ_BASESTRUCTS_HPP
#define JEJ_BASESTRUCTS_HPP

namespace jej
{

    //For ComponentHelper
    class CollisionComponent;
    class RenderComponent;
    class ShaderComponent;
    class ShapeComponent;
    class TextureComponent;
    class TransformComponent;


#ifdef JEJ_USE_MAX
    using  JEJ_COUNT = unsigned long long int;
#elif defined JEJ_USE_LARGE
    using  JEJ_COUNT = unsigned long int;
#elif defined JEJ_USE_MIN
    using  JEJ_COUNT= unsigned short int;
#else
    using  JEJ_COUNT = unsigned int;
#endif


    enum class ComponentType : unsigned short int
    {
        Failure,
        Render,
        Shader,
        Shape,
        Texture,
        Transform
    };


    //TODO: Specialize all components here with increasing indices

    template <typename T>
    struct ComponentHelper
    {
#ifdef _WIN32
        ComponentHelper<T>(){ static_assert(false, "Invalid ComponentHelper type."); };
#endif
    };

    template <>
    struct ComponentHelper<CollisionComponent>
    {
        static const unsigned short int index = 0u;
        ComponentHelper<CollisionComponent>(){};
    };

    template <>
    struct ComponentHelper<RenderComponent>
    {
        static const unsigned short int index = 1u;
        ComponentHelper<RenderComponent>(){};
    };

    template <>
    struct ComponentHelper<ShaderComponent>
    {
        static const unsigned short int index = 2u;
        ComponentHelper<ShaderComponent>(){};
    };

    template <>
    struct ComponentHelper<ShapeComponent>
    {
        static const unsigned short int index = 3u;
        ComponentHelper<ShapeComponent>(){};
    };

    template <>
    struct ComponentHelper<TextureComponent>
    {
        static const unsigned short int index = 4u;
        ComponentHelper<TextureComponent>(){};
    };

    template <>
    struct ComponentHelper<TransformComponent>
    {
        static const unsigned short int index = 5u;
        ComponentHelper<TransformComponent>(){};
    };


    enum class ShapeType
    {
        Failed,
        Circle,
        Rectangle,
        Convex,
        Triangle
    };


    //Vector of two ints
    struct Vector2i
    {
        int x = 0;
        int y = 0;

        Vector2i(){};
        Vector2i(const int p_x, const int p_y)
        {
            x = p_x;
            y = p_y;
        };
    };

    //Vector of three ints
    struct Vector3i
    {
        int x = 0;
        int y = 0;
        int z = 0;

        Vector3i(){};
        Vector3i(const int p_x, const int p_y, const int p_z)
        {
            x = p_x;
            y = p_y;
            z = p_z;
        };
    };

    //Vector of four ints
    struct Vector4i
    {
        int x = 0;
        int y = 0;
        int z = 0;
        int w = 0;

        Vector4i(){};
        Vector4i(const int p_x, const int p_y, const int p_z, const int p_w)
        {
            x = p_x;
            y = p_y;
            z = p_z;
            w = p_w;
        };
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