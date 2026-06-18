#include "props.h"

namespace Props
{
    // Allows creation of scene nodes for trees considered 'out of bounds', giving them flags required for reflections
    void EnableTreeReflections()
    {
        // TEST AL,AL -> MOV AL,0x1
        Hooking::WriteToMemory((DWORD)0xAD5DFD, Shared::enableReflections, sizeof(Shared::enableReflections));
    }
}