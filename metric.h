#ifndef METRIC_H
#define METRIC_H

#include <string>
#include <variant>
#include <chrono>

// типы данных для значений метрик
using metric_value = std::variant<double, int>;

// структура для хранения одной записи метрики
struct metric {
    std::string name;
    metric_value value;
    std::chrono::system_clock::time_point timestamp;

    metric(const std::string& name, metric_value value, std::chrono::system_clock::time_point timestamp)
        : name(name), value(value), timestamp(timestamp) {}
};

#endif