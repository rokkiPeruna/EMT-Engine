#ifndef JEJ_WIN32WINDOW_HPP
#define JEJ_WIN32WINDOW_HPP

//Engine headers
#include <Window/Window.hpp>
#include <IO_Manager/Win32/Keyboard.hpp>
#include <IO_Manager/Win32/Mouse.hpp>
/////////////////////////////////

//Standard headers
#include <Windows.h>
/////////////////////////////////

namespace jej//NAMESPACE jej STARTS
{
    

    class Win32Window : public Window
    {
        friend LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

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


        //inherited methods override/////////////////////////////////

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

        //Change virtual keyboard codes coming from Win32 to jej::Keyboard values
        static Keyboard::Key _virtualKeyCodeToJejKeycode(WPARAM p_keycode, LPARAM p_flags);

    private:

        //Win32 window creation methods
        bool _createWindowClass();
        bool _initWindow();

        //Win32 specific init data
        WindowOSInitData m_winOSInitData;


    };
}//NAMESPACE jej ENDS
#endif