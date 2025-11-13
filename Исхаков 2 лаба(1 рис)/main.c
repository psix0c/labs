#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_PAINT:                
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            //простой дом
            HPEN hBlackPen = CreatePen(PS_DASH, 2, RGB(0, 0, 0));
            SelectObject(hdc, hBlackPen);
            Rectangle(hdc, 90, 70, 200, 180);
            POINT triangle[] = {{90, 70}, {145, 30}, {200, 70}};
            Polygon(hdc, triangle, 3);
            MoveToEx(hdc, 180, 180, NULL);
            LineTo(hdc, 180, 140);
            LineTo(hdc, 160, 140);
            LineTo(hdc, 160, 180);
            Rectangle(hdc, 120, 140, 140, 160);

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
