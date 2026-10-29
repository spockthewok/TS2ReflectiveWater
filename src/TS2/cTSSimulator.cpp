#include "TS2/cTSSimulator.h"
#include "common.h"

int cTSSimulator::GetTimeOfDay()
{
    using Func = int(__thiscall *)(cTSSimulator *);
    auto vFunc = Common::GetVTableFn<Func>(this, 0xC0);
    return vFunc(this);
}