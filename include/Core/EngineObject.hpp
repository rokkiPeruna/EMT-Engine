#ifndef JEJ_ENGINEOBJECT_HPP
#define JEJ_ENGINEOBJECT_HPP

#include <memory>
#include <string>

namespace jej //NAMESPACE jej
{

	class Graphics;
	class Window;
    struct WindowBaseInitData;
    struct WindowOSInitData;

	class EngineObject
	{

	private:

		//Constructor
		EngineObject();

	public:

		//Return engine
		static EngineObject& GetInstance();

		//Initialize engine, should be first call in main
		static bool Initialize(const std::string& p_root, const WindowBaseInitData* p_data = nullptr, const WindowOSInitData* p_osData = nullptr);

		//Disabled copy-constructors, there should be only one EngineObject
		EngineObject(const EngineObject&) = delete;
		EngineObject operator=(const EngineObject&) = delete;

		//Destructor
		~EngineObject();

		//Draw everything
		void EngineDraw();

		//Mother of all updates
		void EngineUpdate();

		std::shared_ptr<Graphics>& GetGraphicsRef();
		std::shared_ptr<Window>& GetWindowRef();

	private:

		std::shared_ptr<Graphics> m_graphicsPtr;
		std::shared_ptr<Window> m_windowPtr;

	};

} //NAMESPACE jej

#endif 