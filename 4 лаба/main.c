#include <windows.h>
#include <math.h>

#define MAX_DEPTH 5

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void DrawStarRecursive(HDC hdc, int centerX, int centerY, int radius, int points, int depth) {
    if (depth > MAX_DEPTH || radius < 2) {
        return;
    }

    POINT vershina[5];
    double angle_step = 2.0 * M_PI / points;
    double start_angle = -M_PI / 2.0;

    for (int i = 0; i < points; ++i) {
        vershina[i].x = centerX + (int)(radius * cos(start_angle + i * angle_step));
        vershina[i].y = centerY + (int)(radius * sin(start_angle + i * angle_step));
    }

    if (points == 5) {
        MoveToEx(hdc, vershina[0].x, vershina[0].y, NULL);
        LineTo(hdc, vershina[2].x, vershina[2].y);
        LineTo(hdc, vershina[4].x, vershina[4].y);
        LineTo(hdc, vershina[1].x, vershina[1].y);
        LineTo(hdc, vershina[3].x, vershina[3].y);
        LineTo(hdc, vershina[0].x, vershina[0].y);
    } else if (points == 4) {
        MoveToEx(hdc, vershina[0].x, vershina[0].y, NULL);
        LineTo(hdc, vershina[2].x, vershina[2].y);
        MoveToEx(hdc, vershina[1].x, vershina[1].y, NULL);
        LineTo(hdc, vershina[3].x, vershina[3].y);
    }

    int next_points = (points == 5) ? 4 : 5;
    int next_radius = radius / 3;
    for (int i = 0; i < points; ++i) {
        DrawStarRecursive(hdc, vershina[i].x, vershina[i].y, next_radius, next_points, depth + 1);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "RecursiveStarWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Рекурсивная звезда",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            FillRect(hdc, &clientRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            SelectObject(hdc, hPen);

            int centerX = clientRect.right / 2;
            int centerY = clientRect.bottom / 2;
            int radius = min(clientRect.right, clientRect.bottom) / 3;

            DrawStarRecursive(hdc, centerX, centerY, radius, 5, 1);

            DeleteObject(hPen);
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}