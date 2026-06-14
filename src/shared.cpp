#include "shared.h"

// Base addresses of various TS2 methods and functions
const DWORD ToChar = 0x40FE7B;
const DWORD GetSimulator = 0x72A999;
const DWORD Globals = 0x799A0D;
const DWORD RegisterEnvCubeForSkyBox = 0xA96480;

// General purpose bytecode for "MOV AL,0x1"
const char enableReflections[2] = {0xB0, 0x01};