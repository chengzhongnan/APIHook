#pragma once

#include "CHookBase.h"
#include <winsock2.h>

class Hook_Send : public CHookBase<Hook_Send>
{
public:
	Hook_Send() {}
	~Hook_Send() {}
public:
	virtual void StartHook();

private:
	static int WINAPI Send(SOCKET s, const char* buf, int len, int flags);
};

class Hook_Recv : public CHookBase<Hook_Recv>
{
public:
	Hook_Recv() {}
	~Hook_Recv() {}
public:
	virtual void StartHook();

private:
	static int WINAPI Recv(SOCKET s, char* buf, int len, int flags);
};

class Hook_Bind : public CHookBase<Hook_Bind>
{
public:
	Hook_Bind() {}
	~Hook_Bind() {}

public:
	virtual void StartHook();

private:
	static int WINAPI Bind(int sockfd, const struct sockaddr *addr, int addrlen);
};

class Hook_GetWindowTextA : public CHookBase<Hook_GetWindowTextA>
{
public:
	Hook_GetWindowTextA() {}
	~Hook_GetWindowTextA() {}

public:
	virtual void StartHook();

private:
	static int WINAPI MyGetWindowTextA(HWND  hWnd, LPSTR lpString, int nMaxCount);
};

class Hook_SetWindowTextA : public CHookBase<Hook_SetWindowTextA>
{
public:
	Hook_SetWindowTextA() {}
	~Hook_SetWindowTextA() {}

public:
	virtual void StartHook();

private:
	static int WINAPI MySetWindowTextA(HWND hWnd, LPCSTR lpString);
};