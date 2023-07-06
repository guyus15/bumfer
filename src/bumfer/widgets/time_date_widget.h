#ifndef BUMFER_TIME_DATE_WIDGET_H
#define BUMFER_TIME_DATE_WIDGET_H

#include <bumfer/widgets/widget.h>

#include <chrono>
#include <string>

class TimeDateWidget : public Widget
{
public:
    void Initialise() override;
    void Update() override;

    [[nodiscard]] std::string GetTimeString() const;
    [[nodiscard]] std::string GetDateString() const;

private:
    std::chrono::system_clock::time_point m_current_time_point;
};

#endif // BUMFER_TIME_DATE_WIDGET_H
