#include "TS2/cTSWeatherInfo.h"
#include "common.h"

int cTSWeatherInfo::Season()
{
    using Func = int(__thiscall *)(cTSWeatherInfo *);
    auto vFunc = Common::GetVTableFn<Func>(this, 0x44);
    return vFunc(this);
}

int cTSWeatherInfo::PrecipitationType()
{
    using Func = int(__thiscall *)(cTSWeatherInfo *);
    auto vFunc = Common::GetVTableFn<Func>(this, 0x64);
    return vFunc(this);
}