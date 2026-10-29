#include "config.h"
#include "headers.h"
#include "include/ini.h"

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
    bool oceanReflections = true;
    float oceanReflectionOffset = 0.45f;
    // Props
    bool treeReflections = true;
    bool bridgeReflections = true;
    // Lots
    bool wallReflections = true;
    bool floorReflections = true;
    bool ceilingReflections = true;
    // Terrain
    bool poolTerrainReflections = true;
    bool lotTerrainReflections = true;
    // Skyboxes
    bool fixSkyboxReflections = true;
    // Neighbourhood
    bool betterNHoodReflections = true;
    // Ponds
    bool pondReflections = true;

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

        oceanReflections = GetIniValue("Ocean", "oceanReflections", oceanReflections);
        oceanReflectionOffset = GetIniValue("Ocean", "oceanReflectionOffset", oceanReflectionOffset);
        treeReflections = GetIniValue("Props", "treeReflections", treeReflections);
        bridgeReflections = GetIniValue("Props", "bridgeReflections", bridgeReflections);
        wallReflections = GetIniValue("Lots", "wallReflections", wallReflections);
        floorReflections = GetIniValue("Lots", "floorReflections", floorReflections);
        ceilingReflections = GetIniValue("Lots", "ceilingReflections", ceilingReflections);
        poolTerrainReflections = GetIniValue("Terrain", "poolTerrainReflections", poolTerrainReflections);
        lotTerrainReflections = GetIniValue("Terrain", "lotTerrainReflections", lotTerrainReflections);
        fixSkyboxReflections = GetIniValue("Skyboxes", "fixSkyboxReflections", fixSkyboxReflections);
        betterNHoodReflections = GetIniValue("Neighbourhood", "betterNHoodReflections", betterNHoodReflections);

        if (IsDllLoaded("TS2BetaFloors.asi"))
            pondReflections = SetIniValue("Ponds", "pondReflections", false);
        else
            pondReflections = GetIniValue("Ponds", "pondReflections", pondReflections);

        if (iniGenerate)
            file.generate(ini, true);
        else if (iniWrite)
            file.write(ini, true);
    }
}