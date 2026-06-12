#include "hooking.h"
#include "TS2.h"
#include "reflections.h"

namespace Reflections
{
    // Force enables lot ocean reflections
    void ForceLotReflections()
    {
        // XOR AL,AL -> MOV AL,1
        Hooking::WriteToMemory((DWORD)0xA808F8, enableReflections, sizeof(enableReflections));
    }
    // Prevents hood deco trees becoming imposters in lot view as these don't reflect
    void EnableTreeReflections()
    {
        // TEST AL,AL -> MOV AL,1
        Hooking::WriteToMemory((DWORD)0xAD5DFD, enableReflections, sizeof(enableReflections));
    }
    // Skips visibility flag filtering to allow the terrain to reflect in pool water
    void EnablePoolTerrainReflections()
    {
        // JMP 0xA68B54
        Hooking::WriteToMemory((DWORD)0xA68B1C, poolJump, sizeof(poolJump));
    }
    // Gives visibility flag to non-imposter walls so ocean plane can "see" them
    void __declspec(naked) EnableWallReflections()
    {
        __asm {
            mov ecx,[ebp+0xC]
            mov eax,[ecx]
            push edi
            push 0x12391A0 // "Practical"
            call [eax+0x90]
            push edi
            push 0x12366EC // "Walls"
            jmp InitRenderStatesForNewSubsets_Exit
        }
    }
    // Same as above but for ceilings (floor tiles above ground level)
    void __declspec(naked) EnableCeilingReflections()
    {
        __asm {
            push 0x12391A0 // "Practical"
            mov ecx,ebx
            call [ebp+0x90]
            mov ebx,[esi+0x30]
            mov ebp,[ebx]
            lea ecx,[esp+0x64]
            mov [esp+0x10],eax
            call ToChar
            push eax
            push 0x123F024 // "Ceilings"
            jmp SetSubsetRenderStates_Exit
        }
    }
    // Adds offset to ocean plane height to reduce visible gap between reflection and terrain
    void __declspec(naked) AdjustLotSkirtOffset()
    {
        __asm {
            fld dword ptr ds:[lotSkirtOffset]
            faddp st(1),st(0)
            mov ecx,dword ptr ds:[0x141C0D8]
            jmp OceanPlaneHeight_Exit
        }
    }
    // Use Castaway's ocean reflection setup
    void __declspec(naked) EnableCastawayStyleReflections()
    {
        __asm {
            fstp [esp+0x4C]
            mov edx,[ebx]
            add esp,0x8
            push 0x7 // 7 = kRenderTypePoolReflection
            lea ecx,[esp+0x3C]
            push ecx
            push eax
            mov ecx,ebx
            call [edx+0x194]
            mov ecx,[esi]
            mov edx,[ecx]
            push 0x9 // 9 = kRenderTypeOceanReflection (Castaway uses 0x2, but this breaks mirrors)
            call [edx+0x184]
            mov ecx,[esi]
            mov eax,[ecx]
            push 0x1
            call [eax+0x1EC]
            mov ecx,[esi]
            mov edx,[ecx]
            push 0x123AF80 // Skybox pointer
            push ebp
            call [edx+0x1F0]
            mov ecx,[esi]
            mov eax,[ecx]
            push -0x1
            call [eax+0x140]
            mov ecx,[esi]
            mov edx,[ecx]
            push -0x1
            call [edx+0x138]
            jmp ConfigureOceanReflection_Exit
        }
    }
}