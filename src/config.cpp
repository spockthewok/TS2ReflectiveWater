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

    template <typename T>
    static T SetIniValue(const std::string &section, const std::string &key, T defaultValue)
    {
        if constexpr (std::is_same_v<T, std::string>)
            ini[section][key] = defaultValue;
        else
            ini[section][key] = std::to_string(defaultValue);

        return defaultValue;
    }

    template <typename T>
    static T GetIniValue(const std::string &section, const std::string &key, T defaultValue)
    {
        if (!ini.has(section) || !ini[section].has(key))
            return SetIniValue(section, key, defaultValue);

        const auto &value = ini[section][key];

        if constexpr (std::is_same_v<T, bool>)
            return (value == "true" || value == "1");
        else if constexpr (std::is_same_v<T, int>)
            return std::stoi(value);
        else if constexpr (std::is_same_v<T, float>)
            return std::stof(value);
        else if constexpr (std::is_same_v<T, double>)
            return std::stod(value);
        else if constexpr (std::is_same_v<T, std::string>)
            return value;

        return defaultValue;
    }

    static bool IsDllLoaded(const char *dllName)
    {
        return (GetModuleHandleA(dllName) != nullptr);
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

        oceanReflectionOffset = GetIniValue("Ocean", "oceanReflectionOffset", oceanReflectionOffset);
        enableTreeReflections = GetIniValue("Props", "enableTreeReflections", enableTreeReflections);
        enableBridgeReflections = GetIniValue("Props", "enableBridgeReflection", enableBridgeReflections);
        enableWallReflections = GetIniValue("Lots", "enableWallReflections", enableWallReflections);
        enableFloorReflections = GetIniValue("Lots", "enableFloorReflections", enableFloorReflections);
        enableCeilingReflections = GetIniValue("Lots", "enableCeilingReflections", enableCeilingReflections);
        if (!hasBetaFloors)
            enablePondReflections = GetIniValue("Ponds", "enablePondReflections", enablePondReflections);

        file.write(ini, true);
    }
}