#include "TS2/cTSGlobals.h"
#include "common.h"

cTSSimulator *cTSGlobals::GetSimulator()
{
    using Func = cTSSimulator *(__thiscall *)(cTSGlobals *);
    auto vFunc = Common::GetVTableFn<Func>(this, 0xC);
    return vFunc(this);
}

cTSWeatherInfo *cTSGlobals::CurrentWeatherInfo()
{
    using Func = cTSWeatherInfo *(__thiscall *)(cTSGlobals *);
    auto vFunc = Common::GetVTableFn<Func>(this, 0x84);
    return vFunc(this);
}