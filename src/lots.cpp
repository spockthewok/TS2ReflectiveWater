#include "lots.h"

namespace
{
    const DWORD InitRenderStatesForNewSubsets_Exit = 0xA771CB;
    const DWORD SetSubsetRenderStates_Exit_1 = 0xAE5634;
    const DWORD SetSubsetRenderStates_Exit_2 = 0xAE59A7;
}

// Gives visibility flag to walls/floors/ceilings on lot so ocean plane can "see" them
namespace Lots
{
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

    void __declspec(naked) EnableFloorReflections()
    {
        __asm {
            push 0x12391A0 // "Practical"
            call [ebp+0x90]
            mov eax,[esi+0x28]
            mov ebp,[eax]
            lea ecx,[esp+0x34]
            mov [esp+0x10],eax
            call dword ptr [cRZString::ToChar]
            mov ecx,[esp+0x10]
            push eax
            push 0x1236704 // "Ground"
            jmp SetSubsetRenderStates_Exit_1
        }
    }

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
            call dword ptr [cRZString::ToChar]
            push eax
            push 0x123F024 // "Ceilings"
            jmp SetSubsetRenderStates_Exit_2
        }
    }
}