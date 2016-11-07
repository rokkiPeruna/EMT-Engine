#include <Window/Win32Window/Win32Window.hpp>


namespace jej//NAMESPACE jej STARTS
{
    LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
    {
        LRESULT ret = 1;

        Win32Window* context = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);
        auto& tmpWinData = context->GetWinData();
        auto& tmpOSData = context->GetWinOSData();

        switch (umsg)
        {
        case WM_CREATE:
        {
            break;
        }
        case WM_PAINT:
        {
            //TODO: Messenger::printMessages();

            ValidateRect(tmpOSData.m_hWnd, NULL);
            
            GetWindowRect(tmpOSData.m_hWnd, &tmpOSData.rectWin);

            //Offset = lower left corner
            tmpOSData.offSetX = tmpOSData.rectWin.right;
            tmpOSData.offSetY = tmpOSData.rectWin.bottom;

            //Size = width & height
            tmpWinData.sizeX = tmpOSData.rectWin.left - tmpOSData.rectWin.right;
            tmpWinData.sizeY = tmpOSData.rectWin.top;


            //TODO: Get EngineObject::GetInstance().GetGraphicsRef().Render()
            

            break;
        }

        case WM_MOVE:
        {
  
            tmpOSData.offSetX = LOWORD(lparam);
            tmpOSData.offSetY -= (HIWORD(lparam) - tmpWinData.sizeY);

            break;
        }

        case WM_SIZE:
        {
        
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

    //Default constructor
    Win32Window::Win32Window()
        :Window()
    {
        _createWindowClass();

        SetRect(&m_winOSInitData.rectWin, 0, 0, 200, 200);
        AdjustWindowRect(&m_winOSInitData.rectWin, m_winOSInitData.classStyle, FALSE);

        _initWindow();

        SetWindowLongPtr(m_winOSInitData.m_hWnd, GWL_USERDATA, (LONG)(LONG_PTR)this);

        assert(m_winOSInitData.m_hWnd);

        m_isWinActive = true;

        ShowWindow(m_winOSInitData.m_hWnd, TRUE);
    }
    /////////////////////////////////

    //Constructor for user given size, style, etc.
    Win32Window::Win32Window(const WindowBaseInitData& p_winBaseInitData, const WindowOSInitData& p_winOSInitData) :
        Window()
    {
        m_winBaseInitData = p_winBaseInitData;
        m_winOSInitData = p_winOSInitData;

        _createWindowClass();

        SetRect(&m_winOSInitData.rectWin, 0, 0, m_winBaseInitData.sizeX, m_winBaseInitData.sizeY);
        AdjustWindowRect(&m_winOSInitData.rectWin, m_winOSInitData.classStyle, FALSE);

        _initWindow();

        SetWindowLongPtr(m_winOSInitData.m_hWnd, GWL_USERDATA, (LONG)(LONG_PTR)this);

        assert(m_winOSInitData.m_hWnd);

        m_isWinActive = true;

        ShowWindow(m_winOSInitData.m_hWnd, TRUE);
    }

    //Default destructor
    Win32Window::~Win32Window()
    {
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
            SendMessage(m_hWnd, WM_PAINT, 0, 0);

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
        wc.style = GetWinOSData().classStyle;
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetWinOSData().m_hInstance;
        wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
        wc.hCursor = LoadCursor(NULL, GetWinOSData().cursor);
        wc.hbrBackground = GetWinOSData().brushG;
        wc.lpszMenuName = LPCWSTR(GetWinData().nameMenu.c_str());
        wc.lpszClassName = LPCWSTR(GetWinData().nameApp.c_str());

        //TODO: Remove comments after Messenger is implemented
        //Messenger::add(Messenger::MessageType::Debug, "Window status before registration: ", GetLastError());

        if (!RegisterClassEx(&wc))
        {
            //TODO: Remove comments after Messenger is implemented
            //Messenger::add(Messenger::MessageType::Error, "Window status after registration: ", GetLastError());
            return false;
        }
        return true;
    }
    /////////////////////////////////

    bool Win32Window::_initWindow()
    {
        m_winOSInitData.m_hWnd = CreateWindowEx(
            WS_EX_LEFT,
            LPCWSTR(GetWinData().nameApp.c_str()),
            LPCWSTR(GetWinData().nameWindow.c_str()),
            m_winOSInitData.style,
            m_winOSInitData.offSetX,
            m_winOSInitData.offSetY,
            m_winBaseInitData.sizeX,
            m_winBaseInitData.sizeY,
            NULL,
            NULL,
            m_winOSInitData.m_hInstance,
            NULL
            );

        //TODO: Remove comments after implementing Messesger
        //Messenger::add(Messenger::MessageType::Debug, "Window status after creation: ", GetLastError());

        if (!m_winOSInitData.m_hWnd)
            return false;

        return true;
    }

}//NAMESPACE jej ENDS