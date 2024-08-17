#pragma once

#include "InitializerAttribute.h"

class GameModuleInitializerAttribute : public InitializerAttribute<GameModuleInitializerAttribute> {
public:
    GameModuleInitializerAttribute(InitializePriority priority = InitializePriority::Normal)
        : InitializerAttribute(priority) {}

    void Initialize() override {
        // Game-specific initialization logic
    }
};
