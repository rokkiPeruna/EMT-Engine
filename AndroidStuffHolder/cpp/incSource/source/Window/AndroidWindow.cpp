#include <Window/AndroidWindow.hpp>

#include <EntityComponentSys/Systems/RenderSystem.hpp>

#ifdef __ANDROID__
#include <android/sensor.h>
#endif

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

namespace jej
{
#ifdef __ANDROID__
	static void engine_handle_cmd(struct android_app* app, int32_t cmd)
	{
		struct engine* engine = (struct engine*)app->userData;
		switch (cmd) {
		//case APP_CMD_SAVE_STATE:
		//	// The system has asked us to save our current state.  Do so.
		//	engine->app->savedState = malloc(sizeof(struct saved_state));
		//	*((struct saved_state*)engine->app->savedState) = engine->state;
		//	engine->app->savedStateSize = sizeof(struct saved_state);
		//	break;
		case APP_CMD_INIT_WINDOW:
			// The window is being shown, get it ready.
			if ( != NULL) {
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
			if (engine->accelerometerSensor != NULL) {
				ASensorEventQueue_enableSensor(engine->sensorEventQueue,
					engine->accelerometerSensor);
				// We'd like to get 60 events per second (in us).
				ASensorEventQueue_setEventRate(engine->sensorEventQueue,
					engine->accelerometerSensor,
					(1000L / 60) * 1000);
			}
			break;
		case APP_CMD_LOST_FOCUS:
			// When our app loses focus, we stop monitoring the accelerometer.
			// This is to avoid consuming battery while not being used.
			if (engine->accelerometerSensor != NULL) {
				ASensorEventQueue_disableSensor(engine->sensorEventQueue,
					engine->accelerometerSensor);
			}
			// Also stop animating.
			engine->animating = 0;
			//engine_draw_frame(engine);
			break;
		}
	}


	//TODO: Move this to IO_Manager's Android cpp.

	static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
	{
		struct engine* engine = (struct engine*)app->userData;
		if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
			engine->animating = 1;
			engine->state.x = AMotionEvent_getX(event, 0);
			engine->state.y = AMotionEvent_getY(event, 0);
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

	AndroidWindow::~AndroidWindow()
	{

	}
	////////////////////////////////
#ifdef __ANDROID_
	AndroidWindow& AndroidWindow::GetInstance()
	{
		static AndroidWindow andWindow;
		return andWindow;
	}
#endif
	bool AndroidWindow::UpdateWindowMessages()
	{


#ifdef __ANDROID__

		memset(&m_winOSInitData, 0, sizeof(m_winOSInitData));

		// Make sure glue isn't stripped.
		app_dummy();

        m_winOSInitData.app = EngineObject::GetInstance().state;


		// Make sure glue isn't stripped.
		app_dummy();

		memset(&m_winOSInitData, 0, sizeof(m_winOSInitData));
		globalState->userData = &m_winOSInitData;
		globalState->onAppCmd = AndroidWindow::engine_handle_cmd;
		globalState->onInputEvent = engine_handle_input;
		m_winOSInitData.app = globalState;

		// Prepare to monitor accelerometer
        m_winOSInitData.sensorManager = ASensorManager_getInstance();
        m_winOSInitData.accelerometerSensor = ASensorManager_getDefaultSensor(
                m_winOSInitData.sensorManager,
			ASENSOR_TYPE_ACCELEROMETER);
        m_winOSInitData.sensorEventQueue = ASensorManager_createEventQueue(
                m_winOSInitData.sensorManager,
			state->looper, LOOPER_ID_USER,
			NULL, NULL);

		if (state->savedState != NULL) {
			// We are starting with a previous saved state; restore from it.
            m_winOSInitData.state = *(struct saved_state*)state->savedState;
		}

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
					source->process(state, source);
				}

				// If a sensor has data, process it now.
				if (ident == LOOPER_ID_USER) {
					if (m_winOSInitData.accelerometerSensor != NULL) {
						ASensorEvent event;
						while (ASensorEventQueue_getEvents(m_winOSInitData.sensorEventQueue,
							&event, 1) > 0) {
							//LOGI("accelerometer: x=%f y=%f z=%f",
								//event.acceleration.x, event.acceleration.y,
								//event.acceleration.z;
						}
					}
				}

				// Check if we are exiting.
				if (state->destroyRequested != 0) {
                    delete EngineObject::GetInstance();
					return false;
				}
			}

			if (m_winOSInitData.animating) {
				// Done with events; draw next animation frame.
				// Drawing is throttled to the screen update rate, so there
				// is no need to do timing here.
                RenderSystem::GetInstance()._update(100.f);
			}
		}
#endif
		return true;
	}
	////////////////////////////////

	WindowBaseInitData& AndroidWindow::GetWinData()
	{
		return m_winBaseInitData;
	}
	////////////////////////////////

	WindowOSInitData& AndroidWindow::GetWinOSData()
	{
		return m_winOSInitData;
	}
	////////////////////////////////

	void AndroidWindow::SetWinData(const WindowBaseInitData&)
	{
		return;
	}
	////////////////////////////////

	void AndroidWindow::SetWinOSData(const WindowOSInitData& p_winOSInitData)
	{
		m_winOSInitData = p_winOSInitData;
	}
	////////////////////////////////

	bool AndroidWindow::_initWindow()
	{
		return true;
	}

}