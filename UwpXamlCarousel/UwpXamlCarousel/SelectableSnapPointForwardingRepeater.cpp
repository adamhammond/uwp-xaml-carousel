#include "pch.h"
#include "SelectableSnapPointForwardingRepeater.h"
#include "VirtualizingAnimatedCarouselStackLayout.h"

using namespace UwpXamlCarousel;
using namespace Platform;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;

/*static*/ DependencyProperty^ SelectableSnapPointForwardingRepeater::s_repeatCountProperty = nullptr;
/*static*/ DependencyProperty^ SelectableSnapPointForwardingRepeater::s_selectedItemProperty = nullptr;
/*static*/ constexpr int SelectableSnapPointForwardingRepeater::s_selectedIndexValueWhenNoItemIsSelected = -1;

/*static*/ void SelectableSnapPointForwardingRepeater::RegisterDependencyProperties()
{
    if (s_repeatCountProperty == nullptr)
    {
        s_repeatCountProperty =
            DependencyProperty::Register(
                "RepeatCount",
                int::typeid,
                SelectableSnapPointForwardingRepeater::typeid,
                ref new PropertyMetadata(500));
    }

    if (s_selectedItemProperty == nullptr)
    {
        s_selectedItemProperty =
            DependencyProperty::Register(
                "SelectedItem",
                Object::typeid,
                SelectableSnapPointForwardingRepeater::typeid,
                ref new PropertyMetadata(nullptr));
    }
}

SelectableSnapPointForwardingRepeater::SelectableSnapPointForwardingRepeater()
{
    RegisterDependencyProperties();
}

SelectableSnapPointForwardingRepeater::~SelectableSnapPointForwardingRepeater()
{
}

IVectorView<float>^ SelectableSnapPointForwardingRepeater::GetIrregularSnapPoints(Orientation /* orientation */, SnapPointsAlignment /* alignment */)
{
    return nullptr;
}

float SelectableSnapPointForwardingRepeater::GetRegularSnapPoints(Orientation orientation, SnapPointsAlignment alignment, _Out_ float *offset)
{
    if (alignment == SnapPointsAlignment::Center && orientation == Orientation::Horizontal)
    {
        VirtualizingAnimatedCarouselStackLayout^ layout = dynamic_cast<VirtualizingAnimatedCarouselStackLayout^>(Layout);

        if (layout != nullptr)
        {
            *offset = layout->FirstSnapPointOffset;
            return static_cast<float>(layout->ItemWidth + layout->Spacing);
        }
    }

    *offset = 0.0f;
    return 0.0f;
}

void SelectableSnapPointForwardingRepeater::SetSelectedItemToNone()
{
    SelectedIndex = SelectedIndexValueWhenNoItemIsSelected;
    SelectedItem = nullptr;
}
