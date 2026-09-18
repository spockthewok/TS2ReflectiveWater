#pragma once
#include "headers.h"
#include "include/ini.h"

namespace Config
{
    extern float oceanReflectionOffset;
    extern bool enableTreeReflections;
    extern bool enableBridgeReflections;
    extern bool enableWallReflections;
    extern bool enableFloorReflections;
    extern bool enableCeilingReflections;
    extern bool enablePondReflections;

    void Init();
}