#include "metric_collector.h"
#include <iomanip>
#include <sstream>

metric_collector::metric_collector(const std::string& filename) : running_(true) {
    file_.open(filename, std::ios::app);
    if (!file_.is_open()) {
        throw std::runtime_error("cannot open file: " + filename);
    }
    writer_thread_ = std::thread(&metric_collector::writer_loop, this);
}

metric_collector::~metric_collector() {
    running_ = false;
    writer_thread_.join();
    file_.close();
}

std::string metric_collector::format_timestamp(const std::chrono::system_clock::time_point& tp) {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        tp.time_since_epoch()) % 1000;
    auto time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

void metric_collector::writer_loop() {
    while (running_) {
        auto metric_opt = queue_.pop();
        if (metric_opt) {
            auto& m = metric_opt.value();
            std::string value_str;
            std::visit([&](const auto& value) { value_str = std::to_string(value); }, m.value);
            file_ << format_timestamp(m.timestamp) << " \"" << m.name << "\" " << value_str << "\n";
            file_.flush();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}