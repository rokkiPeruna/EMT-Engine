#ifndef JEJ_WIN32WINDOW_HPP
#define JEJ_WIN32WINDOW_HPP

//Engine headers
#include <Window/Window.hpp>
/////////////////////////////////

//Standard headers
#include <Windows.h>
/////////////////////////////////

namespace jej//NAMESPACE jej STARTS
{
    //Win32 specific initializing data
    struct WindowOSInitData
    {
        short int offsetX = 0;
        short int offsetY = 0;

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

    class Win32Window : public Window
    {

    public:

        //Constructor for user given size, style, etc.
        //Takes in two structs, first for common window attributes,
        //second for Win32 specific attributes.
        //See WindowBaseInitData and WindowOSInitData for more information
        Win32Window(const WindowBaseInitData*, const WindowOSInitData*);

        //Disabled copy constructor
        Win32Window(const Win32Window&) = delete;
        void operator=(const Win32Window&) = delete;

        //Destructor
        virtual ~Win32Window();


        //Pure virtual methods/////////////////////////////////

        //Returns native display type
        virtual EGLNativeDisplayType GetNativeDisplay() const override;

        //Return native window type
        virtual EGLNativeWindowType GetNativeWindow() const override;

        //Window's update loop
        virtual bool UpdateWindowMessages() override;

        //Get window's initialization data, THIS is not OS specific data
        //Includes width, height, names.
        virtual WindowBaseInitData& GetWinData() override;

        //Set window's base initialization data
        virtual void SetWinData(const WindowBaseInitData&) override;

        //Get window's OS specific init data
        virtual WindowOSInitData& GetWinOSData() override;

        //Set window's OS specific init data
        virtual void SetWinOSData(const WindowOSInitData&) override;


    private:

        //Win32 window creation methods
        bool _createWindowClass();
        bool _initWindow();

        //Win32 specific init data
        WindowOSInitData m_winOSInitData;

    };
}//NAMESPACE jej ENDS
#endif