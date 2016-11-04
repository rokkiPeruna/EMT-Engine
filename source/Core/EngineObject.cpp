

#include <Core/EngineObject.hpp>

#include <Graphics/GraphicsES2.hpp>
#include <Window/Window.hpp>


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

	EngineObject& EngineObject::getInstance()
	{
		static EngineObject engine;
		return engine;
	}
	//////////////////////////////////////////

	bool EngineObject::Initialize(const std::string& p_root, const WindowInitData& p_data = WindowInitData(), const WindowOSInitData& p_osData = WindowOSInitData())
	{
		auto& engine = getInstance();
		
		engine.m_windowPtr = std::make_shared<Window>(new Window(p_data, p_osData));
		engine.m_graphicsPtr = std::make_shared<Graphics>(new Graphics(engine.m_windowPtr));

	}
	//////////////////////////////////////////

	void EngineObject::EngineDraw()
	{
		m_graphicsPtr->drawAll();
	}
	//////////////////////////////////////////

	void EngineObject::EngineUpdate()
	{
		m_graphicsPtr->updateBuffersAll();
	}
	//////////////////////////////////////////


} //NAMESPACE jej