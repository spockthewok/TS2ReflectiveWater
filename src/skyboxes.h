#pragma once
#include "headers.h"

const DWORD SetPrecipitationType_Exit = 0x7F54D9;
const DWORD SetLightingStateByName_Exit = 0xAA5684;

const char envCubeOvercast[] = "skymap-overcast-day-highres-envcube";
const char envCubeOvercastSnow[] = "skymap-overcast-snow-day-highres-envcube";
const char envCubeAutumn[] = "skymap-autumn-day-highres-envcube";

namespace Skyboxes
{
    extern "C" void GetPrecipitationType();
    extern "C" void GetSeason();
    extern "C" void GetTimeOfDay();
    extern "C" void HandleWeatherReflections();
    extern "C" void HandleTimeOfDayReflections();
}