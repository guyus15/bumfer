#include <bumfer/widgets/widget_manager.h>

#include <bumfer/widgets/time_date_widget.h>

WidgetManager WidgetManager::s_instance;

void WidgetManager::Initialise()
{
    Register<TimeDateWidget>();
}

void WidgetManager::Update()
{
    for (const auto& widget : Get().m_registry)
    {
        widget->Update();
    }
}

void WidgetManager::Dispose()
{
    for (const auto& widget : Get().m_registry)
    {
        widget->Dispose();
    }
}

WidgetManager& WidgetManager::Get()
{
    return s_instance;
}