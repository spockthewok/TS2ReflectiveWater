#include "reflections/skyboxes.h"
#include "TS2/base.h"
#include <string>

namespace
{
    const DWORD SetPrecipitationType_Exit = 0x7F54D9;
    const DWORD SetLightingStateByName_Exit = 0xAA5684;
}

namespace Skyboxes
{
    // 0 = Day, 1 = Evening, 2 = Night, 3 = Morning
    static int GetTimeOfDay()
    {
        cTSGlobals *globals = TS::Globals();
        cTSSimulator *simulator = globals->GetSimulator();

        if (!simulator)
            return 0;

        return simulator->GetTimeOfDay();
    }

    // 0 = Spring, 1 = Summer, 2 = Autumn, 3 = Winter
    static int GetSeason()
    {
        cTSGlobals *globals = TS::Globals();
        cTSWeatherInfo *weatherInfo = globals->CurrentWeatherInfo();

        if (!weatherInfo)
            return 1; // Summer is the default pre-Seasons EP state

        return weatherInfo->Season();
    }

    // 0 = Clear, 1 = Snow, 2 = Rain, 3 = Hail
    static int GetPrecipitationType()
    {
        cTSGlobals *globals = TS::Globals();
        cTSWeatherInfo *weatherInfo = globals->CurrentWeatherInfo();

        if (!weatherInfo)
            return 0;

        return weatherInfo->PrecipitationType();
    }

    static void HandleWeatherReflections(int precipitationType)
    {
        if (GetTimeOfDay() >= 2) // Night envcube always takes priority
            return;

        std::string envCube;

        switch (precipitationType)
        {
        case 1:
            envCube = "skymap-overcast-snow-day-highres-envcube";
            break;
        case 2:
        case 3:
            envCube = "skymap-overcast-day-highres-envcube";
            break;
        default:
            return;
        }

        RegisterEnvCubeForSkyBox("lotSkirtReflectionSkybox", envCube.c_str());
    }

    static void HandleTimeOfDayReflections()
    {
        std::string envCube;

        if (GetTimeOfDay() >= 2)
            envCube = "skymap-generic-night-envcube";
        else
        {
            int precipitationType = GetPrecipitationType();

            if (precipitationType != 0) // In case time changes but weather doesn't
            {
                HandleWeatherReflections(precipitationType);
                return;
            }

            if (GetSeason() == 2)
                envCube = "skymap-autumn-day-highres-envcube";
            else
                envCube = "skymap-generic-day-highres-envcube";
        }

        RegisterEnvCubeForSkyBox("lotSkirtReflectionSkybox", envCube.c_str());
    }

    // cTSWeatherInfo::SetPrecipitationType
    // Updates skybox reflection on weather change
    // We do this here as lighting manager is inconsistent with when it updates
    void __declspec(naked) UpdateWeatherReflections()
    {
        __asm {
            mov eax,[esp+0x4]
            test eax,eax
            jz LAB_Exit
        LAB_UpdateReflections:
            pushad
            push eax
            call HandleWeatherReflections
            add esp,0x4
            popad
        LAB_Exit:
            cmp edx,eax
            jmp SetPrecipitationType_Exit
        }
    }

    // cLightingManager::SetLightingStateByName
    // Replaces generic day/night checks with our own more accurate checks
    void __declspec(naked) ReplaceEnvCubeSelection()
    {
        __asm {
            call HandleTimeOfDayReflections
            jmp SetLightingStateByName_Exit
        }
    }
}