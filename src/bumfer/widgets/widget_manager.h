#ifndef BUMFER_WIDGET_MANAGER_H
#define BUMFER_WIDGET_MANAGER_H

#include <bumfer/widgets/widget.h>

#include <memory>
#include <vector>

class WidgetManager
{
public:
    static void Initialise();
    static void Update();
    static void Dispose();

private:
    std::vector<std::unique_ptr<IWidget>> m_registry;

    WidgetManager() = default;
    ~WidgetManager() = default;

    static WidgetManager& Get();
    static WidgetManager s_instance;

    template <typename T, typename... Args>
    static void Register(Args... args)
    {
        std::unique_ptr<T> widget = std::make_unique<T>(std::forward<Args>(args)...);
        Get().m_registry.push_back(widget);

        widget->Initialise();
    }
};

#endif // BUMFER_WIDGET_MANAGER_H