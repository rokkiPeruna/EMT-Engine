#ifndef JEJ_SPRITESYSTEM_HPP
#define JEJ_SPRITESYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>

namespace jej
{

    class SpriteComponent;
    class SpriteSystem :public System
    {

        //For modifying m_components
        friend class Entity;

        //For modifying m_components
        friend class System;

    private:
        //Singleton Constructor
        SpriteSystem();

    public:
        //Destructor
        virtual ~SpriteSystem();
        //Get Instance
        static SpriteSystem& GetInstance();

    protected:
        std::vector<std::shared_ptr<SpriteComponent>>m_components;
        void update(const float p_deltaTime) override;

    };
}

#endif