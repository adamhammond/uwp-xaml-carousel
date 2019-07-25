#pragma once

namespace UwpXamlCarousel
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class VirtualizingAnimatedCarouselPrevButton sealed
        : public Windows::UI::Xaml::Controls::Button
    {
    public:
        VirtualizingAnimatedCarouselPrevButton();
        virtual ~VirtualizingAnimatedCarouselPrevButton();
    };
}