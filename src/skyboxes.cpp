#include "TS2.h"
#include "skyboxes.h"

int precipitationType = 0;
int currSeason = 0;
int timeOfDay = 0;

namespace Skyboxes
{
    // Stores precipitation type and updates reflection on weather change
    void __declspec(naked) GetPrecipitationType()
    {
        __asm {
            mov eax,[esp+0x4]
            mov [precipitationType],eax
            cmp [precipitationType],0x0
            jg LAB_UpdateReflections
            jmp LAB_Exit
        LAB_UpdateReflections:
            pushad
            call HandleWeatherReflections
            popad
        LAB_Exit:
            cmp edx,eax
            jmp SetPrecipitationType_Exit
        }
    }
    // Gets current season as int (we only care about autumn, it has a unique skybox)
    void __declspec(naked) GetSeason()
    {
        __asm {
            call Globals
            mov edx,[eax]
            mov ecx,eax
            call [edx+0x84]
            mov esi,eax
            test esi,esi
            jz LAB_Return
            mov edx,[esi]
            mov ecx,esi
            call [edx+0x44]
            mov [currSeason],eax
        LAB_Return:
            ret
        }
    }
    // Gets time of day as int (0 = day, 1 = evening, 2 = night, 3 = morning)
    void __declspec(naked) GetTimeOfDay()
    {
        __asm {
            call Globals
            mov ecx,eax
            call GetSimulator
            test eax,eax
            jz LAB_Return // Simulator object is null when game first launches
            mov edx,[eax]
            mov ecx,eax
            call [edx+0xC0]
            mov [timeOfDay],eax
        LAB_Return:
            ret
        }
    }
    // Handles skybox reflection transitions for overcast weather
    void __declspec(naked) HandleWeatherReflections()
    {
        __asm {
            call GetTimeOfDay // Don't want to use overcast reflection at night
            cmp [timeOfDay],0x2 // Night
            je LAB_Return
            cmp [timeOfDay],0x3 // Morning
            je LAB_Return
            cmp [precipitationType],0x1 // Snow
            je LAB_OvercastSnow
            cmp [precipitationType],0x2 // Rain
            je LAB_Overcast
            cmp [precipitationType],0x3 // Hail
            je LAB_Overcast
        LAB_Overcast:
            push offset envCubeOvercast
            jmp LAB_RegisterEnvCube
        LAB_OvercastSnow:
            push offset envCubeOvercastSnow
        LAB_RegisterEnvCube:
            push 0x123AF80 // Skybox
            call RegisterEnvCubeForSkyBox
            add esp,0x8
        LAB_Return:
            ret
        }
    }
    // Handles skybox reflection transitions for times of the day
    void __declspec(naked) HandleTimeOfDayReflections()
    {
        __asm {
            call GetTimeOfDay
            cmp [timeOfDay],0x2 // Night
            je LAB_Night
            cmp [timeOfDay],0x3 // Morning
            je LAB_Night
            cmp [precipitationType],0x0
            jg LAB_Weather // Also do this here in case time changes but weather doesn't
            call GetSeason
            cmp [currSeason],0x2 // Autumn
            je LAB_Autumn
        LAB_Day:
            push 0x123BA7C // Day envcube
            jmp LAB_RegisterEnvCube
        LAB_Night:
            push 0x123BAA0 // Night envcube
            jmp LAB_RegisterEnvCube
        LAB_Weather:
            call HandleWeatherReflections
            jmp LAB_Exit
        LAB_Autumn:
            push offset envCubeAutumn
        LAB_RegisterEnvCube:
            push 0x123AF80 // Skybox
            call RegisterEnvCubeForSkyBox
            add esp,0x8
        LAB_Exit:
            jmp SetLightingStateByName_Exit
        }
    }
}