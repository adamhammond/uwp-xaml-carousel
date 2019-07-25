#pragma once

#include "SelectableSnapPointForwardingRepeater.h"
#include "VirtualizingAnimatedCarouselNextButton.h"
#include "VirtualizingAnimatedCarouselPrevButton.h"
#include "VirtualizingAnimatedCarouselStackLayout.h"

namespace UwpXamlCarousel
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class VirtualizingAnimatedCarousel sealed
        : public Windows::UI::Xaml::Controls::Control
    {
    public:
        VirtualizingAnimatedCarousel();
        virtual ~VirtualizingAnimatedCarousel();

        // instance properties
        property Platform::Object^ ItemsSource
        {
            Platform::Object^ get() { return static_cast<Platform::Object^>(Windows::UI::Xaml::DependencyObject::GetValue(ItemsSourceProperty)); }
            void set(Platform::Object^ value) { Windows::UI::Xaml::DependencyObject::SetValue(ItemsSourceProperty, value); }
        }

        property Platform::Object^ SelectedItem
        {
            Platform::Object^ get() { return static_cast<Platform::Object^>(Windows::UI::Xaml::DependencyObject::GetValue(SelectedItemProperty)); }
            void set(Platform::Object^ value) { Windows::UI::Xaml::DependencyObject::SetValue(SelectedItemProperty, value); }
        }

        property Platform::Object^ ItemTemplate
        {
            Platform::Object^ get() { return static_cast<Platform::Object^>(Windows::UI::Xaml::DependencyObject::GetValue(ItemTemplateProperty)); }
            void set(Platform::Object^ value) { Windows::UI::Xaml::DependencyObject::SetValue(ItemTemplateProperty, value); }
        }

        property double HorizontalCacheLength
        {
            double get() { return static_cast<double>(Windows::UI::Xaml::DependencyObject::GetValue(HorizontalCacheLengthProperty)); }
            void set(double value) { Windows::UI::Xaml::DependencyObject::SetValue(HorizontalCacheLengthProperty, value); }
        }

        property double VerticalCacheLength
        {
            double get() { return static_cast<double>(Windows::UI::Xaml::DependencyObject::GetValue(VerticalCacheLengthProperty)); }
            void set(double value) { Windows::UI::Xaml::DependencyObject::SetValue(VerticalCacheLengthProperty, value); }
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

        property double ItemSpacing
        {
            double get() { return static_cast<double>(Windows::UI::Xaml::DependencyObject::GetValue(ItemSpacingProperty)); }
            void set(double value) { Windows::UI::Xaml::DependencyObject::SetValue(ItemSpacingProperty, value); }
        }

        // static properties
        static property Windows::UI::Xaml::DependencyProperty^ ItemsSourceProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemsSourceProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ SelectedItemProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_selectedItemProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ ItemTemplateProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemTemplateProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ HorizontalCacheLengthProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_horizontalCacheLengthProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ VerticalCacheLengthProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_verticalCacheLengthProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ RepeatCountProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_repeatCountProperty; }
        }        

        static property Windows::UI::Xaml::DependencyProperty^ ItemWidthProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemWidthProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ ItemHeightProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemHeightProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ ItemScaleRatioProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemScaleRatioProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ ItemSpacingProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return s_itemSpacingProperty; }
        }

    protected:
        virtual void OnApplyTemplate() override;

    private:
        enum class ScrollDirection
        {
            Previous = 0,
            Next
        };

        // static methods
        static void RegisterDependencyProperties();
        static double Floor(double num);
        static double AbsoluteValue(double num);
        template<class T>
        static T^ GetFirstChildOfType(Windows::UI::Xaml::DependencyObject^ parent);

        // instance properties
        property Windows::System::Threading::ThreadPoolTimer^ PrevButtonContinuousScrollingPeriodicTimer
        {
            Windows::System::Threading::ThreadPoolTimer^ get();
            void set(Windows::System::Threading::ThreadPoolTimer^ value);
        }

        property Windows::System::Threading::ThreadPoolTimer^ NextButtonContinuousScrollingPeriodicTimer
        {
            Windows::System::Threading::ThreadPoolTimer^ get();
            void set(Windows::System::Threading::ThreadPoolTimer^ value);
        }

        property Windows::System::Threading::ThreadPoolTimer^ PrevButtonHoldTimer
        {
            Windows::System::Threading::ThreadPoolTimer^ get();
            void set(Windows::System::Threading::ThreadPoolTimer^ value);
        }

        property Windows::System::Threading::ThreadPoolTimer^ NextButtonHoldTimer
        {
            Windows::System::Threading::ThreadPoolTimer^ get();
            void set(Windows::System::Threading::ThreadPoolTimer^ value);
        }

        property Windows::System::Threading::ThreadPoolTimer^ ScrollViewerChangeViewTimer
        {
            Windows::System::Threading::ThreadPoolTimer^ get();
            void set(Windows::System::Threading::ThreadPoolTimer^ value);
        }

        property Windows::System::Threading::ThreadPoolTimer^ PreserveSelectedItemAfterVirtualizingAnimatedCarouselSizeChangeTimer
        {
            Windows::System::Threading::ThreadPoolTimer^ get();
            void set(Windows::System::Threading::ThreadPoolTimer^ value);
        }

        // instance methods 
        void HideCarouselNextPrevButtons();
        void ShowCarouselNextPrevButtons();
        double CenterPointOfViewportInExtent();
        int GetSelectedIndexFromViewport();
        Platform::Object^ GetSelectedItemFromViewport();
        void DetermineIfCarouselNextPrevButtonsShouldBeHidden();
        void SetSelectedItemInViewport(int itemIndexInItemsSource);
        void ResetCarouselWithDefaultSelectionForCurrentItemCount();
        void CancelAllCarouselPrevButtonTimers();
        void CancelAllCarouselNextButtonTimers();
        void CancelAllCarouselScrollRelatedTimers();
        void SelectNextItem(int numberOfItemsToSkip);
        void SelectNextItem();
        void SelectPreviousItem(int numberOfItemsToSkip);
        void SelectPreviousItem();
        void StartContinuousScrolling(UwpXamlCarousel::VirtualizingAnimatedCarousel::ScrollDirection scrollDirection);

        // event handlers
        void CarouselPrevButton_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselPrevButton_PointerCanceled(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselPrevButton_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselPrevButton_PointerExited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselPrevButton_PointerCaptureLost(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselNextButton_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselNextButton_PointerCanceled(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselNextButton_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselNextButton_PointerExited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void CarouselNextButton_PointerCaptureLost(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void OnSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e);
        void Repeater_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
        void Repeater_ElementPrepared(Microsoft::UI::Xaml::Controls::ItemsRepeater^ sender, Microsoft::UI::Xaml::Controls::ItemsRepeaterElementPreparedEventArgs^ e);
        void ScrollViewer_ViewChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::ScrollViewerViewChangedEventArgs^ e);
        void ScrollViewer_ViewChanging(Platform::Object^ sender, Windows::UI::Xaml::Controls::ScrollViewerViewChangingEventArgs^ e);
        void ScrollViewer_LayoutUpdated(Platform::Object^ sender, Platform::Object^ e);
        void ScrollViewer_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);

        // static member variables
        static const Windows::Foundation::TimeSpan s_prevNextButtonHoldPeriod;
        static const int s_continousScrollingItemSkipCount;
        static const Windows::Foundation::TimeSpan s_prevNextButtonContinousScrollingSelectionPeriod;
        static const Windows::Foundation::TimeSpan s_scrollViewerChangeViewDelayPeriodForDefaultItemSelectionInEvenItemCountScenario;
        static const Windows::Foundation::TimeSpan s_scrollViewerChangeViewDelayPeriodToEnsureAnimationIsShown;
        static const Windows::Foundation::TimeSpan s_preserveSelectedItemAfterVirtualizingAnimatedCarouselSizeChangePeriod;
        static Windows::UI::Xaml::DependencyProperty^ s_itemsSourceProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_selectedItemProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_itemTemplateProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_horizontalCacheLengthProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_verticalCacheLengthProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_repeatCountProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_itemWidthProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_itemHeightProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_itemScaleRatioProperty;
        static Windows::UI::Xaml::DependencyProperty^ s_itemSpacingProperty;

        // event registration token instance member variables
        Windows::Foundation::EventRegistrationToken m_loadedEventToken {};
        Windows::Foundation::EventRegistrationToken m_sizeChangedEventToken {};
        Windows::Foundation::EventRegistrationToken m_repeaterLoadedEventToken {};
        Windows::Foundation::EventRegistrationToken m_repeaterElementPreparedEventToken {};
        Windows::Foundation::EventRegistrationToken m_scrollViewerViewChangedEventToken {};
        Windows::Foundation::EventRegistrationToken m_scrollViewerViewChangingEventToken {};
        Windows::Foundation::EventRegistrationToken m_scrollViewerTappedEventToken {};
        Windows::Foundation::EventRegistrationToken m_scrollViewerLayoutUpdatedEventToken {};

        // instance member variables
        Windows::UI::Core::CoreDispatcher^ m_dispatcher = nullptr;;
        UwpXamlCarousel::VirtualizingAnimatedCarouselPrevButton^ m_carouselPrevButton = nullptr;
        UwpXamlCarousel::VirtualizingAnimatedCarouselNextButton^ m_carouselNextButton = nullptr;
        Windows::UI::Xaml::Controls::ScrollViewer^ m_scrollViewer = nullptr;
        UwpXamlCarousel::VirtualizingAnimatedCarouselStackLayout^ m_repeaterLayout = nullptr;
        UwpXamlCarousel::SelectableSnapPointForwardingRepeater^ m_repeater = nullptr;
        Windows::System::Threading::ThreadPoolTimer^ m_prevButtonContinuousScrollingPeriodicTimer = nullptr;
        Windows::System::Threading::ThreadPoolTimer^ m_nextButtonContinuousScrollingPeriodicTimer = nullptr;
        Windows::System::Threading::ThreadPoolTimer^ m_prevButtonHoldTimer = nullptr;
        Windows::System::Threading::ThreadPoolTimer^ m_nextButtonHoldTimer = nullptr;
        Windows::System::Threading::ThreadPoolTimer^ m_scrollViewerChangeViewTimer = nullptr;
        Windows::System::Threading::ThreadPoolTimer^ m_preserveSelectedItemAfterVirtualizingAnimatedCarouselSizeChangeTimer = nullptr;
        int m_selectedItemIndexPriorToVirtualizingAnimatedCarouselSizeChange = UwpXamlCarousel::SelectableSnapPointForwardingRepeater::SelectedIndexValueWhenNoItemIsSelected;
    };
}