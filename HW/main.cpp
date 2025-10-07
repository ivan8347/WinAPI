#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_WND_CLASS_NAME[] = " My Windown Class";
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//Регистрация класса окна
	WNDCLASSEX wClass;    //Структура, описывающая уласс окна
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

	HWND hwnd = CreateWindowEx
	(
		NULL,//exStyles
		g_sz_WND_CLASS_NAME,  // class name
		g_sz_WND_CLASS_NAME,  // Window title
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,   //Window position
		CW_USEDEFAULT, CW_USEDEFAULT,   //Window size
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
		//WS_CHILD - показывает что создаваемое окно является дочерним элементо интерфейса
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1002:
		{

				MessageBox(hwnd, "Привет", "Привет", MB_OK | MB_ICONINFORMATION);
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hStatic = GetDlgItem(hwnd, 1000);
				HWND hEdit = GetDlgItem(hwnd, 1001);
				SendMessage(hEdit, WM_GETTEXT, SIZE,(LPARAM) sz_buffer);
				SendMessage(hStatic, WM_SETTEXT, 0,(LPARAM)sz_buffer);
				SendMessage(hwnd, WM_SETTEXT, 0,(LPARAM)sz_buffer);
				SendMessage(GetDlgItem(hwnd,1002), WM_SETTEXT, 0,(LPARAM)sz_buffer);

		}
				break;
		}
		break;
	case WM_DESTROY:
		MessageBox(NULL, "Лучше двери закройте...", "Finita la comedia", MB_OK | MB_ICONERROR);
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