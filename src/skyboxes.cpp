#include "TS2.h"
#include "skyboxes.h"

int *currSeason = nullptr;
int *precipitationType = nullptr;

namespace Skyboxes
{
    // Stores the precipitation type in a var when the weather changes
    void __declspec(naked) GetPrecipitationType()
    {
        __asm {
            mov eax,[esp+0x4]
            mov [precipitationType],eax
            cmp edx,eax
            jmp SetPrecipitationType_Exit
        }
    }
    // Gets the current season as an int (we only care about autumn - it has a unique skybox)
    void __declspec(naked) GetSeason()
    {
        __asm {
            call Globals
            mov edx,[eax]
            mov ecx,eax
            call [edx+0x84]
            mov esi,eax
            test esi,esi
            jz LAB_Null
            mov edx,[esi]
            mov ecx,esi
            call [edx+0x44]
            mov [currSeason],eax
            jmp LAB_Return
        LAB_Null:
            mov [currSeason],-0x1 // Just to be safe
        LAB_Return:
            ret
        }
    }
    // Fixes skybox reflection transitions for seasons and weather
    void __declspec(naked) FixSkyboxReflections()
    {
        __asm {
            mov eax,[ebx+0x4C]
            cmp eax,0x0 // Morning
            je LAB_Night
            cmp eax,0x3 // Night
            je LAB_Night
            cmp [precipitationType],0x1 // Snow
            je LAB_OvercastSnow
            cmp [precipitationType],0x2 // Rain
            je LAB_Overcast
            cmp [precipitationType],0x3 // Hail
            je LAB_Overcast
            pushad
            call GetSeason
            cmp [currSeason],0x2 // Autumn
            popad
            je LAB_Autumn
        LAB_Day:
            push 0x123BA7C // Day envcube
            jmp LAB_RegisterEnvCube
        LAB_Night:
            push 0x123BAA0 // Night envcube
            jmp LAB_RegisterEnvCube
        LAB_Overcast:
            push offset envCubeOvercast
            jmp LAB_RegisterEnvCube
        LAB_OvercastSnow:
            push offset envCubeOvercastSnow
            jmp LAB_RegisterEnvCube
        LAB_Autumn:
            push offset envCubeAutumn
        LAB_RegisterEnvCube:
            push 0x123AF80 // Skybox
            call RegisterEnvCubeForSkyBox
            add esp,8
        LAB_Exit:
            jmp SetLightingStateByName_Exit
        }
    }
}