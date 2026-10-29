#include "TS2/cWorldDB.h"
#include "common.h"

namespace nTSWorld
{
    bool cWorldDB::IsWaterVertex(int *cVertex)
    {
        using Func = bool(__thiscall *)(cWorldDB *, int *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0xE0);
        return vFunc(this, cVertex);
    }

    float cWorldDB::MaxX()
    {
        using Func = float(__thiscall *)(cWorldDB *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x134);
        return vFunc(this);
    }

    float cWorldDB::MaxY()
    {
        using Func = float(__thiscall *)(cWorldDB *);
        auto vFunc = Common::GetVTableFn<Func>(this, 0x138);
        return vFunc(this);
    }
}