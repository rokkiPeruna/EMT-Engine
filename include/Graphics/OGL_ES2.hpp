#ifndef JEJ_OGL_ES2_HPP
#define JEJ_OGL_ES2_HPP

#include <Graphics/Graphics.hpp>

#include <Core/Settings.hpp>

#include <memory>

namespace jej
{
	class Window;

	//Short: Initialization of OpenGL for Win32 and Android
	class OGL_ES2 : public Graphics
	{
	public:
		
		friend class EngineObject;

		//PUBLIC METHODS

#ifdef _WIN32
		// Constructor for windows surface
		OGL_ES2(std::shared_ptr<Window> p_window, const EGLint p_attributeList[]);

#elif defined ANDOID
		// Constructor for android surface
		OGL_ES2(Window* p_window, const EGLint p_attributeList[], android_app* p_androidApplication);
#endif

        OGL_ES2(const OGL_ES2&);

        //Disabled copy-constructor
		void operator=(const OGL_ES2&) = delete;

		virtual ~OGL_ES2();


	private:

		// PRIVATE METHODS

#ifdef _WIN32
		// Context creation for window surface
		bool _createContext(std::shared_ptr<Window> p_window, const EGLint p_attributeList[] = settings::attributeList);
#elif defined ANDROID
		// Context creation for android surface
		bool _createContext(Window* p_window, android_app* p_androidApplication,  const EGLint p_attributeList[] = settings::attributeList);
#endif
		// Draw specific drawable class 
		virtual bool _draw() override;

		// Draw all drawable class objects
		virtual bool _drawAll() override;

		// eglSwapBuffers posts its color buffer to the associated native window
		virtual void _swapBuffers() override;

		// Update specific drawable buffer
		virtual void _updateBuffers(const unsigned int p_index) override;

		// Update all drawable object buffers
		virtual void _updateBuffersAll() override;




		// PRIVATE VARIABLES

		EGLContext m_context;
		EGLDisplay m_display;
		EGLSurface m_surface;


	};

}

#endif