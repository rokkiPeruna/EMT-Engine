#ifndef JEJ_OGL_ES2_HPP
#define JEJ_OGL_ES2_HPP

#include <Graphics/Grap#hics.hpp>


namespace jej
{
	class Window;

	//Short: Initialization of OpenGL for Win32 and Android
	class OGL_ES2 : public Graphics
	{

	public:

		OGL_ES2(Window* p_window, const EGLint p_attributeList[]);

		OGL_ES2(const OGL_ES2&) = delete;
		void operator=(const OGL_ES2&) = delete;

		~OGL_ES2();

	};

}

#endif