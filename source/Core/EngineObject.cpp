

#include <Core/EngineObject.hpp>

#include <Core/Timer.hpp>

#include <IO_Manager/InputManagerImpl.hpp>


#include <EntityComponentSys/Components/Component.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <EntityComponentSys/Systems/CollisionSystem.hpp>
#include <EntityComponentSys/Systems/RenderSystem.hpp>
#include <EntityComponentSys/Systems/ShaderSystem.hpp>
#include <EntityComponentSys/Systems/TransformSystem.hpp>
#include <Graphics/OGL_ES2.hpp>
#include <Utility/Assert.hpp>
#include <Utility/Messenger.hpp>



#ifdef _WIN32
#include <Window/Win32Window.hpp>
#elif defined ANDROID
#include <Window/AndroidWindow.hpp>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#endif


namespace jej //NAMESPACE jej
{
    EngineObject::EngineObject() :
        m_currentScene(nullptr),
        m_windowPtr(nullptr),
        m_systems(
        &CollisionSystem::GetInstance(),
        &RenderSystem::GetInstance(),
        &ShaderSystem::GetInstance(),
        &ShapeSystem::GetInstance(),
        &TextureSystem::GetInstance(),
        &TransformSystem::GetInstance()
        )
    {

    }
    //////////////////////////////////////////

    EngineObject::~EngineObject()
    {

        //Zero if everything is ok.
        //Positive if something is not removed
        //Negative if something is removed too much
        const int componentLeak = Component::m_componentIDCounter - Component::m_componentIDRemovedCounter;
        const int entityLeak = Entity::m_entityIDCounter - Entity::m_entityIDRemovedCounter;

        //No leaks - no asserts
        JEJ_ASSERT(componentLeak == 0, "Component memory leak!");
        JEJ_ASSERT(entityLeak == 0, "Entity memory leak!");

        //No leaks - no warnings
        //TODO: Android problems
#ifdef _WIN32
        if (componentLeak != 0)
            Messenger::Add(Messenger::MessageType::Warning, "Amount of leaking components: ", componentLeak);

        if (entityLeak != 0)
            Messenger::Add(Messenger::MessageType::Warning, "Amount of leaking components: ", entityLeak);

        Messenger::Add(Messenger::MessageType::Debug, std::to_string(Timer::GetInstance().GetTime()));

        Messenger::WriteLog();

#endif
    }
    //////////////////////////////////////////

    EngineObject& EngineObject::GetInstance()
    {
        static EngineObject engine;
        return engine;
    }
    //////////////////////////////////////////

    bool EngineObject::Initialize(const std::string& p_root, const WindowBaseInitData* p_data, const WindowOSInitData* p_osData)
    {
        EngineObject& engine = GetInstance();

        //Initialize window
#ifdef _WIN32
        engine.m_windowPtr = std::make_shared<Win32Window>(p_data, p_osData);
#elif defined __ANDROID__
<<<<<<< HEAD
        engine.m_windowPtr.reset(new AndroidWindow(p_osData));
=======
        auto* window = &AndroidWindow::GetInstance();
        engine.m_windowPtr.reset(window);
>>>>>>> origin/JuhoAndroidBranch
#endif

<<<<<<< HEAD
        //TODO: Add Android InputManager code
=======
        //TODO: Add Android InputManager code so this works on both Win32 and Android
>>>>>>> origin/JuhoAndroidBranch
        //InputManager::GetInstance();

        //Parse execution path
        //TODO: Android problems
#ifdef _WIN32
        const unsigned int slashPos = p_root.find_last_of("/\\");
        if (slashPos == std::string::npos)
        {
            JEJ_ASSERT(false, "Bad root: Requires argv[0]");
            Messenger::Add(Messenger::MessageType::Error, "Bad root: ", p_root, "Requires argv[0]");
            return false;
        }
        settings::rootPath = p_root.substr(0u, slashPos + 1u);


        //Initialize minor areas
        InputManager::GetInstance();
        Timer::GetInstance(true);


        //TODO: Initialize all systems here
        if (
            std::get<0>(engine.m_systems)->_initialize() &&
            std::get<1>(engine.m_systems)->_initialize() &&
            std::get<2>(engine.m_systems)->_initialize() &&
            std::get<3>(engine.m_systems)->_initialize() &&
            std::get<4>(engine.m_systems)->_initialize() &&
            std::get<5>(engine.m_systems)->_initialize()
            )
        {
            return true;
        }


        return false;
    }
    //////////////////////////////////////////

    bool EngineObject::Finalize()
    {
        //TODO: Call finalize on all systems
        EngineObject& engine = EngineObject::GetInstance();
        if (
            std::get<0>(engine.m_systems)->_finalize() &&
            std::get<1>(engine.m_systems)->_finalize() &&
            std::get<2>(engine.m_systems)->_finalize() &&
            std::get<3>(engine.m_systems)->_finalize() &&
            std::get<4>(engine.m_systems)->_finalize() &&
            std::get<5>(engine.m_systems)->_finalize()
            )
            return true;
        return false;
    }

//    void EngineObject::SetCurrentScene(const Scene& p_scene)
//    {
//        //Doesn't work in future
//        DebugBreak();
//        m_currentScene = std::make_shared<Scene>(p_scene);
//    }
    //////////////////////////////////////////

    void EngineObject::EngineUpdate()
    {
        //TODO: Call update on all systems
        static EngineObject& engine = EngineObject::GetInstance();

        Timer& timer = Timer::GetInstance();
        const float deltaTime = timer.GetTime();
        if (deltaTime > 1.f / 60.f)
        {
            std::get<0>(engine.m_systems)->_update(deltaTime);
            std::get<1>(engine.m_systems)->_update(deltaTime);
            std::get<2>(engine.m_systems)->_update(deltaTime);
            std::get<3>(engine.m_systems)->_update(deltaTime);
            std::get<4>(engine.m_systems)->_update(deltaTime);
            std::get<5>(engine.m_systems)->_update(deltaTime);
            timer.Reset();
        }

        Messenger::PrintMessages();

        InputManager::GetInstance()._update();

        //This calls also RenderSystem's _update() - function in WM_PAINT

        m_windowPtr->UpdateWindowMessages();


    }
    //////////////////////////////////////////

    std::shared_ptr<Scene>& EngineObject::GetSceneRef()
    {
        return m_currentScene;
    }
    //////////////////////////////////////////

    std::shared_ptr<Window>& EngineObject::GetWindowRef()
    {
        return m_windowPtr;
    }
    //////////////////////////////////////////

#ifdef JEJ_DEBUG_MODE
    std::vector<unsigned int> EngineObject::_getAllCompIDs() const
    {
        std::vector<unsigned int> IDs;
        IDs.reserve(Component::m_componentIDCounter);

        for (const auto& itr : std::get<ComponentHelper<RenderComponent>::index>(m_systems)->m_components)
        {
            unsigned int id = itr->m_componentID;
            IDs.emplace_back(id);
        }
        for (const auto& itr : std::get<ComponentHelper<ShaderComponent>::index>(m_systems)->m_components)
        {
            unsigned int id = itr->m_componentID;
            IDs.emplace_back(id);
        }
        for (const auto& itr : std::get<ComponentHelper<ShapeComponent>::index>(m_systems)->m_components)
        {
            unsigned int id = itr->m_componentID;
            IDs.emplace_back(id);
        }
        for (const auto& itr : std::get<ComponentHelper<TextureComponent>::index>(m_systems)->m_components)
        {
            unsigned int id = itr->m_componentID;
            IDs.emplace_back(id);
        }
        for (const auto& itr : std::get<ComponentHelper<TransformComponent>::index>(m_systems)->m_components)
        {
            unsigned int id = itr->m_componentID;
            IDs.emplace_back(id);
        }

        return IDs;
    }
    //////////////////////////////////////////
#endif
    
#ifdef __ANDROID__
	//void EngineObject::SetAndroidApp(android_app* p_app)
	//{
	//	state = p_app;
	//}
#endif

} //NAMESPACE jej