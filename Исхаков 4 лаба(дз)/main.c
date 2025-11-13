#include <windows.h>
#include <math.h>


void DrawFractalTree(HDC hdc, int x1, int y1, double angle, int depth)
{
    if (depth == 0) return;

    int length = depth * 10;
    int x2 = x1 + (int)(cos(angle * M_PI / 180) * length);
    int y2 = y1 - (int)(sin(angle * M_PI / 180) * length);

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);

    DrawFractalTree(hdc, x2, y2, angle - 20, depth - 1);
    DrawFractalTree(hdc, x2, y2, angle + 20, depth - 1);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // небо
            HBRUSH hSkyBrush = CreateSolidBrush(RGB(135, 206, 235));
            SelectObject(hdc, hSkyBrush);
            Rectangle(hdc, 0, 0, 800, 300);
            DeleteObject(hSkyBrush);

            // земля
            HBRUSH hGroundBrush = CreateSolidBrush(RGB(34, 139, 34));
            SelectObject(hdc, hGroundBrush);
            Rectangle(hdc, 0, 300, 800, 600);
            DeleteObject(hGroundBrush);

            // солнышко
            HBRUSH hSunBrush = CreateSolidBrush(RGB(255, 255, 0));
            SelectObject(hdc, hSunBrush);
            Ellipse(hdc, 650, 50, 750, 150);
            DeleteObject(hSunBrush);

            // облака
            HBRUSH hCloudBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, hCloudBrush);

            Ellipse(hdc, 100, 80, 160, 120);
            Ellipse(hdc, 120, 70, 180, 110);
            Ellipse(hdc, 140, 80, 200, 120);

            Ellipse(hdc, 300, 60, 360, 100);
            Ellipse(hdc, 320, 50, 380, 90);
            Ellipse(hdc, 340, 60, 400, 100);

            Ellipse(hdc, 500, 90, 560, 130);
            Ellipse(hdc, 520, 80, 580, 120);
            Ellipse(hdc, 540, 90, 600, 130);

            Ellipse(hdc, 200, 120, 260, 160);
            Ellipse(hdc, 220, 110, 280, 150);
            Ellipse(hdc, 240, 120, 300, 160);

            DeleteObject(hCloudBrush);

            // домик
            HBRUSH hHouseBrush = CreateSolidBrush(RGB(210, 180, 140));
            SelectObject(hdc, hHouseBrush);
            Rectangle(hdc, 200, 200, 400, 400);
            DeleteObject(hHouseBrush);

            HBRUSH hRoofBrush = CreateSolidBrush(RGB(139, 0, 0));
            SelectObject(hdc, hRoofBrush);
            POINT roof[] = {{180, 200}, {300, 120}, {420, 200}};
            Polygon(hdc, roof, 3);
            DeleteObject(hRoofBrush);

            HBRUSH hWindowBrush = CreateSolidBrush(RGB(173, 216, 230));
            SelectObject(hdc, hWindowBrush);
            Rectangle(hdc, 250, 250, 300, 300);
            DeleteObject(hWindowBrush);

            HPEN hBlack1Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, hBlack1Pen);
            MoveToEx(hdc, 275, 250, NULL);
            LineTo(hdc, 275, 300);
            MoveToEx(hdc, 250, 275, NULL);
            LineTo(hdc, 300, 275);

            HBRUSH hDoorBrush = CreateSolidBrush(RGB(101, 67, 33));
            SelectObject(hdc, hDoorBrush);
            Rectangle(hdc, 320, 300, 370, 400);
            DeleteObject(hDoorBrush);

            HBRUSH hKnobBrush = CreateSolidBrush(RGB(255, 215, 0));
            SelectObject(hdc, hKnobBrush);
            Ellipse(hdc, 355, 340, 365, 350);
            DeleteObject(hKnobBrush);

            HBRUSH hTrunkBrush = CreateSolidBrush(RGB(101, 67, 33));
            SelectObject(hdc, hTrunkBrush);
            Rectangle(hdc, 500, 250, 520, 350);
            DeleteObject(hTrunkBrush);

            HBRUSH hLeavesBrush = CreateSolidBrush(RGB(0, 100, 0));
            SelectObject(hdc, hLeavesBrush);
            Ellipse(hdc, 470, 200, 550, 280);
            DeleteObject(hLeavesBrush);

            SelectObject(hdc, hTrunkBrush = CreateSolidBrush(RGB(101, 67, 33)));
            Rectangle(hdc, 600, 270, 620, 370);
            DeleteObject(hTrunkBrush);

            SelectObject(hdc, hLeavesBrush = CreateSolidBrush(RGB(0, 100, 0)));
            Ellipse(hdc, 570, 220, 650, 300);
            DeleteObject(hLeavesBrush);

            HPEN hZaborPen = CreatePen(PS_SOLID, 2, RGB(150, 75, 0));
            SelectObject(hdc, hZaborPen);
            HBRUSH hZaborBrush = CreateSolidBrush(RGB(222, 184, 135));
            SelectObject(hdc, hZaborBrush);

            Rectangle(hdc, 50, 350, 750, 360);
            Rectangle(hdc, 50, 380, 750, 390);

            for (int i = 50; i < 750; i += 100)
            {
                Rectangle(hdc, i, 350, i + 10, 420);
            }

            DeleteObject(hZaborBrush);
            DeleteObject(hZaborPen);

            for (int i = 0; i < 6; i++)
            {
                int x = 100 + i * 120;
                int y = 450;

                HPEN hGreenPen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0));
                SelectObject(hdc, hGreenPen);
                MoveToEx(hdc, x, y, NULL);
                LineTo(hdc, x, y - 40);
                DeleteObject(hGreenPen);

                HBRUSH hFlowerBrush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hFlowerBrush);
                Ellipse(hdc, x - 10, y - 50, x + 10, y - 30);
                DeleteObject(hFlowerBrush);
            }

            SelectObject(hdc, hBlack1Pen);

            MoveToEx(hdc, 150, 100, NULL);
            LineTo(hdc, 160, 90);
            MoveToEx(hdc, 150, 100, NULL);
            LineTo(hdc, 160, 110);

            MoveToEx(hdc, 400, 80, NULL);
            LineTo(hdc, 410, 70);
            MoveToEx(hdc, 400, 80, NULL);
            LineTo(hdc, 410, 90);

            MoveToEx(hdc, 550, 120, NULL);
            LineTo(hdc, 560, 110);
            MoveToEx(hdc, 550, 120, NULL);
            LineTo(hdc, 560, 130);

            MoveToEx(hdc, 700, 150, NULL);
            LineTo(hdc, 710, 140);
            MoveToEx(hdc, 700, 150, NULL);
            LineTo(hdc, 710, 160);

            // рекурсивное дерево (пример справа от домика)
            SelectObject(hdc, GetStockObject(BLACK_PEN));
            DrawFractalTree(hdc, 700, 550, 90, 7);

            DeleteObject(hBlack1Pen);
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

    HWND hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        "Моё окно",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
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
