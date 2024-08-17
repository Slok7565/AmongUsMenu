#pragma once

#include <vector>
#include <algorithm>
#include <typeinfo>
#include <functional>
#include <iostream>

enum class InitializePriority {
    VeryHigh,
    High,
    Normal,
    Low,
    VeryLow
};

template <typename T>
class InitializerAttribute {
public:
    InitializerAttribute(InitializePriority priority = InitializePriority::Normal)
        : priority(priority) {}

    virtual void Initialize() = 0;

    static void FindInitializers();
    static void InitializeAll();

protected:
    InitializePriority priority;

private:
    static std::vector<std::function<void()>> allInitializers;
};

template <typename T>
std::vector<std::function<void()>> InitializerAttribute<T>::allInitializers;

template <typename T>
void InitializerAttribute<T>::FindInitializers() {
    // Implementation to find and register initializers
    // This code needs reflection capabilities, which are not natively available in C++
    // You'd typically use a manual registration approach in C++
}

template <typename T>
void InitializerAttribute<T>::InitializeAll() {
    if (allInitializers.empty()) {
        FindInitializers();
    }
    for (auto& initializer : allInitializers) {
        initializer();
    }
}
