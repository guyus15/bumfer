#ifndef BUMFER_TIME_DATE_WIDGET_H
#define BUMFER_TIME_DATE_WIDGET_H

#include <bumfer/widgets/widget.h>

#include <chrono>

class TimeDateWidget : public IWidget
{
public:
    void Initialise() override;
    void Update() override;
    void Dispose() override;

private:
    std::chrono::system_clock m_clock;
};

#endif // BUMFER_TIME_DATE_WIDGET_H
