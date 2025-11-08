#define _CRT_SECURE_NO_WARNINGS
# include <Windows.h>
#include<cstdio>
#include<float.h>
#include "resource.h"
CONST INT g_i_BUTTON_SIZE = 80;
CONST INT g_i_INTERVAL = 2;

CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;

CONST INT g_i_BUTTON_DOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL; //������� ������
CONST INT g_i_SCREEN_WIDTH = (g_i_BUTTON_SIZE + g_i_INTERVAL) * 5 - g_i_INTERVAL;
CONST INT g_i_SCREEN_HEIGHT = g_i_BUTTON_SIZE;

CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_INTERVAL * 4;


CONST CHAR g_OPERATION[] = "+-*/";
CONST INT g_i_OPERATION_STAT_X = g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;


#define BUTTON_SHIFT_X(shift) g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(shift)
#define BUTTON_SHIFT_Y(shift) g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(shift)

//CONST INT SIZE = 256;
CONST CHAR g_sz_CLASS_NAME[] = "Calc_SPU_411";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID SetSkin(HWND hwnd, CONST CHAR SZ_SKIN[]);
VOID SetSkinDLL(HWND hwnd, CONST CHAR SZ_SKIN[]);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// ����������� ������ ����
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_CLASS_NAME;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration filed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	//�������� ����
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,
		g_sz_CLASS_NAME,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_SCREEN_WIDTH + 2 * g_i_BUTTON_START_X + 16,
		g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4 + 42,
		//CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//������ ����� ���������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DOUBLE a = DBL_MIN;
	static DOUBLE b = DBL_MIN;
	static INT operation = 0;
	static BOOL input = FALSE;
	static BOOL input_operation = FALSE;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);

		//HICON hIconPlus = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON_PLUS));
		//HICON hIconPlus = (HICON)LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON_PLUS), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "0",

			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			10, 10,
			g_i_SCREEN_WIDTH, g_i_SCREEN_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);

		AddFontResourceEx("Fonts\\digital-7 (mono).ttf", FR_PRIVATE, 0);
		HFONT hFont = CreateFont
		(
			60,
			30,
			0, 0,
			500, 0,0,0,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_CHARACTER_PRECIS,
			ANTIALIASED_QUALITY,
			DEFAULT_PITCH,
			"Digital-7 Mono"

		);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);


		INT digit = 1;
		CHAR sz_digit[2] = "";
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = digit + '0';
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
					g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * i / 3,
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0 + digit),
					GetModuleHandle(NULL),
					NULL
				); 
				
				digit++;
			}
		}

		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(2), BUTTON_SHIFT_Y(3),
			//g_i_BUTTON_START_X + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_POINT), GetModuleHandle(NULL),
			NULL
		);
		CHAR operation[2] = "";
		for (int i = 0; i < 4; i++)
		{
			operation[0] = g_OPERATION[i];
			CreateWindowEx
			(
				NULL, "Button", operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				BUTTON_SHIFT_X(3), BUTTON_SHIFT_Y(3 - i),
				//g_i_OPERATION_STAT_X,
				//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + i),
				GetModuleHandle(NULL),
				NULL
			);
			//SendMessage(IDC_BUTTON_PLUS, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIconPlus);
		}
		HWND hButton0 = CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_BUTTON_START_X, BUTTON_SHIFT_Y(3),
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		/*HANDLE hImage0 = LoadImage
		(
			GetModuleHandle(NULL), "buttons\\square_blue\\button_0.bmp",
			IMAGE_BITMAP,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			LR_LOADFROMFILE

		);
		SendMessage(hButton0, BM_SETIMAGE, 0, (LPARAM)hImage0);*/
		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(1),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);

		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
		//SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

		
		//SetSkinDLL(hwnd, "metal_mistral");
		SetSkinDLL(hwnd, "square_blue");
	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_display[SIZE] = {};
		CHAR  sz_digit[2] = {};
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_display);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			if (input_operation)sz_display[0] = 0;
			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + 48;

			if (strcmp(sz_display, "0"))
				strcat_s(sz_display, sz_digit);
			else
				strcpy_s(sz_display, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
			input_operation = FALSE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_POINT && strchr(sz_display, '.') == NULL)
		{
			strcat_s(sz_display, ".");
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			if (strlen(sz_display) == 1)sz_display[0] = '0';
			else sz_display[strlen(sz_display) - 1] = 0;
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLR)
		{
			a = b = DBL_MIN;
			operation = 0;
			input = input_operation = FALSE;
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"0");
		}

		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			//if(a == DBL_MIN)a = atof(sz_display);
		//else b = atof(sz_display);
			if (input)
			{
				(a == DBL_MIN ? a : b) = atof(sz_display);  // ANSI/ASCII to FLOAT
				//if(input)
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			}
			input = FALSE;
			operation = LOWORD(wParam);
			input_operation = TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			if (input) b = atof(sz_display);

			switch (operation)
			{
			case IDC_BUTTON_PLUS:    a += b; break;
			case IDC_BUTTON_ASTER:	 a *= b; break;
			case IDC_BUTTON_SLASH:	 a /= b; break;
			case IDC_BUTTON_MINUS:	 a -= b; break;
			}
			input = FALSE;
			input_operation = FALSE;
			sprintf_s(sz_display, "%g", a);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
		}


		/*switch (LOWORD(wParam))
		{
		case ID_MENU_THEME_BLUE:
			SetSkin(hwnd, "square_blue");
			break;
		case ID_MENU_THEME_METAL:
			SetSkin(hwnd, "metal_mistral");
			break;
		case ID_MENU_THEME_BMP:
			SetSkin(hwnd, "bmp");
			break;
		//case ID_MENU_THEME_BLUE:
		//	SetSkin(hwnd, "square_blue.dll");
		//	break;
		//case ID_MENU_THEME_METAL:
		//	SetSkin(hwnd, "metal_mistral.dll");
		//	break;

		case ID_MENU_FONT_CONSOLAS:
			SetFont(hwnd, "Consolas");
			break;
		case ID_MENU_FONT_PULS:
			SetFont(hwnd, "Torment Pulsation Regular");
			break;
		case ID_MENU_FONT_DOOM:
			SetFont(hwnd, "Ocular Doom Regular");
			break;

			SendMessage(GetDlgItem(hwnd, IDC_EDIT), WM_SETTEXT, 0, (LPARAM)"0");
			a = b = DBL_MIN;
			operation = 0;
			input = input_operation = FALSE;
			break;
		}*/


	}
	break;
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (wParam == '8')
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
			if (wParam == VK_OEM_PLUS)
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0);
		}

		else if (wParam >= '0' && wParam <= '9')
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);

		if (wParam >= 0x60 && wParam <= 0x69)
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);

		switch (wParam)
		{
		case VK_ADD:
			//case VK_OEM_PLUS:  
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0); break;
		case VK_SUBTRACT:
		case VK_OEM_MINUS:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, TRUE, 0); break;
		case VK_MULTIPLY:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0); break;
		case VK_DIVIDE:
		case VK_OEM_2:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0); break;
		case VK_DECIMAL:
		case VK_OEM_PERIOD:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, TRUE, 0); break;
		case VK_BACK:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, TRUE, 0); break;
		case VK_ESCAPE:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, TRUE, 0); break;
		case VK_RETURN:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, TRUE, 0); break;
		}
	}
	break;
	case WM_KEYUP:
	{
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (wParam == '8')
			{
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
			}
			if (wParam == VK_OEM_PLUS)
			{
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, FALSE, 0);
				SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0);
			}
		}
		else if (wParam >= '0' && wParam <= '9')
		{
			SendMessage(GetDlgItem(hwnd, wParam - '0' + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, wParam - '0' + IDC_BUTTON_0, 0);
		}
		if (wParam >= 0x60 && wParam <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, wParam - 0x60 + IDC_BUTTON_0, 0);
		}
		switch (wParam)
		{
		case VK_ADD:
			//case VK_OEM_PLUS:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0);

			break;
		case VK_SUBTRACT:
		case VK_OEM_MINUS:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MINUS, 0);
			break;
		case VK_MULTIPLY:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
			break;
		case VK_DIVIDE:
		case VK_OEM_2:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SLASH, 0);

			break;
		case VK_DECIMAL:
		case VK_OEM_PERIOD:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_POINT, 0);
			break;
		case VK_BACK:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_BSP, 0);
			break;
		case VK_ESCAPE:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLR, 0);
			break;
		case VK_RETURN:
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, FALSE, 0);
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);
			break;
		}
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
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
VOID SetSkinDLL(HWND hwnd, CONST CHAR SZ_SKIN[])
{
	HMODULE hSkin = LoadLibrary(SZ_SKIN);
	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_EQUAL; i++)
	{
		HBITMAP hBitmap = (HBITMAP)LoadImage
		(
			hSkin,
			MAKEINTRESOURCE(i),
			IMAGE_BITMAP,
			i > IDC_BUTTON_0 ? g_i_BUTTON_SIZE : g_i_BUTTON_DOUBLE_SIZE,
			i == IDC_BUTTON_EQUAL ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
				LR_SHARED
			);
			SendMessage(GetDlgItem(hwnd,  i), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	}
}
/*VOID SetSkin(HWND hwnd, CONST CHAR SZ_SKIN[])
{
	for (int i = 0; i < 10; i++)
	{
		CHAR sz_filename[FILENAME_MAX] = {};
		sprintf(sz_filename, "buttons\\%s\\button_%i.bmp",SZ_SKIN,i);
			HBITMAP hBitmap = (HBITMAP)LoadImage
			(
				GetModuleHandle(NULL),
				sz_filename,
				IMAGE_BITMAP,
				i > 0 ? g_i_BUTTON_SIZE : g_i_BUTTON_DOUBLE_SIZE,
				g_i_BUTTON_SIZE,
				LR_LOADFROMFILE
			);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0 + i), BM_SETIMAGE, 0, (LPARAM)hBitmap);
	}
	

}*/


