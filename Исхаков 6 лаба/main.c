#include <windows.h>
#include <stdio.h>
#include <string.h>

#define MAX_N 100
int a[MAX_N];
int b[MAX_N];
int n = 0;

int min_idx = -1;
int max_idx = -1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void LoadData(void);
void Draw(HDC hdc, RECT area, const char* title, int data[], int highlight);

void LoadData(void) {
    FILE* f;
    if (fopen_s(&f, "f.txt", "rt") != 0 || f == NULL) {
        n = 12;
        int d[] = { 5, 80, 32, 10, 95, 22, 56, 78, 44, 60, 18, 100 };
        memcpy(a, d, sizeof(d));
    }
    else {
        fscanf_s(f, "%d", &n);
        if (n > MAX_N) n = MAX_N;
        if (n < 0) n = 0;

        for (int i = 0; i < n; i++) {
            fscanf_s(f, "%d", &a[i]);
        }
        fclose(f);
    }

    memcpy(b, a, sizeof(int) * n);

    if (n < 2) return;

    int min_v = b[0];
    int max_v = b[0];
    min_idx = 0;
    max_idx = 0;

    for (int i = 1; i < n; i++) {
        if (b[i] < min_v) {
            min_v = b[i];
            min_idx = i;
        }
        if (b[i] > max_v) {
            max_v = b[i];
            max_idx = i;
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = {0};
    HWND hwnd;
    MSG msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "MyWindowClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Class Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    LoadData();

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "MyWindowClass",
        "Array Visualization",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

void Draw(HDC hdc, RECT area, const char* title, int data[], int highlight) {
    HFONT font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    HFONT old_font = (HFONT)SelectObject(hdc, font);

    HBRUSH b_norm  = CreateSolidBrush(RGB(100, 150, 200));
    HBRUSH b_min   = CreateSolidBrush(RGB(100, 200, 100));
    HBRUSH b_max   = CreateSolidBrush(RGB(250, 100, 100));
    HBRUSH b_found = CreateSolidBrush(RGB(255, 215, 0));

    SetBkMode(hdc, TRANSPARENT);

    SetTextAlign(hdc, TA_CENTER);
    TextOutA(hdc, area.left + (area.right - area.left) / 2, area.top + 10, title, (int)strlen(title));

    if (n > 0) {
        int chart_w = area.right - area.left - 40;
        int chart_h = area.bottom - area.top - 50;
        float bar_w = (float)chart_w / n;

        int max_val = 1;
        for (int i = 0; i < n; i++) {
            if (data[i] > max_val) max_val = data[i];
        }

        int start = (min_idx < max_idx) ? min_idx : max_idx;
        int end = (min_idx > max_idx) ? min_idx : max_idx;

        for (int i = 0; i < n; i++) {
            int bar_h = (int)((float)data[i] / max_val * chart_h);
            int x1 = area.left + 20 + (int)(i * bar_w);
            int y1 = area.bottom - 20 - bar_h;
            int x2 = area.left + 20 + (int)((i + 1) * bar_w - 2);
            int y2 = area.bottom - 20;

            HBRUSH cur_b = b_norm;
            if (i == min_idx) {
                cur_b = b_min;
            } else if (i == max_idx) {
                cur_b = b_max;
            } else if (highlight && (i > start && i < end) && (data[i] % 2 == 0)) {
                cur_b = b_found;
            }

            SelectObject(hdc, cur_b);
            Rectangle(hdc, x1, y1, x2, y2);

            char buf[16];
            sprintf_s(buf, 16, "%d", data[i]);
            TextOutA(hdc, x1 + (int)(bar_w/2) - 5, y2 + 2, buf, (int)strlen(buf));
        }
    }

    SelectObject(hdc, old_font);

    DeleteObject(b_norm);
    DeleteObject(b_min);
    DeleteObject(b_max);
    DeleteObject(b_found);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rect;
        GetClientRect(hwnd, &rect);

        RECT r_top = {rect.left, rect.top, rect.right, rect.bottom / 2};
        RECT r_bot = {rect.left, rect.bottom / 2, rect.right, rect.bottom};

        Draw(hdc, r_top, "Original Array (min/max highlighted)", a, 0);
        Draw(hdc, r_bot, "Processing (even numbers found highlighted)", b, 1);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}