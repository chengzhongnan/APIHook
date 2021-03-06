// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#include <cstdio>
#include <windows.h>
#include <ws2tcpip.h>
#include <winsock2.h>

#include "APIHook.h"

// #pragma comment(lib,"detours.lib")
#pragma comment(lib, "ws2_32.lib")

void WINAPI StartHook()
{
	Hook_Send::GetInstance()->StartHook();
	Hook_Recv::GetInstance()->StartHook();
	Hook_Bind::GetInstance()->StartHook();
	Hook_GetWindowTextA::GetInstance()->StartHook();
	Hook_SetWindowTextA::GetInstance()->StartHook();
}

void WINAPI StopHook()
{
	Hook_Send::GetInstance()->RemoveHook();
	Hook_Recv::GetInstance()->RemoveHook();
	Hook_Bind::GetInstance()->RemoveHook();
	Hook_GetWindowTextA::GetInstance()->RemoveHook();
	Hook_SetWindowTextA::GetInstance()->RemoveHook();
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);
		StartHook();
	}
	break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
	{
		StopHook();
	}
	break;
	}
	return TRUE;
}