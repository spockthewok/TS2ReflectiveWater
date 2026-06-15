#pragma once
#include "headers.h"
#include "shared.h"

namespace Skyboxes
{
    extern "C" void GetPrecipitationType();
    extern "C" void GetSeason();
    extern "C" void GetTimeOfDay();
    extern "C" void HandleWeatherReflections();
    extern "C" void HandleTimeOfDayReflections();
}