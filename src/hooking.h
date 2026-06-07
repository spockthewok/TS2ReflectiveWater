#pragma once
#include "headers.h"

namespace Hooking
{
	void Nop(BYTE *pAddress, DWORD dwLen);
	void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen);
	void WriteToMemory(DWORD addressToWrite, const char *valueToWrite, int byteNum);
}