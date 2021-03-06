// APIHook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "APIHook.h"

void Hook_Send::StartHook()
{
	HMODULE hModule = GetModuleHandle(L"ws2_32.dll");
	m_pOrigAddress = GetProcAddress(hModule, "send");

	CHookBase::HookFunction(m_pOrigAddress, (LPVOID)(&Hook_Send::Send), m_bRawData);
}

int WINAPI Hook_Send::Send(SOCKET s, const char* buf, int len, int flags)
{
	auto ins = Hook_Send::GetInstance();
	ins->RemoveHook();
	int retValue = send(s, buf, len, flags);
	ins->StartHook();

	OutputDebugStringA("send");

	return retValue;
}

void Hook_Recv::StartHook()
{
	HMODULE hModule = GetModuleHandle(L"ws2_32.dll");
	m_pOrigAddress = GetProcAddress(hModule, "recv");

	CHookBase::HookFunction(m_pOrigAddress, (LPVOID)(&Hook_Recv::Recv), m_bRawData);
}

int WINAPI Hook_Recv::Recv(SOCKET s, char* buf, int len, int flags)
{
	auto ins = Hook_Recv::GetInstance();
	ins->RemoveHook();
	int retValue = recv(s, buf, len, flags);
	ins->StartHook();

	OutputDebugStringA("recv");

	return retValue;
}

void Hook_Bind::StartHook()
{
	HMODULE hModule = GetModuleHandle(L"ws2_32.dll");
	m_pOrigAddress = GetProcAddress(hModule, "bind");

	CHookBase::HookFunction(m_pOrigAddress, (LPVOID)(&Hook_Bind::Bind), m_bRawData);
}

int WINAPI Hook_Bind::Bind(int sockfd, const struct sockaddr *addr, int addrlen)
{
	auto ins = Hook_Bind::GetInstance();
	ins->RemoveHook();
	int retValue = bind(sockfd, addr, addrlen);
	ins->StartHook();

	return retValue;
}

void Hook_GetWindowTextA::StartHook()
{
	auto hModule = GetModuleHandle(L"user32.dll");
	m_pOrigAddress = GetProcAddress(hModule, "GetWindowTextA");

	CHookBase::HookFunction(m_pOrigAddress, (LPVOID)(&Hook_GetWindowTextA::MyGetWindowTextA), m_bRawData);
}

int WINAPI Hook_GetWindowTextA::MyGetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount)
{
	auto ins = Hook_GetWindowTextA::GetInstance();
	ins->RemoveHook();
	int retValue = GetWindowTextA(hWnd, lpString, nMaxCount);
	ins->StartHook();

	char szBuff[1024];
	sprintf_s(szBuff, "GetWindowTextA: %s", lpString);
	OutputDebugStringA(szBuff);

	return retValue;
}

void Hook_SetWindowTextA::StartHook()
{
	auto hModule = GetModuleHandle(L"user32.dll");
	m_pOrigAddress = GetProcAddress(hModule, "SetWindowTextA");

	CHookBase::HookFunction(m_pOrigAddress, (LPVOID)(&Hook_SetWindowTextA::MySetWindowTextA), m_bRawData);
}

int WINAPI Hook_SetWindowTextA::MySetWindowTextA(HWND hWnd, LPCSTR lpString)
{
	auto ins = Hook_SetWindowTextA::GetInstance();
	ins->RemoveHook();
	int retValue = SetWindowTextA(hWnd, lpString);
	ins->StartHook();

	char szBuff[1024];
	sprintf_s(szBuff, "SetWindowTextA: %s", lpString);
	OutputDebugStringA(szBuff);

	return retValue;
}
