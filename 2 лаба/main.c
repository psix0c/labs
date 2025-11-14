#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_PAINT:                // чтобы переключать картинки нужны комментарии  (большой минус этой работы))
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
            //лого
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

            // небоо
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

            // облачко 1
            Ellipse(hdc, 100, 80, 160, 120);
            Ellipse(hdc, 120, 70, 180, 110);
            Ellipse(hdc, 140, 80, 200, 120);

            // облачко 2
            Ellipse(hdc, 300, 60, 360, 100);
            Ellipse(hdc, 320, 50, 380, 90);
            Ellipse(hdc, 340, 60, 400, 100);

            // облачко 3
            Ellipse(hdc, 500, 90, 560, 130);
            Ellipse(hdc, 520, 80, 580, 120);
            Ellipse(hdc, 540, 90, 600, 130);

            // облачко 4
            Ellipse(hdc, 200, 120, 260, 160);
            Ellipse(hdc, 220, 110, 280, 150);
            Ellipse(hdc, 240, 120, 300, 160);

            DeleteObject(hCloudBrush);

            // домик
            // основание домика
            HBRUSH hHouseBrush = CreateSolidBrush(RGB(210, 180, 140));
            SelectObject(hdc, hHouseBrush);
            Rectangle(hdc, 200, 200, 400, 400);
            DeleteObject(hHouseBrush);

            // крыша домика
            HBRUSH hRoofBrush = CreateSolidBrush(RGB(139, 0, 0));
            SelectObject(hdc, hRoofBrush);
            POINT roof[] = {{180, 200}, {300, 120}, {420, 200}};
            Polygon(hdc, roof, 3);
            DeleteObject(hRoofBrush);

            // виндов
            HBRUSH hWindowBrush = CreateSolidBrush(RGB(173, 216, 230));
            SelectObject(hdc, hWindowBrush);
            Rectangle(hdc, 250, 250, 300, 300);
            DeleteObject(hWindowBrush);

            // рама window
            HPEN hBlack1Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            SelectObject(hdc, hBlack1Pen);
            MoveToEx(hdc, 275, 250, NULL);
            LineTo(hdc, 275, 300);
            MoveToEx(hdc, 250, 275, NULL);
            LineTo(hdc, 300, 275);

            // дверка
            HBRUSH hDoorBrush = CreateSolidBrush(RGB(101, 67, 33));
            SelectObject(hdc, hDoorBrush);
            Rectangle(hdc, 320, 300, 370, 400);
            DeleteObject(hDoorBrush);

            // кружок на дверке
            HBRUSH hKnobBrush = CreateSolidBrush(RGB(255, 215, 0));
            SelectObject(hdc, hKnobBrush);
            Ellipse(hdc, 355, 340, 365, 350);
            DeleteObject(hKnobBrush);

            // деревья
            // дерево
            HBRUSH hTrunkBrush = CreateSolidBrush(RGB(101, 67, 33));
            SelectObject(hdc, hTrunkBrush);
            Rectangle(hdc, 500, 250, 520, 350);
            DeleteObject(hTrunkBrush);

            HBRUSH hLeavesBrush = CreateSolidBrush(RGB(0, 100, 0));
            SelectObject(hdc, hLeavesBrush);
            Ellipse(hdc, 470, 200, 550, 280);
            DeleteObject(hLeavesBrush);

            // дерево
            SelectObject(hdc, hTrunkBrush = CreateSolidBrush(RGB(101, 67, 33)));
            Rectangle(hdc, 600, 270, 620, 370);
            DeleteObject(hTrunkBrush);

            SelectObject(hdc, hLeavesBrush = CreateSolidBrush(RGB(0, 100, 0)));
            Ellipse(hdc, 570, 220, 650, 300);
            DeleteObject(hLeavesBrush);

            //  заборчик
            HPEN hZaborPen = CreatePen(PS_SOLID, 2, RGB(150, 75, 0));
            SelectObject(hdc, hZaborPen);
            HBRUSH hZaborBrush = CreateSolidBrush(RGB(222, 184, 135));
            SelectObject(hdc, hZaborBrush);

            // заборчик (гориз)
            Rectangle(hdc, 50, 350, 750, 360);
            Rectangle(hdc, 50, 380, 750, 390);

            // заборчик (вертик)
            for (int i = 50; i < 750; i += 100)
            {
                Rectangle(hdc, i, 350, i + 10, 420);
            }

            DeleteObject(hZaborBrush);
            DeleteObject(hZaborPen);

            // цветочки
            for (int i = 0; i < 6; i++)
            {
                int x = 100 + i * 120;       // узнать позицию x для текущего цветкаа
                int y = 450;                  // фиксированная позиция y для всех цветков

                // стебельь
                HPEN hGreenPen = CreatePen(PS_SOLID, 2, RGB(0, 128, 0));
                SelectObject(hdc, hGreenPen);
                MoveToEx(hdc, x, y, NULL);
                LineTo(hdc, x, y - 40);
                DeleteObject(hGreenPen);

                // цветочек
                HBRUSH hFlowerBrush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hFlowerBrush);
                Ellipse(hdc, x - 10, y - 50, x + 10, y - 30);
                DeleteObject(hFlowerBrush);
            }

            // очень красивые птички
            SelectObject(hdc, hBlack1Pen);

            // очень красивая птичка 1
            MoveToEx(hdc, 150, 100, NULL);
            LineTo(hdc, 160, 90);
            MoveToEx(hdc, 150, 100, NULL);
            LineTo(hdc, 160, 110);

            // очень красивая птичка 2
            MoveToEx(hdc, 400, 80, NULL);
            LineTo(hdc, 410, 70);
            MoveToEx(hdc, 400, 80, NULL);
            LineTo(hdc, 410, 90);

            // очень красивая птичка 3
            MoveToEx(hdc, 550, 120, NULL);
            LineTo(hdc, 560, 110);
            MoveToEx(hdc, 550, 120, NULL);
            LineTo(hdc, 560, 130);

            // очень красивая птичка 4
            MoveToEx(hdc, 700, 150, NULL);
            LineTo(hdc, 710, 140);
            MoveToEx(hdc, 700, 150, NULL);
            LineTo(hdc, 710, 160);

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