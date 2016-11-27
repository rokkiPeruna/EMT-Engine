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
        friend class EngineObject;
        friend class System;

    private:
        
        //Singleton constructor
        SpriteSystem();

    public:
        
        //Destructor
        virtual ~SpriteSystem();
        
        //Get instance
        static SpriteSystem& GetInstance();

    protected:
        static std::vector<std::shared_ptr<SpriteComponent>> m_components;
        void _update(const float p_deltaTime) override;

    };
}

#endif