#include <Window/Win32Window.hpp>

#include <Core/EngineObject.hpp>
#include <Utility/Assert.hpp>
#include <Utility/Messenger.hpp>
#include <Utility/Windows/Windows.hpp>


namespace jej//NAMESPACE jej STARTS
{
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
            tmpOSData.offsetX = tmpOSData.rectWin.right;
            tmpOSData.offsetY = tmpOSData.rectWin.bottom;

            //Size = width & height
            tmpWinData.sizeX = tmpOSData.rectWin.left - tmpOSData.rectWin.right;
            tmpWinData.sizeY = tmpOSData.rectWin.top;

            //Render
            EngineObject::GetInstance().EngineDraw();

            break;
        }

        case WM_MOVE:
        {
            Win32Window* context = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);
            auto& tmpWinData = context->GetWinData();
            auto& tmpOSData = context->GetWinOSData();


            tmpOSData.offsetX = LOWORD(lparam);
            tmpOSData.offsetY -= (HIWORD(lparam) - tmpWinData.sizeY);

            break;
        }

        case WM_SIZE:
        {
            Win32Window* context = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);
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

    //Constructor for user given size, style, etc.
    Win32Window::Win32Window(const WindowBaseInitData* p_winBaseInitData, const WindowOSInitData* p_winOSInitData) :
        Window(),
        m_winOSInitData()
    {
        m_winBaseInitData = p_winBaseInitData != nullptr ? *p_winBaseInitData : WindowBaseInitData();
        m_winOSInitData = p_winOSInitData != nullptr ? *p_winOSInitData : WindowOSInitData();

        m_winOSInitData.m_hInstance = GetModuleHandle(NULL);
        m_winOSInitData.brush = CreateSolidBrush(m_winOSInitData.backGroundColor);

        _createWindowClass();

        SetRect(&m_winOSInitData.rectWin, 0, 0, m_winBaseInitData.sizeX, m_winBaseInitData.sizeY);
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

        int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);

        if (gotMsg)
        {
            if (msg.message == WM_QUIT)
                m_isWinActive = false;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
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
        wc.lpfnWndProc = WndProc;
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

}//NAMESPACE jej ENDS