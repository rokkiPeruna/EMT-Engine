/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include <initializer_list>
#include <jni.h>
#include <errno.h>
#include <cassert>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <Core

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

using namespace kerberos;

//Saved state data.
struct saved_state
{
	float angle;
	int32_t x;
	int32_t y;
};

//Shared state for our app.
struct engineAndroid
{
	struct android_app* app;

	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;

	int animating;
	int width;
	int height;
	saved_state state;

	GraphicsES2* m_graphicsPtr = nullptr;
	kerberos::Window* m_windowPtr = nullptr;
	Timer* m_timer = nullptr;

};


void createBox(kerberos::GraphicsES2* rafiikka)
{
	kerberos::Drawable::DrawableData ddata;

	ddata.vertices = {
		0.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		-1.f, 0.f, 0.f,
		0.f, -1.f, 0.f,
		1.f, 0.f, 0.f
	};

	ddata.indices = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 1
	};

	ddata.fShaderPath = "fragShaderTex.frag";

	rafiikka->addDrawable(ddata);
}

void createTriangle(kerberos::GraphicsES2* rafiikka)
{
	kerberos::Drawable::DrawableData ddata;
	rafiikka->addDrawable(ddata);
}

void createStar(kerberos::GraphicsES2* rafiikka)
{
	kerberos::Random<float> randomi(0.1f, 0.25f);
	float min = randomi.r();
	float max = randomi.setRange(0.45f, 0.7f).r();


	kerberos::Drawable::DrawableData ddata;

	ddata.fShaderPath = "fragShaderTex.frag";

	ddata.vertices = {
		0.f, 0.f, 0.f,
		0.f, max, 0.f,
		-min, min, 0.f,
		-max, 0.f, 0.f,
		-min, -min, 0.f,
		0.f, -max, 0.f,
		min, -min, 0.f,
		max, 0.f, 0.f,
		min, min, 0.f
	};

	ddata.indices = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 1
	};

	ddata.textureCoords = {
		0, 0,
		0.5f, 0.5f,
		1, 0,
		0, 1,
		1, 0,
		0.5f, 0.5f,
		1, 0,
		0, 1,
		1, 0
	};

	rafiikka->addDrawable(ddata);
}


//Start program
static int engine_init_display(struct engineAndroid* engine)
{
	

	const EGLint attribs[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};

	Window::WindowInitData data;
	WindowAndroid::WindowAndroidInitData aData;

	engine->m_windowPtr = reinterpret_cast<Window*>(new kerberos::WindowAndroid(data, aData));
	engine->m_graphicsPtr = new GraphicsES2(engine->m_windowPtr, attribs, engine->app);
	engine->state.x = engine->m_windowPtr->getWindowDataRef().sizeX;
	engine->state.y = engine->m_windowPtr->getWindowDataRef().sizeY;
	engine->state.angle = 0;

	engine->m_timer = new Timer();
	engine->m_timer->reset();

	settings::setApp(engine->app);

	createBox(engine->m_graphicsPtr);
	createTriangle(engine->m_graphicsPtr);
	createStar(engine->m_graphicsPtr);

	return 0;
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engineAndroid* engine)
{
	if (!engine->m_windowPtr)
		return;
	if (!engine->m_graphicsPtr)
		return;

	auto* app = engine->m_windowPtr->getApplication();
	app->render();
	app->update(engine->m_timer->getTime());
	engine->m_timer->reset();
}

//Terminate program
static void engine_term_display(struct engineAndroid* engine)
{
	if (engine->m_graphicsPtr)
		delete engine->m_graphicsPtr;
	if (engine->m_windowPtr)
		delete engine->m_windowPtr;
	if (engine->m_timer)
		delete engine->m_timer;
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
	struct engineAndroid* engine = (struct engineAndroid*)app->userData;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
		engine->animating = 1;
		engine->state.x = AMotionEvent_getX(event, 0);
		engine->state.y = AMotionEvent_getY(event, 0);
		return 1;
	}
	return 0;
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
	struct engineAndroid* engine = (struct engineAndroid*)app->userData;
	switch (cmd)
	{
		// The system has asked us to save our current state.  Do so.
	case APP_CMD_SAVE_STATE:
		engine->app->savedState = malloc(sizeof(struct saved_state));
		*((struct saved_state*)engine->app->savedState) = engine->state;
		engine->app->savedStateSize = sizeof(struct saved_state);
		break;


		// The window is being shown, get it ready.
	case APP_CMD_INIT_WINDOW:
		if (engine->app->window != NULL)
		{
			engine_init_display(engine);
			engine_draw_frame(engine);
		}
		break;


		// The window is being hidden or closed, clean it up.
	case APP_CMD_TERM_WINDOW:
		engine_term_display(engine);
		break;


		// When our app gains focus, we start monitoring the accelerometer.
	case APP_CMD_GAINED_FOCUS:
		if (engine->accelerometerSensor != NULL)
		{
			ASensorEventQueue_enableSensor(
				engine->sensorEventQueue,
				engine->accelerometerSensor);
			ASensorEventQueue_setEventRate(
				engine->sensorEventQueue,
				engine->accelerometerSensor,
				(1000L / 60) * 1000);
		}
		break;


		// When our app loses focus, we stop monitoring the accelerometer.
		// This is to avoid consuming battery while not being used.
	case APP_CMD_LOST_FOCUS:
		if (engine->accelerometerSensor != NULL)
		{
			ASensorEventQueue_disableSensor(
				engine->sensorEventQueue,
				engine->accelerometerSensor);
		}
		engine_draw_frame(engine);
		break;
	}
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state)
{
	struct engineAndroid engine;

	// Make sure glue isn't stripped.
	app_dummy();

	memset(&engine, 0, sizeof(engine));
	state->userData = &engine;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	engine.app = state;

	// Prepare to monitor accelerometer
	engine.sensorManager = ASensorManager_getInstance();
	engine.accelerometerSensor = ASensorManager_getDefaultSensor(
		engine.sensorManager,
		ASENSOR_TYPE_ACCELEROMETER);
	engine.sensorEventQueue = ASensorManager_createEventQueue(
		engine.sensorManager,
		state->looper, LOOPER_ID_USER,
		NULL, NULL);

	// We are starting with a previous saved state; restore from it.
	if (state->savedState != NULL)
		engine.state = *(struct saved_state*)state->savedState;




	// loop waiting for stuff to do.
	while (1)
	{
		// Read all pending events.
		int ident;
		int events;
		struct android_poll_source* source;

		// If not animating, we will block forever waiting for events.
		// If animating, we loop until all events are read, then continue
		// to draw the next frame of animation.
		while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
		{
			// Process this event.
			if (source != NULL)
				source->process(state, source);

			// If a sensor has data, process it now.
			if (ident == LOOPER_ID_USER)
			{
				if (engine.accelerometerSensor != NULL)
				{
					ASensorEvent event;
					while (ASensorEventQueue_getEvents(engine.sensorEventQueue, &event, 1) > 0)
					{
						LOGI("accelerometer: x=%f y=%f z=%f",
							event.acceleration.x, event.acceleration.y,
							event.acceleration.z);
					}
				}
			}

			// Check if we are exiting.
			if (state->destroyRequested != 0)
			{
				engine_term_display(&engine);
				return;
			}
		}

		if (engine.animating)
		{
			// Done with events; draw next animation frame.
			engine.state.angle += .01f;
			if (engine.state.angle > 1)
				engine.state.angle = 0;

			// Drawing is throttled to the screen update rate, so there
			// is no need to do timing here.
			engine_draw_frame(&engine);
		}
	}
}
//END_INCLUDE(all)
