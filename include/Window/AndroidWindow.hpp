#ifndef JEJ_ANDROIDWINDOW_HPP
#define JEJ_ANDROIDWINDOW_HPP

#include <Window/Window.hpp>
#ifdef __ANDROID__
#include <android_native_app_glue.h>
#include <android/sensor.h>
#include <Core/AndroidAppState.hpp>
#endif

//Forward declaring android_app - struct
struct android_app;

namespace jej
{

	//For returning to Android app's previous state
	struct saved_state {
		float angle;
		int32_t x;
		int32_t y;
	};

	//Android specific initializing data
	struct WindowOSInitData
	{
		android_app* app;



#ifdef __ANDROID__
		ASensorManager* sensorManager;
		const ASensor* accelerometerSensor;
		ASensorEventQueue* sensorEventQueue;

		int animating;
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;

        struct saved_state state;

		WindowOSInitData():
			animating(-1)
		{
            app = AndroidAppState::m_AppState;
		};
#endif
	};



	class AndroidWindow : public Window
	{
		friend class EngineObject;
		friend class RenderSystem;

	private:
		//Constructor
		AndroidWindow();
	public:


		//Disabled copy constructor
		AndroidWindow(const AndroidWindow&) = delete;
		void operator=(const AndroidWindow&) = delete;

		//Destructor
		~AndroidWindow();
#ifdef __ANDROID__
		static AndroidWindow& GetInstance();

		static void engine_handle_cmd(struct android_app* app, int32_t cmd);

		static int32_t engine_handle_input(struct android_app* app, AInputEvent* event);
#endif
		//inherited methods override/////////////////////////////////

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

		bool _initWindow();

		android_app* state;

		//Android specific window init data
		WindowOSInitData m_winOSInitData;
	};

}


#endif