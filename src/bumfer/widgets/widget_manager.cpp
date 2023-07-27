#include <bumfer/widgets/widget_manager.h>

#include <bumfer/widgets/spotify_widget.h>
#include <bumfer/widgets/time_date_widget.h>

WidgetManager WidgetManager::s_instance;

void WidgetManager::Initialise()
{
    Register<SpotifyWidget>();
    Register<TimeDateWidget>();
}

void WidgetManager::Update()
{
    for (const auto &[_, widget] : Get().m_registry)
    {
        widget->Update();
    }
}

void WidgetManager::Dispose()
{
    for (const auto &[_, widget] : Get().m_registry)
    {
        widget->Dispose();
    }
}

WidgetManager &WidgetManager::Get()
{
    return s_instance;
}