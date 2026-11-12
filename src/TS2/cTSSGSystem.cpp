#include "TS2/cTSSGSystem.h"
#include "common.h"

namespace nTSSG
{
    cFloorManager *cTSSGSystem::FloorManager()
    {
        using Func = cFloorManager *(__thiscall *)(cTSSGSystem *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x98);
        return vFunc(this);
    }
}