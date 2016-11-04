//Copyrights
//Link to repo's wikipage containing this classes long description

#ifndef JEJ_WINDOW_HPP
#define JEJ_WINDOW_HPP



//Third party libraries
#include <GLES2/gl2.h>
#include <EGL\egl.h>
/////////////////////////////////

//Standard headers
#include <string>
/////////////////////////////////

namespace jej //NAMESPACE jej STARTS
{
    //This is a baseclass for various OS windows, e.g. Win32, Android, etc.
    //Pure virtual class
    class Window
    {
    public:
        //Cross-platform window data
        struct WindowInitData
        {
            short int sizeX = 0;
            short int sizeY = 0;
            std::wstring nameApp = L"appName";
            std::wstring nameMenu = L"menuName";
            std::wstring nameWindow = L"windowName";
        };

        //Public methods and variables
    public:
        //Default constructor
        Window();

        //Disabled copy constructors
        Window(const Window&) = delete;
        void operator=(const Window&) = delete;

        //Destructor
        virtual ~Window();


        //Pure virtual methods

        //Returns native display type
        virtual EGLNativeDisplayType GetNativeDisplay() = 0;

        //Return native window type
        virtual EGLNativeWindowType GetNativeWindow() = 0;

        //Window's update loop
        virtual bool UpdateWindowMessages() = 0;


        //Protected methods and variables
    protected:







    };
}//NAMESPACE jej ENDS
#endif