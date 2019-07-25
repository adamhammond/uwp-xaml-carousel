#pragma once

namespace UwpXamlCarousel
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class DemoViewModel sealed
        : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        DemoViewModel();
        virtual ~DemoViewModel();

        // INotifyPropertyChanged
        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property Windows::Foundation::Collections::IVector<Platform::String^>^ Users
        {
            Windows::Foundation::Collections::IVector<Platform::String^>^ get();
            void set(Windows::Foundation::Collections::IVector<Platform::String^>^ value);
        }

        property Platform::String^ SelectedUser
        {
            Platform::String^ get();
            void set(Platform::String^ value);
        }

    private:
        Windows::Foundation::Collections::IVector<Platform::String^>^ m_users;
        Platform::String^ m_selectedUser;
    };
}
