#ifndef JEJ_COMPONENT_HPP
#define JEJ_COMPONENT_HPP

namespace jej
{
    enum class ComponentType
    {
        //This is TransformComponent, it takes daadiidaa...
        Transform = 1
    };

    class Component
    {
    public:
        //
        Component();

        //
        virtual ~Component();

        unsigned short int _MyComponentType;

        unsigned int ID;

    private:

        static unsigned int m_IDCounter;
        static unsigned int m_IDRemovedCounter;
    };
}


#endif