//Copyrights
//Link to repo's wikipage containing this classes long description

#ifndef JEJ_WINDOW_HPP
#define JEJ_WINDOW_HPP



//Third party libraries
#include <External/OpenGL_ES2/GLES2/gl2.h>
#include <External/OpenGL_ES2/EGL/egl.h>
/////////////////////////////////

//Standard headers
#include <memory>
#include <string>
/////////////////////////////////


namespace jej//NAMESPACE jej STARTS
{
    
    

    //This is a baseclass for various OS windows, e.g. Win32, Android, etc.
    //Pure virtual class
    class Window
    {

        //Public methods and variables
    public:


#ifdef _WIN32

        //Win32 specific initializing data
        struct WindowOSInitData
        {
            int offsetX = 600;
            int offsetY = 600;

            HINSTANCE m_hInstance;
            HWND m_hWnd;

            LPWSTR cursor = IDC_ARROW;
            DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
            UINT classStyle = CS_HREDRAW | CS_VREDRAW;
            COLORREF backGroundColor = 0x00111111;
            HBRUSH brush = nullptr;

            RECT rectWin;

            WindowOSInitData(){};
        };

#elif defined __ANDROID__

        //Android specific initializing data
        struct WindowOSInitData
        {
            android_app* app;

            ASensorManager* sensorManager;
            const ASensor* accelerometerSensor;
            ASensorEventQueue* sensorEventQueue;

            int animating;
            EGLDisplay display;
            EGLSurface surface;
            EGLContext context;

            struct saved_state state;

            WindowOSInitData() :
                animating(-1)
            {
                app = AndroidAppState::m_AppState;
            };

        };

#endif




        struct WindowBaseInitData
        {
            int32_t sizeX = 400u;
            int32_t sizeY = 250u;
            std::wstring nameApp = L"appName";
            std::wstring nameMenu = L"menuName";
            std::wstring nameWindow = L"windowName";

            WindowBaseInitData(){};
        };
        /////////////////////////////////


        

        //Default constructor
        Window();

        //Disabled copy constructor
        Window(const Window&) = delete;
        void operator=(const Window&) = delete;

        //Destructor
        virtual ~Window();


        //Pure virtual methods
#ifdef _WIN32 //These are only needed in Windows platform
        //Returns native display type
        virtual EGLNativeDisplayType GetNativeDisplay() const = 0;

        //Return native window type
        virtual EGLNativeWindowType GetNativeWindow() const = 0;
#endif
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