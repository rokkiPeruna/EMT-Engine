#ifndef JEJ_MOUSE_HPP
#define JEJ_MOUSE_HPP

#include <Core/BaseStructs.hpp>

namespace jej
{


    class Mouse
    {
    private:
        Mouse();

    public:

        enum class Button : int
        {
            Left,       //The left mouse button
            Right,      //The right mouse button
            Middle,     //The middle (wheel) mouse button

            ButtonCount //Keep last -- the total number of mouse buttons
        };

        //
        ~Mouse();

        //Deleted copyconstructor and assign operator
        NOCOPY(Mouse);

        //Get Mouse instance for singleton
        static Mouse& GetInstance();

        //Checks if any and which mouse button is pressed
        bool IsButtonPressed(Button button) const;

        //Return mouse position
        jej::Vector2i GetMousePosition() const;
    };
}

#endif