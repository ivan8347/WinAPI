# include <Windows.h>
#include<cstdio>
#include "resource.h"

#define DEFAULT_LOGIN_HINT "Введите имя пользователя"
	static HWND hEditLogin, hEditPassword;
	//char buf[256];

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, NULL);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		 hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		//SetWindowText(hEditLogin, "Введите имя пользователя");
		 hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		SetWindowText(hEditLogin, DEFAULT_LOGIN_HINT);

		SetFocus(hEditLogin);
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	}
	return TRUE;
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		

		case IDC_EDIT_LOGIN:
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				char buf[256];
				GetWindowText(hEditLogin, buf, sizeof(buf));
				if (strcmp(buf, DEFAULT_LOGIN_HINT) == 0)
				{
					SetWindowText(hEditLogin, "");
				}
			}
			else if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				
				char buf[256];
				GetWindowText(hEditLogin, buf, sizeof(buf));
				if (strlen(buf) == 0)
				{
					SetWindowText(hEditLogin, DEFAULT_LOGIN_HINT);
				}
			}
			break;

		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//HWND window_handler = GetDlgItem(parent_window_handler, ELEMENT_ID);
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:
		{
			char buf1[256];
			char buf2[256];
			char message[512];

			GetWindowText(hEditLogin, buf1, sizeof(buf1));
			GetWindowText(hEditPassword, buf2, sizeof(buf2));
			//MessageBox(hwnd, buf1, "Вы ввели имя:", MB_OK);
			snprintf(message, sizeof(message), "Имя: %s\nПароль: %s", buf1, buf2);

			MessageBox(hwnd, message, "Вы ввели данные", MB_OK);
		}
		break;

		//case IDOK:		MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION);	break;
		case IDCANCEL:	EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;

}