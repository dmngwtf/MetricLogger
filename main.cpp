#include "metric_collector.h"
#include <thread>
#include <random>
#include <iostream>

int main() {
    // инициализация сборщика метрик
    metric_collector collector("metrics.log");

    // генератор случайных чисел для эмуляции метрик
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> cpu_dist(0.0, 4.0); // эмуляция загрузки CPU (0-4 ядра)
    std::uniform_int_distribution<> req_dist(0, 100);   // эмуляция HTTP запросов

    // эмуляция сбора метрик в нескольких потоках
    std::thread t1([&] {
        for (int i = 0; i < 5; ++i) {
            collector.add_metric("CPU", cpu_dist(gen));
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    std::thread t2([&] {
        for (int i = 0; i < 5; ++i) {
            collector.add_metric("HTTP requests RPS", req_dist(gen));
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
        }
    });

    t1.join();
    t2.join();

    // даем время фоновому потоку записать все метрики
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "metrics written to metrics.log\n";
    return 0;
}