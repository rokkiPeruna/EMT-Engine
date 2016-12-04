#ifndef JEJ_ANDROIDWINDOW_HPP
#define JEJ_ANDROIDWINDOW_HPP

#include <Window/Window.hpp>
#ifdef __ANDROID__
#include <android_native_app_glue.h>
#include <android/sensor.h>
#endif

namespace jej
{
	//Forward declaring android_app - struct
	struct android_app;

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
#endif
		int animating;
		struct saved_state state;

		WindowOSInitData():
			animating(-1)
		{
		};
	};



	class AndroidWindow : public Window
	{

		friend void engine_handle_cmd(struct android_app* app, int32_t cmd);

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