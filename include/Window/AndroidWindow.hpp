#ifndef JEJ_ANDROIDWINDOW_HPP
#define JEJ_ANDROIDWINDOW_HPP


#ifdef __ANDROID__

#include <Window/Window.hpp>


#include <android/sensor.h>
#include <android_native_app_glue.h>

#include <Core/AndroidAppState.hpp>

namespace jej
{

    //Forward declaring android_app - struct
    //struct android_app;


 


    



    class AndroidWindow : public Window
    {
        friend class EngineObject;
        friend class RenderSystem;

    
    public:


        



        //Constructor
        AndroidWindow();

        //Disabled copy constructor
        AndroidWindow(const AndroidWindow&) = delete;
        void operator=(const AndroidWindow&) = delete;

        //Destructor
        ~AndroidWindow();


        static AndroidWindow& GetInstance();

        static void engine_handle_cmd(struct android_app* app, int32_t cmd);

        static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);

        //inherited methods override/////////////////////////////////

        //Window's update loop
        virtual bool UpdateWindowMessages() override;

        //Get window's initialization data, THIS is not OS specific data
        //Includes width, height, names.
        virtual Window::WindowBaseInitData& GetWinData() override;

        //Set window's base initialization data
        virtual void SetWinData(const Window::WindowBaseInitData&) override;

        //Get window's OS specific init data
        virtual Window::WindowOSInitData& GetWinOSData() override;

        //Set window's OS specific init data
        virtual void SetWinOSData(const Window::WindowOSInitData&) override;

        virtual bool GetWinActivityState() override { return m_isWinActive; }


    private:

        bool m_isWinActive;
        bool _initWindow();

        android_app* state;

        //Android specific window init data
        Window::WindowOSInitData m_winOSInitData;
    };

}


#endif
#endif