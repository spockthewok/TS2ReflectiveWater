#include "props.h"

namespace Props
{
    // Prevents hood deco trees becoming imposters in lot view as these don't reflect
    void EnableTreeReflections()
    {
        // TEST AL,AL -> MOV AL,0x1
        Hooking::WriteToMemory((DWORD)0xAD5DFD, enableReflections, sizeof(enableReflections));
    }
}