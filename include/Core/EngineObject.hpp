#ifndef JEJ_ENGINEOBJECT_HPP
#define JEJ_ENGINEOBJECT_HPP

#include <Core/Settings.hpp>
#include <Core/BaseStructs.hpp>

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#ifdef __ANDROID__
#include <android_native_app_glue.h>
#endif

struct android_app;

namespace jej //NAMESPACE jej
{

    class Graphics;
    class Scene;
    class Window;

    struct WindowBaseInitData;
    struct WindowOSInitData;

    //For m_systems tuple
    class CollisionSystem;
    class RenderSystem;
    class ShaderSystem;
    class ShapeSystem;
    class TextureSystem;
    class TransformSystem;

    class EngineObject
    {

        friend class Win32Window;

        //For accessing m_system
        friend class Entity;

        //For accessing m_system
        friend class System;

        //For adding components to RenderComponents m_shader, m_shape, m_transform
        friend class RenderComponent;

    private:

        //Constructor
        EngineObject();

    public:

        //Return engine
        static EngineObject& GetInstance();

        //Initialize engine, should be first call in main
        static bool Initialize(const std::string& p_root, const WindowBaseInitData* p_data = nullptr, const WindowOSInitData* p_osData = nullptr);

        //Finalize method, must be called prior to EngineUpdate
        static bool Finalize();

        //Disabled copy-constructors, there should be only one EngineObject during the entire process
        NOCOPY(EngineObject);

        //Destructor
        ~EngineObject();

        //Set m_scene 
        //void SetCurrentScene(const Scene& p_scene);

        //Mother of all updates
        void EngineUpdate();

		Scene* CreateScene(const bool p_active, const std::string& p_name = "");

		Scene* SetCurrentScene(const JEJ_COUNT p_ID);

		Scene* GetCurrentScene();
		const Scene* GetCurrentScene() const;

		bool RemoveScene(const JEJ_COUNT p_ID);

        std::shared_ptr<Graphics>& GetGraphicsRef();
        std::shared_ptr<Scene>& GetSceneRef();
		const std::shared_ptr<Scene>& GetSceneRef() const; 


		std::shared_ptr<Window>& GetWindowRef();



        //#ifdef JEJ_DEBUG_MODE
        std::vector<unsigned int> _getAllCompIDs() const;
        //#endif

    private:

        //TODO Add all systems
        //Pointer to each system, populated in Initialize
        std::tuple<CollisionSystem*, RenderSystem*, ShaderSystem*, ShapeSystem*, TextureSystem*, TransformSystem*> m_systems;

		std::vector<std::shared_ptr<Scene>> m_scenes;
        std::shared_ptr<Window> m_windowPtr; 

		JEJ_COUNT m_currentSceneID;


    };

} //NAMESPACE jej

#endif 