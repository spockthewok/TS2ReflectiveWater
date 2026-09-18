#include "terrain.h"

namespace
{
    const DWORD SetSubsetRenderStates_Exit = 0xAE1A66;

    const BYTE poolJump[2] = {0xEB, 0x36};
}

namespace Terrain
{
    // cPoolManager::SetupPoolReflectionCamera
    // Skips render flag filtering to allow terrain to reflect in pool water
    void EnablePoolTerrainReflections()
    {
        // JMP 0xA68B54
        Hooking::WriteToMemory((DWORD)0xA68B1C, poolJump, sizeof(poolJump));
    }

    // cTerrain::SetSubsetRenderStates
    // Gives render flag to terrain material types so ocean plane can "see" them
    void __declspec(naked) EnableLotTerrainReflections()
    {
        __asm {
            mov eax,[esp+0x1C]
            test eax,eax
            jz LAB_ApplyFlag
            cmp eax,0x1
            je LAB_ApplyFlag
            cmp eax,0x3
            je LAB_ApplyFlag
            cmp eax,0x4
            jne LAB_Exit
        LAB_ApplyFlag:
            mov eax,[esi]
            mov ebx,[edi]
            mov ecx,esi
            call [eax+0x14]
            push eax
            push 0x12391A0 // "Practical"
            mov ecx,edi
            call [ebx+0x90]
        LAB_Exit:
            mov eax,[esp+0x10]
            push eax
            jmp SetSubsetRenderStates_Exit
        }
    }
}