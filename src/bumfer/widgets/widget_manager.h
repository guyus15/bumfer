#ifndef BUMFER_WIDGET_MANAGER_H
#define BUMFER_WIDGET_MANAGER_H

#include <bumfer/widgets/widget.h>

#include <cassert>
#include <memory>
#include <unordered_map>

class WidgetManager
{
public:
    static void Initialise();
    static void Update();
    static void Dispose();

    template <typename T>
    static const T *GetWidget()
    {
        const auto it = Get().m_registry.find(typeid(T).hash_code());
        assert(it != Get().m_registry.end());
        return dynamic_cast<T *>(it->second.get());
    }

    template <typename T>
    static bool HasWidget()
    {
        const auto it = Get().m_registry.find(typeid(T).hash_code());
        return it != Get().m_registry.end();
    }

private:
    std::unordered_map<size_t, std::unique_ptr<Widget>> m_registry;

    WidgetManager() = default;
    ~WidgetManager() = default;

    static WidgetManager &Get();
    static WidgetManager s_instance;

    template <typename T, typename... Args>
    static void Register(Args... args)
    {
        std::unique_ptr<T> widget = std::make_unique<T>(std::forward<Args>(args)...);
        Get().m_registry[typeid(T).hash_code()] = std::move(widget);
        Get().m_registry[typeid(T).hash_code()]->Initialise();
    }
};

#endif // BUMFER_WIDGET_MANAGER_H