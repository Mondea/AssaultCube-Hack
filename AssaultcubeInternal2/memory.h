#pragma once
#include <Windows.h>

void NopMem(BYTE* src, int len);
void SetMem(BYTE* src, int len, BYTE byteArr[]);
void CpyMem(BYTE* src, int len, BYTE byteArr[]);