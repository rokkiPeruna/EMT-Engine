#ifndef JEJ_ENGINEOBJECT_HPP
#define JEJ_ENGINEOBJECT_HPP

#include <memory>
#include <string>
#include <tuple>

namespace jej //NAMESPACE jej
{

	class Graphics;
    class Scene;
	class Window;

    struct WindowBaseInitData;
    struct WindowOSInitData;

    class TransformSystem;

	class EngineObject
	{

        friend class Win32Window;
        
        //For accessing m_system
        friend class Entity;

        //For accessing m_system
        friend class System;

	private:

		//Constructor
		EngineObject();

	public:

		//Return engine
		static EngineObject& GetInstance();

		//Initialize engine, should be first call in main
		static bool Initialize(const std::string& p_root, const WindowBaseInitData* p_data = nullptr, const WindowOSInitData* p_osData = nullptr);

		//Disabled copy-constructors, there should be only one EngineObject during the entire process
		EngineObject(const EngineObject&) = delete;
		EngineObject operator=(const EngineObject&) = delete;

		//Destructor
		~EngineObject();

		//Draw everything
		void EngineDraw();

		//Mother of all updates
		void EngineUpdate();

		std::shared_ptr<Graphics>& GetGraphicsRef();
        std::shared_ptr<Scene>& GetSceneRef();
        std::shared_ptr<Window>& GetWindowRef();
        

	private:

        //TODO Add all systems
        //Pointer to each system, populated in Initialize
        std::tuple<TransformSystem*> m_systems;

        std::shared_ptr<Scene> m_currentScene;
		std::shared_ptr<Graphics> m_graphicsPtr;
        std::shared_ptr<Window> m_windowPtr;

	};

} //NAMESPACE jej

#endif 