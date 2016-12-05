#include <Window/Win32Window.hpp>

#include <Core/EngineObject.hpp>
#include <Utility/Assert.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Windows.hpp>
#include <EntityComponentSys/Systems/RenderSystem.hpp>
#include <IO_Manager/Win32/InputManager.hpp>


namespace jej//NAMESPACE jej STARTS
{

    //Constructor for user given size, style, etc.
    Win32Window::Win32Window(const WindowBaseInitData* p_winBaseInitData, const WindowOSInitData* p_winOSInitData) :
        Window(),
        m_winOSInitData(p_winOSInitData == nullptr ? WindowOSInitData() : *p_winOSInitData)
    {
        m_winBaseInitData = p_winBaseInitData == nullptr ? WindowBaseInitData() : *p_winBaseInitData;

        m_winOSInitData.m_hInstance = GetModuleHandle(NULL);
        m_winOSInitData.brush = CreateSolidBrush(m_winOSInitData.backGroundColor);

        _createWindowClass();

        SetRect(&m_winOSInitData.rectWin, m_winOSInitData.offsetX, m_winOSInitData.offsetY, m_winBaseInitData.sizeX, m_winBaseInitData.sizeY);
        AdjustWindowRect(&m_winOSInitData.rectWin, m_winOSInitData.style, FALSE);

        _initWindow();

        SetWindowLongPtr(m_winOSInitData.m_hWnd, GWL_USERDATA, (LONG)(LONG_PTR)this);

        if (!m_winOSInitData.m_hWnd)
        {
            Messenger::Add(Messenger::MessageType::Error, "Window creation failed: ", getWinError());
            JEJ_ASSERT(false, "Window creation failed.");
        }
        m_isWinActive = true;

        ShowWindow(m_winOSInitData.m_hWnd, TRUE);
    }

    //Default destructor
    Win32Window::~Win32Window()
    {
        DeleteObject(m_winOSInitData.brush);

        if (m_winOSInitData.m_hWnd)
            DestroyWindow(m_winOSInitData.m_hWnd);
    }
    /////////////////////////////////

    ////Public methods///////////////////////////////////////////////////////////////////////////////////////////////////


    //Return Win32 native display
    EGLNativeDisplayType Win32Window::GetNativeDisplay() const
    {
        return GetDC(GetNativeWindow());
    }
    /////////////////////////////////

    //Return Win32 native window
    EGLNativeWindowType Win32Window::GetNativeWindow() const
    {
        return m_winOSInitData.m_hWnd;
    }
    /////////////////////////////////

    //Win32 message update loop
    bool Win32Window::UpdateWindowMessages()
    {
        MSG msg = { 0 };
        bool shouldCall_WM_PAINT = true;

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_PAINT) //Check if any message is WM_PAINT - message
                shouldCall_WM_PAINT = false;
            if (msg.message == WM_QUIT)
                m_isWinActive = false;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        if (shouldCall_WM_PAINT) //If no WM_PAINT - message handled, call WM_PAINT (because game engine, dah)
            SendMessage(m_winOSInitData.m_hWnd, WM_PAINT, 0, 0);

        return m_isWinActive;
    }
    /////////////////////////////////

    //Return window base data struct
    WindowBaseInitData& Win32Window::GetWinData()
    {
        return m_winBaseInitData;
    }
    /////////////////////////////////

    //Set window base data struct
    void Win32Window::SetWinData(const WindowBaseInitData& p_winBaseInitData)
    {
        m_winBaseInitData = p_winBaseInitData;
    }
    /////////////////////////////////

    //Get window's OS specific data struct
    WindowOSInitData& Win32Window::GetWinOSData()
    {
        return m_winOSInitData;
    }
    /////////////////////////////////

    //Set windos's OS specific data struct
    void Win32Window::SetWinOSData(const WindowOSInitData& p_winOSInitData)
    {
        m_winOSInitData = p_winOSInitData;
    }
    /////////////////////////////////

    ////Private methods///////////////////////////////////////////////////////////////////////////////////////////////////

    bool Win32Window::_createWindowClass()
    {

        WNDCLASSEX wc = { 0 };
        wc.cbSize = sizeof(wc);
        wc.style = m_winOSInitData.classStyle;
        wc.lpfnWndProc = (WNDPROC)WndProc;
        wc.hInstance = m_winOSInitData.m_hInstance;
        wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
        wc.hCursor = LoadCursor(NULL, m_winOSInitData.cursor);
        wc.hbrBackground = m_winOSInitData.brush;
        wc.lpszMenuName = LPCWSTR(m_winBaseInitData.nameMenu.c_str());
        wc.lpszClassName = LPCWSTR(m_winBaseInitData.nameApp.c_str());

        if (!RegisterClassEx(&wc))
        {
            Messenger::Add(Messenger::MessageType::Error, "Window registration failed: ", getWinError());
            return false;
        }
        return true;
    }
    /////////////////////////////////

    bool Win32Window::_initWindow()
    {
        m_winOSInitData.m_hWnd = CreateWindowEx(
            WS_EX_LEFT,
            LPCWSTR(m_winBaseInitData.nameApp.c_str()),
            LPCWSTR(m_winBaseInitData.nameWindow.c_str()),
            m_winOSInitData.style,
            m_winOSInitData.offsetX,
            m_winOSInitData.offsetY,
            m_winBaseInitData.sizeX,
            m_winBaseInitData.sizeY,
            NULL,
            NULL,
            m_winOSInitData.m_hInstance,
            NULL
            );

        if (!m_winOSInitData.m_hWnd)
        {
            Messenger::Add(Messenger::MessageType::Debug, "Window creation failed: ", getWinError());
            return false;
        }

        return true;
    }
    /////////////////////////////////

    Keyboard::Key Win32Window::_virtualKeyCodeToJejKeycode(WPARAM p_keycode, LPARAM p_flags)
    {
        switch (p_keycode)
        {
            // Differentiate between left and right shift
        case VK_SHIFT:
        {
            static UINT lShift = MapVirtualKeyW(VK_LSHIFT, MAPVK_VK_TO_VSC);
            UINT scancode = static_cast<UINT>((p_flags & (0xFF << 16)) >> 16);
            return scancode == lShift ? Keyboard::Key::LShift : Keyboard::Key::RShift;
        }

        // Differentiate between left and right alt
        case VK_MENU: return (HIWORD(p_flags) & KF_EXTENDED) ? Keyboard::Key::RAlt : Keyboard::Key::LAlt;

            // Differentiate between left and right control
        case VK_CONTROL: return (HIWORD(p_flags) & KF_EXTENDED) ? Keyboard::Key::RControl : Keyboard::Key::LControl;

            // Other keys just work
        case VK_LWIN:       return Keyboard::Key::LSystem;
        case VK_RWIN:       return Keyboard::Key::RSystem;
        case VK_APPS:       return Keyboard::Key::Menu;
        case VK_OEM_1:      return Keyboard::Key::SemiColon;
        case VK_OEM_2:      return Keyboard::Key::Slash;
        case VK_OEM_PLUS:   return Keyboard::Key::Equal;
        case VK_OEM_MINUS:  return Keyboard::Key::Dash;
        case VK_OEM_4:      return Keyboard::Key::LBracket;
        case VK_OEM_6:      return Keyboard::Key::RBracket;
        case VK_OEM_COMMA:  return Keyboard::Key::Comma;
        case VK_OEM_PERIOD: return Keyboard::Key::Period;
        case VK_OEM_7:      return Keyboard::Key::Quote;
        case VK_OEM_5:      return Keyboard::Key::BackSlash;
        case VK_OEM_3:      return Keyboard::Key::Tilde;
        case VK_ESCAPE:     return Keyboard::Key::Escape;
        case VK_SPACE:      return Keyboard::Key::Space;
        case VK_RETURN:     return Keyboard::Key::Return;
        case VK_BACK:       return Keyboard::Key::BackSpace;
        case VK_TAB:        return Keyboard::Key::Tab;
        case VK_PRIOR:      return Keyboard::Key::PageUp;
        case VK_NEXT:       return Keyboard::Key::PageDown;
        case VK_END:        return Keyboard::Key::End;
        case VK_HOME:       return Keyboard::Key::Home;
        case VK_INSERT:     return Keyboard::Key::Insert;
        case VK_DELETE:     return Keyboard::Key::Delete;
        case VK_ADD:        return Keyboard::Key::Add;
        case VK_SUBTRACT:   return Keyboard::Key::Subtract;
        case VK_MULTIPLY:   return Keyboard::Key::Multiply;
        case VK_DIVIDE:     return Keyboard::Key::Divide;
        case VK_PAUSE:      return Keyboard::Key::Pause;
        case VK_F1:         return Keyboard::Key::F1;
        case VK_F2:         return Keyboard::Key::F2;
        case VK_F3:         return Keyboard::Key::F3;
        case VK_F4:         return Keyboard::Key::F4;
        case VK_F5:         return Keyboard::Key::F5;
        case VK_F6:         return Keyboard::Key::F6;
        case VK_F7:         return Keyboard::Key::F7;
        case VK_F8:         return Keyboard::Key::F8;
        case VK_F9:         return Keyboard::Key::F9;
        case VK_F10:        return Keyboard::Key::F10;
        case VK_F11:        return Keyboard::Key::F11;
        case VK_F12:        return Keyboard::Key::F12;
        case VK_F13:        return Keyboard::Key::F13;
        case VK_F14:        return Keyboard::Key::F14;
        case VK_F15:        return Keyboard::Key::F15;
        case VK_LEFT:       return Keyboard::Key::Left;
        case VK_RIGHT:      return Keyboard::Key::Right;
        case VK_UP:         return Keyboard::Key::Up;
        case VK_DOWN:       return Keyboard::Key::Down;
        case VK_NUMPAD0:    return Keyboard::Key::Numpad0;
        case VK_NUMPAD1:    return Keyboard::Key::Numpad1;
        case VK_NUMPAD2:    return Keyboard::Key::Numpad2;
        case VK_NUMPAD3:    return Keyboard::Key::Numpad3;
        case VK_NUMPAD4:    return Keyboard::Key::Numpad4;
        case VK_NUMPAD5:    return Keyboard::Key::Numpad5;
        case VK_NUMPAD6:    return Keyboard::Key::Numpad6;
        case VK_NUMPAD7:    return Keyboard::Key::Numpad7;
        case VK_NUMPAD8:    return Keyboard::Key::Numpad8;
        case VK_NUMPAD9:    return Keyboard::Key::Numpad9;
        case 'A':           return Keyboard::Key::A;
        case 'Z':           return Keyboard::Key::Z;
        case 'E':           return Keyboard::Key::E;
        case 'R':           return Keyboard::Key::R;
        case 'T':           return Keyboard::Key::T;
        case 'Y':           return Keyboard::Key::Y;
        case 'U':           return Keyboard::Key::U;
        case 'I':           return Keyboard::Key::I;
        case 'O':           return Keyboard::Key::O;
        case 'P':           return Keyboard::Key::P;
        case 'Q':           return Keyboard::Key::Q;
        case 'S':           return Keyboard::Key::S;
        case 'D':           return Keyboard::Key::D;
        case 'F':           return Keyboard::Key::F;
        case 'G':           return Keyboard::Key::G;
        case 'H':           return Keyboard::Key::H;
        case 'J':           return Keyboard::Key::J;
        case 'K':           return Keyboard::Key::K;
        case 'L':           return Keyboard::Key::L;
        case 'M':           return Keyboard::Key::M;
        case 'W':           return Keyboard::Key::W;
        case 'X':           return Keyboard::Key::X;
        case 'C':           return Keyboard::Key::C;
        case 'V':           return Keyboard::Key::V;
        case 'B':           return Keyboard::Key::B;
        case 'N':           return Keyboard::Key::N;
        case '0':           return Keyboard::Key::Num0;
        case '1':           return Keyboard::Key::Num1;
        case '2':           return Keyboard::Key::Num2;
        case '3':           return Keyboard::Key::Num3;
        case '4':           return Keyboard::Key::Num4;
        case '5':           return Keyboard::Key::Num5;
        case '6':           return Keyboard::Key::Num6;
        case '7':           return Keyboard::Key::Num7;
        case '8':           return Keyboard::Key::Num8;
        case '9':           return Keyboard::Key::Num9;
        }

        return Keyboard::Key::Unknown;
    }
    /////////////////////////////////

    LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
    {
        LRESULT ret = 1;

        switch (umsg)
        {
        case WM_CREATE:
        {
            break;
        }
        case WM_PAINT:
        {
            Win32Window* context = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);
            auto& tmpWinData = context->GetWinData();
            auto& tmpOSData = context->GetWinOSData();

            Messenger::PrintMessages();

            ValidateRect(tmpOSData.m_hWnd, NULL);

            GetWindowRect(tmpOSData.m_hWnd, &tmpOSData.rectWin);

            //Offset = lower left corner
            tmpOSData.offsetX = tmpOSData.rectWin.left;
            tmpOSData.offsetY = tmpOSData.rectWin.top;
            //
            //Size = width & height
            tmpWinData.sizeX = std::abs(tmpOSData.rectWin.left - tmpOSData.rectWin.right);
            tmpWinData.sizeY = std::abs(tmpOSData.rectWin.top - tmpOSData.rectWin.bottom);

            //Render

            RenderSystem::GetInstance()._update(100.f);

            break;
        }

        case WM_MOVE:
        {
            Win32Window* context = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);
            
            //Suppresses throw in Win10
            if (!context)
                break;

            auto& tmpWinData = context->GetWinData();
            auto& tmpOSData = context->GetWinOSData();


            tmpOSData.offsetX = LOWORD(lparam);
            tmpOSData.offsetY -= (HIWORD(lparam) - tmpWinData.sizeY);

            break;
        }

        case WM_CHAR:
        {
            break; //TODO: Add code to allow user to give in-game char inputs (etc. player name)
        }

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            //Takes virtual key code, changes it to jej:Keyboard::Key value and pushes it to InputManager keyboard input queue
            InputManager::GetInstance().GetKeyboardInputQueue().emplace
                (Win32Window::_virtualKeyCodeToJejKeycode(wparam, lparam));
            break;
        }

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            break;//TODO: Add code to allow more complex controls, might require another queue or other changes
        }

        case WM_MOUSEWHEEL:
        {
            break;//TODO: Add code to allow reaction to mousewheel
        }

        case WM_SIZE:
        {
            Win32Window* context = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);

            //Suppresses throw in Win10
            if (!context)
                break;

            auto& tmpWinData = context->GetWinData();

            tmpWinData.sizeX = LOWORD(lparam);
            tmpWinData.sizeY = HIWORD(lparam);

            break;
        }


        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        default:
        {
            ret = DefWindowProc(hwnd, umsg, wparam, lparam);
            break;
        }
        }

        return ret;
    }
    /////////////////////////////////
}//NAMESPACE jej ENDS