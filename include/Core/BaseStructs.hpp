#ifndef JEJ_BASESTRUCTS_HPP
#define JEJ_BASESTRUCTS_HPP



namespace jej
{
    
    //For ComponentHelper
	class RenderComponent;
	class ShaderComponent;
	class ShapeComponent;
	class TransformComponent;


#ifdef JEJ_USE_MAX
    typedef unsigned long long int JEJ_COUNT;
#elif defined JEJ_USE_LARGE
    typedef unsigned long int JEJ_COUNT;
#elif defined JEJ_USE_MIN
    typedef unsigned short int JEJ_COUNT;
#else
    typedef unsigned int JEJ_COUNT;
#endif



    enum class ComponentType : unsigned short int
    {
        Failure,
        Transform,
        Render,
		Shader,
        Shape
    };
    

    //TODO: Specialize all components here with increasing indices

    template <typename T>
    struct ComponentHelper{};

	template <>
	struct ComponentHelper<RenderComponent>
	{
		static const unsigned short int index = 0u;
	};


	/*template <>
	struct ComponentHelper<ShaderComponent>
	{
		static const unsigned short int index = 3u;
	};

	template <>
	struct ComponentHelper<ShapeComponent>
	{
		static const unsigned short int index = 2u;
	};*/

    template <>
    struct ComponentHelper<TransformComponent>
    {
        static const unsigned short int index = 1u;
    };

	




	enum class ShapeType
	{
		Circle,
		Rectangle,
		Convex,
		Triangle
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