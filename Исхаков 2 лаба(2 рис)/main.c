#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HPEN hRedPen = CreatePen(PS_DASH, 2, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(255, 0, 0));
            SelectObject(hdc, hBlueBrush);
            SelectObject(hdc, hRedPen);
            BeginPath(hdc);
            MoveToEx(hdc, 70, 40, NULL);
            LineTo(hdc, 55, 70 );
            LineTo(hdc, 70, 100 );
            LineTo(hdc, 85, 70 );
            LineTo(hdc, 70, 40 );
            EndPath(hdc);
            FillPath(hdc);
            BeginPath(hdc);
            MoveToEx(hdc, 70, 100, NULL);
            LineTo(hdc, 40, 100 );
            LineTo(hdc, 25, 130 );
            LineTo(hdc, 55, 130 );
            LineTo(hdc, 70, 100 );
            EndPath(hdc);
            FillPath(hdc);
            BeginPath(hdc);
            MoveToEx(hdc, 70, 100, NULL);
            LineTo(hdc, 100, 100 );
            LineTo(hdc, 115, 130 );
            LineTo(hdc, 85, 130 );
            LineTo(hdc, 70, 100 );
            EndPath(hdc);
            FillPath(hdc);


            EndPaint(hwnd, &ps);


        }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    // Создаём окно — с рамкой, заголовком и кнопкой закрытия:
    HWND hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        "Моё окно",                // заголовок
        WS_OVERLAPPEDWINDOW,       // полный набор (рамка + все кнопки)
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}