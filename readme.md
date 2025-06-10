# CppMetrics

## Установка
```bash
git clone https://github.com/your-username/CppMetrics.git
cd CppMetrics
```

## Сборка
```bash
g++ -std=c++17 -pthread metric_collector.cpp main.cpp -o metrics_app
./metrics_app
```

Создаст `metrics.log` в текущей папке.

## Использование
```cpp
#include "metric_collector.h"

int main() {
    metric_collector collector("metrics.log");
    collector.add_metric("CPU", 1.23);
    collector.add_metric("HTTP requests", 42);
}
```

Вывод:
```
2025-06-10 12:22:01.123 "CPU" 1.23
2025-06-10 12:22:01.133 "HTTP requests" 42
```

## Тесты
```bash
g++ -std=c++17 -pthread metric_collector.cpp test_metrics.cpp -o test_metrics
./test_metrics
```

## Файлы
- `metric.h` — структура метрик
- `thread_safe_queue.h` — потокобезопасная очередь
- `metric_collector.h/cpp` — основной код
- `main.cpp` — пример
- `test_metrics.cpp` — тесты

