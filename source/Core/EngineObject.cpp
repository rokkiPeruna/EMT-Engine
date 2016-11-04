

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

	bool EngineObject::Initialize(const std::string& root)
	{
		auto& engine = getInstance();

		engine.m_graphicsPtr = std::make_unique<Graphics>();
		engine.m_windowPtr = std::make_unique<Window>();

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