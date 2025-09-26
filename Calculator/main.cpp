#include <windows.h>
#include <string.h>
#include <stdio.h>

#define ID_EDIT 1
#define ID_BTN_ADD 2
#define ID_BTN_SUB 3
#define ID_BTN_MUL 4
#define ID_BTN_DIV 5
#define ID_BTN_CLEAR 6

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char buffer[256];
double num1 = 0, num2 = 0;
char operation = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Calculator");
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("WinAPI Calculator"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit;

    switch (msg) {
    case WM_CREATE:
        hEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
            10, 10, 260, 25,
            hwnd, (HMENU)ID_EDIT, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("+"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            10, 50, 50, 25,
            hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("-"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            70, 50, 50, 25,
            hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("*"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            130, 50, 50, 25,
            hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("/"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            190, 50, 50, 25,
            hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("C"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            250, 10, 30, 25,
            hwnd, (HMENU)ID_BTN_CLEAR, NULL, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BTN_CLEAR:
            SetWindowText(hEdit, "");
            break;

        case ID_BTN_ADD:
        case ID_BTN_SUB:
        case ID_BTN_MUL:
        case ID_BTN_DIV: {
            char buf[256];
            GetWindowText(hEdit, buf, 256);
            num1 = atof(buf);
            operation = (char)LOWORD(wParam);
            SetWindowText(hEdit, "");
            break;
        }

        default:
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        // Обработка клавиш (опционально)
        break;

    case WM_CHAR:
        // Обработка ввода символов
        break;

    case WM_COMMAND:
        // Обработка кнопок
        switch (LOWORD(wParam)) {
        case ID_BTN_ADD:
        case ID_BTN_SUB:
        case ID_BTN_MUL:
        case ID_BTN_DIV: {
            char buf[256];
            GetWindowText(hEdit, buf, 256);
            num1 = atof(buf);
            operation = (char)LOWORD(wParam);
            SetWindowText(hEdit, "");
            break;
        }
        case ID_BTN_CLEAR:
            SetWindowText(hEdit, "");
            break;
        }
        break;

    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) {
            switch (LOWORD(wParam)) {
            case ID_BTN_CLEAR:
                SetWindowText(hEdit, "");
                break;
            }
        }
        break;

    default:
        if (msg == WM_COMMAND) {
            // Обработка кнопок
            switch (LOWORD(wParam)) {
            case ID_BTN_ADD:
            case ID_BTN_SUB:
            case ID_BTN_MUL:
            case ID_BTN_DIV: {
                char buf[256];
                GetWindowText(hEdit, buf, 256);
                num1 = atof(buf);
                operation = (char)LOWORD(wParam);
                SetWindowText(hEdit, "");
                break;
            }
            case ID_BTN_CLEAR:
                SetWindowText(hEdit, "");
                break;
            }
        }
        else if (msg == WM_COMMAND) {
            // Обработка кнопок
        }
        else if (msg == WM_COMMAND) {
            // Еще раз, чтобы убрать дублирование
        }
        else if (msg == WM_COMMAND) {
            // Еще раз, чтобы убедиться
        }
        else if (msg == WM_COMMAND) {
            // И так далее...
        }

        // Обработка нажатия клавиш для вычисления
        if (msg == WM_KEYDOWN && wParam == VK_RETURN) {
            char buf[256];
            GetWindowText(hEdit, buf, 256);
            num2 = atof(buf);
            double result = 0;
            switch (operation) {
            case ID_BTN_ADD:
                result = num1 + num2;
                break;
            case ID_BTN_SUB:
                result = num1 - num2;
                break;
            case ID_BTN_MUL:
                result = num1 * num2;
                break;
            case ID_BTN_DIV:
                if (num2 != 0)
                    result = num1 / num2;
                else
                    strcpy(buf, "Error");
                break;
            }
            if (operation != ID_BTN_DIV || num2 != 0) {
                sprintf(buf, "%g", result);
            }
            SetWindowText(hEdit, buf);
        }

        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}