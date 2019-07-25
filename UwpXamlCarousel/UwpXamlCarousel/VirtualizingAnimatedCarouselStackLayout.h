#pragma once

#include "sal.h"

namespace UwpXamlCarousel
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class VirtualizingAnimatedCarouselStackLayout sealed
        : public Microsoft::UI::Xaml::Controls::VirtualizingLayout
    {
    public:
        VirtualizingAnimatedCarouselStackLayout();
        virtual ~VirtualizingAnimatedCarouselStackLayout();

        property Windows::Foundation::Rect RealizationRect;

        property Windows::Foundation::Rect ViewportRect
        {
            Windows::Foundation::Rect get()
            {
                float viewportWidth = static_cast<float>(RealizationRect.Width / (1 + HorizontalCacheLength));
                float viewportHeight = RealizationRect.Height;
                float viewportXCoordinate = (RealizationRect.X + (RealizationRect.Width - viewportWidth) / 2.0f);
                float viewportYCoordinate = RealizationRect.Y;
                return Windows::Foundation::Rect(viewportXCoordinate, viewportYCoordinate, viewportWidth, viewportHeight);
            }
        }

        property double ItemWidth
        {
            double get() { return static_cast<double>(Windows::UI::Xaml::DependencyObject::GetValue(ItemWidthProperty)); }
            void set(double value) { Windows::UI::Xaml::DependencyObject::SetValue(ItemWidthProperty, value); }
        }

        property double ItemHeight
        {
            double get() { return static_cast<double>(Windows::UI::Xaml::DependencyObject::GetValue(ItemHeightProperty)); }
            void set(double value) { Windows::UI::Xaml::DependencyObject::SetValue(ItemHeightProperty, value); }
        }

        property double Spacing
        {
            double get() { return static_cast<double>(Windows::UI::Xaml::DependencyObject::GetValue(SpacingProperty)); }
            void set(double value) { Windows::UI::Xaml::DependencyObject::SetValue(SpacingProperty, value); }
        }

        property double HorizontalCacheLength
        {
            double get() { return static_cast<double>(Windows::UI::Xaml::DependencyObject::GetValue(HorizontalCacheLengthProperty)); }
            void set(double value) { Windows::UI::Xaml::DependencyObject::SetValue(HorizontalCacheLengthProperty, value); }
        }

        property int RepeatCount
        {
            int get() { return static_cast<int>(Windows::UI::Xaml::DependencyObject::GetValue(RepeatCountProperty)); }
            void set(int value)
            {
                if (value < 0)
                {
                    throw ref new Platform::InvalidArgumentException("RepeatCount must be a non-negative integer");
                }

                Windows::UI::Xaml::DependencyObject::SetValue(RepeatCountProperty, value);
            }
        }

        property double ItemScaleRatio
        {
            double get() { return static_cast<double>(Windows::UI::Xaml::DependencyObject::GetValue(ItemScaleRatioProperty)); }
            void set(double value)
            {
                if ((value <= 0) || (value > 1))
                {
                    throw ref new Platform::InvalidArgumentException("ItemScaleRatio must be a number, x, where 0 < x <= 1");
                }

                Windows::UI::Xaml::DependencyObject::SetValue(ItemScaleRatioProperty, value);
            }
        }

        property Windows::UI::Xaml::Thickness Margin
        {
            Windows::UI::Xaml::Thickness get() { return m_margin; }
            void set(Windows::UI::Xaml::Thickness value) { m_margin = value; }
        }

        property int MaxNumberOfItemsThatCanFitInViewport
        {
            int get() { return m_maxNumberOfItemsThatCanFitInViewport; }
            void set(int value) { m_maxNumberOfItemsThatCanFitInViewport = value; }
        }

        property float FirstSnapPointOffset
        {
            float get() { return m_firstSnapPointOffset; }
            void set(float value) { m_firstSnapPointOffset = value; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ ItemWidthProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemWidthProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ ItemHeightProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemHeightProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ SpacingProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_spacingProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ HorizontalCacheLengthProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_horizontalCacheLengthProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ RepeatCountProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_repeatCountProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ ItemScaleRatioProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemScaleRatioProperty; }
        }

    protected:
        // VirtualizingLayout
        virtual Windows::Foundation::Size MeasureOverride(Microsoft::UI::Xaml::Controls::VirtualizingLayoutContext^ context, Windows::Foundation::Size availableSize) override;
        virtual Windows::Foundation::Size ArrangeOverride(Microsoft::UI::Xaml::Controls::VirtualizingLayoutContext^ context, Windows::Foundation::Size finalSize) override;

    private:
        static void RegisterDependencyProperties();
        static double Floor(double num);
        static double Ceiling(double num);
        static int AbsoluteValue(int num);

        int FirstRealizedIndexInRect(Windows::Foundation::Rect realizationRect, int itemCount);
        int LastRealizedIndexInRect(Windows::Foundation::Rect realizationRect, int itemCount);

        static Windows::UI::Xaml::DependencyProperty^ s_itemWidthProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_itemHeightProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_spacingProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_horizontalCacheLengthProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_repeatCountProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_itemScaleRatioProperty;

        Windows::UI::Xaml::Thickness m_margin = Windows::UI::Xaml::Thickness { 0, 0, 0, 0 };
        int m_maxNumberOfItemsThatCanFitInViewport = 0;
        float m_firstSnapPointOffset = 0.0f;
    };
}
