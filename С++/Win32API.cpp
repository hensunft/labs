#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include<time.h>

int i = 0;

static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("SemenPi");

HINSTANCE hInst;
int y = 0; //8 лаба

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1000, 650,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND  hwndButton1, hwndButton2, hwndButton3;
    PAINTSTRUCT ps;
    HDC hdc{};
    RECT rect;
    static int fpic = 0;
    static HPEN hpen;
    static HBRUSH hbrush1;
    static HBRUSH hbrush2;
    TCHAR student[] = _T("Работа выполнена студентом группы ИУ3-22Б Ленчином Романом");
    TCHAR propalo[] = _T("Пропало дерево((");
    TCHAR test[] = _T("TEST");
    static char txt[32] = "";
    int loword;
    static bool flagtimer;

    switch (message)
    {

    case WM_CREATE:
        srand(time(0));
        hdc = GetDC(hWnd);
        hwndButton1 = CreateWindow(L"button", L"Отобразить рисунок",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            100, 600, 150, 50,
            hWnd, (HMENU)1, hInst, NULL);

        hwndButton2 = CreateWindow(L"button", L"Очистить рисунок",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            425, 600, 150, 50,
            hWnd, (HMENU)2, hInst, NULL);

        hwndButton3 = CreateWindow(L"button", L"Фамилия студента",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            750, 600, 150, 50,
            hWnd, (HMENU)3, hInst, NULL);


        return 0;

    case WM_COMMAND:
        hbrush1 = CreateSolidBrush(RGB(89, 53, 31));
        hbrush2 = CreateSolidBrush(RGB(255, 165, 0));
        loword = LOWORD(wParam);
        switch (loword) {
        case 1: fpic = 1; break;
        case 2: fpic = 2; break;
        case 3: fpic = 3; break;
        default: break;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        SelectObject(hdc, hbrush1);
        GetClientRect(hWnd, &rect);
        switch (fpic) {
        case 1:
            SelectObject(hdc, hbrush1); //коричневый
            Rectangle(hdc, 475+y, 200, 525+y, 550);
            SelectObject(hdc, hbrush2); //оранжевый
            Ellipse(hdc, 400+y, 15, 600+y, 215); //большой круг
            Ellipse(hdc, 510+y, 330, 575+y, 395);
            break;
        case 2:
            TextOut(hdc, 400, 300, propalo, _tcslen(propalo));
            break;
        case 3:
            TextOut(hdc, 275, 300, student, _tcslen(student));
            break;
        }

    case WM_LBUTTONDOWN:
        SetTimer(hWnd, 100, 25, NULL); //8 лаба
        break;

    case WM_RBUTTONDOWN:
        KillTimer(hWnd, 100); //8 лаба
        break;
    
    case WM_TIMER:
        y = (y + 1) % 400;
        InvalidateRect(hWnd, NULL, TRUE); //8 лаба
        break;

        EndPaint(hWnd, &ps);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}