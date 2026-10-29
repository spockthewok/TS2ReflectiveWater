#include "reflections/props.h"
#include "hooking.h"

namespace
{
    const DWORD GetMergedGeometryUnderShapeRef_Exit = 0xAD5091;
}

namespace Props
{
    // cNHoodOccupantManager::PrepareForDisplay
    // Removes IsOccupantInBounds() check for flora occupants
    // Allows scene graph nodes to be created for them, giving flags required for reflections
    void EnableTreeReflections()
    {
        Hooking::Nop((BYTE *)0xAD5DFD, 8);
    }

    // cNHoodOccupantManager::GetMergedGeometryUnderShapeRef
    // Gives render flag to neighbourhood bridges for lot view reflections
    // Bridges will only be present if using TS2VisibleHoodFX
    void __declspec(naked) EnableBridgeReflections()
    {
        __asm {
            push 0x11E2D20 // "Props"
            call [eax+0x90]
            mov ecx,[esp+0x10]
            mov eax,[ecx]
            push esi
            push 0x12391A0 // "Practical"
            jmp GetMergedGeometryUnderShapeRef_Exit
        }
    }
}