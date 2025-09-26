#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
# include"resource.h"

CONST CHAR* VALUES[] = { "Вася","Петя","Маня","Дуня"};


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;

}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:

	{
		

		HWND hList = GetDlgItem(hwnd, IDC_LIST_BOX);
		for (int i = 0; i < sizeof(VALUES) / sizeof(VALUES[0]); i++)
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)VALUES[i]);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{

			HWND hList = GetDlgItem(hwnd, IDC_LIST_BOX);
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT); 
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
			SetWindowText(hEdit, sz_buffer);
			CHAR sz_message[SIZE];
			sprintf(sz_message, "Вы выбрали вариант №%i со значением '%s'", i + 1, sz_buffer);
			MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		 case IDC_BUTTON:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST_BOX);
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CHAR sz_input[256];
			GetWindowText(hEdit, sz_input, sizeof(sz_input));
			if (strlen(sz_input) > 0)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_input);
				SetWindowText(hEdit, ""); 
			}
			else
			{
				MessageBox(hwnd, "Пожалуйста, введите текст для добавления.", "Ошибка", MB_OK | MB_ICONERROR);
			}
		 } break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
		break;
	}
	return FALSE;


}