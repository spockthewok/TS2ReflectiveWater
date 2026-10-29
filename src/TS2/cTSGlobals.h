#pragma once
#include "TS2/cTSSimulator.h"
#include "TS2/cTSWeatherInfo.h"

class cTSGlobals
{
public:
    cTSSimulator *GetSimulator();
    cTSWeatherInfo *CurrentWeatherInfo();
};