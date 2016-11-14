#ifndef JEJ_TRANSFORM_SYSTEM_HPP
#define JEJ_TRANSFORM_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>

namespace jej
{

    //For m_components
    class TransformComponent;

    class TransformSystem : public System
    {

        //For modifying m_components
        friend class Entity;

    private:

        TransformSystem();

        static std::vector<std::shared_ptr<TransformComponent>> m_components;

    public:

        static TransformSystem& GetInstance();

        virtual ~TransformSystem();

        void update(const float deltaTime) override;

        

        

    };

}

#endif