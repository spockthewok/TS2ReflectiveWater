#include "hooking.h"
#include "reflections.h"

namespace Reflections
{
    // Force enables lot ocean reflections
    void ForceReflections()
    {
        // XOR AL,AL -> MOV AL,1
        Hooking::WriteToMemory((DWORD)0xA808F8, EnableReflections, sizeof(EnableReflections));
    }
    // Prevents hood deco trees becoming billboard imposters in lot view as these do not reflect
    void EnableTreeReflections()
    {
        // TEST AL,AL -> MOV AL,1
        Hooking::WriteToMemory((DWORD)0xAD5DFD, EnableReflections, sizeof(EnableReflections));
    }
    // Adds tiny offset to ocean reflection plane height to reduce visible gap between reflection and terrain
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
            call RenderGroupManager
            jmp ConfigureOceanReflection_Exit
        }
    }
}