#include <Core/AndroidAppState.hpp>

#ifdef __ANDROID__
android_app* AndroidAppState::m_AppState;

AndroidAppState::AndroidAppState(android_app* p_app)
{
    AndroidAppState::m_AppState = p_app;
}

#endif