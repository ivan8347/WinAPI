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

		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "0",

			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
			10, 10,
			g_i_SCREEN_WIDTH, g_i_SCREEN_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		HICON hIcons[10];
		hIcons[0] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_1));
		hIcons[1] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_2));
		hIcons[2] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_3));
		hIcons[3] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_4));
		hIcons[4] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_5));
		hIcons[5] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_6));
		hIcons[6] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_7));
		hIcons[7] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_8));
		hIcons[8] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_9));
		hIcons[9] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_BUTTON_0));
		HICON hIcon[4];
		hIcon[0] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_PLUS));
		hIcon[1] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_MINUS));
		hIcon[2] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_ASTER));
		hIcon[3] = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_SLASH));

		INT digit = 1;
		CHAR sz_digit[2] = "";
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = digit + '0';
				HWND hBt = CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
					g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * i / 3,
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0 + digit),
					GetModuleHandle(NULL),
					NULL
				);
				SendMessage(hBt, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcons[digit - 1]);
				digit++;
			}
		}

		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
			//operation[1] = '\0';
			HWND hBtn = CreateWindowEx
			(
				NULL, "Button", operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
				BUTTON_SHIFT_X(3), BUTTON_SHIFT_Y(3 - i),
				//g_i_OPERATION_STAT_X,
				//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + i),
				GetModuleHandle(NULL),
				NULL
			);
			//SendMessage(hBtn, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hIcon[i]);
			SendMessage(hBtn, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon[i]);
		}
		for (int i = 0; i < 4; i++)
		{
			if (!hIcon[i])
			{
				MessageBox(hwnd, "���� �� ������ �� ���������!", "������", MB_OK | MB_ICONERROR);
			}
		}

		HWND hBt0 = CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_ICON,
			g_i_BUTTON_START_X, g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL), NULL
		);
		SendMessage(hBt0, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcons[9]);

		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
		break;
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

			//CHAR op_char = g_OPERATION[LOWORD(wParam) - IDC_BUTTON_PLUS];
			//CHAR op_str[2] = { op_char };
			//SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)op_str);
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

	}
	break;

	case WM_CHAR:

	{


		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		CHAR sz_display[256] = {};
		CHAR digit[2] = { (CHAR)wParam,'\0'};
		SendMessage(hEdit, WM_GETTEXT, sizeof(sz_display), (LPARAM)sz_display);

		if (wParam >= '0' && wParam <= '9')
		{

			if (input_operation || strcmp(sz_display, "0") == 0)
				strcpy(sz_display, digit);
			else
				strcat(sz_display, digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
			input_operation = FALSE;
		}
		else if (wParam == '.')
		{
			if (!strchr(sz_display, '.'))
			{
				strcat(sz_display, ".");
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
			}
		}
		else if (wParam == '+') SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_PLUS, 0);
		else if (wParam == '-') SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_MINUS, 0);
		else if (wParam == '*') SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
		else if (wParam == '/') SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_SLASH, 0);
		else if (wParam == '\r') SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0); // Enter
		else if (wParam == 27) SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_CLR, 0);     // Escape
		else if (wParam == 8) SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_BSP, 0);      // Backspace
	}break;




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