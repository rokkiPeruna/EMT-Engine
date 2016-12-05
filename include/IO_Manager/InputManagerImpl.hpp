#ifndef JEJ_IO_MANAGER_IMPL_HPP
#define JEJ_IO_MANAGER_IMPL_HPP

#ifdef _WIN32
#include <IO_Manager/Win32/InputManager.hpp>
#elif defined __ANDROID__
#include <IO_Manager/Android/InputManager.hpp>
#endif


#endif