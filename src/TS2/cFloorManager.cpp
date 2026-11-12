#include "TS2/cFloorManager.h"
#include "common.h"

namespace nTSSG
{
    cFloor *cFloorManager::Floor(int level)
    {
        using Func = cFloor *(__thiscall *)(cFloorManager *, int);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x4C);
        return vFunc(this, level);
    }
}