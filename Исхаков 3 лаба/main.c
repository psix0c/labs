#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HPEN bgreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
            SelectObject(hdc, bgreenPen);
            MoveToEx(hdc, 50, 20, 0);
            LineTo(hdc, 30, 40);
            LineTo(hdc, 70, 40);
            LineTo(hdc, 50, 20);
            MoveToEx(hdc, 30, 40, 0);
            LineTo(hdc, 30, 160);
            LineTo(hdc, 70, 160);
            LineTo(hdc, 70, 40);

            int a = 0;
            while(a <= 100) {
            MoveToEx(hdc, 50+40*a, 20, 0);
            LineTo(hdc, 30+40*a, 40);
            LineTo(hdc, 70+40*a, 40);
            LineTo(hdc, 50+40*a, 20);
            MoveToEx(hdc, 30+40*a, 40, 0);
            LineTo(hdc, 30+40*a, 160);
            LineTo(hdc, 70+40*a, 160);
            LineTo(hdc, 70+40*a, 40);
            a++;
            }

            int x = 440;
            int y = 200;
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, pen);
            int ab = 0;
            while (ab <= 20) {
                MoveToEx(hdc, x + ab * 5, y + ab * 5, 0);
                LineTo(hdc, x + ab * 2 + 50, y + 100 - ab * 5);
                ab++;
            }

            int x1 = 200;
            int y1 = 200;
            HPEN pen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, pen1);
            int a1 = 0;
            while (a1 <= 20) {
                MoveToEx(hdc, x1 + a1 * 5, y1 + 10 - a1, 0);
                LineTo(hdc, x1 + a1 * 5, y1 + 80 + a1);
                a1++;
            }

            EndPaint(hwnd, &ps);
    }
    return 0;

case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
}

return
DefWindowProc(hwnd, msg, wParam, lParam);

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);


    HWND hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        "Моё окно",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}
