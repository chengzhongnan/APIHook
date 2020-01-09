#pragma once
#include <windows.h>
#include <cstdio>

template <typename T>
class CHookBase
{
protected:
	CHookBase() {}
	~CHookBase() {}

public:
	virtual void StartHook(){ }
	virtual void RemoveHook() 
	{
		if (m_pOrigAddress != NULL)
		{
			ResolveHook(m_pOrigAddress, m_bRawData);
		}

		m_pOrigAddress = NULL;
	}

	static const int JMP_SIZE = 5;

	static T* GetInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new T();
		}

		return m_pInstance;
	}

protected:
	FARPROC m_pOrigAddress = NULL;
	BYTE m_bRawData[JMP_SIZE] = { 0x00, 0x00, 0x00, 0x00, 0x00 };
	
	inline static T* m_pInstance = NULL;

protected:
	static void HookFunction(FARPROC pOrigAddress, LPVOID newFunction, BYTE* pRawBytes)
	{
		if (pOrigAddress == NULL)
		{
			return;
		}

		BYTE tempJMP[JMP_SIZE] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };
		BYTE JMP[JMP_SIZE] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };

		DWORD JMPSize = ((DWORD)newFunction - (DWORD)pOrigAddress - 5);
		DWORD oldProtect = 0;
		VirtualProtect((LPVOID)pOrigAddress, JMP_SIZE, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(pRawBytes, pOrigAddress, JMP_SIZE);
		memcpy(&JMP[1], &JMPSize, 4);
		memcpy(pOrigAddress, JMP, JMP_SIZE);
		VirtualProtect((LPVOID)pOrigAddress, JMP_SIZE, oldProtect, &oldProtect);
	}

	static void ResolveHook(FARPROC pOrigAddress, BYTE* pRawBytes)
	{
		if (pOrigAddress == NULL)
		{
			return;
		}

		DWORD oldProtect = 0;
		VirtualProtect((LPVOID)pOrigAddress, JMP_SIZE, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(pOrigAddress, pRawBytes, JMP_SIZE);
		VirtualProtect((LPVOID)pOrigAddress, JMP_SIZE, oldProtect, &oldProtect);
	}
};
