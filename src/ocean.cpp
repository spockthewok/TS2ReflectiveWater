#include "ocean.h"

namespace
{
    const DWORD ConfigureOceanReflection_Exit_1 = 0xA8098F;
    const DWORD ConfigureOceanReflection_Exit_2 = 0xA80AA2;

    const float lotSkirtOffset = 0.45;
}

namespace Ocean
{
    // Force enables lot ocean reflections
    void ForceLotReflections()
    {
        // XOR AL,AL -> MOV AL,0x1
        Hooking::WriteToMemory((DWORD)0xA808F8, Shared::enableReflections, sizeof(Shared::enableReflections));
    }
    // Adds offset to ocean plane height to reduce visible gap between reflection and terrain
    void __declspec(naked) AdjustLotSkirtOffset()
    {
        __asm {
            fld dword ptr [lotSkirtOffset]
            faddp st(1),st(0)
            mov ecx,dword ptr ds:[0x141C0D8] // DAT_0141C0D8
            jmp ConfigureOceanReflection_Exit_1
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
            push 0x123AF80 // "lotSkirtReflectionSkybox"
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
            jmp ConfigureOceanReflection_Exit_2
        }
    }
}