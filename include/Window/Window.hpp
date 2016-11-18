//Copyrights
//Link to repo's wikipage containing this classes long description

#ifndef JEJ_WINDOW_HPP
#define JEJ_WINDOW_HPP



//Third party libraries
#include <GLES2/gl2.h>
#include <EGL/egl.h>
/////////////////////////////////

//Standard headers
#include <string>
/////////////////////////////////


namespace jej//NAMESPACE jej STARTS
{
    //Forward declaration for OS specific data struct
    struct WindowOSInitData;

    struct WindowBaseInitData
    {
        unsigned int sizeX;
        unsigned int sizeY;
        std::wstring nameApp = L"appName";
        std::wstring nameMenu = L"menuName";
        std::wstring nameWindow = L"windowName";

        WindowBaseInitData(): sizeX(200), sizeY(200){};
    };
    /////////////////////////////////

    //This is a baseclass for various OS windows, e.g. Win32, Android, etc.
    //Pure virtual class
    class Window
    {

        //Public methods and variables
    public:
        //Default constructor
        Window();

        //Disabled copy constructor
        Window(const Window&) = delete;
        void operator=(const Window&) = delete;

        //Destructor
        virtual ~Window();


        //Pure virtual methods

        //Returns native display type
        virtual EGLNativeDisplayType GetNativeDisplay() const = 0;

        //Return native window type
        virtual EGLNativeWindowType GetNativeWindow() const = 0;

        //Window's update loop
        virtual bool UpdateWindowMessages() = 0;

        //Get window's initialization data, THIS is not OS specific data
        virtual WindowBaseInitData& GetWinData() = 0;

        //Set window's base initialization data
        virtual void SetWinData(const WindowBaseInitData&) = 0;

        //Get window's OS specific init data
        virtual WindowOSInitData& GetWinOSData() = 0;

        //Set window's OS specific init data
        virtual void SetWinOSData(const WindowOSInitData&) = 0;


        //Protected methods and variables
    protected:

        WindowBaseInitData m_winBaseInitData;

        bool m_isWinActive;


    };
}//NAMESPACE jej ENDS
#endif