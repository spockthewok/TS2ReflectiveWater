#include "hooking.h"
#include "reflections.h"
#include "skyboxes.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        Reflections::ForceLotReflections();
        Reflections::EnableTreeReflections();
        Reflections::EnablePoolTerrainReflections();
        Hooking::MakeJMP((BYTE *)0xA80989, (DWORD)Reflections::AdjustLotSkirtOffset, 6);
        Hooking::MakeJMP((BYTE *)0xA809D3, (DWORD)Reflections::EnableCastawayStyleReflections, 6);
        Hooking::MakeJMP((BYTE *)0x7F54D3, (DWORD)Skyboxes::GetPrecipitationType, 6);
        Hooking::MakeJMP((BYTE *)0xAA55ED, (DWORD)Skyboxes::HandleTimeOfDayReflections, 5);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}