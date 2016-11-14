#ifndef JEJ_RENDER_SYSTEM_HPP
#define JEJ_RENDER_SYSTEM_HPP

//
#include <EntityComponentSys/Systems/System.hpp>
//

//
#include <memory>
//

namespace jej
{
    //Forward declarating Window-class etc.
    class Window;
    class RenderComponent;
    //

    class RenderSystem
        :public System
    {

    private:
        //Constructor is private for singleton
        RenderSystem();

    public:

        //Disabled copy-constructors
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem operator=(const RenderSystem&) = delete;

        //Destructor
        ~RenderSystem();

        //Create instance of class
        static RenderSystem& GetInstance();

        //This renders and draws every RenderComponent
        void Update();

    protected:

        std::vector<std::shared_ptr<RenderComponent>> m_components;

        std::shared_ptr<Window> m_window;
    };
}

#endif