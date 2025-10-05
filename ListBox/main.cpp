#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
# include"resource.h"

CONST CHAR* g_ITEMS[] = { "����","����","����","����"};
//CONST CHAR* g_ITEMS[] = { "This","is","me","first","List","Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{

	//hInstance - ��������� ����������� exe* - ����� ���������
	//hPrevInst - ���������� ��������� ���������
	//lpCmdLine - ��������� ������ � ������� ���� ��������� ���������
	//nCmdShow  - ����� ����������� ����

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, (DLGPROC)DlgProc, 0);
	return 0;


}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:

	{
		//HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
		//for (int i = 0,i < sizeof(g_ITEMS) / sizeof()


		HWND hList = GetDlgItem(hwnd, IDC_LIST);
		for (int i = 0; i < sizeof(g_ITEMS) / sizeof(g_ITEMS[0]); i++)
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_ITEMS[i]);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST:
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcEdit, 0);
			}
			break;
		case IDC_BUTTON_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
			break;

		case IDC_BUTTON_DEL:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (i != LB_ERR)
			{
				SendMessage(hListBox, LB_DELETESTRING, i, 0);
			}
			/*else
			{
				MessageBox(hwnd, "����������, �������� ������� ��� ��������", "��������", MB_OK | MB_ICONINFORMATION);
			}*/
		}
		break;


		case IDOK:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
			//HWND hEdit = GetDlgItem(hwnd, IDC_EDIT); 
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};


			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, (LPARAM)hListBox);
			SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);

			//SetWindowText(hEdit, sz_buffer);
			sprintf(sz_message, "�� ������� ������� �%i �� ��������� '%s'", i + 1, sz_buffer);
			MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		/*case IDC_BUTTON:
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
			   MessageBox(hwnd, "����������, ������� ����� ��� ����������.", "������", MB_OK | MB_ICONERROR);
		   }
		} break;*/

		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}

	return FALSE;
}
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ITEM));

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hEditItem = GetDlgItem(hwnd, IDC_EDIT_ITEM);
			CHAR sz_buffer[FILENAME_MAX] = {};
			SendMessage(hEditItem, WM_GETTEXT, FILENAME_MAX, (LPARAM)sz_buffer);
			HWND hListBox = GetDlgItem(GetParent(hwnd), IDC_LIST);
			if (SendMessage(hListBox, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			else
			{
				MessageBox(hwnd, "����� ������� ��� ���� � ������, ������� ������ ��������", " �������", MB_OK | MB_ICONINFORMATION);
				break;
			}


		}

		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}

	return FALSE;
}



BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"�������� �������");
		CHAR sz_buffer[FILENAME_MAX] = {};
		HWND hListBox = GetDlgItem(GetParent(hwnd), IDC_LIST);
		HWND hEditItem = GetDlgItem(hwnd, IDC_EDIT_ITEM);

		INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
		SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hEditItem, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDOK:
		{


			HWND hEditItem = GetDlgItem(hwnd, IDC_EDIT_ITEM);
			CHAR sz_buffer[FILENAME_MAX] = {};
			//SendMessage(hwnd, WM_GETTEXT, FILENAME_MAX, (LPARAM)sz_buffer);
			HWND hListBox = GetDlgItem(GetParent(hwnd), IDC_LIST);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (i != LB_ERR) 
			{
				SendMessage(hEditItem, WM_GETTEXT, FILENAME_MAX, (LPARAM)sz_buffer);
				SendMessage(hListBox, LB_DELETESTRING, i, 0);
				SendMessage(hListBox, LB_INSERTSTRING, i, (LPARAM)sz_buffer);
				SendMessage(hListBox, LB_SETCURSEL, i, 0);
			}
			
			EndDialog(hwnd, 0);
		}
		break;


		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}

