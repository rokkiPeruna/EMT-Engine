#include <Window/AndroidWindow.hpp>

#ifdef __ANDROID__

#include <EntityComponentSys/Systems/RenderSystem.hpp>
#include <Core/AndroidAppState.hpp>


#include <android/sensor.h>
#include <android_native_app_glue.h>


namespace jej
{

    void AndroidWindow::engine_handle_cmd(struct android_app* app, int32_t cmd)
    {
        auto& engine = AndroidWindow::GetInstance().m_winOSInitData;
        auto& rend = RenderSystem::GetInstance();

        switch (cmd) {
            //case APP_CMD_SAVE_STATE:
            //	// The system has asked us to save our current state.  Do so.
            //	engine->app->savedState = malloc(sizeof(struct saved_state));
            //	*((struct saved_state*)engine->app->savedState) = engine->state;
            //	engine->app->savedStateSize = sizeof(struct saved_state);
            //	break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (rend.m_display != nullptr) {
                //engine_init_display(engine);
                rend._update(100.f);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            rend.~RenderSystem();
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
    ///////////////////////////////////////


    //TODO: Move this to IO_Manager's Android cpp.

    int32_t AndroidWindow::engine_handle_input(struct android_app* app, AInputEvent* event)
    {

        auto& window = AndroidWindow::GetInstance();

        if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
        {
            window.m_winOSInitData.animating = 1;
            window.m_winOSInitData.state.x = AMotionEvent_getX(event, 0);
            window.m_winOSInitData.state.y = AMotionEvent_getY(event, 0);
            return 1;
        }
        return 0;
    }
    ///////////////////////////////////////


    AndroidWindow::AndroidWindow() :
        m_winOSInitData()
    {

    }
    ////////////////////////////////


    AndroidWindow::~AndroidWindow()
    {

    }
    ///////////////////////////////////////


    AndroidWindow& AndroidWindow::GetInstance()
    {
        static AndroidWindow window;
        return window;
    }
    ////////////////////////////////


    bool AndroidWindow::UpdateWindowMessages()
    {

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
        return true;
    }
    ///////////////////////////////////////


    WindowBaseInitData& AndroidWindow::GetWinData()
    {
        return m_winBaseInitData;
    }
    ///////////////////////////////////////


    WindowOSInitData& AndroidWindow::GetWinOSData()
    {
        return m_winOSInitData;
    }
    ///////////////////////////////////////


    void AndroidWindow::SetWinData(const WindowBaseInitData&)
    {
        return;
    }
    ///////////////////////////////////////


    void AndroidWindow::SetWinOSData(const WindowOSInitData& p_winOSInitData)
    {
        m_winOSInitData = p_winOSInitData;
    }
    ///////////////////////////////////////


    bool AndroidWindow::_initWindow()
    {
        return true;
    }
    ///////////////////////////////////////


}

#endif
