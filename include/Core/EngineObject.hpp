#ifndef JEJ_ENGINEOBJECT_HPP
#define JEJ_ENGINEOBJECT_HPP

#include <memory>
#include <string>

namespace jej //NAMESPACE jej
{

	class Graphics;
	class Window;

	class EngineObject
	{

	private:

		//Constructor
		EngineObject();

	public:

		//Return engine
		static EngineObject& getInstance();

		//Initialize engine, should be first call in main
		static bool Initialize(const std::string& root);

		//Disabled copy-constructors, there should be only one EngineObject
		EngineObject(const EngineObject&) = delete;
		EngineObject operator=(const EngineObject&) = delete;

		//Destructor
		~EngineObject();

		//Draw everything
		void EngineDraw();

		//Mother of all updates
		void EngineUpdate();

	private:

		std::unique_ptr<Graphics> m_graphicsPtr;
		std::unique_ptr<Window> m_windowPtr;

	};

} //NAMESPACE jej

#endif 