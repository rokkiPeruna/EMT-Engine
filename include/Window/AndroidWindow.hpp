#ifndef JEJ_ANDROIDWINDOW_HPP
#define JEJ_ANDROIDWINDOW_HPP

#include <Window/Window.hpp>

namespace jej
{
	//Android specific initializing data
	struct WindowOSInitData
	{
		

		WindowOSInitData(){};
	};


	class AndroidWindow : public Window
	{
	public:

		//Constructor
		AndroidWindow(const WindowOSInitData* p_winOSinitData);

		//Disabled copy constructor
		AndroidWindow(const AndroidWindow&) = delete;
		void operator=(const AndroidWindow&) = delete;

		//Destructor
		~AndroidWindow();


		//inherited methods override/////////////////////////////////

		//Window's update loop
		virtual bool UpdateWindowMessages() override;

		//Get window's initialization data, THIS is not OS specific data
		//Includes width, height, names.
		virtual WindowBaseInitData& GetWinData() override;

		//Set window's base initialization data
		virtual void SetWinData(const WindowBaseInitData&) override;

		//Get window's OS specific init data
		virtual WindowOSInitData& GetWinOSData() override;

		//Set window's OS specific init data
		virtual void SetWinOSData(const WindowOSInitData&) override;

	private:

		//Android specific window init data
		WindowOSInitData m_winOSInitData;
	};

}


#endif