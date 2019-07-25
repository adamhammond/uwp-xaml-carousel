//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "DemoViewModel.h"
#include "VirtualizingAnimatedCarousel.h"

namespace UwpXamlCarousel
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
        property DemoViewModel^ ViewModel
        {
            DemoViewModel^ get();
            void set(DemoViewModel^ value);
        }

    private:
        DemoViewModel^ m_viewModel = nullptr;
	};
}
