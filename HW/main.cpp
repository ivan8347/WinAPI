#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include<Windows.h>
#include <cstdio> // или <stdio.h>
#include"resource.h"

CONST CHAR g_sz_WND_CLASS_NAME[] = "My Window Class";
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//Регистрация класса окна
	WNDCLASSEX wClass;    //Структура, описывающая класс окна
	ZeroMemory(&wClass, sizeof(wClass));


	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "Saturn.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIcon = (HICON)LoadImage(hInstance, "Palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "Mario (2).ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WND_CLASS_NAME;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registrtion failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//Создание окна

	/**/int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);


	int winWidth = screenWidth * 2 / 4;
	int winHeight = screenHeight * 3 / 4;

	// Центрируем окно
	int x = (screenWidth - winWidth) / 2;
	int y = (screenHeight - winHeight) / 2;

	// Объявляем буфер для заголовка
	char windowTitle[256];
	int percentWidth = winWidth * 100 / screenWidth;
	int percentHeight = winHeight * 100 / screenHeight;

	sprintf_s(windowTitle, sizeof(windowTitle),
		"Размер: %dx%d (%d%% x %d%%) | Позиция: (%d, %d)",
		winWidth, winHeight,
		percentWidth, percentHeight,
		x, y);

	// Создаем окно с динамическим заголовком
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WND_CLASS_NAME,
		windowTitle, // сюда передается сформированный заголовок
		WS_OVERLAPPEDWINDOW,
		x, y,
		winWidth, winHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	/*HWND hwnd = CreateWindowEx
	(
		NULL,//exStyles
		g_sz_WND_CLASS_NAME,  // class name
		g_sz_WND_CLASS_NAME,  // Window title
		WS_OVERLAPPEDWINDOW,
		x,y,   //Window position
		winWidth, winHeight,   //Window size
		NULL,
		NULL,
		hInstance,
		NULL
	);*/
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
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
		/*case WM_SIZE:
		{
			int winWidth = LOWORD(lParam);
			int winHeight = HIWORD(lParam);

			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);

			int percentWidth = winWidth * 100 / screenWidth;
			int percentHeight = winHeight * 100 / screenHeight;

			char windowTitle[256];

			sprintf_s(windowTitle, sizeof(windowTitle),
				"Размер: %dx%d (%d%% x %d%%)",
				winWidth, winHeight,
				percentWidth , percentHeight);

			SetWindowText(hwnd, windowTitle);
		}
		break;*/

	case WM_CREATE:
	{

		HWND hStatic = CreateWindowEx
		(
			NULL,
			"Static",
			"Этот Static-text создан при помощи функции CreateWindowEx",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			500, 25,
			hwnd,
			(HMENU)1000,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hStatic2 = CreateWindowEx
		(
			NULL,
			"Static",
			"Достоинства",
			WS_CHILD | WS_VISIBLE,
			10, 110,
			100, 25,
			hwnd, (HMENU)1007, GetModuleHandle(NULL),
			NULL

		);
		HWND hStatic3 = CreateWindowEx
		(
			NULL,
			"Static",
			"Недостатки",
			WS_CHILD | WS_VISIBLE,
			310, 110,
			100, 25,
			hwnd, (HMENU)1008, GetModuleHandle(NULL),
			NULL

		);
		// WS - Window Style
		//ES_ - EditControl Style
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 45,
			500, 22,
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL

		);
		HWND hButton = CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE,
			430, 70,
			80, 32,
			hwnd,
			(HMENU)1002,
			GetModuleHandle(NULL),
			NULL

		);
		HWND hButton2 = CreateWindowEx
		(
			NULL,
			"Button",
			"OK",
			WS_CHILD | WS_VISIBLE,
			430, 500,
			80, 32,
			hwnd,
			(HMENU)1005,
			GetModuleHandle(NULL),
			NULL

		);
		HWND hButton3 = CreateWindowEx
		(
			NULL,
			"Button",
			"Clear",
			WS_CHILD | WS_VISIBLE,
			330, 500,
			80, 32,
			hwnd,
			(HMENU)1006,
			GetModuleHandle(NULL),
			NULL

		);
		//WS_CHILD - показывает что создаваемое окно является дочерним элементо интерфейса
		HWND hList1 = CreateWindowEx
		(
			NULL,
			"LISTBOX",
			"",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 130,
			200, 200,
			hwnd,
			(HMENU)1003,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hList2 = CreateWindowEx
		(
			NULL,
			"LISTBOX",
			"",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			310, 130,
			200, 200,
			hwnd,
			(HMENU)1004,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hCheck1 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Умный",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			10, 330,
			200, 25,
			hwnd,
			(HMENU)1009,
			GetModuleHandle(NULL),
			NULL

		);
		HWND hCheck2 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Красивый",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			10, 355,
			200, 25,
			hwnd,
			(HMENU)1010,
			GetModuleHandle(NULL),
			NULL

		);
		HWND hCheck3 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Очень красивый",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			10, 380,
			200, 25,
			hwnd,
			(HMENU)1011,
			GetModuleHandle(NULL),
			NULL

		);
		HWND hCheck4 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Замечательный",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			10, 405,
			200, 25,
			hwnd,
			(HMENU)1012,
			GetModuleHandle(NULL),
			NULL

		);
		HWND hCheck5 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Просто МОЛОДЕЦ",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			10, 430,
			200, 25,
			hwnd,
			(HMENU)1013,
			GetModuleHandle(NULL),
			NULL

		);
		HWND hCheck6 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Глупый",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			310, 330,
			200, 25,
			hwnd,
			(HMENU)1014,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hCheck7 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Лысый",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			310, 355,
			200, 25,
			hwnd,
			(HMENU)1015,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hCheck8 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Зануда",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			310, 380,
			200, 25,
			hwnd,
			(HMENU)1016,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hCheck9 = CreateWindowEx
		(
			NULL,
			"BUTTON",
			"Просто не хороший человек",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			310, 405,
			210, 25,
			hwnd,
			(HMENU)1017,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hButton4 = CreateWindowEx
		(
			NULL,
			"Button",
			"Игра",
			WS_CHILD | WS_VISIBLE,
			230, 500,
			80, 32,
			hwnd, (HMENU)1018,
			GetModuleHandle(NULL),
			NULL

		);


	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1002:
		{

			//MessageBox(hwnd, "Привет", "Привет", MB_OK | MB_ICONINFORMATION);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);
			HWND hList1 = GetDlgItem(hwnd, 1003);
			HWND hList2 = GetDlgItem(hwnd, 1004);

			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (SendMessage(hList1, LB_FINDSTRINGEXACT, -1, (LPARAM)sz_buffer) == LB_ERR)
			{
				SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
				SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			}
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);

			//SendMessage(hwnd, WM_SETTEXT, 0,(LPARAM)sz_buffer);
			//SendMessage(GetDlgItem(hwnd,1002), WM_SETTEXT, 0,(LPARAM)sz_buffer);

		}
		break;
		case 1006:
		{
			HWND hEdit = GetDlgItem(hwnd, 1001);
			HWND hList1 = GetDlgItem(hwnd, 1003);
			HWND hList2 = GetDlgItem(hwnd, 1004);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);
			SendMessage(hList2, LB_RESETCONTENT, 0, 0);
		}
		break;
		case 1005:
		{
			HWND hList1 = GetDlgItem(hwnd, 1003);
			HWND hList2 = GetDlgItem(hwnd, 1004);
			int checkBox[] = { 1009, 1010, 1011, 1012, 1013 };

			for (int i = 0; i < sizeof(checkBox) / sizeof(checkBox[0]); i++)
			{
				HWND hCheck = GetDlgItem(hwnd, checkBox[i]);
				LRESULT state = SendMessage(hCheck, BM_GETCHECK, 0, 0);

				if (state == BST_CHECKED)
				{
					char buffer[256];
					GetWindowText(hCheck, buffer, sizeof(buffer));

					// Проверка на повтор
					if (SendMessage(hList1, LB_FINDSTRINGEXACT, -1, (LPARAM)buffer) == LB_ERR)
					{
						SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)buffer);
					}
				}
			}
			int checkBox2[] = { 1014, 1015, 1016, 1017 };

			for (int i = 0; i < sizeof(checkBox2) / sizeof(checkBox2[0]); i++)
			{
				HWND hCheck = GetDlgItem(hwnd, checkBox2[i]);
				LRESULT state = SendMessage(hCheck, BM_GETCHECK, 0, 0);

				if (state == BST_CHECKED)
				{
					char buffer[256];
					GetWindowText(hCheck, buffer, sizeof(buffer));

					// Проверка на повтор
					if (SendMessage(hList2, LB_FINDSTRINGEXACT, -1, (LPARAM)buffer) == LB_ERR)
					{
						SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)buffer);
					}
				}
			}
		}
		break;
		case 1018:
		{
			STARTUPINFOA game = { sizeof(game) };
			PROCESS_INFORMATION pi;
			LPCSTR exePath = "U:\\Users\\kit\\source\\repos\\OOP\\Geometry\\bin\\Debug\\Geometry.exe";
			if (CreateProcess(exePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &game, &pi));
			{
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);

			}
		}break;
		}
		break;
	case WM_DESTROY:
		//MessageBox(NULL, "Лучше двери закройте...", "Finita la comedia", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);

		break;
	case WM_CLOSE:
		if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Че,внатуре?", MB_YESNO | MB_ICONQUESTION) == IDYES)
			DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return FALSE;
}