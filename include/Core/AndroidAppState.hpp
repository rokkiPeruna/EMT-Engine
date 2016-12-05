#ifndef JEJ_ANDROID_APP_STATE_HPP
#define JEJ_ANDROID_APP_STATE_HPP

#ifdef __ANDROID__
#include <android_native_app_glue.h>

struct AndroidAppState
{
    static android_app* m_AppState;

    AndroidAppState(android_app* p_app);
    AndroidAppState(){}
};

#endif
#endif
