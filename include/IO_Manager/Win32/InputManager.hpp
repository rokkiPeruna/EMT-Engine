#ifndef JEJ_INPUT_MANAGER_HPP
#define JEJ_INPUT_MANAGER_HPP

#include <IO_Manager/InputManagerImpl.hpp>
#include <Core/BaseStructs.hpp>

#include <IO_Manager/Win32/Keyboard.hpp>
#include <IO_Manager/Win32/Mouse.hpp>

#include <queue>

namespace jej
{
	class Keyboard;
	class Mouse;

	class InputManager
	{

		friend class Mouse;
		friend class Keyboard;
		friend class Win32Window;

	private:
		InputManager();

	public:
		//
		~InputManager();

		//Deleted copyconstructor and assign operator
		InputManager(const InputManager&) = delete;
		InputManager operator=(const InputManager&) = delete;

		//Return singleton instance
		static InputManager& GetInstance();

		//Return input queues
		std::queue<Keyboard::Key>& GetKeyboardInputQueue() { return m_keyboardInputQueue; }
		std::queue<Mouse::Button>& GetMouseInputQueue() { return m_mouseInputQueue; }

		//At this moment, does nothing else but handles input queues
		void Update();


	private:

		//Input queues for keyboard and mouse
		std::queue<Keyboard::Key> m_keyboardInputQueue;
		std::queue<Mouse::Button> m_mouseInputQueue;

		//Handle inputs
		void _handleInputQueues();

		//Checks if keyboard key is pressed
		bool _isKeyboardKeyPressed(const Keyboard::Key key) const;

		//Checks mouse button is pressed
		bool _isMouseButtonPressed(const Mouse::Button button) const;

		//Returns mouse position
		jej::Vector2i _getMousePosition() const;

	};

}//NAMESPACE jej ENDS

#endif