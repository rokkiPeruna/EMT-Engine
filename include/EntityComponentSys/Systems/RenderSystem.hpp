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

    class RenderSystem : public System
    {

		//For manipulating m_components
		friend class EngineObject;
		friend class Entity;

    private:

        //Constructor is private for singleton
        RenderSystem();

		static std::vector<std::shared_ptr<RenderComponent>> m_components;

    public:

        //Disabled copy-constructors
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem operator=(const RenderSystem&) = delete;

        //Destructor
        ~RenderSystem();

        //Create instance of class
        static RenderSystem& GetInstance();

		

    protected:

		//This renders and draws every RenderComponent
		void update(const float p_deltaTime) override;

        std::shared_ptr<Window> m_window;
    };
}

#endif