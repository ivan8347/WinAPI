# include <Windows.h>
#include<cstdio>
#include "resource.h"



LRESULT CALLBACK WhdProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	
	return 0;
}
LRESULT CALLBACK WhdProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_COMMAND:
	{
		break;
	}
	case WM_DESTROY:
	{
		PostMessage(0);
		break;
	}
	case WM_CLOSE:
	{
		SendMessage(hwnd, WM_DESTROY, 0, 0);
		break;
	}
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);


	}
	return FALSE;
}