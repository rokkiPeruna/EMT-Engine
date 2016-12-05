#include <Window/AndroidWindow.hpp>

<<<<<<< HEAD
=======
#include <EntityComponentSys/Systems/RenderSystem.hpp>


#ifdef __ANDROID__
#include <android/sensor.h>
#include <android_native_app_glue.h>
#endif
>>>>>>> origin/JuhoAndroidBranch


namespace jej
{
<<<<<<< HEAD
	AndroidWindow::AndroidWindow(const WindowOSInitData* p_winOSinitData):
		m_winOSInitData(p_winOSinitData == nullptr ? WindowOSInitData() : *p_winOSinitData)
	{
		
	}
	//
=======
#ifdef __ANDROID__
	void AndroidWindow::engine_handle_cmd(struct android_app* app, int32_t cmd)
	{
		auto& engine = AndroidWindow::GetInstance().m_winOSInitData;
		switch (cmd) {
		//case APP_CMD_SAVE_STATE:
		//	// The system has asked us to save our current state.  Do so.
		//	engine->app->savedState = malloc(sizeof(struct saved_state));
		//	*((struct saved_state*)engine->app->savedState) = engine->state;
		//	engine->app->savedStateSize = sizeof(struct saved_state);
		//	break;
		case APP_CMD_INIT_WINDOW:
			// The window is being shown, get it ready.
			if ( RenderSystem::GetInstance().m_display!= nullptr) {
				//engine_init_display(engine);
                RenderSystem::GetInstance()._update(100.f);
			}
			break;
		case APP_CMD_TERM_WINDOW:
			// The window is being hidden or closed, clean it up.
                RenderSystem::GetInstance().~RenderSystem();
			break;
		case APP_CMD_GAINED_FOCUS:
			// When our app gains focus, we start monitoring the accelerometer.
			if (engine.accelerometerSensor != NULL) {
				ASensorEventQueue_enableSensor(engine.sensorEventQueue,
					engine.accelerometerSensor);
				// We'd like to get 60 events per second (in us).
				ASensorEventQueue_setEventRate(engine.sensorEventQueue,
					engine.accelerometerSensor,
					(1000L / 60) * 1000);
			}
			break;
		case APP_CMD_LOST_FOCUS:
			// When our app loses focus, we stop monitoring the accelerometer.
			// This is to avoid consuming battery while not being used.
			if (engine.accelerometerSensor != NULL) {
				ASensorEventQueue_disableSensor(engine.sensorEventQueue,
					engine.accelerometerSensor);
			}
			// Also stop animating.
			engine.animating = 0;
			//engine_draw_frame(engine);
			break;
		}
	}


	//TODO: Move this to IO_Manager's Android cpp.

	int32_t AndroidWindow::engine_handle_input(struct android_app* app, AInputEvent* event)
	{
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
            AndroidWindow::GetInstance().m_winOSInitData.animating = 1;
            AndroidWindow::GetInstance().m_winOSInitData.state.x = AMotionEvent_getX(event, 0);
            AndroidWindow::GetInstance().m_winOSInitData.state.y = AMotionEvent_getY(event, 0);
			return 1;
		}
		return 0;
	}

#endif
	AndroidWindow::AndroidWindow():
    m_winOSInitData()
	{
		
	}
	////////////////////////////////
>>>>>>> origin/JuhoAndroidBranch

	AndroidWindow::~AndroidWindow()
	{

	}
<<<<<<< HEAD
	//

	bool AndroidWindow::UpdateWindowMessages()
	{
		return true;
	}
	//
=======
	////////////////////////////////
#ifdef __ANDROID__
	AndroidWindow& AndroidWindow::GetInstance()
	{
		static AndroidWindow andWindow;
		return andWindow;
	}
    ////////////////////////////////
#endif
	bool AndroidWindow::UpdateWindowMessages()
	{


#ifdef __ANDROID__

		AndroidAppState state;

		while (1) {
			// Read all pending events.
			int ident;
			int events;
			struct android_poll_source* source;

			// If not animating, we will block forever waiting for events.
			// If animating, we loop until all events are read, then continue
			// to draw the next frame of animation.
			while ((ident = ALooper_pollAll(m_winOSInitData.animating ? 0 : -1, NULL, &events,
				(void**)&source)) >= 0) {

				// Process this event.
				if (source != NULL) {
					source->process(state.m_AppState, source);
				}

				// If a sensor has data, process it now.
				//if (ident == LOOPER_ID_USER) {
				//	if (m_winOSInitData.accelerometerSensor != NULL) {
				//		ASensorEvent event;
				//		while (ASensorEventQueue_getEvents(m_winOSInitData.sensorEventQueue,
				//			&event, 1) > 0) {
				//			//LOGI("accelerometer: x=%f y=%f z=%f",
				//				//event.acceleration.x, event.acceleration.y,
				//				//event.acceleration.z;
				//		}
				//	}
				//}

				// Check if we are exiting.
				if (state.m_AppState->destroyRequested != 0) {
                    //delete EngineObject::GetInstance();
					return false;
				}

				//if (m_winOSInitData.animating) {
					// Done with events; draw next animation frame.
					// Drawing is throttled to the screen update rate, so there
					// is no need to do timing here.
					RenderSystem::GetInstance()._update(100.f);
				//}
			}


		}
#endif
		return true;
	}
	////////////////////////////////
>>>>>>> origin/JuhoAndroidBranch

	WindowBaseInitData& AndroidWindow::GetWinData()
	{
		return m_winBaseInitData;
	}
<<<<<<< HEAD
	//
=======
	////////////////////////////////
>>>>>>> origin/JuhoAndroidBranch

	WindowOSInitData& AndroidWindow::GetWinOSData()
	{
		return m_winOSInitData;
	}
<<<<<<< HEAD
	//
=======
	////////////////////////////////

	void AndroidWindow::SetWinData(const WindowBaseInitData&)
	{
		return;
	}
	////////////////////////////////
>>>>>>> origin/JuhoAndroidBranch

	void AndroidWindow::SetWinOSData(const WindowOSInitData& p_winOSInitData)
	{
		m_winOSInitData = p_winOSInitData;
	}
<<<<<<< HEAD
=======
	////////////////////////////////

	bool AndroidWindow::_initWindow()
	{
		return true;
	}
>>>>>>> origin/JuhoAndroidBranch

}