#include <IO_Manager/Win32/Mouse.hpp>
#include <IO_Manager/Win32/InputManager.hpp>

namespace jej
{
	Mouse::Mouse()
	{

	}
	//

	Mouse::~Mouse()
	{

	}
	//

	Mouse& Mouse::GetInstance()
	{
		static Mouse mouse;
		return mouse;
	}
	//

	bool Mouse::IsButtonPressed(Mouse::Button button) const
	{
		return InputManager::GetInstance()._isMouseButtonPressed(button);
	}
	//

	jej::Vector2i Mouse::GetMousePosition() const
	{
		return InputManager::GetInstance()._getMousePosition();
	}
}