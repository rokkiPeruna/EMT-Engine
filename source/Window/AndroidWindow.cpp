#include <Window/AndroidWindow.hpp>



namespace jej
{
	AndroidWindow::AndroidWindow(const WindowOSInitData* p_winOSinitData):
		m_winOSInitData(p_winOSinitData == nullptr ? WindowOSInitData() : *p_winOSinitData)
	{
		
	}
	//

	AndroidWindow::~AndroidWindow()
	{

	}
	//

	bool AndroidWindow::UpdateWindowMessages()
	{
		return true;
	}
	//

	WindowBaseInitData& AndroidWindow::GetWinData()
	{
		return m_winBaseInitData;
	}
	//

	WindowOSInitData& AndroidWindow::GetWinOSData()
	{
		return m_winOSInitData;
	}
	//

	void AndroidWindow::SetWinOSData(const WindowOSInitData& p_winOSInitData)
	{
		m_winOSInitData = p_winOSInitData;
	}

}