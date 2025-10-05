#define _CRT_SECURE_NO_WARNINGS
# include <Windows.h>
#include<cstdio>
#include "resource.h"

CONST CHAR* VALUES[] = { "Вася","Петя","Маня","Дуня" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DlgProc, NULL);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		for (int i = 0; i < sizeof(VALUES) / sizeof(VALUES[0]); i++)
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)VALUES[i]);
		SetWindowText(hCombo, "Выберите студента");
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			HWND hCheck1 = GetDlgItem(hwnd, IDC_CHECK1);
			HWND hCheck2 = GetDlgItem(hwnd, IDC_CHECK2);
			HWND hCheck3 = GetDlgItem(hwnd, IDC_CHECK3);
			HWND hCheck4 = GetDlgItem(hwnd, IDC_CHECK4);
			HWND hCheck5 = GetDlgItem(hwnd, IDC_CHECK5);

			CHAR sz_buffer[FILENAME_MAX] = {};
			CHAR result_message[1024] = { 0 };
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
				//sprintf(result_message, "Вы выбрали вариант №%i со значением '%s'", i + 1, sz_buffer);
				if (i != CB_ERR)
			{
				strcat(result_message, "Выбран студент: ");
				strcat(result_message, sz_buffer);
			}
			if (i != CB_ERR)
				{
					SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
				}
				if (SendMessage(hCheck1, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"Умный");
					strcat(result_message, " \n Умный  ");
				}
				if (SendMessage(hCheck2, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"Красивый");
					strcat(result_message, "\n Красивый ");
				}
				if (SendMessage(hCheck3, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"Очень красивый");
					strcat(result_message, "\n Очень красивый");
				}
				if (SendMessage(hCheck4, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"Замечательный");
					strcat(result_message, "\n Замечательный");
				}
				if (SendMessage(hCheck5, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"Просто молодец");
					strcat(result_message, "\n Просто молодец");
				}
				MessageBox(hwnd, result_message, "Выбор", MB_OK | MB_ICONINFORMATION);
				/*if (SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR)
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
				else
				{
					MessageBox(hwnd, "Такой элемент уже есть в списке, введите другое значение", " Опаньки", MB_OK | MB_ICONINFORMATION);
					break;
				}*/

		}
		break;

		case IDCANCEL:EndDialog(hwnd, 0);

			break;
		case WM_CLOSE:EndDialog(hwnd, 0);
		}
	}
	return FALSE;
}