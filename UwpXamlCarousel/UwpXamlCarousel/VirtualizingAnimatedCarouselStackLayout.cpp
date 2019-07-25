#include "pch.h"
#include "VirtualizingAnimatedCarouselStackLayout.h"

using namespace UwpXamlCarousel;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

/*static*/ DependencyProperty^ VirtualizingAnimatedCarouselStackLayout::s_itemWidthProperty = nullptr;
/*static*/ DependencyProperty^ VirtualizingAnimatedCarouselStackLayout::s_itemHeightProperty = nullptr;
/*static*/ DependencyProperty^ VirtualizingAnimatedCarouselStackLayout::s_spacingProperty = nullptr;
/*static*/ DependencyProperty^ VirtualizingAnimatedCarouselStackLayout::s_horizontalCacheLengthProperty = nullptr;
/*static*/ DependencyProperty^ VirtualizingAnimatedCarouselStackLayout::s_repeatCountProperty = nullptr;
/*static*/ DependencyProperty^ VirtualizingAnimatedCarouselStackLayout::s_itemScaleRatioProperty = nullptr;

/*static*/ void VirtualizingAnimatedCarouselStackLayout::RegisterDependencyProperties()
{
    if (s_itemWidthProperty == nullptr)
    {
        s_itemWidthProperty =
            DependencyProperty::Register(
                "ItemWidth",
                double::typeid,
                VirtualizingAnimatedCarouselStackLayout::typeid,
                ref new PropertyMetadata(450.0));
    }

    if (s_itemHeightProperty == nullptr)
    {
        s_itemHeightProperty =
            DependencyProperty::Register(
                "ItemHeight",
                double::typeid,
                VirtualizingAnimatedCarouselStackLayout::typeid,
                ref new PropertyMetadata(525.0));
    }

    if (s_spacingProperty == nullptr)
    {
        s_spacingProperty =
            DependencyProperty::Register(
                "Spacing",
                double::typeid,
                VirtualizingAnimatedCarouselStackLayout::typeid,
                ref new PropertyMetadata(50.0));
    }

    if (s_horizontalCacheLengthProperty == nullptr)
    {
        s_horizontalCacheLengthProperty =
            DependencyProperty::Register(
                "HorizontalCacheLength",
                double::typeid,
                VirtualizingAnimatedCarouselStackLayout::typeid,
                ref new PropertyMetadata(0.5));
    }

    if (s_repeatCountProperty == nullptr)
    {
        s_repeatCountProperty =
            DependencyProperty::Register(
                "RepeatCount",
                int::typeid,
                VirtualizingAnimatedCarouselStackLayout::typeid,
                ref new PropertyMetadata(500));
    }

    if (s_itemScaleRatioProperty == nullptr)
    {
        s_itemScaleRatioProperty =
            DependencyProperty::Register(
                "ItemScaleRatio",
                double::typeid,
                VirtualizingAnimatedCarouselStackLayout::typeid,
                ref new PropertyMetadata(0.5));
    }
}

/*static*/ double VirtualizingAnimatedCarouselStackLayout::Floor(double num)
{
    return static_cast<int>(num);
}

/*static*/ double VirtualizingAnimatedCarouselStackLayout::Ceiling(double num)
{
    double numFloor = Floor(num);
    return ((numFloor < num) ? ++numFloor : numFloor);
}

/*static*/ int VirtualizingAnimatedCarouselStackLayout::AbsoluteValue(int num)
{
    int mask = num >> (sizeof(int) * 8 - 1);
    int abs = num ^ mask;
    abs += mask & 1;
    return abs;
}

VirtualizingAnimatedCarouselStackLayout::VirtualizingAnimatedCarouselStackLayout()
{
    RegisterDependencyProperties();
}

VirtualizingAnimatedCarouselStackLayout::~VirtualizingAnimatedCarouselStackLayout()
{
}

int VirtualizingAnimatedCarouselStackLayout::FirstRealizedIndexInRect(Rect realizationRect, int itemCount)
{
    return static_cast<int>(realizationRect.X / (ItemWidth + Spacing));
}

int VirtualizingAnimatedCarouselStackLayout::LastRealizedIndexInRect(Rect realizationRect, int itemCount)
{
    return static_cast<int>(realizationRect.Right / (ItemWidth + Spacing));
}

Size VirtualizingAnimatedCarouselStackLayout::MeasureOverride(VirtualizingLayoutContext^ context, Size availableSize)
{
    Rect realizationRect = context->RealizationRect;

    if (RealizationRect.X != realizationRect.X
        || RealizationRect.Y != realizationRect.Y
        || RealizationRect.Width != realizationRect.Width
        || RealizationRect.Height != realizationRect.Height)
    {
        RealizationRect = Rect(realizationRect.X, realizationRect.Y, realizationRect.Width, realizationRect.Height);
    }

    int itemCount = context->ItemCount;

    // Max number of items that can fit in the viewport after animations have been applied
    // (e.g. if ItemScaleRatio < 1.0 then more items will be able to fit in the viewport than could fit if the items weren't animated)
    int maxNumberOfItemsThatCanFitInViewport = 1 + static_cast<int>(Ceiling((ViewportRect.Width - ItemWidth - Spacing) / (ItemWidth * ItemScaleRatio + Spacing)));

    if (maxNumberOfItemsThatCanFitInViewport != MaxNumberOfItemsThatCanFitInViewport)
    {
        MaxNumberOfItemsThatCanFitInViewport = maxNumberOfItemsThatCanFitInViewport;
    }

    if (realizationRect.Width == 0 || itemCount == 0)
    {
        return Size(0.0f, static_cast<float>(ItemHeight));
    }
    else if (itemCount == 1)
    {
        double marginLeftRight = (ViewportRect.Width - ItemWidth) / 2.0;
        double marginTopBottom = 0.0;

        if (Margin.Left != marginLeftRight
            || Margin.Top != marginTopBottom
            || Margin.Right != marginLeftRight
            || Margin.Bottom != marginTopBottom)
        {
            Margin = Thickness(marginLeftRight, marginTopBottom, marginLeftRight, marginTopBottom);
        }

        return Size(static_cast<float>(Margin.Left + ItemWidth + Margin.Right), static_cast<float>(ItemHeight));
    }
    else if (itemCount < maxNumberOfItemsThatCanFitInViewport)
    {
        double scrollViewerExtentWidthWithoutMargin = (((ItemWidth + Spacing) * itemCount) - Spacing);
        double differenceBetweenViewportWidthAndExtentWidthWithoutMargin = ViewportRect.Width - scrollViewerExtentWidthWithoutMargin;
        double marginLeftRight;
        double marginTopBottom = 0.0;

        if ((itemCount % 2) == 0)
        {
            marginLeftRight = ((((ItemWidth + Spacing) / 2.0) + (((itemCount / 2) - 1) * (ItemWidth + Spacing))) + (differenceBetweenViewportWidthAndExtentWidthWithoutMargin / 2.0));
        }
        else
        {
            marginLeftRight = (((itemCount / 2) * (ItemWidth + Spacing)) + (differenceBetweenViewportWidthAndExtentWidthWithoutMargin / 2.0));
        }

        if (Margin.Left != marginLeftRight
            || Margin.Top != marginTopBottom
            || Margin.Right != marginLeftRight
            || Margin.Bottom != marginTopBottom)
        {
            Margin = Thickness(marginLeftRight, marginTopBottom, marginLeftRight, marginTopBottom);
        }

        for (int i = 0; i < itemCount; ++i)
        {
            UIElement^ element = context->GetOrCreateElementAt(i);
            element->Measure(Size(static_cast<float>(ItemWidth), static_cast<float>(ItemHeight)));
        }

        return Size(static_cast<float>(Margin.Left + ((ItemWidth + Spacing) * itemCount) - Spacing + Margin.Right), static_cast<float>(ItemHeight));
    }
    else
    {
        double marginLeftRight = 0.0;
        double marginTopBottom = 0.0;

        if (Margin.Left != marginLeftRight
            || Margin.Top != marginTopBottom
            || Margin.Right != marginLeftRight
            || Margin.Bottom != marginTopBottom)
        {
            Margin = Thickness(marginLeftRight, marginTopBottom, marginLeftRight, marginTopBottom);
        }

        int firstRealizedIndex = FirstRealizedIndexInRect(realizationRect, itemCount);
        int lastRealizedIndex = LastRealizedIndexInRect(realizationRect, itemCount);

        // Viewport + Buffer Rect.
        for (int currentIndex = firstRealizedIndex; currentIndex <= lastRealizedIndex; ++currentIndex)
        {
            int realIndex = AbsoluteValue(currentIndex % itemCount);
            UIElement^ element = context->GetOrCreateElementAt(realIndex);
            element->Measure(Size(static_cast<float>(ItemWidth), static_cast<float>(ItemHeight)));
        }

        return Size(static_cast<float>(((ItemWidth + Spacing) * itemCount * RepeatCount) - Spacing), static_cast<float>(ItemHeight));
    }
}

Size VirtualizingAnimatedCarouselStackLayout::ArrangeOverride(VirtualizingLayoutContext^ context, Size finalSize)
{
    Rect realizationRect = context->RealizationRect;

    if (RealizationRect.X != realizationRect.X
        || RealizationRect.Y != realizationRect.Y
        || RealizationRect.Width != realizationRect.Width
        || RealizationRect.Height != realizationRect.Height)
    {
        RealizationRect = Rect(realizationRect.X, realizationRect.Y, realizationRect.Width, realizationRect.Height);
    }

    int itemCount = context->ItemCount;

    // Max number of items that can fit in the viewport after animations have been applied
    // (e.g. if ItemScaleRatio < 1.0 then more items will be able to fit in the viewport than could fit if the items weren't animated)
    int maxNumberOfItemsThatCanFitInViewport = 1 + static_cast<int>(Ceiling((ViewportRect.Width - ItemWidth - Spacing) / (ItemWidth * ItemScaleRatio + Spacing)));

    if (maxNumberOfItemsThatCanFitInViewport != MaxNumberOfItemsThatCanFitInViewport)
    {
        MaxNumberOfItemsThatCanFitInViewport = maxNumberOfItemsThatCanFitInViewport;
    }

    if (itemCount == 0)
    {
        // do nothing
    }
    else if (itemCount == 1)
    {
        double marginLeftRight = (ViewportRect.Width - ItemWidth) / 2.0;
        double marginTopBottom = 0.0;

        if (Margin.Left != marginLeftRight
            || Margin.Top != marginTopBottom
            || Margin.Right != marginLeftRight
            || Margin.Bottom != marginTopBottom)
        {
            Margin = Thickness(marginLeftRight, marginTopBottom, marginLeftRight, marginTopBottom);
        }

        int realIndex = 0;
        UIElement^ element = context->GetOrCreateElementAt(realIndex);
        Rect arrangeRect = Rect(static_cast<float>(Margin.Left), 0.0f, static_cast<float>(ItemWidth), static_cast<float>(ItemHeight));

        float firstSnapPointOffset = static_cast<float>(arrangeRect.X + (ItemWidth / 2.0));

        if (FirstSnapPointOffset != firstSnapPointOffset)
        {
            FirstSnapPointOffset = firstSnapPointOffset;
        }

        element->Arrange(arrangeRect);
    }
    else if (itemCount < maxNumberOfItemsThatCanFitInViewport)
    {
        double scrollViewerExtentWidthWithoutMargin = (((ItemWidth + Spacing) * itemCount) - Spacing);
        double differenceBetweenViewportWidthAndExtentWidthWithoutMargin = ViewportRect.Width - scrollViewerExtentWidthWithoutMargin;
        double marginLeftRight;
        double marginTopBottom = 0.0;

        if ((itemCount % 2) == 0)
        {
            marginLeftRight = ((((ItemWidth + Spacing) / 2.0) + (((itemCount / 2) - 1) * (ItemWidth + Spacing))) + (differenceBetweenViewportWidthAndExtentWidthWithoutMargin / 2.0));
        }
        else
        {
            marginLeftRight = (((itemCount / 2) * (ItemWidth + Spacing)) + (differenceBetweenViewportWidthAndExtentWidthWithoutMargin / 2.0));
        }

        if (Margin.Left != marginLeftRight
            || Margin.Top != marginTopBottom
            || Margin.Right != marginLeftRight
            || Margin.Bottom != marginTopBottom)
        {
            Margin = Thickness(marginLeftRight, marginTopBottom, marginLeftRight, marginTopBottom);
        }

        for (int i = 0; i < itemCount; ++i)
        {
            UIElement^ element = context->GetOrCreateElementAt(i);
            double arrangeRectX = (finalSize.Width / 2.0); // center of extent

            if ((itemCount % 2) == 0)
            {
                if (i < (itemCount / 2))
                {
                    arrangeRectX -= (((Spacing / 2.0) + ItemWidth) + ((((itemCount / 2) - 1) - i) * (ItemWidth + Spacing)));
                }
                else
                {
                    arrangeRectX += ((Spacing / 2.0) + ((i - (itemCount / 2)) * (ItemWidth + Spacing)));
                }
            }
            else
            {
                if (i == (itemCount / 2))
                {
                    arrangeRectX -= (ItemWidth / 2.0);
                }
                else if (i < (itemCount / 2))
                {
                    arrangeRectX -= ((ItemWidth / 2.0) + (((itemCount / 2) - i) * (ItemWidth + Spacing)));
                }
                else
                {
                    arrangeRectX += (((ItemWidth / 2.0) + Spacing) + (((i - (itemCount / 2)) - 1) * (ItemWidth + Spacing)));
                }
            }

            if (i == 0)
            {
                float firstSnapPointOffset = static_cast<float>(arrangeRectX + (ItemWidth / 2.0));

                if (FirstSnapPointOffset != firstSnapPointOffset)
                {
                    FirstSnapPointOffset = firstSnapPointOffset;
                }
            }

            Rect arrangeRect = Rect(static_cast<float>(arrangeRectX), 0.0f, static_cast<float>(ItemWidth), static_cast<float>(ItemHeight));
            element->Arrange(arrangeRect);
        }
    }
    else
    {
        int firstRealizedIndex = FirstRealizedIndexInRect(realizationRect, itemCount);
        int lastRealizedIndex = LastRealizedIndexInRect(realizationRect, itemCount);

        // Viewport + Buffer Rect.
        for (int currentIndex = firstRealizedIndex; currentIndex <= lastRealizedIndex; ++currentIndex)
        {
            int realIndex = AbsoluteValue(currentIndex % itemCount);
            UIElement^ element = context->GetOrCreateElementAt(realIndex);
            Rect arrangeRect = Rect(static_cast<float>(currentIndex * (ItemWidth + Spacing)), 0.0f, static_cast<float>(ItemWidth), static_cast<float>(ItemHeight));
            element->Arrange(arrangeRect);
        }

        float firstSnapPointOffset = static_cast<float>(Margin.Left + (ItemWidth / 2.0));

        if (FirstSnapPointOffset != firstSnapPointOffset)
        {
            FirstSnapPointOffset = firstSnapPointOffset;
        }
    }

    return finalSize;
}
