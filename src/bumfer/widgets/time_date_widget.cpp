#include <bumfer/widgets/time_date_widget.h>

#include <iomanip>
#include <iostream>
#include <sstream>

void TimeDateWidget::Initialise()
{
    // Ensure that a the current time point is valid before it is accessed for the
    // first time.
    m_current_time_point = std::chrono::system_clock::now();
}

void TimeDateWidget::Update()
{
    m_current_time_point = std::chrono::system_clock::now();
}

std::string TimeDateWidget::GetTimeString() const
{
    const std::time_t t = std::chrono::system_clock::to_time_t(m_current_time_point);

    std::stringstream time_string_stream{};
    time_string_stream << std::put_time(std::localtime(&t), "%T (%Z)");

    return time_string_stream.str();
}

std::string TimeDateWidget::GetDateString() const
{
    const std::time_t t = std::chrono::system_clock::to_time_t(m_current_time_point);

    std::stringstream time_string_stream{};
    time_string_stream << std::put_time(std::localtime(&t), "%A %d of %B, %Y");

    return time_string_stream.str();
}