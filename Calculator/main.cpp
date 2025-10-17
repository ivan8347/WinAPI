# include <Windows.h>
#include<cstdio>
#include < cmath >
#include "resource.h"


CONST INT g_i_BUTTON_SIZE = 60;
CONST INT g_i_INTERVAL = 2;

CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;

CONST INT g_i_BUTTON_DOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL; //двойная кнопка
CONST INT g_i_SCREEN_WIDTH = (g_i_BUTTON_SIZE + g_i_INTERVAL) * 5 - g_i_INTERVAL;
CONST INT g_i_SCREEN_HEIGHT = g_i_BUTTON_SIZE;

CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_INTERVAL * 5;

CONST INT wndWidth = g_i_SCREEN_WIDTH + 2 * g_i_BUTTON_START_X + 16;
CONST INT wndHeight = g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 5 + 42;

CONST CHAR g_OPERATION[] = "+-*/";
CONST INT g_i_OPERATION_STAT_X = g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;


#define BUTTON_SHIFT_X(shift) g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(shift)
#define BUTTON_SHIFT_Y(shift) g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(shift)


CONST CHAR g_sz_CLASS_NAME[] = "Calc_SPU_411";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	// регистрация класса окна
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_DESKTOP;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_CLASS_NAME;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration filed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	//создание окна
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (screenWidth - wndWidth) / 2;
	int y = (screenHeight - wndHeight) / 2;

	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,
		g_sz_CLASS_NAME,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		x, y,
		wndWidth,
		wndHeight,
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
	//запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;


}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{

		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit",
			"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
			10, 10,
			g_i_SCREEN_WIDTH, g_i_SCREEN_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		INT digit = 1;
		CHAR sz_digit[2] = "";
		for (int i = 9; i >= 1; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = digit + '0';
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * i / 3,
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0 + digit),
					GetModuleHandle(NULL),
					NULL
				); digit++;
			}
		}
		CreateWindowEx
		(
			NULL, "Button", " 1 / X",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(0), BUTTON_SHIFT_Y(0),

			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_1_X,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "X ^ n",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(2), BUTTON_SHIFT_Y(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_POW), GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "X ^ 2",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(1), BUTTON_SHIFT_Y(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_X_2), GetModuleHandle(NULL),
			NULL
		);
		CreateWindowExW
		(
			NULL, L"Button", L"√x",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(3), BUTTON_SHIFT_Y(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_SQRT), GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "%",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_PER), GetModuleHandle(NULL),
			NULL
		);



		CreateWindowEx
		(
			NULL, "Button", ",",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(2), BUTTON_SHIFT_Y(4),
			//g_i_BUTTON_START_X + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_POINT), GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "+ / -",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(0), BUTTON_SHIFT_Y(4),
			//g_i_BUTTON_START_X + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)(IDC_BUTTON_P_M), GetModuleHandle(NULL),
			NULL
		);
		CHAR operation[2] = "";
		for (int i = 0; i < 4; i++)
		{
			operation[0] = g_OPERATION[i];
			CreateWindowEx
			(
				NULL, "Button", operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				BUTTON_SHIFT_X(3), BUTTON_SHIFT_Y(4 - i),
				//g_i_OPERATION_STAT_X,
				//g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + i),
				GetModuleHandle(NULL),
				NULL

			);
		}
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(1), BUTTON_SHIFT_Y(4),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			//g_i_BUTTON_START_X, g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			//g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL), NULL

		);
		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(1),
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
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
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
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(3),
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);


	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_0:
		case IDC_BUTTON_1:
		case IDC_BUTTON_2:
		case IDC_BUTTON_3:
		case IDC_BUTTON_4:
		case IDC_BUTTON_5:
		case IDC_BUTTON_6:
		case IDC_BUTTON_7:
		case IDC_BUTTON_8:
		case IDC_BUTTON_9:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			CHAR digit = '0' + (LOWORD(wParam) - IDC_BUTTON_0);
			strncat_s(sz_buffer, sizeof(sz_buffer), &digit, 1);
			SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);

		}
		break;
		case IDC_BUTTON_PLUS:
		case IDC_BUTTON_MINUS:
		case IDC_BUTTON_ASTER:
		case IDC_BUTTON_SLASH:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			INT len = strlen(sz_buffer);
			if (len > 0)
			{
				CHAR last = sz_buffer[len - 1];
				if (strchr(g_OPERATION, last))
				{

					sz_buffer[len - 1] = g_OPERATION[LOWORD(wParam) - IDC_BUTTON_PLUS];
				}
				else
				{
					CHAR op = g_OPERATION[LOWORD(wParam) - IDC_BUTTON_PLUS];
					strncat_s(sz_buffer, sizeof(sz_buffer), &op, 1);
				}
				SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
			}
		}
		break;

		case IDC_BUTTON_POINT:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			INT len = strlen(sz_buffer);
			if (len > 0)
			{
				if (strchr(sz_buffer, '.')) {}
				else
				{
					strcat_s(sz_buffer, ".");
					SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
				}
			}
		}break;


		case IDC_BUTTON_EQUAL:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			DOUBLE a, b;
			CHAR op;
			DOUBLE result;
			if (sscanf_s(sz_buffer, "%lf%c%lf", &a, &op, 1, &b) == 3)
			{
				switch (op)
				{
				case '+': result = a + b; break;
				case '-': result = a - b; break;
				case '*': result = a * b; break;
				case '/':
				{
					if (b == 0)
					{
						MessageBox(hwnd, "Делить на '0' НЕЛЬЗЯ!!!!!", "Ошибка", MB_OK | MB_ICONERROR);
						return 0;
					}
					else
					{
						result = a / b; break;
					}
				}
				}
				sprintf_s(sz_buffer, sizeof(sz_buffer), "%.10g", result);
				SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
			}
			break;
		}
		break;
		case IDC_BUTTON_CLR:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
		}
		break;
		case IDC_BUTTON_BSP:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			INT len = strlen(sz_buffer);
			if (len > 0)
			{
				sz_buffer[len - 1] = '\0'; // удаляем последний символ
				SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
			}
			break;
		}

		case IDC_BUTTON_P_M:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			DOUBLE value;
			sscanf_s(sz_buffer, "%lf", &value) == 1;
			
				value = -value;
				sprintf_s(sz_buffer, sizeof(sz_buffer), "%.10g", value);
				SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
			
		}break;

		case IDC_BUTTON_1_X:

		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			DOUBLE value;
			sscanf_s(sz_buffer, "%lf", &value) == 1;

			DOUBLE result = 1 / value;
			sprintf_s(sz_buffer, sizeof(sz_buffer), "%.10g", result);
			SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
		}break;

		case IDC_BUTTON_X_2:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			DOUBLE value;
			sscanf_s(sz_buffer, "%lf", &value) == 1;
			DOUBLE result = value * value;
			sprintf_s(sz_buffer, sizeof(sz_buffer), "%.10g", result);
			SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);

		}break;

		case IDC_BUTTON_POW:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			DOUBLE value, n;
			CHAR op = '^';

			if (sscanf_s(sz_buffer, "%lf%c%lf", &value, &op, sizeof(op), &n) == 3)
			{
				DOUBLE result = pow(value, n);
				sprintf_s(sz_buffer, sizeof(sz_buffer), "%.10g", result);
				SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
			}
			else
			{
				strcat_s(sz_buffer, "^");
				SendMessage(hEdit, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
			}
			break;
		}
		case IDC_BUTTON_PER:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			DOUBLE a, b;
			CHAR op;

			DOUBLE result;
			if (sscanf_s(sz_buffer, "%lf%c%lf", &a, &op, sizeof(op), &b) == 3)
			{
				DOUBLE percent = a * (b / 100);
				if (op == '+' || op == '-')
				{
					result = (op == '+') ? (a + percent) : (a - percent);
				}
				else if (op == '*' || op == '/')
				{
					DOUBLE percent = a * (b / 100);

					result = (op == '*') ? (a * percent) : (a / percent);
				}
				sprintf_s(sz_buffer, sizeof(sz_buffer), "%.10g", result);
				SendMessage(hEdit, WM_SETTEXT, sizeof(sz_buffer), (LPARAM)sz_buffer);
				break;
			}
			if (sscanf_s(sz_buffer, "%lf", &a) == 1)
			{
				DOUBLE result = a / 100.0;
				sprintf_s(sz_buffer, sizeof(sz_buffer), "%.10g", result);
				SendMessage(hEdit, WM_SETTEXT, sizeof(sz_buffer), (LPARAM)sz_buffer);
			}
		}
		break;

		case IDC_BUTTON_SQRT:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			DOUBLE value;
			sscanf_s(sz_buffer, "%lf", &value) == 1;

			DOUBLE result = sqrt(value);
			sprintf_s(sz_buffer, sizeof(sz_buffer), "%.10g", result);
			SendMessage(hEdit, WM_SETTEXT, sizeof(sz_buffer), (LPARAM)sz_buffer);
		}
		break;













		}break;
	}
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

