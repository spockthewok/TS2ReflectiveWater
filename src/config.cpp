#include "config.h"

namespace
{
    mINI::INIStructure ini;
    const std::filesystem::path configNameBase = "TS2ReflectiveWater.ini";
    const std::filesystem::path configNameRPC = "mods/TS2ReflectiveWater.ini";
    bool iniGenerate = false;
    bool iniWrite = false;
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

        iniWrite = true;

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

    static std::string GetModuleName()
    {
        char buffer[MAX_PATH];

        DWORD pathLen = GetModuleFileNameA(nullptr, buffer, MAX_PATH);

        if (pathLen == 0 || pathLen == MAX_PATH)
            return "";

        std::filesystem::path exePath(buffer);
        return exePath.filename().string();
    }

    static bool IsDllLoaded(LPCSTR dllName)
    {
        return (GetModuleHandleA(dllName) != nullptr);
    }

    void Init()
    {
        std::filesystem::path configName = configNameBase;

        if (GetModuleName().find("RPC.exe") != std::string::npos)
            configName = configNameRPC;

        mINI::INIFile file(configName);

        if (!file.read(ini))
            iniGenerate = true;

        oceanReflectionOffset = GetIniValue("Ocean", "oceanReflectionOffset", oceanReflectionOffset);
        enableTreeReflections = GetIniValue("Props", "enableTreeReflections", enableTreeReflections);
        enableBridgeReflections = GetIniValue("Props", "enableBridgeReflections", enableBridgeReflections);
        enableWallReflections = GetIniValue("Lots", "enableWallReflections", enableWallReflections);
        enableFloorReflections = GetIniValue("Lots", "enableFloorReflections", enableFloorReflections);
        enableCeilingReflections = GetIniValue("Lots", "enableCeilingReflections", enableCeilingReflections);

        bool hasBetaFloors = IsDllLoaded("TS2BetaFloors.asi");
        if (hasBetaFloors)
            enablePondReflections = SetIniValue("Ponds", "enablePondReflections", false);
        else
            enablePondReflections = GetIniValue("Ponds", "enablePondReflections", enablePondReflections);

        if (iniGenerate)
            file.generate(ini, true);
        else if (iniWrite)
            file.write(ini, true);
    }
}