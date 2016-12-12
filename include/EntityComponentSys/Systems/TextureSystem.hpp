#ifndef JEJ_TEXTURE_SYSTEM_HPP
#define JEJ_TEXTURE_SYSTEM_HPP

#include <EntityComponentSys/Systems/System.hpp>
#include <EntityComponentSys/Components/TextureComponent.hpp>
#include <External/OpenGL_ES2/EGL/eglplatform.h>
#include <External/OpenGL_ES2/GLES2/gl2.h>


namespace jej
{

    class TextureSystem : public System
    {
        friend class TextureComponent;

        //For modifying m_components
        friend class Entity;
        friend class EngineObject;
        friend class System;

    private:

        //Singleton constructor
        TextureSystem();

    public:

        //Disabled copy-constructors
        NOCOPY(TextureSystem);

        //Destructor
        virtual ~TextureSystem();

        // Get the one and only instance of singleton 
        static TextureSystem& GetInstance();

    protected:

        static std::vector<std::shared_ptr<TextureComponent>> m_components;

        // Load images for components
        bool _finalize() override;

        // Initialize texturesystem (don't load images here! not present yet)
        bool _initialize() override;

        //Update
        void _update(const float p_deltaTime) override;


    private:

        //Bind texture
        void _bindImage(TextureComponent* p_component);

        //SpriteSheet stuff
        void _drawFromSheet(TextureComponent* p_component);
        
        //Font stuff
        void _fontStuff();


        

    };

}

#endif