#ifndef JEJ_SPRITESYSTEM_HPP
#define JEJ_SPRITESYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>

namespace jej
{

    class TextureComponent;
    class TextureSystem :public System
    {

        //For modifying m_components
        friend class Entity;
        friend class EngineObject;
        friend class System;

    private:
        
        //Singleton constructor
        TextureSystem();

    public:
        
        //Destructor
        virtual ~TextureSystem();
        
        //Get instance
        static TextureSystem& GetInstance();

    protected:
        static std::vector<std::shared_ptr<TextureComponent>> m_components;
        void _update(const float p_deltaTime) override;

    };
}

#endif