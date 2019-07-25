#pragma once

namespace UwpXamlCarousel
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class VirtualizingAnimatedCarouselNextButton sealed
        : public Windows::UI::Xaml::Controls::Button
    {
    public:
        VirtualizingAnimatedCarouselNextButton();
        virtual ~VirtualizingAnimatedCarouselNextButton();
    };
}