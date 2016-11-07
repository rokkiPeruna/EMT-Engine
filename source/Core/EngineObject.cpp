

#include <Core/EngineObject.hpp>

#include <Graphics/OGL_ES2.hpp>
#include <Window/Win32Window.hpp>


namespace jej //NAMESPACE jej
{

    EngineObject::EngineObject() :
        m_graphicsPtr(nullptr),
        m_windowPtr(nullptr)
    {

    }
    //////////////////////////////////////////

    EngineObject::~EngineObject()
    {

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

        settings::rootPath = p_root;

        engine.m_windowPtr = std::make_shared<Win32Window>(Win32Window(p_data, p_osData));
        engine.m_graphicsPtr = std::make_shared<OGL_ES2>(OGL_ES2(engine.m_windowPtr, settings::attributeList));


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

    std::shared_ptr<Window>& EngineObject::GetWindowRef()
    {
        return m_windowPtr;
    }
    //////////////////////////////////////////


} //NAMESPACE jej