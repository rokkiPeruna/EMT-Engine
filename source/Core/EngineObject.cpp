

#include <Core/EngineObject.hpp>

#include <EntityComponentSys/Components/Component.hpp>
#include <EntityComponentSys/Entity/Entity.hpp>
#include <Graphics/OGL_ES2.hpp>
#include <Utility/Assert.hpp>
#include <Utility/Messenger.hpp>
#include <Window/Win32Window.hpp>

#include <EntityComponentSys/Systems/RenderSystem.hpp>
#include <EntityComponentSys/Systems/TransformSystem.hpp>

namespace jej //NAMESPACE jej
{
    EngineObject::EngineObject() :
        m_currentScene(nullptr),
        m_graphicsPtr(nullptr),
        m_windowPtr(nullptr)
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
        if (componentLeak != 0)
            Messenger::Add(Messenger::MessageType::Warning, "Amount of leaking components: ", componentLeak);

        if (entityLeak != 0)
            Messenger::Add(Messenger::MessageType::Warning, "Amount of leaking components: ", entityLeak);

        Messenger::WriteLog();
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
        auto& engine = GetInstance();

        //TODO:
        //Initialize all systems here
		std::get<0>(engine.m_systems) = &RenderSystem::GetInstance();
        std::get<1>(engine.m_systems) = &TransformSystem::GetInstance();


        //Parse execution path
        const unsigned int slashPos = p_root.find_last_of("/\\");
        if (slashPos == std::string::npos)
            Messenger::Add(Messenger::MessageType::Error, "Bad root: ", p_root);
        settings::rootPath = p_root.substr(0u, slashPos + 1u);

        //Initialize window and graphics
        engine.m_windowPtr.reset(new Win32Window(p_data, p_osData));
        engine.m_graphicsPtr.reset(new OGL_ES2(engine.m_windowPtr, settings::attributeList));

        return true;
    }
    //////////////////////////////////////////

    void EngineObject::EngineDraw()
    {
        m_graphicsPtr->_drawAll();
    }
    //////////////////////////////////////////

    void EngineObject::EngineUpdate()
    {
        m_graphicsPtr->_updateBuffersAll();
    }
    //////////////////////////////////////////

    std::shared_ptr<Graphics>& EngineObject::GetGraphicsRef()
    {
        return m_graphicsPtr;
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


} //NAMESPACE jej