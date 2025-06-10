#ifndef METRIC_COLLECTOR_H
#define METRIC_COLLECTOR_H

#include "metric.h"
#include "thread_safe_queue.h"
#include <string>
#include <thread>
#include <atomic>
#include <fstream>

class metric_collector {
public:
    explicit metric_collector(const std::string& filename);
    ~metric_collector();

    // добавление метрики
    template<typename T>
    void add_metric(const std::string& name, T value) {
        auto timestamp = std::chrono::system_clock::now();
        queue_.push(metric{name, metric_value{value}, timestamp});
    }

private:
    thread_safe_queue<metric> queue_;
    std::ofstream file_;
    std::thread writer_thread_;
    std::atomic<bool> running_;

    // форматирование времени в строку
    std::string format_timestamp(const std::chrono::system_clock::time_point& tp);

    // фоновый поток для записи
    void writer_loop();
};

#endif