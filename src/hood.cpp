#include "hood.h"

namespace
{
    const DWORD BuildWaterReflection_Exit = 0xADA9BE;
}

namespace Hood
{
    // cNHoodTerrain::BuildWaterReflection
    // Changes render group ID allowed to reflect from 999 to -1 (reflect everything)
    void __declspec(naked) EnableHoodFullSceneReflections()
    {
        __asm {
            push -0x1
            call [edx+0x144]
            mov ecx,[esi]
            mov eax,[ecx]
            push 0x1
            call [eax+0x188]
            mov edx,[ebx]
            push -0x1
            jmp BuildWaterReflection_Exit
        }
    }
}