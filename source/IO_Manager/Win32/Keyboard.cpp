#include <IO_Manager/Win32/Keyboard.hpp>
#include <IO_Manager/Win32/InputManager.hpp>

namespace jej
{
    Keyboard::Keyboard()
    {

    }
    //

    Keyboard::~Keyboard()
    {

    }
    //

    Keyboard& Keyboard::GetInstance()
    {
        static Keyboard keyboard;
        return keyboard;
    }
    //

    bool Keyboard::IsKeyPressed(Keyboard::Key key) const
    {
        return InputManager::GetInstance()._isKeyboardKeyPressed(key);
    }
}