#include "config.h"

namespace
{
    mINI::INIStructure ini;
    const char *configNameBase = "TS2ReflectiveWater.ini";
    const char *configNameRPC = "mods/TS2ReflectiveWater.ini";
}

namespace Config
{
    // Ocean
    float oceanReflectionOffset = 0.45;
    // Props
    bool enableTreeReflections = true;
    bool enableBridgeReflections = true;
    // Lots
    bool enableWallReflections = true;
    bool enableFloorReflections = true;
    bool enableCeilingReflections = true;
    // Ponds
    bool enablePondReflections = true;

    static std::string GetString(const std::string &section, const std::string &key, std::string defaultValue)
    {
        if (!ini[section].has(key))
        {
            ini[section][key] = defaultValue;
            return defaultValue;
        }

        return ini[section][key];
    }

    static bool GetBool(const std::string &section, const std::string &key, bool defaultValue)
    {
        std::string defaultString;
        if (defaultValue)
            defaultString = "true";
        else
            defaultString = "false";

        std::string value = GetString(section, key, defaultString);

        return (value == "true" || value == "1");
    }

    static float GetFloat(const std::string &section, const std::string &key, float defaultValue)
    {
        if (!ini[section].has(key))
        {
            ini[section][key] = std::to_string(defaultValue);
            return defaultValue;
        }

        return std::stof(ini[section][key]);
    }

    static bool IsDllLoaded(const char *dllName)
    {
        HMODULE hModule = GetModuleHandleA(dllName);
        return (hModule != nullptr);
    }

    void Init()
    {
        const char *configName = configNameBase;

        if (std::filesystem::exists(configNameRPC))
            configName = configNameRPC;

        mINI::INIFile file(configName);

        bool hasBetaFloors = IsDllLoaded("TS2BetaFloors.asi");
        if (hasBetaFloors)
            enablePondReflections = false;

        if (!file.read(ini))
            return;

        oceanReflectionOffset = GetFloat("Ocean", "oceanReflectionOffset", oceanReflectionOffset);
        enableTreeReflections = GetBool("Props", "enableTreeReflections", enableTreeReflections);
        enableBridgeReflections = GetBool("Props", "enableBridgeReflection", enableBridgeReflections);
        enableWallReflections = GetBool("Lots", "enableWallReflections", enableWallReflections);
        enableFloorReflections = GetBool("Lots", "enableFloorReflections", enableFloorReflections);
        enableCeilingReflections = GetBool("Lots", "enableCeilingReflections", enableCeilingReflections);

        if (!hasBetaFloors)
            enablePondReflections = GetBool("Ponds", "enablePondReflections", enablePondReflections);
    }
}